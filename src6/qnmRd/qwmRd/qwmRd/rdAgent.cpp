//  Copyright (C) 2002-2003 RealVNC Ltd. All Rights Reserved.
//  Copyright (C) 1999 AT&T Laboratories Cambridge. All Rights Reserved.
//
//  This file is part of the VNC system.
//
//  The VNC system is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
//  USA.
//
// If the source code for the VNC system is not available from the place 
// whence you received this file, check http://www.uk.research.att.com/vnc or contact
// the authors on vnc@uk.research.att.com for information on obtaining it.


// CRdAgent.cpp

// CRdAgent class implementation

// Includes
#include "stdhdrs.h"
#include "qyOmniThread.h"
#include <string.h>
#include <lmcons.h>

// Custom
#include "WinVNC.h"
#include "rdAgent.h"
#include "vncSockConnect.h"
#include "vncCorbaConnect.h"
#include "rdConn.h"
#include "vncService.h"

#include	"qwmRd.h"

// CRdAgent::UpdateTracker routines

void
CRdAgent::ServerUpdateTracker::add_changed(const rfb::Region2D &rgn) {
	RdConnList::iterator i;
	
	omni_mutex_lock l(m_server->m_connsLock);

	// Post this update to all the connected clients
	for (i = m_server->m_authConns.begin(); i != m_server->m_authConns.end(); i++)
	{
    CRdConn* client = m_server->GetClient(*i);
		// Post the update
    omni_mutex_lock l(client->GetUpdateLock());
		client->GetUpdateTracker().add_changed(rgn);
	}
}

void
CRdAgent::ServerUpdateTracker::add_copied(const rfb::Region2D &dest, const rfb::Point &delta) {
	RdConnList::iterator i;
	
	omni_mutex_lock l(m_server->m_connsLock);

	// Post this update to all the connected clients
	for (i = m_server->m_authConns.begin(); i != m_server->m_authConns.end(); i++)
	{
    CRdConn* client = m_server->GetClient(*i);
		// Post the update
    omni_mutex_lock l(client->GetUpdateLock());
		client->GetUpdateTracker().add_copied(dest, delta);
	}
}

// Constructor/destructor
CRdAgent::CRdAgent()
{
	// Initialise some important stuffs...
	m_socketConn = NULL;
	m_corbaConn = NULL;
	m_httpConn = NULL;
	m_enableHttpConn = false;
	m_desktop = NULL;
	m_name = NULL;
	m_port = DISPLAY_TO_PORT(0);
	m_autoportselect = TRUE;
	m_passwd_required = TRUE;
	m_auth_hosts = 0;
	m_blacklist = 0;
	{
	    vncPasswd::FromClear clearPWD;
	    memcpy(m_password, clearPWD, MAXPWLEN);
	}
	m_querysetting = 2;
	m_querytimeout = 10;

	// Autolock settings
	m_lock_on_exit = 0;

	// Set the polling mode options
	m_poll_fullscreen = FALSE;
	m_poll_foreground = FALSE;
	m_poll_undercursor = TRUE;

	m_poll_oneventonly = FALSE;
	m_poll_consoleonly = TRUE;

	// General options
	m_loopbackOnly = FALSE;
	m_loopback_allowed = FALSE;
	m_lock_on_exit = 0;
	m_connect_pri = 0;

	// Set the input options
	//  m_enable_remote_inputs = TRUE;
	m_enable_remote_inputs = gQnmRdStruct.ucbMonDesktop  ?  FALSE  :  TRUE;		//  2006/03/06, 这里，为了满足远程监控的需求，特意将管理中心输入端在监控状态时给屏蔽掉
	m_disable_local_inputs = FALSE;

	// Clear the client mapping table
	for (int x=0; x<MAX_CLIENTS; x++)
		m_connMap[x] = NULL;
	m_nextid = 0;

	// Initialise the update tracker
	m_update_tracker.init(this);

	// Signal set when a client quits
	m_clientquitsig = new omni_condition(&m_connsLock);
}

