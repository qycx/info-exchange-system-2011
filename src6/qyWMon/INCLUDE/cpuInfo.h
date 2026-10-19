
#ifndef __CPUINFO_H__
#define __CPUINFO_H__  //  {

#define STORE_TLBCACHE_INFO(x,y)	x = (x < y) ? y : x
#define VENDOR_STRING_LENGTH		(12 + 1)
#define CHIPNAME_STRING_LENGTH		(48 + 1)
#define SERIALNUMBER_STRING_LENGTH	(29 + 1)
#define TLBCACHE_INFO_UNITS			(15)
#define CLASSICAL_CPU_FREQ_LOOP		10000000
#define RDTSC_INSTRUCTION			_asm _emit 0x0f _asm _emit 0x31
#define	CPUSPEED_I32TO64(x, y)		(((__int64) x << 32) + y)

#define CPUID_AWARE_COMPILER
#ifdef CPUID_AWARE_COMPILER
	#define CPUID_INSTRUCTION		cpuid
#else
	#define CPUID_INSTRUCTION		_asm _emit 0x0f _asm _emit 0xa2
#endif

#define MMX_FEATURE					0x00000001
#define MMX_PLUS_FEATURE			0x00000002
#define SSE_FEATURE					0x00000004
#define SSE2_FEATURE				0x00000008
#define AMD_3DNOW_FEATURE			0x00000010
#define AMD_3DNOW_PLUS_FEATURE		0x00000020
#define IA64_FEATURE				0x00000040
#define MP_CAPABLE					0x00000080
#define HYPERTHREAD_FEATURE			0x00000100
#define SERIALNUMBER_FEATURE		0x00000200
#define APIC_FEATURE				0x00000400
#define SSE_FP_FEATURE				0x00000800
#define SSE_MMX_FEATURE				0x00001000
#define CMOV_FEATURE				0x00002000
#define MTRR_FEATURE				0x00004000
#define L1CACHE_FEATURE				0x00008000
#define L2CACHE_FEATURE				0x00010000
#define L3CACHE_FEATURE				0x00020000
#define ACPI_FEATURE				0x00040000
#define THERMALMONITOR_FEATURE		0x00080000
#define TEMPSENSEDIODE_FEATURE		0x00100000
#define FREQUENCYID_FEATURE			0x00200000
#define VOLTAGEID_FREQUENCY			0x00400000




typedef	void (*DELAY_FUNC)(unsigned int uiMS);

class CPUSpeed {
public:
	CPUSpeed ();
	~CPUSpeed ();
		
	// Variables.
	int CPUSpeedInMHz;

	// Functions.
	__int64 __cdecl GetCyclesDifference (DELAY_FUNC, unsigned int);
		
private:
	// Functions.
	static void Delay (unsigned int);
	static void DelayOverhead (unsigned int);

protected:
	
};

class CPUInfo {
public:
	CPUInfo ();
	~CPUInfo ();

	char * GetVendorString ();
	TCHAR * GetVendorID ();
	char * GetExtendedProcessorName ();
	char * GetProcessorSerialNumber ();
	int GetLogicalProcessorsPerPhysical ();
	int GetProcessorClockFrequency ();
	int GetProcessorAPICID ();
	int GetProcessorCacheXSize (DWORD);
	BOOL DoesCPUSupportFeature (DWORD);

	BOOL  __cdecl  DoesCPUSupportCPUID ();
	BOOL  bRetrieveAll(  );


private:
	typedef  struct  __cpuId_t				{
					 int					Type;
					 int					Family;
					 int					Model;
					 int					Revision;
					 int					iCache;			//  added by me, 2004/07/31
					 int					ExtendedFamily;
					 int					ExtendedModel;
					 unsigned  int			uiBrandId;		//  2005/01/16
					 //
					 char					ProcessorName[CHIPNAME_STRING_LENGTH];
					 char					Vendor[VENDOR_STRING_LENGTH];
					 char					SerialNumber[SERIALNUMBER_STRING_LENGTH];
	}		 CPU_ID;

	typedef  struct  tagCPUPowerManagement	{
					 BOOL					HasVoltageID;
					 BOOL					HasFrequencyID;
					 BOOL					HasTempSenseDiode;
	}		 CPUPowerManagement;

	typedef  struct  tagCPUExtendedFeatures	{
					 BOOL					Has3DNow;
					 BOOL					Has3DNowPlus;
					 BOOL					SupportsMP;
					 BOOL					HasMMXPlus;
					 BOOL					HasSSEMMX;
					 BOOL					SupportsHyperthreading;
					 int					LogicalProcessorsPerPhysical;
					 int					APIC_ID;
					 CPUPowerManagement		PowerManagement;
	}		 CPUExtendedFeatures;	
	
	typedef  struct  CPUtagFeatures			{
					 BOOL					HasFPU;
					 BOOL 					HasTSC;
					 BOOL 					HasMMX;
					 BOOL 					HasSSE;
					 BOOL 					HasSSEFP;
					 BOOL 					HasSSE2;
					 BOOL 					HasIA64;
					 BOOL 					HasAPIC;
					 BOOL 					HasCMOV;
					 BOOL 					HasMTRR;
					 BOOL 					HasACPI;
					 BOOL 					HasSerial;
					 BOOL 					HasThermal;
					 int 					CPUSpeed;
					 int 					L1CacheSize;
					 int 					L2CacheSize;
					 int 					L3CacheSize;
					 CPUExtendedFeatures	ExtendedFeatures;
	}		 CPUFeatures;
    
	//  enum  Manufacturer  {
	//  	CONST_AMD, CONST_Intel, CONST_NSC, CONST_UMC, CONST_Cyrix, CONST_NexGen, CONST_IDT, CONST_Rise, CONST_Transmeta, CONST_UnknownManufacturer
	//  };

	// Functions.
	BOOL __cdecl RetrieveCPUFeatures ();
	BOOL __cdecl RetrieveCPUIdentity ();
	BOOL __cdecl RetrieveCPUCacheDetails ();
	BOOL __cdecl RetrieveClassicalCPUCacheDetails ();
	BOOL __cdecl RetrieveCPUClockSpeed ();
	BOOL __cdecl RetrieveClassicalCPUClockSpeed ();
	BOOL __cdecl RetrieveCPUExtendedLevelSupport (int);
	BOOL __cdecl RetrieveExtendedCPUFeatures ();
	BOOL __cdecl RetrieveProcessorSerialNumber ();
	BOOL __cdecl RetrieveCPUPowerManagement ();
	//  BOOL __cdecl RetrieveClassicalCPUIdentity ();
	BOOL __cdecl RetrieveExtendedCPUIdentity ();
	
	// Variables.
public:
	unsigned  int	ChipManufacturer;
	CPU_ID			ChipID;
	CPUFeatures		Features;
protected:
	CPUSpeed	*	m_pSpeed;
	
protected:

};

#endif //  }  __CPUINFO_H__

