

#include	<stdio.h>
#include	<stdlib.h>
#include	<winsock2.h>
#include	<ws2tcpip.h>
#include	<sys/timeb.h>
#include	"qyCommon.h"
#include	"in_systm.h"
#include	"ip.h"
#include	"tcp.h"
#include	"udp.h"
#include	"qyBuildPkt.h"
#include	"aeNbtScan.h"



my_uint32_t get32(void* data) {
	union {
		char bytes[4];
		my_uint32_t all;
	} x;

	memcpy(x.bytes, data, 4);
	return(ntohl(x.all));
};

my_uint16_t get16(void* data) {
        union {
                char bytes[2];
                my_uint16_t all;
        } x;

        memcpy(x.bytes, data, 2);
        return(ntohs(x.all));
};

 extern  "C"  void  freeNbHostInfo(  	struct  nb_host_info	*	hostinfo  )
{
	 if  (  !hostinfo  )  return;
	 if  (  hostinfo->header  )  free(  hostinfo->header  );
	 if  (  hostinfo->footer  )  free(  hostinfo->footer  );
	 if  (  hostinfo->names  )  free(  hostinfo->names  );
	 free(  hostinfo  );  
	 return;
}

 extern  "C"  struct nb_host_info* parse_response(char* buff, unsigned  int buffsize) 
{
	int								iErr				=	-1;		
	struct  nb_host_info		*	hostinfo			=	NULL;
	nbname_response_footer_t	*	response_footer		=	NULL;
	nbname_response_header_t	*	response_header		=	NULL;
	unsigned  int					name_table_size;
	unsigned  int					offset				=	0;

	if  (  (  hostinfo  =  (  struct  nb_host_info  *  )malloc(  sizeof(  struct  nb_host_info  )  )  )  ==  NULL  )  goto  errLabel;
	bzero(  hostinfo,  sizeof(  struct  nb_host_info  )  );

	if  (  (  hostinfo->header  =  (  nbname_response_header_t  *  )malloc(sizeof(nbname_response_header_t)))==NULL) goto  errLabel;
	if  (  (  hostinfo->footer  =  (  nbname_response_footer_t  *  )malloc(sizeof(nbname_response_footer_t)))==NULL) goto  errLabel;
	response_header  =  hostinfo->header;
	response_footer  =  hostinfo->footer;
	bzero(response_header, sizeof(nbname_response_header_t));
	bzero(response_footer, sizeof(nbname_response_footer_t));
	

	/* Parsing received packet */
	/* Start with header */
	if( offset+sizeof(response_header->transaction_id) >= buffsize) goto broken_packet;
	response_header->transaction_id = get16(buff+offset); 
	//Move pointer to the next structure field
	offset+=sizeof(response_header->transaction_id);
    
	//  hostinfo->header = response_header;		//  2004/05/23

	// Check if there is room for next field in buffer
	if( offset+sizeof(response_header->flags) >= buffsize) goto broken_packet; 
	response_header->flags = get16(buff+offset);
        offset+=sizeof(response_header->flags);
	
	if( offset+sizeof(response_header->question_count) >= buffsize) goto broken_packet;
	response_header->question_count = get16(buff+offset);
        offset+=sizeof(response_header->question_count);
        
	if( offset+sizeof(response_header->answer_count) >= buffsize) goto broken_packet;
	response_header->answer_count = get16(buff+offset);
        offset+=sizeof(response_header->answer_count);
        
	if( offset+sizeof(response_header->name_service_count) >= buffsize) goto broken_packet;
	response_header->name_service_count = get16(buff+offset);
        offset+=sizeof(response_header->name_service_count);
        
	if( offset+sizeof(response_header->additional_record_count) >= buffsize) goto broken_packet;
	response_header->additional_record_count = get16(buff+offset);
        offset+=sizeof(response_header->additional_record_count);
        
	if( offset+sizeof(response_header->question_name) >= buffsize) goto broken_packet;
	strncpy(response_header->question_name, buff+offset, sizeof(response_header->question_name));
        offset+=sizeof(response_header->question_name);
        
	if( offset+sizeof(response_header->question_type) >= buffsize) goto broken_packet;
	response_header->question_type = get16(buff+offset);
        offset+=sizeof(response_header->question_type);
        
	if( offset+sizeof(response_header->question_class) >= buffsize) goto broken_packet;
	response_header->question_class = get16(buff+offset);
        offset+=sizeof(response_header->question_class);
        
	if( offset+sizeof(response_header->ttl) >= buffsize) goto broken_packet;
        response_header->ttl = get32(buff+offset);
        offset+=sizeof(response_header->ttl);
        
	if( offset+sizeof(response_header->rdata_length) >= buffsize) goto broken_packet;
        response_header->rdata_length = get16(buff+offset);
        offset+=sizeof(response_header->rdata_length);
        
	if( offset+sizeof(response_header->number_of_names) >= buffsize) goto broken_packet;
	//  response_header->number_of_names = *(typeof(response_header->number_of_names)*)(buff+offset);
	response_header->number_of_names = *(my_uint8_t  *)(buff+offset);
	       offset+=sizeof(response_header->number_of_names);

	/* Done with packet header - it is okay */
	
	name_table_size = (response_header->number_of_names) * (sizeof(struct nbname));
	if( offset+name_table_size >= buffsize) goto broken_packet;
	
	if((hostinfo->names = (  struct nbname*  )malloc(name_table_size))==NULL) goto  errLabel;
	memcpy(hostinfo->names, buff + offset, name_table_size);
	
	offset+=name_table_size;

	/* Done with name table - it is okay */ 
 
        /* Now parse response footer */

	if( offset+sizeof(response_footer->adapter_address) >= buffsize) goto broken_packet;	
	memcpy(response_footer->adapter_address, 
	       (buff+offset), 
	       sizeof(response_footer->adapter_address));
	offset+=sizeof(response_footer->adapter_address);

	//  hostinfo->footer=response_footer;		//  2004/05/23×¢ÊÍ

	if( offset+sizeof(response_footer->version_major) >= buffsize) goto broken_packet;
	//  response_footer->version_major = *(typeof(response_footer->version_major)*)(buff+offset);
	response_footer->version_major = *(my_uint8_t  *)(buff+offset);
	offset+=sizeof(response_footer->version_major);
	
	if( offset+sizeof(response_footer->version_minor) >= buffsize) goto broken_packet;
	//  response_footer->version_minor = *(typeof(response_footer->version_minor)*)(buff+offset);
	response_footer->version_minor = *(my_uint8_t  *)(buff+offset);
	offset+=sizeof(response_footer->version_minor);
	
	if( offset+sizeof(response_footer->duration) >= buffsize) goto broken_packet;
	response_footer->duration = get16(buff+offset);
	offset+=sizeof(response_footer->duration);
	
	if( offset+sizeof(response_footer->frmps_received) >= buffsize) goto broken_packet;
	response_footer->frmps_received= get16(buff+offset);
	offset+=sizeof(response_footer->frmps_received);
	
	if( offset+sizeof(response_footer->frmps_transmitted) >= buffsize) goto broken_packet;
	response_footer->frmps_transmitted = get16(buff+offset);
	offset+=sizeof(response_footer->frmps_transmitted);
	
	if( offset+sizeof(response_footer->iframe_receive_errors) >= buffsize) goto broken_packet;
	response_footer->iframe_receive_errors = get16(buff+offset);
	offset+=sizeof(response_footer->iframe_receive_errors);
	
	if( offset+sizeof(response_footer->transmit_aborts) >= buffsize) goto broken_packet;
	response_footer->transmit_aborts =  get16(buff+offset);
	offset+=sizeof(response_footer->transmit_aborts);
	
	if( offset+sizeof(response_footer->transmitted) >= buffsize) goto broken_packet;
	response_footer->transmitted = get32(buff+offset);
	offset+=sizeof(response_footer->transmitted);
	
	if( offset+sizeof(response_footer->received) >= buffsize) goto broken_packet;
	response_footer->received = get32(buff+offset);
	offset+=sizeof(response_footer->received);
	
	if( offset+sizeof(response_footer->iframe_transmit_errors) >= buffsize) goto broken_packet;
	response_footer->iframe_transmit_errors = get16(buff+offset);
	offset+=sizeof(response_footer->iframe_transmit_errors);
	
	if( offset+sizeof(response_footer->no_receive_buffer) >= buffsize) goto broken_packet;
	response_footer->no_receive_buffer = get16(buff+offset);
	offset+=sizeof(response_footer->no_receive_buffer);
	
	if( offset+sizeof(response_footer->tl_timeouts) >= buffsize) goto broken_packet;
	response_footer->tl_timeouts = get16(buff+offset);
	offset+=sizeof(response_footer->tl_timeouts);
	
	if( offset+sizeof(response_footer->ti_timeouts) >= buffsize) goto broken_packet;
	response_footer->ti_timeouts = get16(buff+offset);
	offset+=sizeof(response_footer->ti_timeouts);
	
	if( offset+sizeof(response_footer->free_ncbs) >= buffsize) goto broken_packet;
	response_footer->free_ncbs = get16(buff+offset);
	offset+=sizeof(response_footer->free_ncbs);
	
	if( offset+sizeof(response_footer->ncbs) >= buffsize) goto broken_packet;
	response_footer->ncbs = get16(buff+offset);
	offset+=sizeof(response_footer->ncbs);
	
	if( offset+sizeof(response_footer->max_ncbs) >= buffsize) goto broken_packet;
	response_footer->max_ncbs = get16(buff+offset);
	offset+=sizeof(response_footer->max_ncbs);
	
	if( offset+sizeof(response_footer->no_transmit_buffers) >= buffsize) goto broken_packet;
	response_footer->no_transmit_buffers = get16(buff+offset);
	offset+=sizeof(response_footer->no_transmit_buffers);
	
	if( offset+sizeof(response_footer->max_datagram) >= buffsize) goto broken_packet;
	response_footer->max_datagram = get16(buff+offset);
	offset+=sizeof(response_footer->max_datagram);
	
	if( offset+sizeof(response_footer->pending_sessions) >= buffsize) goto broken_packet;
	response_footer->pending_sessions = get16(buff+offset);
	offset+=sizeof(response_footer->pending_sessions);
	
	if( offset+sizeof(response_footer->max_sessions) >= buffsize) goto broken_packet;
	response_footer->max_sessions = get16(buff+offset);
	offset+=sizeof(response_footer->max_sessions);
	
	if( offset+sizeof(response_footer->packet_sessions) >= buffsize) goto broken_packet;
	response_footer->packet_sessions = get16(buff+offset);
	offset+=sizeof(response_footer->packet_sessions);
	
	/* Done with packet footer and the whole packet */

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		freeNbHostInfo(  hostinfo  );  hostinfo  =  NULL;
	}

	return   hostinfo;
	
broken_packet: 
		hostinfo->is_broken = offset;
		return  hostinfo;	
}