CRdAgent::~CRdAgent()
{
	vnclog.Print(LL_STATE, VNCLOG("shutting down server object\n"));

	// If there is a socket_conn object then delete it
	if (m_socketConn != NULL)
	{
		delete m_socketConn;
		m_socketConn = NULL;
	}

	if (m_corbaConn != NULL)
	{
		delete m_corbaConn;
		m_corbaConn = NULL;
	}

	if (m_httpConn != NULL)
	{
		delete m_httpConn;
		m_httpConn = NULL;
	}

	// Remove any active clients!
	KillAuthClients();
	KillUnauthClients();

	// Wait for all the clients to die
	WaitUntilAuthEmpty();
	WaitUntilUnauthEmpty();

	// Don't free the desktop until no KillClient is likely to free it
	{	omni_mutex_lock l(m_desktopLock);

		if (m_desktop != NULL)
		{
			delete m_desktop;
			m_desktop = NULL;
		}
	}

	// Don't free the authhosts string until no more connections are possible
	if (m_auth_hosts != 0)
	{
		free(m_auth_hosts);
		m_auth_hosts = 0;
	}

	if (m_name != NULL)
	{
		free(m_name);
		m_name = NULL;
	}

	if (m_clientquitsig != NULL)
	{
		delete m_clientquitsig;
		m_clientquitsig = NULL;
	}

	// Free the host blacklist
	while (m_blacklist) {
		CRdAgent::BlacklistEntry *current = m_blacklist;
		m_blacklist=m_blacklist->_next;

		free (current->_machineName);
		delete current;
	}

	vnclog.Print(LL_STATE, VNCLOG("shutting down server object(4)\n"));
}

// Client handling functions
RdConnId
CRdAgent::AddClient(CQySock *socket, BOOL auth, BOOL shared)
{
	return AddClient(socket, auth, shared, FALSE, 0, TRUE, TRUE); 
}

RdConnId
CRdAgent::AddClient(CQySock *socket, BOOL auth, BOOL shared,
					 BOOL teleport, int capability,
					 BOOL keysenabled, BOOL ptrenabled)
{
	CRdConn *client;

	omni_mutex_lock l(m_connsLock);

	// Try to allocate a client id...
	RdConnId clientid = m_nextid;
	do
	{
		clientid = (clientid+1) % MAX_CLIENTS;
		if (clientid == m_nextid)
		{
			delete socket;
			return -1;
		}
	}
	while (m_connMap[clientid] != NULL);

	// Create a new client and add it to the relevant client list
	client = new CRdConn();
	if (client == NULL) {
		delete socket;
		return -1;
	}

	// Set the client's settings
	client->SetTeleport(teleport);
	client->SetCapability(capability);
	client->EnableKeyboard(keysenabled && m_enable_remote_inputs);
	client->EnablePointer(ptrenabled && m_enable_remote_inputs);

	// Start the client
	if (!client->Init(this, socket, auth, shared, clientid))
	{
		// The client will delete the socket for us...
		vnclog.Print(LL_CONNERR, VNCLOG("failed to initialise client object\n"));
		delete client;
		return -1;
	}

	m_connMap[clientid] = client;

	// Add the client to unauth the client list
	m_unauthConns.push_back(clientid);

	// Notify anyone interested about this event
	DoNotify(WM_SRV_CLIENT_CONNECT, 0, 0);

	vnclog.Print(LL_INTINFO, VNCLOG("AddClient() done\n"));

	return clientid;
}

BOOL
CRdAgent::Authenticated(RdConnId clientid)
{
	RdConnList::iterator i;
	BOOL authok = TRUE;

	omni_mutex_lock l1(m_desktopLock);
	omni_mutex_lock l2(m_connsLock);

	// Search the unauthenticated client list
	for (i = m_unauthConns.begin(); i != m_unauthConns.end(); i++)
	{
		// Is this the right client?
		if ((*i) == clientid)
		{
			CRdConn *client = GetClient(clientid);

			// Yes, so remove the client and add it to the auth list
			m_unauthConns.erase(i);

			// Create the screen handler if necessary
			if (m_desktop == NULL)
			{
				m_desktop = new vncDesktop();
				if (m_desktop == NULL)
				{
					client->Kill();
					authok = FALSE;
					break;
				}
				if (!m_desktop->Init(this))
				{
					client->Kill();
					authok = FALSE;

					delete m_desktop;
					m_desktop = NULL;

					break;
				}
			}

			// Tell the client about this new buffer
			client->SetBuffer(&(m_desktop->m_buffer));

			// Add the client to the auth list
			m_authConns.push_back(clientid);

			break;
		}
	}

	// Notify anyone interested of this event
	DoNotify(WM_SRV_CLIENT_AUTHENTICATED, 0, 0);

	vnclog.Print(LL_INTINFO, VNCLOG("Authenticated() done\n"));

	return authok;
}

