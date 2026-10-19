#include	"stdafx.h"
#include	"qnmCgi.h"
#include	<iphlpapi.h>
#include	<tchar.h>



 int outputLogin(  void  *  pQnmCgi  )
{
	 printMimeHeader(  );
	 printf(  "<html>"  );
	 printf(  "<head><title>用户登录</title></head>"  );
	 printf(  "<body>"  );
	 printf(  "<H1>用户登录</H1>"  );
	 printf(  "<P><HR><P>"  );
     printf(  "请正确输入您的<B>用户名</B>和<B>密码</B>:<P>"  );
	 printf(  "<form action=qnm.cgi method=post>"  );
	 printf(  "用户名：<input type =text name=usr><p>"  );
	 printf(  "密码：<input type=password name=pswd><p>"  );
	 printf(  "<input type=submit name=submit value=确定>"  );
	 printf(  "</form>"  );
	 printf(  "</body>"  );
	 printf(  "</html>"  );
	 printf(  "\n"  );
	 return  0;
}