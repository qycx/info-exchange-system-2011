
#include	"stdafx.h"
#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCustom.h"
#include	"qnmCustomComm.h"


 QY_DMITEM  CONST_qyMcAppNameTable[]  =  
{
	{	CONST_qyCustomId_null,				_T(  "QyMc -清扬创新内网管理系统"  ),			},
	{	CONST_qyCustomId_hgzh,				_T(  "QyMc -海关总署内网管理系统"  ),			},
	{	CONST_qyCustomId_shhg,				_T(  "QyMc -海关网络管理系统"  ),				},
	{	CONST_qyCustomId_gab,				_T(  "QyMc -公安部内网管理系统"  ),				},
	{	CONST_qyCustomId_zjga,				_T(  "QyMc -浙江公安内网管理系统"  ),			},
	{	CONST_qyCustomId_hbga,				_T(  "QyMc -湖北省公安厅内网管理系统"  ),		},
	{	CONST_qyCustomId_sjs,				_T(  "QyMc -审计署内网管理系统"  ),				},
	{	-1,									NULL,									},
};


  QY_DMITEM  CONST_qyMcAppNameTable_netMc2[]  =  
{
	{	CONST_qyCustomId_null,				_T(  "QyMc -清扬创新内网管理系统"  ),			},
	{	CONST_qyCustomId_shhg,				_T(  "QyMc -上海海关业务管理网监控管理系统"  ),	},
#ifdef  __HZSJ__
	{	CONST_qyCustomId_zjga,				_T(  "QyMc -杭州公安内网管理系统"  ),		},
#else
	{	CONST_qyCustomId_zjga,				_T(  "QyMc -浙江公安内网管理系统"  ),		},
#endif  __HZSJ__
	{	-1,									NULL,									},
};




 QY_DMITEM	CONST_qyRegToolAppNameTable[]  =
{
	{	CONST_qyCustomId_null,  			_T(  "qyRegTool.exe"  ),			},
	{	CONST_qyCustomId_hgzh,				_T(  "hgzsRegTool.exe"  ),			},
	{	CONST_qyCustomId_shhg,				_T(  "RegTool.exe"  ),			},
	{	CONST_qyCustomId_gab,				_T(  "gabRegTool.exe"  ),			},
	{	CONST_qyCustomId_zjga,				_T(  "regTool.exe"  ),			},
	{	CONST_qyCustomId_hbga,				_T(  "hbgaRegTool.exe"  ),			},
	{	CONST_qyCustomId_sjs,				_T(  "sjsRegTool.exe"  ),			},
	{	-1,									NULL,						},
};



 extern  "C"  TCHAR  *  qyGetRegToolAppName(  )
{
	 int		iCustomId;
	 TCHAR	*	pAppName	=	NULL;

	 iCustomId  =  qyGetCustomId(  );
	 pAppName  =  qyGetDesByType(  CONST_qyRegToolAppNameTable,  iCustomId  );

	 return  pAppName  ?  pAppName  :  DEFAULT_regToolAppName;
}
 