void
CRdAgent::KillClient(RdConnId clientid)
{
	RdConnList::iterator i;
	BOOL done = FALSE;

	omni_mutex_lock l(m_connsLock);

	// Find the client in one of the two lists
	for (i = m_unauthConns.begin(); i != m_unauthConns.end(); i++)
	{
		// Is this the right client?
		if ((*i) == clientid)
		{
			vnclog.Print(LL_INTINFO, VNCLOG("killing unauth client\n"));

			// Ask the client to die
			CRdConn *client = GetClient(clientid);
			client->Kill();

			done = TRUE;
			break;
		}
	}
	if (!done)
	{
		for (i = m_authConns.begin(); i != m_authConns.end(); i++)
		{
			// Is this the right client?
			if ((*i) == clientid)
			{
				vnclog.Print(LL_INTINFO, VNCLOG("killing auth client\n"));

				// Yes, so kill it
				CRdConn *client = GetClient(clientid);
				client->Kill();

				done = TRUE;
				break;
			}
		}
	}

	vnclog.Print(LL_INTINFO, VNCLOG("KillClient() done\n"));
}

void
CRdAgent::KillAuthClients()
{
	RdConnList::iterator i;
	omni_mutex_lock l(m_connsLock);

	// Tell all the authorised clients to die!
	for (i = m_authConns.begin(); i != m_authConns.end(); i++)
	{
		vnclog.Print(LL_INTINFO, VNCLOG("killing auth client\n"));

		// Kill the client
		GetClient(*i)->Kill();
	}

	vnclog.Print(LL_INTINFO, VNCLOG("KillAuthClients() done\n"));
}

void
CRdAgent::KillUnauthClients()
{
	RdConnList::iterator i;
	omni_mutex_lock l(m_connsLock);

	// Tell all the authorised clients to die!
	for (i = m_unauthConns.begin(); i != m_unauthConns.end(); i++)
	{
		vnclog.Print(LL_INTINFO, VNCLOG("killing unauth client\n"));

		// Kill the client
		GetClient(*i)->Kill();
	}

	vnclog.Print(LL_INTINFO, VNCLOG("KillUnauthClients() done\n"));
}

UINT
CRdAgent::AuthClientCount()
{
	omni_mutex_lock l(m_connsLock);

	return m_authConns.size();
}

UINT
CRdAgent::UnauthClientCount()
{
	omni_mutex_lock l(m_connsLock);

	return m_unauthConns.size();
}

BOOL
CRdAgent::UpdateWanted()
{
	RdConnList::iterator i;
	omni_mutex_lock l(m_connsLock);

	// Iterate over the authorised clients
	for (i = m_authConns.begin(); i != m_authConns.end(); i++)
	{
		if (GetClient(*i)->UpdateWanted())
			return TRUE;
	}
	return FALSE;
}

BOOL
CRdAgent::RemoteEventReceived()
{
	RdConnList::iterator i;
	BOOL result = FALSE;
	omni_mutex_lock l(m_connsLock);

	// Iterate over the authorised clients
	for (i = m_authConns.begin(); i != m_authConns.end(); i++)
	{
		result = result || GetClient(*i)->RemoteEventReceived();
	}
	return result;
}

void
CRdAgent::WaitUntilAuthEmpty()
{
	omni_mutex_lock l(m_connsLock);

	// Wait for all the clients to exit
	while (!m_authConns.empty())
	{
		// Wait for a client to quit
		m_clientquitsig->wait();
	}
}

void
CRdAgent::WaitUntilUnauthEmpty()
{
	omni_mutex_lock l(m_connsLock);

	// Wait for all the clients to exit
	while (!m_unauthConns.empty())
	{
		// Wait for a client to quit
		m_clientquitsig->wait();
	}
}

// Client info retrieval/setup
CRdConn*
CRdAgent::GetClient(RdConnId clientid)
{
	if ((clientid >= 0) && (clientid < MAX_CLIENTS))
		return m_connMap[clientid];
	return NULL;
}

RdConnList
CRdAgent::ClientList()
{
	RdConnList clients;

	omni_mutex_lock l(m_connsLock);

	clients = m_authConns;

	return clients;
}

void
CRdAgent::SetTeleport(RdConnId clientid, BOOL teleport)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		client->SetTeleport(teleport);
}

