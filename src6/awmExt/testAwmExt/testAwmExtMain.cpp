

#include "stdafx.h"
#include "awmExt.h"

 int testAwmExtMain( )
{
	CDatabase tmpDb;
	SCANNING_LOG_TAB_RCD sLTR;
	CString sqlCStr;
	char computerInfoBuf[MAX_AWM_MON_OFFICE_NAME_LEN + MAX_AWM_MON_SUB_OFFICE_NAME_LEN + MAX_IP_ADDR_LEN + 1];
	int i = 0;



	TRY {
		if ( !tmpDb.Open( DEFAULT_AWM_EXT_DSN_NAME ) ) goto errLabel;

		while ( 1 ) {

			i ++;

			memset( &sLTR, 0, sizeof( sLTR ) );
			sprintf( sLTR.officeName, "off%03d", i % 100 );
			sprintf( sLTR.scannedIp, "203.186.10.%d", i % 100 );

			memset( computerInfoBuf, ' ', sizeof( computerInfoBuf ) - 1 );
			computerInfoBuf[sizeof( computerInfoBuf ) - 1] = 0;
			memcpy( computerInfoBuf, sLTR.officeName, strlen( sLTR.officeName ) );
			memcpy( computerInfoBuf + MAX_AWM_MON_OFFICE_NAME_LEN, sLTR.subOfficeName, strlen( sLTR.subOfficeName ) );
			memcpy( computerInfoBuf + MAX_AWM_MON_OFFICE_NAME_LEN + MAX_AWM_MON_SUB_OFFICE_NAME_LEN, sLTR.scannedIp, strlen( sLTR.scannedIp ) );
		
			sqlCStr = CString( "insert into originalLogTab( computerInfo, recvdTime ) values( " )
				+ "'" + computerInfoBuf + "'"
				+ "," + "'" + sLTR.recvdTime + "'"
				+ ")";

			tmpDb.ExecuteSQL( sqlCStr );
		
		}

		}
	CATCH ( CDBException, e ) {
		// debugLog(  e->m_strError.GetBuffer(  0  )  );
	}
	END_CATCH

errLabel:
	
	if ( tmpDb.IsOpen( ) )
		tmpDb.Close( );

	return 0;

}


