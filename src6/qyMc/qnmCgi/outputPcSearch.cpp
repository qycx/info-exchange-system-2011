
#include	"stdafx.h"
#include	"qnmCgi.h"



 int outputPcSearch(  void  *  pQnmCgi  )
{
	 printMimeHeader(  );
	 printf(  "<html>"  );
	 printf(  "<head><title>计算机查询</title></head>"  );
	 printf(  "<body>"  );
	 printf(  "<form action=qnm.cgi method=post>"  );
	 printf(  "单位：<input type =text name=unit><p>"  );
	 printf(  "部门：<input type =text name=department><p>"  );
	 printf(  "使用人：<input type =text name=usr><p>"  );
	 printf(  "<input type=submit name=submit value=确定>"  );
	 printf(  "</form>"  );
	 printf(  "</body>"  );
	 printf(  "</html>"  );
	 printf(  "\n"  );
	 return  0;
}