void
CRdAgent::SetCapability(RdConnId clientid, int capability)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		client->SetCapability(capability);
}

void
CRdAgent::SetKeyboardEnabled(RdConnId clientid, BOOL enabled)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		client->EnableKeyboard(enabled);
}

void
CRdAgent::SetPointerEnabled(RdConnId clientid, BOOL enabled)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		client->EnablePointer(enabled);
}

BOOL
CRdAgent::IsTeleport(RdConnId clientid)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		return client->IsTeleport();
	return FALSE;
}

int
CRdAgent::GetCapability(RdConnId clientid)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		return client->GetCapability();
	return 0;
}

BOOL
CRdAgent::GetKeyboardEnabled(RdConnId clientid)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		return client->IsKeyboardEnabled();
	return FALSE;
}

BOOL
CRdAgent::GetPointerEnabled(RdConnId clientid)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		return client->IsPointerEnabled();
	return FALSE;
}

const char*
CRdAgent::GetClientName(RdConnId clientid)
{
	omni_mutex_lock l(m_connsLock);

	CRdConn *client = GetClient(clientid);
	if (client != NULL)
		return client->GetClientName();
	return NULL;
}

// RemoveClient should ONLY EVER be used by the client to remove itself.
void
CRdAgent::RemoveClient(RdConnId clientid)
{
	RdConnList::iterator i;
	BOOL done = FALSE;

	omni_mutex_lock l1(m_desktopLock);
	{	omni_mutex_lock l2(m_connsLock);

		// Find the client in one of the two lists
		for (i = m_unauthConns.begin(); i != m_unauthConns.end(); i++)
		{
			// Is this the right client?
			if ((*i) == clientid)
			{
				vnclog.Print(LL_INTINFO, VNCLOG("removing unauthorised client\n"));

				// Yes, so remove the client and kill it
				m_unauthConns.erase(i);
				m_connMap[clientid] = NULL;

				done = TRUE;
				break;
			}
		}
		if (!done)
		{
			for (i = m_authConns.begin(); i != m_authConns.end(); i++)
			{
				// Is this the right client?
				if ((*i) == clientid)
				{
					vnclog.Print(LL_INTINFO, VNCLOG("removing authorised client\n"));

					// Yes, so remove the client and kill it
					m_authConns.erase(i);
					m_connMap[clientid] = NULL;

					done = TRUE;
					break;
				}
			}
		}

		// Signal that a client has quit
		m_clientquitsig->signal();

	} // Unlock the clientLock

	// Are there any authorised clients connected?
	if (m_authConns.empty() && (m_desktop != NULL))
	{
		vnclog.Print(LL_STATE, VNCLOG("deleting desktop server\n"));

		// Are there locksettings set?
		if (LockSettings() == 1)
		{
		    // Yes - lock the machine on disconnect!
			vncService::LockWorkstation();
		} else if (LockSettings() > 1)
		{
		    char username[UNLEN+1];

		    vncService::CurrentUser((char *)&username, sizeof(username));
		    if (strcmp(username, "") != 0)
		    {
				// Yes - force a user logoff on disconnect!
				if (!ExitWindowsEx(EWX_LOGOFF, 0))
					vnclog.Print(LL_CONNERR, VNCLOG("client disconnect - failed to logoff user!\n"));
		    }
		}

		// Delete the screen server
		delete m_desktop;
		m_desktop = NULL;
	}

	// Notify anyone interested of the change
	DoNotify(WM_SRV_CLIENT_DISCONNECT, 0, 0);

	vnclog.Print(LL_INTINFO, VNCLOG("RemoveClient() done\n"));


	gQnmRdStruct.iErr  =  CONST_qyRet_rdEnd;	//  2005/02/11, 在远程桌面退出时，应整体退出


}

// NOTIFICATION HANDLING!

// Connect/disconnect notification
BOOL
CRdAgent::AddNotify(HWND hwnd)
{
	omni_mutex_lock l(m_connsLock);

	// Add the window handle to the list
	m_notifyList.push_front(hwnd);

	return TRUE;
}

BOOL
CRdAgent::RemNotify(HWND hwnd)
{
	omni_mutex_lock l(m_connsLock);

	// Remove the window handle from the list
	vncNotifyList::iterator i;
	for (i=m_notifyList.begin(); i!=m_notifyList.end(); i++)
	{
		if ((*i) == hwnd)
		{
			// Found the handle, so remove it
			m_notifyList.erase(i);
			return TRUE;
		}
	}

	return FALSE;
}

