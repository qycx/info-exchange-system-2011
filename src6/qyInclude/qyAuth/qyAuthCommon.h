
#ifndef  __QYAUTHCOMMON_H__
#define  __QYAUTHCOMMON_H__	/* { */


typedef  struct  __qyRightCommon_t  {
				 int				i;
}		 QY_RIGHT_COMMON;

typedef  struct  __qyGrpCommon_t  {
				 int				type;
				 int				id;			
				 QY_RIGHT_COMMON	right;
}		  QY_GRP_COMMON;

typedef  struct  __qyUsrCommon_t {
				 int				type;
				 int				id;
				 QY_GRP_COMMON		grp;
}			QY_USR_COMMON;




#endif  /*  }  */

