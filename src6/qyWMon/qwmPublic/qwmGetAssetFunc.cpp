

#include	<windows.h>
#include	<stdio.h>
#include	<string.h>


typedef  struct  __qwmCpusInfo_t		{
				 unsigned  int			cnt;
				 struct					{
						char			processorType[64];
				 }						cpus[1];
}		 QWM_CPUS_INFO;

 int  getCpusInfo(  QWM_CPUS_INFO  *  pCpusInfo  )
{
    OSVERSIONINFO		osinfo;
    SYSTEM_INFO			sysinfo;
    char			*	cpu			=	NULL;
    int					count		=	0;

	//  SetUnhandledExceptionFilter(  myExceptionFilter  );

    osinfo.dwOSVersionInfoSize  =  sizeof(OSVERSIONINFO);
    GetVersionEx(&osinfo);
    
	GetSystemInfo(&sysinfo);
        
    if  (  osinfo.dwPlatformId  ==  VER_PLATFORM_WIN32_NT  )  {   
		switch  (  sysinfo.wProcessorArchitecture  )  {   
				case  PROCESSOR_ARCHITECTURE_INTEL:
                	  switch  (  sysinfo.wProcessorLevel  )  {   
							  case  3:  cpu  =  "Intel 386";     break;
                    		  case  4:  cpu  =  "Intel 486";     break;
                    		  case  5:  
							  case  6:  cpu  =  "Intel Pentium"; break;
                    		  default:  cpu  =  "Unknown Intel"; break;
                	  }
                	  break;

				case  PROCESSOR_ARCHITECTURE_MIPS:
                	  switch  (  sysinfo.wProcessorLevel  )  {   
							  case  1:  cpu = "MIPS R2000";    break;
                    		  case  2: cpu = "MIPS R3000";    break;
                    		  case  3: cpu = "MIPS R6000";    break;
                    		  case  4: cpu = "MIPS R4000";    break;
                    		  case  6: cpu = "MIPS R6000A";   break;
                    		  case  9: cpu = "MIPS R10000";   break;
							  case 10: cpu = "MIPS R4200";    break;
							  case 11: cpu = "MIPS R4300";    break;
							  case 16: cpu = "MIPS R8000";    break;
							  case 32: cpu = "MIPS R4600";    break;
							  case 33: cpu = "MIPS R4700";    break;
							  case 34: cpu = "MIPS R4650";    break;
							  case 35: cpu = "MIPS R5000";    break;
							  default: cpu = "Unknown MIPS";  break;
					  }
					  break;

			    case  PROCESSOR_ARCHITECTURE_ALPHA:
                	  switch  (  sysinfo.wProcessorLevel  )  { 
							  case  21064:  cpu = "Alpha 21064";  break;
                    		  case  21066:  cpu = "Alpha 21066";  break;
                    		  case  21164:  cpu = "Alpha 21164";  break;
                    		  default:		cpu = "Unknown Alpha";    break;
                	  }
                	  break;
			    case  PROCESSOR_ARCHITECTURE_PPC:
                	  switch  (  sysinfo.wProcessorLevel  )  { 
							  case  1:  cpu = "PPC 601";     break;
                    		  case  3:  cpu = "PPC 603";     break;
                    		  case  4:  cpu = "PPC 604";     break;
                    		  case  6:  cpu = "PPC 603+";    break;
                    		  case  9:  cpu = "PPC 604+";    break;
                    		  case 20:  cpu = "PPC 620";     break;
                    		  default:  cpu = "Unknown PPC"; break;
                	  }
                	  break;

                default:
                		cpu  =  "unrecognised";
                		break;
        
			}
		} 
	else   {  /* Windows 95 or Windows98 */
      
	        switch  (  sysinfo.dwProcessorType  )  {
					case (386):   cpu = "Intel 386";       break;
            		case (486):   cpu = "Intel 486";       break;
            		case (586):   cpu = "Intel Pentium";   break;
            		case (860):   cpu = "Intel i860";      break;
            		case (2000):  cpu = "MIPS R2000";      break;
            		case (3000):  cpu = "MIPS R3000";      break;
            		case (4000):  cpu = "MIPS R4000";      break;
            		case (4400):  cpu = "MIPS R4400";      break;
            		case (4600):  cpu = "MIPS R4600";      break;
            		case (5000):  cpu = "MIPS R5000";      break;
            		case (8000):  cpu = "MIPS R8000";      break;
            		case (10000): cpu = "MIPS R10000";     break;
            		case (21064): cpu = "DEC Alpha 21064"; break;
            		case (21066): cpu = "DEC Alpha 21066"; break;
            		case (21164): cpu = "DEC Alpha 21164"; break;
            		default:     cpu = "unrecognised";
        	}
    
	}

	pCpusInfo->cnt  =  sysinfo.dwNumberOfProcessors;
	_snprintf(  pCpusInfo->cpus[0].processorType,  sizeof(  pCpusInfo->cpus[0].processorType  ),  "%s",  cpu  );

//  errLabel:
	return  0;

}