// Send a notification message
void
CRdAgent::DoNotify(UINT message, WPARAM wparam, LPARAM lparam)
{
	omni_mutex_lock l(m_connsLock);

	// Send the given message to all the notification windows
	vncNotifyList::iterator i;
	for (i=m_notifyList.begin(); i!=m_notifyList.end(); i++)
	{
		PostMessage((*i), message, wparam, lparam);
	}
}

void
CRdAgent::UpdateMouse()
{
	RdConnList::iterator i;
	
	omni_mutex_lock l(m_connsLock);

	// Post this mouse update to all the connected clients
	for (i = m_authConns.begin(); i != m_authConns.end(); i++)
	{
		// Post the update
		GetClient(*i)->UpdateMouse();
	}
}

void
CRdAgent::UpdateClipText(const char* text)
{
	RdConnList::iterator i;
	
	omni_mutex_lock l(m_connsLock);

	// Post this update to all the connected clients
	for (i = m_authConns.begin(); i != m_authConns.end(); i++)
	{
		// Post the update
		GetClient(*i)->UpdateClipText(text);
	}
}

void
CRdAgent::UpdatePalette()
{
	RdConnList::iterator i;
	
	omni_mutex_lock l(m_connsLock);

	// Post this update to all the connected clients
	for (i = m_authConns.begin(); i != m_authConns.end(); i++)
	{
		// Post the update
		GetClient(*i)->UpdatePalette();
	}
}

void
CRdAgent::UpdateLocalFormat()
{
	RdConnList::iterator i;
	
	omni_mutex_lock l(m_connsLock);

	// Post this update to all the connected clients
	for (i = m_authConns.begin(); i != m_authConns.end(); i++)
	{
		// Post the update
		GetClient(*i)->UpdateLocalFormat();
	}
}

void
CRdAgent::UpdateLocalClipText(LPSTR text)
{
	omni_mutex_lock l(m_desktopLock);

	if (m_desktop != NULL)
		m_desktop->SetClipText(text);
}

// Name and port number handling
void
CRdAgent::SetName(const char * name)
{
	// Set the name of the desktop
	if (m_name != NULL)
	{
		free(m_name);
		m_name = NULL;
	}
	
	m_name = strdup(name);
}

void
CRdAgent::SetPort(const UINT port)
{
    if (m_port != port)
    {
	/////////////////////////////////
	// Adjust the listen socket

	// Set the port number to use
	m_port = port;

	// If there is already a listening socket then close and re-open it...
	BOOL socketon = SockConnected();

	SockConnect(FALSE);
	if (socketon)
	    SockConnect(TRUE);

    }
}

UINT
CRdAgent::GetPort()
{
	return m_port;
}

void
CRdAgent::SetPassword(const char *passwd)
{
	memcpy(m_password, passwd, MAXPWLEN);
}

void
CRdAgent::GetPassword(char *passwd)
{
	memcpy(passwd, m_password, MAXPWLEN);
}

// Remote input handling
void
CRdAgent::EnableRemoteInputs(BOOL enable)
{
	//  m_enable_remote_inputs = enable;
	m_enable_remote_inputs = gQnmRdStruct.ucbMonDesktop  ?  FALSE  :  enable;	//  2006/03/06, 为了满足远程监控的需求，特意将远程输入在远程监控时给屏蔽掉	
	
}

BOOL CRdAgent::RemoteInputsEnabled()
{
	return m_enable_remote_inputs;
}

// Local input handling
void
CRdAgent::DisableLocalInputs(BOOL disable)
{
	m_disable_local_inputs = disable;
}

BOOL CRdAgent::LocalInputsDisabled()
{
	return m_disable_local_inputs;
}

