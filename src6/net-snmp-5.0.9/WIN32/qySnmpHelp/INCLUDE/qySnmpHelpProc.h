

#ifndef  __QYSNMPHELPPROC_H__
#define  __QYSNMPHELPPROC_H__	/*  {  */


#define		CONST_snmpCmd_get							"get"
#define     CONST_snmpCmd_set							"set"
#define		CONST_snmpCmd_walk							"walk"

#define		CONST_snmpMibPrefix_privateId				"1.3.6.1.4.1."
#define		CONST_hexStrHint							"Hex-STRING"


//  
#define		CONST_snmpMib2_sysDescr								"1.3.6.1.2.1.1.1.0"
#define		CONST_snmpMib2_sysObjectId							"1.3.6.1.2.1.1.2.0"
#define		CONST_snmpMib2_sysUpTime							"1.3.6.1.2.1.1.3.0"			
#define		CONST_snmpMib2_ifNumber								"1.3.6.1.2.1.2.1.0"
#define		CONST_snmpMib2_ifDescr								"1.3.6.1.2.1.2.2.1.2"
#define		CONST_snmpMib2_ifType								"1.3.6.1.2.1.2.2.1.3"
#define		CONST_snmpMib2_ifSpeed								"1.3.6.1.2.1.2.2.1.5"
#define		CONST_snmpMib2_ifPhysAddress						"1.3.6.1.2.1.2.2.1.6"
#define		CONST_snmpMib2_ifAdminStatus						"1.3.6.1.2.1.2.2.1.7"
#define		CONST_snmpMib2_ifOperStatus							"1.3.6.1.2.1.2.2.1.8"
#define		CONST_snmpMib2_ifInOctets							"1.3.6.1.2.1.2.2.1.10"				//  输入字节数
#define		CONST_snmpMib2_ifInUcastPkts						"1.3.6.1.2.1.2.2.1.11"				//  输入非广播包数
#define		CONST_snmpMib2_ifInNUcastPkts						"1.3.6.1.2.1.2.2.1.12"				//  输入广播包数
#define		CONST_snmpMib2_ifInDiscards							"1.3.6.1.2.1.2.2.1.13"				//  输入包丢弃数
#define		CONST_snmpMib2_ifInErrors							"1.3.6.1.2.1.2.2.1.14"				//  输入包错误数
#define		CONST_snmpMib2_ifInUnknownProtos					"1.3.6.1.2.1.2.2.1.15"				//  输入未知协议包数
#define		CONST_snmpMib2_ifOutOctets							"1.3.6.1.2.1.2.2.1.16"				//  输出字节数
#define		CONST_snmpMib2_ifOutUcastPkts						"1.3.6.1.2.1.2.2.1.17"				//  输出非广播包数
#define		CONST_snmpMib2_ifOutNUcastPkts						"1.3.6.1.2.1.2.2.1.18"				//  输出广播包数
#define		CONST_snmpMib2_ifOutDiscards						"1.3.6.1.2.1.2.2.1.19"				//  输出包丢弃数
#define		CONST_snmpMib2_ifOutErrors							"1.3.6.1.2.1.2.2.1.20"				//  输出包错误数
//
#define		CONST_snmpMib2_ipForwarding							"1.3.6.1.2.1.4.1.0"
#define		CONST_snmpMib2_ipAdEntAddr							"1.3.6.1.2.1.4.20.1.1"
#define		CONST_snmpMib2_ipNetToMediaIfIndex					"1.3.6.1.2.1.4.22.1.1"
#define		CONST_snmpMib2_ipNetToMediaPhysAddress				"1.3.6.1.2.1.4.22.1.2"				//  ip mac  的对应.RFC1213-MIB.my 
#define		CONST_snmpMib2_dot1dBaseBridgeAddress				"1.3.6.1.2.1.17.1.1.0"				//  MacAddress	read-only	mandatory	The MAC address used by this bridge when it must be referred to in a unique fashion. It is recommended that this be the numerically smallest MAC address of all ports that belong to this bridge. However it is only required to be unique. When concatenated with dot1dStpPriority a unique BridgeIdentifier is formed which is used in the Spanning Tree Protocol.
#define		CONST_snmpMib2_dot1dBaseNumPorts					"1.3.6.1.2.1.17.1.2.0"				//  INTEGER	read-only	mandatory	The number of ports controlled by this bridging entity.			IEEE 802.1D-1990: Section 6.4.1.1.3
#define		CONST_snmpMib2_dot1dTpFdbAddress					"1.3.6.1.2.1.17.4.3.1.1"			//  read-only	mandatory	A unicast MAC address for which the bridge has forwarding and/or filtering information.	
#define		CONST_snmpMib2_dot1dTpFdbPort						"1.3.6.1.2.1.17.4.3.1.2"			//  INTEGER	read-only	mandatory	Either the value '0', or the port number of the port on which a frame having a source address equal to the value of the corresponding instance of dot1dTpFdbAddress has been seen. A value of '0' indicates that the port number has not been learned but that the bridge does have some forwarding/filtering information about this address (e.g. in the dot1dStaticTable). Implementors are encouraged to assign the port value to this object whenever it is learned even for addresses for which the corresponding value of dot1dTpFdbStatus is not learned(3).
#define		CONST_snmpMib2_dot1dBasePortIfIndex					"1.3.6.1.2.1.17.1.4.1.2"			//  INTEGER	read-only	mandatory	The value of the instance of the ifIndex object, defined in MIB-II, for the interface corresponding to this port.
#define		CONST_snmpMib2_dot1dStpPort							"1.3.6.1.2.1.17.2.15.1.1"			
#define		CONST_snmpMib2_dot1qVlan							"1.3.6.1.2.1.17.7.1.4.3.1.1"		//  oid.nnn, nnn是Vlan num, oid value是vlan's description
#define		CONST_snmpMib2_dot1qPvid							"1.3.6.1.2.1.17.7.1.4.5.1.1"		//  interface number and refer to the ifindex. 3Com Cabletron Enterasys Bay Huawei 
#define		CONST_snmpMib2_host									"1.3.6.1.2.1.25.1.1.0"
#define		CONST_snmpMib2_ifName								"1.3.6.1.2.1.31.1.1.1.1"			//  rfc1573-MIB
#define		CONST_snmpMib2_cdpCacheEntry						"1.3.6.1.4.1.9.9.23.1.2.1.1"
#define		CONST_snmpMib2_cdpCacheIfIndex						"1.3.6.1.4.1.9.9.23.1.2.1.1.1"
#define		CONST_snmpMib2_cdpCacheDeviceIndex					"1.3.6.1.4.1.9.9.23.1.2.1.1.2"
#define		CONST_snmpMib2_cdpCacheAddressType					"1.3.6.1.4.1.9.9.23.1.2.1.1.3"
#define		CONST_snmpMib2_cdpCacheAddress						"1.3.6.1.4.1.9.9.23.1.2.1.1.4"
#define		CONST_snmpMib2_cdpCacheVersion						"1.3.6.1.4.1.9.9.23.1.2.1.1.5"
#define		CONST_snmpMib2_cdpCacheDeviceId						"1.3.6.1.4.1.9.9.23.1.2.1.1.6"
#define		CONST_snmpMib2_cdpCacheDevicePort					"1.3.6.1.4.1.9.9.23.1.2.1.1.7"
#define		CONST_snmpMib2_cdpCachePlatform						"1.3.6.1.4.1.9.9.23.1.2.1.1.8"
#define		CONST_snmpMib2_cdpCacheCapabilities					"1.3.6.1.4.1.9.9.23.1.2.1.1.9"
#define		CONST_snmpMib2_managementDomainLocalMode			"1.3.6.1.4.1.9.9.46.1.2.1.1.3"		//  client(1), server(2), transparent(3)	
#define		CONST_snmpMib2_vtpVlanId							"1.3.6.1.4.1.9.9.46.1.3.1.1.1"		//  vtpVlanIndex
#define		CONST_snmpMib2_vtpVlanState							"1.3.6.1.4.1.9.9.46.1.3.1.1.2"		// 
#define		CONST_snmpMib2_vtpVlanType							"1.3.6.1.4.1.9.9.46.1.3.1.1.3"		//  1 ethernet;2 fddi;3 tokenRing;4 fddiNet;5 trNet;6 deprecated; 
#define		CONST_snmpMib2_vtpVlanName							"1.3.6.1.4.1.9.9.46.1.3.1.1.4"
#define		CONST_snmpMib2_vlanTrunkPortDynamicState			"1.3.6.1.4.1.9.9.46.1.6.1.1.13"		//  on(1),        off(2),        desirable(3),        auto(4),        onNoNegotiate(5)        
//
#define		CONST_snmpMib2_vmVlanType							"1.3.6.1.4.1.9.9.68.1.2.2.1.1"		//  static(1), dynamic(2), multiVlan(3)
#define		CONST_snmpMib2_vmVlan								"1.3.6.1.4.1.9.9.68.1.2.2.1.2"		//  0~4095,read-write
#define		CONST_snmpMib2_cpsGlobalMaxSecureAddress			"1.3.6.1.4.1.9.9.315.1.1.1"
#define		CONST_snmpMib2_cpsGlobalTotalSecureAddress			"1.3.6.1.4.1.9.9.315.1.1.2"
#define		CONST_snmpMib2_cpsGlobalPortSecurityEnable			"1.3.6.1.4.1.9.9.315.1.1.3"
#define		CONST_snmpMib2_cpsIfPortSecurityEnable				"1.3.6.1.4.1.9.9.315.1.2.1.1.1"		//  true(1), false(2)
#define		CONST_snmpMib2_cpsIfPortSecurityStatus				"1.3.6.1.4.1.9.9.315.1.2.1.1.2"		//   secureup(1), securedown(2), shutdown(3)
#define		CONST_snmpMib2_cpsIfMaxSecureMacAddr				"1.3.6.1.4.1.9.9.315.1.2.1.1.3"
#define		CONST_snmpMib2_cpsIfCurrentSecureMacAddrCount		"1.3.6.1.4.1.9.9.315.1.2.1.1.4"
#define		CONST_snmpMib2_cpsIfViolationAction					"1.3.6.1.4.1.9.9.315.1.2.1.1.8"		//  shutdown(1), dropNotify(2), drop(3) 
#define		CONST_snmpMib2_cpsSecureMacAddrType					"1.3.6.1.4.1.9.9.315.1.2.2.1.2"
//  #define		CONST_snmpMib2_cpsSecureMacAddrRemainingAge			"1.3.6.1.4.1.9.9.315.1.2.2.1.3"
#define		CONST_snmpMib2_cpsSecureMacAddrRowStatus			"1.3.6.1.4.1.9.9.315.1.2.2.1.4"



