
#ifndef  __AENBTSCAN_H__
#define  __AENBTSCAN_H__	/*  {  */

typedef  unsigned  char  my_uint8_t;
typedef  unsigned  short  my_uint16_t;
typedef  unsigned  int  my_uint32_t;

#ifndef  PF_commonHandler
	typedef  int  (  *  PF_commonHandler  )(  LPVOID  p0,  LPVOID  p1,  LPVOID  p2  );
#endif


#define		NB_DGRAM				137
#define		DEFAULT_UDP_PORT		789
#define		FL_BROADCAST			0x0010
#define		bzero(p,n)				memset((p),(0),(n))


struct nbname {
	char ascii_name [16] ;
	my_uint16_t rr_flags;
};

struct nbname_request {
        my_uint16_t transaction_id;
        my_uint16_t flags;
        my_uint16_t question_count;
        my_uint16_t answer_count;
        my_uint16_t name_service_count;
        my_uint16_t additional_record_count;
        char question_name[34]; 
        my_uint16_t question_type;
        my_uint16_t question_class;
};

#define NBNAME_REQUEST_SIZE 50
#define UDP_HEADER_SIZE 8
#define IP_HEADER_SIZE 20

typedef struct nbname_response_header {
	my_uint16_t transaction_id;
	my_uint16_t flags;
	my_uint16_t question_count;
	my_uint16_t answer_count;
	my_uint16_t name_service_count;
	my_uint16_t additional_record_count;
	char question_name[34];
	my_uint16_t question_type;
	my_uint16_t question_class;
	my_uint32_t ttl;
	my_uint16_t rdata_length;
	my_uint8_t number_of_names;
} nbname_response_header_t;

/* #define NBNAME_RESPONSE_NUMBER_OF_NAMES_OFFSET 56 */

#define NBNAME_RESPONSE_HEADER_SIZE 57

typedef struct nbname_response_footer {
	my_uint8_t adapter_address [6];
	my_uint8_t version_major;
	my_uint8_t version_minor;
	my_uint16_t duration;
	my_uint16_t frmps_received;
	my_uint16_t frmps_transmitted;
	my_uint16_t iframe_receive_errors;
	my_uint16_t transmit_aborts;
	my_uint32_t transmitted;
	my_uint32_t received;
	my_uint16_t iframe_transmit_errors;
	my_uint16_t no_receive_buffer;
	my_uint16_t tl_timeouts;
	my_uint16_t ti_timeouts;
	my_uint16_t free_ncbs;
	my_uint16_t ncbs;
	my_uint16_t max_ncbs;
	my_uint16_t no_transmit_buffers;
	my_uint16_t max_datagram;
	my_uint16_t pending_sessions;
	my_uint16_t max_sessions;
	my_uint16_t packet_sessions;
} nbname_response_footer_t ;

#define NBNAME_RESPONSE_FOOTER_SIZE 50

struct  nb_host_info							{
			struct  nbname_response_header  *	header;
			struct  nbname					*	names;
			struct  nbname_response_footer	*	footer;
			int									is_broken;
};

typedef struct nb_service {
	char nb_name[16];
	my_uint8_t service_number;
	int unique;
	char* service_name;
} nb_service_t ;


#ifdef  __cplusplus
  extern  "C"  {
#endif
	
struct nb_host_info* parse_response(char* buff, unsigned  int buffsize);
void  freeNbHostInfo(  	struct  nb_host_info	*	hostinfo  );



#ifdef  __cplusplus
  }
#endif


#endif  /*  }  */

