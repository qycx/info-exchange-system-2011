// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the QYMC_WINCE_CORE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// QYMC_WINCE_CORE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef QYMC_WINCE_CORE_EXPORTS
#define QYMC_WINCE_CORE_API __declspec(dllexport)
#else
#define QYMC_WINCE_CORE_API __declspec(dllimport)
#endif

// This class is exported from the qyMc_winCe_core.dll
class QYMC_WINCE_CORE_API CqyMc_winCe_core {
public:
	CqyMc_winCe_core(void);
	// TODO: add your methods here.
};

extern QYMC_WINCE_CORE_API int nqyMc_winCe_core;

QYMC_WINCE_CORE_API int fnqyMc_winCe_core(void);