typedef  int  (  *PF_qyOutput  )(  char  *  str,  void  *  p2  );


#include	"qySnmpCommProc.h"




#define		CONST_snmpCmd_null									0
#define		CONST_snmpCmd_enumPortIfDescr						1
#define		CONST_snmpCmd_enumPortIfType						2
#define		CONST_snmpCmd_enumPortIfPhysAddress					3
#define		CONST_snmpCmd_enumPortIfAdminStatus					4
#define		CONST_snmpCmd_enumPortIfOperStatus					5
#define		CONST_snmpCmd_enumPortIfSpeed						6
#define		CONST_snmpCmd_enumPortIfInOctets					7
#define		CONST_snmpCmd_enumPortIfOutOctets					8
#define		CONST_snmpCmd_enumPortIfInSpeed						9
#define		CONST_snmpCmd_enumPortIfOutSpeed					10
#define		CONST_snmpCmd_enumSysUpTime							11
//
#define		CONST_snmpCmd_enumBridgePortIfIndex					110
#define		CONST_snmpCmd_enumDot1dTpFdbPort					111
#define		CONST_snmpCmd_enumConnectedMac						112		//  不用
#define		CONST_snmpCmd_enumConnectedIp						113
#define		CONST_snmpCmd_getDot1dBaseBridgeAddress				114		//  2006/11/01
//
#define		CONST_snmpCmd_enumManagementDomainLocalMode			120
#define		CONST_snmpCmd_enumVtpVlanType						121
#define		CONST_snmpCmd_enumDot1dStpPort						122		//  不用
#define		CONST_snmpCmd_enumVmVlan							123
#define		CONST_snmpCmd_enumVmVlanType						124
#define		CONST_snmpCmd_enumDot1qPvid							125
#define		CONST_snmpCmd_enumDot1qVlan							126
#define		CONST_snmpCmd_enumIpNetToMediaPhysAddress			CONST_snmpCmd_enumConnectedIp
#define		CONST_snmpCmd_enumIpNetToMediaIfIndex				127
#define		CONST_snmpCmd_enumCdpCacheAddressType				229
#define		CONST_snmpCmd_enumCdpCacheAddress					230
#define		CONST_snmpCmd_enumCdpCacheVersion					231		//  不用
#define		CONST_snmpCmd_enumCdpCacheDevicePort				232
#define		CONST_snmpCmd_enumCdpCachePlatform					233
//
#define		CONST_snmpCmd_enumCpsGlobalMaxSecureAddress			300
#define		CONST_snmpCmd_enumCpsGlobalTotalSecureAddress		301
#define		CONST_snmpCmd_enumCpsGlobalPortSecurityEnable		302
#define		CONST_snmpCmd_enumCpsIfPortSecurityEnable			310
#define		CONST_snmpCmd_enumCpsIfPortSecurityStatus			311
#define		CONST_snmpCmd_enumCpsIfMaxSecureMacAddr				312
#define		CONST_snmpCmd_enumCpsIfCurrentSecureMacAddrCount	313
#define		CONST_snmpCmd_enumCpsIfViolationAction				314
#define		CONST_snmpCmd_enumCpsSecureMacAddrType				320
#define		CONST_snmpCmd_enumCpsSecureMacAddrRowStatus			322



