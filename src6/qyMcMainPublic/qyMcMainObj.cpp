
#include "stdafx.h"
#include "qyMcMainCommon.h"




 CQyString  getMcQueryCntStr(  QY_MC_QUERY  *  pQuery  )
{
	 return  CQyString(  "select count( * ) "  )  +  CQyString(  pQuery->fromPart  )  +  CQyString(  _T(  " "  )  )  +  CQyString(  pQuery->wherePart  );
}


 CQyString  getMcQueryCurnItemStr(  QY_MC_QUERY  *  pQuery  )
{	
	traceLogA(  "getMcQueryCurnItemStr .. 这个函数不应再被调用。"  );
	
	return  CQyString( ""  );

}


