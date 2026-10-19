


// written by ls.
 extern  "C"  int  Encrypt(  char  *  pSource,  int  iSourceLen,  char  *  pDestcode  )
{
	int iErr = 0, i;

	for  (  i  =  0;  i  <  iSourceLen;  i  ++  )
		pDestcode[i]  =  ~pSource[i]  &  127;

	// pDestcode[i] = '\0';

	
	return  iErr;

}