//
//

#define		CONST_snmpBufSize							(  512  *  1024  )		//  争取将所有的snmp会话取回的记录都存在这里
#define		CONST_maxSnmpRcdSize						1024					//  最大的snmpRcd的大小

typedef  struct  __qySnmpBuf_t  						{
								
				 unsigned  int							uiBufSize;					//  snmpBuf中buf的大小
				 unsigned  int							uiRcdSize;					//  将存放的snmp记录大小
				 unsigned  int							uiCnt;						//  当前存放的snmp记录数
				 char							*		ptr;

}		 QY_SNMP_BUF;

//  编译出错，暂时先放这，2004/04/22
#define		CONST_maxShowWhoLen							32

typedef  struct  __qySnmpCtx_t							{

				 void							*		pParentParam;
				 void							*		pDb;
				 WCHAR									showWho[CONST_maxShowWhoLen  +  1];	//  2005/11/27,修改了类型

				 QY_SNMPOBJPOLICY_RCD					defaultPolicy;
				 QY_SNMPOBJPOLICY_RCD					curPolicy;

				 int									iCmd;
				 char									scanningTime[14  +  1];	//  扫描时间

				 char									oidBuf[256];
				 long									lVlanId;
				 int									iResult;

				 PF_qyOutput							pfOutput;
				 char									buf[4096];

				 char									snmpRcdBuf[CONST_maxSnmpRcdSize];
				 PF_qyOutput							pfProcSnmpBuf;
				 QY_SNMP_BUF							snmpBuf;

				 QY_SNMP_OBJ					*		pObj;

				 char									Dot1dBaseBridgeAddress[128  +  1];		//  2006/11/01, 这个参数本应加在QY_SNMP_OBJ里面，为了保持原数据结构的稳定性，暂时先放在这里

}		 QY_SNMP_CTX;