// Socket connection handling
BOOL
CRdAgent::SockConnect(BOOL On)
{
	// Are we being asked to switch socket connects on or off?
	if (On)
	{
		// Is there a listening socket?
		if (m_socketConn == NULL)
		{
			m_socketConn = new vncSockConnect();
			if (m_socketConn == NULL)
				return FALSE;

			// Are we to use automatic port selection?
			if (m_autoportselect)
			{
				BOOL ok = FALSE;

				// Yes, so cycle through the ports, looking for a free one!
				for (int i=0; i < 99; i++)
				{
					m_port = DISPLAY_TO_PORT(i);

					vnclog.Print(LL_CLIENTS, VNCLOG("trying port number %d\n"), m_port);

					// Attempt to connect to the port
					CQySock tempsock;
					if (tempsock.Create())
					{
						if (!tempsock.Connect("localhost", m_port))
						{
							// Couldn't connect, so this port is probably usable!
							if (m_socketConn->Init(this, m_port))
							{
								ok = TRUE;
								break;
							}
						}
					}
				}

				if (!ok)
				{
					delete m_socketConn;
					m_socketConn = NULL;
					return FALSE;
				}
			} else
			{
				// No autoportselect
				if (!m_socketConn->Init(this, m_port))
				{
					delete m_socketConn;
					m_socketConn = NULL;
					return FALSE;
				}
			}

			// Now let's start the HTTP connection stuff
			EnableHTTPConnect(m_enableHttpConn);
		}
	}
	else
	{
		// *** JNW - Trying to fix up a lock-up when the listening socket closes
		KillAuthClients();
		KillUnauthClients();
		WaitUntilAuthEmpty();
		WaitUntilUnauthEmpty();

		// Is there a listening socket?
		if (m_socketConn != NULL)
		{
			// Close the socket
			delete m_socketConn;
			m_socketConn = NULL;
		}

		// Is there an HTTP socket active?
		EnableHTTPConnect(m_enableHttpConn);
	}

	return TRUE;
}

BOOL
CRdAgent::SockConnected()
{
	return m_socketConn != NULL;
}

BOOL
CRdAgent::EnableHTTPConnect(BOOL enable) {
	m_enableHttpConn = enable;
	if (enable && m_socketConn) {
		if (m_httpConn == NULL)
		{
			m_httpConn = new vncHTTPConnect;
			if (m_httpConn != NULL)
			{
				// Start up the HTTP server
				if (!m_httpConn->Init(this,
				    PORT_TO_DISPLAY(m_port) + HTTP_PORT_OFFSET))
				{
					delete m_httpConn;
					m_httpConn = NULL;
					return FALSE;
				}
			}
		}
	} else {
		if (m_httpConn != NULL)
		{
			// Close the socket
			delete m_httpConn;
			m_httpConn = NULL;
		}
	}

	return TRUE;
}

BOOL
CRdAgent::SetLoopbackOnly(BOOL loopbackOnly)
{
	if (loopbackOnly != m_loopbackOnly)
	{
		m_loopbackOnly = loopbackOnly;
		BOOL socketConn = SockConnected();
		SockConnect(FALSE);
		SockConnect(socketConn);
	}
	return TRUE;
}

BOOL
CRdAgent::LoopbackOnly()
{
	return m_loopbackOnly;
}

// CORBA connection handling
BOOL
CRdAgent::CORBAConnect(BOOL On)
{
	// Are we being asked to switch CORBA connects on or off?
	if (On)
	{
		// Is there a CORBA object?
		if (m_corbaConn == NULL)
		{
			m_corbaConn = new vncCorbaConnect();
		}
		if (m_corbaConn == NULL)
			return FALSE;
		if (!m_corbaConn->Init(this))
		{
			delete m_corbaConn;
			m_corbaConn = NULL;
			return FALSE;
		}
	}
	else
	{
		// Is there a listening socket?
		if (m_corbaConn != NULL)
		{
			// Close the socket
			delete m_corbaConn;
			m_corbaConn = NULL;
		}
	}

	return TRUE;
}

BOOL
CRdAgent::CORBAConnected()
{
	return m_corbaConn != NULL;
}

void
CRdAgent::GetScreenInfo(int &width, int &height, int &depth)
{
	rfbServerInitMsg scrinfo;

	omni_mutex_lock l(m_desktopLock);

	vnclog.Print(LL_INTINFO, VNCLOG("GetScreenInfo called\n"));

	// Is a desktop object currently active?
	if (m_desktop == NULL)
	{
		vncDesktop desktop;

		// No, so create a dummy desktop and interrogate it
		if (!desktop.Init(this))
		{
			scrinfo.framebufferWidth = 0;
			scrinfo.framebufferHeight = 0;
			scrinfo.format.bitsPerPixel = 0;
		}
		else
		{
			desktop.FillDisplayInfo(&scrinfo);
		}
	}
	else
	{
		m_desktop->FillDisplayInfo(&scrinfo);
	}

	// Get the info from the scrinfo structure
	width = scrinfo.framebufferWidth;
	height = scrinfo.framebufferHeight;
	depth = scrinfo.format.bitsPerPixel;
}