extern  int  failures;
extern  int  numprinted;

void  resetAllGlobals(  );
char  *  convrtHexStr2str(  unsigned  char  *  s,  char  *  buf,  unsigned  int  size  );
unsigned  long  convrtHexStr2ulIp(  char  *  hexStr  );
char  *  stdOidStr(  char  *  oidStr  );


int  qySnmpGetFunc(  int  argc,  char  *  argv[],  QY_SNMP_CTX  *  pCtx  );
int  qySnmpSetFunc(  int  argc,  char  *  argv[],  QY_SNMP_CTX  *  pCtx  );
int  qySnmpWalkFunc(  int  argc,  char  *  argv[],  QY_SNMP_CTX  *  pCtx  );

extern  unsigned  long  WINAPI  qySnmpHelpThreadProc(  void  *  );
extern  unsigned  long  WINAPI  qyNbtScanThreadProc(  void  *  );

int  qySnmpScript(  QY_SNMP_CTX  *  pCtx,   char  *  ip   );
int  qySnmpMonFlow(  QY_SNMP_CTX  *  pCtx   );
int  qySnmpMonIfFlow(  QY_SNMP_CTX  *  pCtx  );
int  qySnmpMonSwitchFlow(  QY_SNMP_CTX  *  pCtx,  char  *  ip  );
int  qySnmpWillBlockSwitchPort(  QY_SNMP_CTX  *  pCtx,  char  *  ip,  int  iPortIfIndex,  int  ifAdminStatus  );
int  doSnmpOpCmd(  QY_SNMP_CTX  *  pCtx,  char  *  ip,  int  iPortIfIndex,  char  *  processedMac,  char  *  processedIp,  int  iSnmpOpCmd,  void  *  opCmdU  );
int  qySnmpHelpFunc(  QY_SNMP_CTX  *  pCtx,  char  *  method,  char  *  ip,  char  *  oidStr,   int  iCmd,  char  *  typeBuf,  char  *  valBuf,  QY_SNMP_ARG  *  pArg  );


int  setSnmpBufInfo(  QY_SNMP_BUF  *  pSnmpBuf,  unsigned  int  rcdSize  );
void  resetSnmpBufInfo(  QY_SNMP_BUF  *  pSnmpBuf  );
BOOL  bSnmpBufNoRoom(  QY_SNMP_BUF  *  pSnmpBuf  );
int  addSnmpRcd(  void  *  rcd,  QY_SNMP_BUF  *  pSnmpBuf  );


int  qySnmpOutputProc(  char  *  str,  void  *  p2  );
int  qyProcSnmpBuf(  char  *  null,  void  *  p2  );

int  qyProcSnmpObjPorts(  void  *  p2  );
int  qyProcSnmpObjPortsSth(  void  *  p2,  BOOL  bMonFlow  );
int  qyProcSnmpObjConnnectedDevs(  void  *  p2  );


int  qyRefresh_secureMac(  void  *  pdb,  char  *  switchMac,  int  iPortIfIndex,  char  *  secureMac,  int  iAddrType,  char  *  scanningTime  );



#ifdef  __DEBUG__

 int  testSnmpFunc(  );
 int  testSnmpFunc1(  void  *  pCtx  );
 int  showQySnmpObj(  QY_SNMP_OBJ  *  pObj  );

#endif


#ifdef  __QYTYPES_H__


 	extern  QY_DMITEM		CONST_qySnmpEnterpriseTable[];
	extern	QY_DMITEM		CONST_qySnmpReservedProductTable[];
	extern  QY_DMITEM		CONST_qySnmpIbmProductTable[];
	extern	QY_DMITEM		CONST_qySnmpUnixProductTable[];
	extern	QY_DMITEM		CONST_qySnmpAccProductTable[];
	extern  QY_DMITEM		CONST_qySnmpCiscoProductTable[];
	extern	QY_DMITEM		CONST_qySnmpHpProductTable[];
	extern  QY_DMITEM		CONST_qySnmpWellfleetProductTable[];
	extern	QY_DMITEM		CONST_qySnmpNovellProductTable[];
	extern	QY_DMITEM		CONST_qySnmpDecProductTable[];
	extern  QY_DMITEM		CONST_qySnmpSunProductTable[];
	extern  QY_DMITEM		CONST_qySnmp3ComProductTable[];
	extern	QY_DMITEM		CONST_qySnmpSynOpticsProductTable[];
	extern  QY_DMITEM		CONST_qySnmpCabletronProductTable[];
	extern	QY_DMITEM		CONST_qySnmpSiliconGraphicsProductTable[];
	extern	QY_DMITEM		CONST_qySnmpLannetProductTable[];
	extern	QY_DMITEM		CONST_qySnmpSynerneticsProductTable[];
	extern	QY_DMITEM		CONST_qySnmpDLinkProductTable[];
	extern  QY_DMITEM		CONST_qySnmpSmcProductTable[];
	extern	QY_DMITEM		CONST_qySnmpIntelProductTable[];
	extern	QY_DMITEM		CONST_qySnmpUTStartcomProductTable[];
	extern  QY_DMITEM		CONST_qySnmpNorthernTelecomProductTable[];
	extern	QY_DMITEM		CONST_qySnmpZeroOneProductTable[];
	extern	QY_DMITEM		CONST_qySnmpAlcatelXylanProductTable[];
	extern	QY_DMITEM		CONST_qySnmpExtremeNetworksProductTable[];
	extern	QY_DMITEM		CONST_qySnmpFoundryProductTable[];
	extern	QY_DMITEM		CONST_qySnmpLucentProductTable[];
	extern  QY_DMITEM		CONST_qySnmpHuaweiProductTable[];
	extern	QY_DMITEM		CONST_qySnmpUCDavisProductTable[];
	extern	QY_DMITEM		CONST_qySnmpWRIProductTable[];
	extern  QY_DMITEM		CONST_qySnmpRapidCityCommunicationProductTable[];
	extern	QY_DMITEM		CONST_qySnmpAlliedProductTable[];
	extern  QY_DMITEM		CONST_qySnmpAcctonProductTable[];
	extern  QY_DMITEM		CONST_qySnmpMicrosoftProductTable[];
	extern	QY_DMITEM		CONST_qySnmpApcProductTable[];
	extern	QY_DMITEM		CONST_qySnmpNetgearProductTable[];
	extern	QY_DMITEM		CONST_qySnmpStarProductTable[];
	extern	QY_DMITEM		CONST_qySnmpAlcatelProductTable[];
	extern  QY_DMITEM		CONST_qySnmpAvayaProductTable[];
	extern	QY_DMITEM		CONST_qySnmpNetSnmpProductTable[];
	extern  QY_DMITEM		CONST_qySnmpHarbourProductTable[];
	extern  QY_DMITEM		CONST_qySnmpTopsecProductTable[];
	extern	QY_DMITEM		CONST_qySnmpBitwayProductTable[];



	extern  QY_DMITEM		CONST_qyIfTypeTable[];
	extern  QY_DMITEM		CONST_qyVlanTypeTable[];
	extern  QY_DMITEM		CONST_ciscoNetworkProtocolTable[];


#endif


#endif  /*  }  */