void
CRdAgent::SetAuthHosts(const char*hostlist) {
	omni_mutex_lock l(m_connsLock);

	if (hostlist == 0) {
		vnclog.Print(LL_INTINFO, VNCLOG("authhosts cleared\n"));
		m_auth_hosts = 0;
		return;
	}

	vnclog.Print(LL_INTINFO, VNCLOG("authhosts set to \"%s\"\n"), hostlist);
	if (m_auth_hosts != 0)
		free(m_auth_hosts);

	m_auth_hosts = strdup(hostlist);
}

char*
CRdAgent::AuthHosts() {
	omni_mutex_lock l(m_connsLock);

	if (m_auth_hosts == 0)
		return strdup("");
	else
		return strdup(m_auth_hosts);
}

inline BOOL
MatchStringToTemplate(const char *addr, UINT addrlen,
				      const char *filtstr, UINT filtlen) {
	if (filtlen == 0)
		return 1;
	if (addrlen < filtlen)
		return 0;
	for (int x = 0; x < filtlen; x++) {
		if (addr[x] != filtstr[x])
			return 0;
	}
	if ((addrlen > filtlen) && (addr[filtlen] != '.'))
		return 0;
	return 1;
}

CRdAgent::AcceptQueryReject
CRdAgent::VerifyHost(const char *hostname) {
	omni_mutex_lock l(m_connsLock);

	// -=- Is the specified host blacklisted?
	CRdAgent::BlacklistEntry	*current = m_blacklist;
	CRdAgent::BlacklistEntry	*previous = 0;
	SYSTEMTIME					systime;
	FILETIME					ftime;
	LARGE_INTEGER				now;

	// Get the current time as a 64-bit value
	GetSystemTime(&systime);
	SystemTimeToFileTime(&systime, &ftime);
	now.LowPart=ftime.dwLowDateTime;now.HighPart=ftime.dwHighDateTime;
	now.QuadPart /= 10000000; // Convert it into seconds

	while (current) {

		// Has the blacklist entry timed out?
		if ((now.QuadPart - current->_lastRefTime.QuadPart) > 0) {

			// Yes.  Is it a "blocked" entry?
			if (current->_blocked) {
				// Yes, so unblock it & re-set the reference time
				current->_blocked = FALSE;
				current->_lastRefTime.QuadPart = now.QuadPart + 10;
			} else {
				// No, so remove it
				if (previous)
					previous->_next = current->_next;
				else
					m_blacklist = current->_next;
				CRdAgent::BlacklistEntry *next = current->_next;
				free(current->_machineName);
				delete current;
				current = next;
				continue;
			}

		}

		// Is this the entry we're interested in?
		if ((strcmp(current->_machineName, hostname) == 0) &&
			(current->_blocked)) {
			// Machine is blocked, so just reject it
			return CRdAgent::aqrReject;
		}

		previous = current;
		current = current->_next;
	}

	// Has a hostname been specified?
	if (hostname == 0) {
		vnclog.Print(LL_INTWARN, VNCLOG("verify failed - null hostname\n"));
		return CRdAgent::aqrReject;
	}

	// Set the state machine into the correct mode & process the filter
	enum vh_Mode {vh_ExpectDelimiter, vh_ExpectIncludeExclude, vh_ExpectPattern};
	vh_Mode machineMode = vh_ExpectIncludeExclude;
	
	CRdAgent::AcceptQueryReject verifiedHost = CRdAgent::aqrAccept;

	CRdAgent::AcceptQueryReject patternType = CRdAgent::aqrReject;
	UINT authHostsPos = 0;
	UINT patternStart = 0;
	UINT hostNameLen = strlen(hostname);

	// Run through the auth hosts string until we hit the end
	if (m_auth_hosts) {
		while (1) {

			// Which mode are we in?
			switch (machineMode) {

				// ExpectIncludeExclude - we should see a + or -.
			case vh_ExpectIncludeExclude:
				if (m_auth_hosts[authHostsPos] == '+') {
					patternType = CRdAgent::aqrAccept;
					patternStart = authHostsPos+1;
					machineMode = vh_ExpectPattern;
				} else if (m_auth_hosts[authHostsPos] == '-') {	
					patternType = CRdAgent::aqrReject;
					patternStart = authHostsPos+1;
					machineMode = vh_ExpectPattern;
				} else if (m_auth_hosts[authHostsPos] == '?') {	
					patternType = CRdAgent::aqrQuery;
					patternStart = authHostsPos+1;
					machineMode = vh_ExpectPattern;
				} else if (m_auth_hosts[authHostsPos] != '\0') {
					vnclog.Print(LL_INTWARN, VNCLOG("verify host - malformed AuthHosts string\n"));
					machineMode = vh_ExpectDelimiter;
				}
				break;

				// ExpectPattern - we expect to see a valid pattern
			case vh_ExpectPattern:
				// ExpectDelimiter - we're scanning for the next ':', skipping a pattern
			case vh_ExpectDelimiter:
				if ((m_auth_hosts[authHostsPos] == ':') ||
					(m_auth_hosts[authHostsPos] == '\0')) {
					if (machineMode == vh_ExpectPattern) {
						if (patternStart == 0) {
							vnclog.Print(LL_INTWARN, VNCLOG("verify host - pattern processing failed!\n"));
						} else {
							// Process the match
							if (MatchStringToTemplate(hostname, hostNameLen,
								&(m_auth_hosts[patternStart]), authHostsPos-patternStart)) {
								// The hostname matched - apply the include/exclude rule
								verifiedHost = patternType;
							}
						}
					}

					// We now expect another + or -
					machineMode = vh_ExpectIncludeExclude;
				}
				break;
			}

			// Have we hit the end of the pattern string?
			if (m_auth_hosts[authHostsPos] == '\0')
				break;
			authHostsPos++;
		}
	}

	// Based on the server's QuerySetting, adjust the verification result
	switch (verifiedHost) {
	case CRdAgent::aqrAccept:
		if (QuerySetting() >= 3)
			verifiedHost = CRdAgent::aqrQuery;
		break;
	case CRdAgent::aqrQuery:
		if (QuerySetting() <= 1)
			verifiedHost = CRdAgent::aqrAccept;
		else if (QuerySetting() == 4)
			verifiedHost = CRdAgent::aqrReject;
		break;
	case CRdAgent::aqrReject:
		if (QuerySetting() == 0)
			verifiedHost = CRdAgent::aqrQuery;
		break;
	};

	return verifiedHost;
}

void
CRdAgent::AddAuthHostsBlacklist(const char *machine) {
	omni_mutex_lock l(m_connsLock);

	// -=- Is the specified host blacklisted?
	CRdAgent::BlacklistEntry	*current = m_blacklist;

	// Get the current time as a 64-bit value
	SYSTEMTIME					systime;
	FILETIME					ftime;
	LARGE_INTEGER				now;
	GetSystemTime(&systime);
	SystemTimeToFileTime(&systime, &ftime);
	now.LowPart=ftime.dwLowDateTime;now.HighPart=ftime.dwHighDateTime;
	now.QuadPart /= 10000000; // Convert it into seconds

	while (current) {

		// Is this the entry we're interested in?
		if (strcmp(current->_machineName, machine) == 0) {

			// If the host is already blocked then ignore
			if (current->_blocked)
				return;

			// Set the RefTime & failureCount
			current->_lastRefTime.QuadPart = now.QuadPart + 10;
			current->_failureCount++;

			if (current->_failureCount > 5)
				current->_blocked = TRUE;
			return;
		}

		current = current->_next;
	}

	// Didn't find the entry
	current = new CRdAgent::BlacklistEntry;
	current->_blocked = FALSE;
	current->_failureCount = 0;
	current->_lastRefTime.QuadPart = now.QuadPart + 10;
	current->_machineName = strdup(machine);
	current->_next = m_blacklist;
	m_blacklist = current;
}

void
CRdAgent::RemAuthHostsBlacklist(const char *machine) {
	omni_mutex_lock l(m_connsLock);

	// -=- Is the specified host blacklisted?
	CRdAgent::BlacklistEntry	*current = m_blacklist;
	CRdAgent::BlacklistEntry	*previous = 0;

	while (current) {

		// Is this the entry we're interested in?
		if (strcmp(current->_machineName, machine) == 0) {
			if (previous)
				previous->_next = current->_next;
			else
				m_blacklist = current->_next;
			CRdAgent::BlacklistEntry *next = current->_next;
			free (current->_machineName);
			delete current;
			current = next;
			continue;
		}

		previous = current;
		current = current->_next;
	}
}
