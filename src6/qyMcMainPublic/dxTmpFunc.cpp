
#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<windows.h>

#include	<tchar.h>
#include	<strsafe.h>

#include	<MMSystem.h>

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>

#include	<dshow.h>


#include	"qyCommon.h"


#ifdef  __DEBUG__

void WINAPI myDisplayType(LPCTSTR label, const AM_MEDIA_TYPE *pmtIn);

static void myFreeMediaType(  AM_MEDIA_TYPE& mt)
{
    if (mt.cbFormat != 0)
    {
        CoTaskMemFree((PVOID)mt.pbFormat);
        mt.cbFormat = 0;
        mt.pbFormat = NULL;
    }
    if (mt.pUnk != NULL)
    {
        // Unecessary because pUnk should not be used, but safest.
        mt.pUnk->Release();
        mt.pUnk = NULL;
    }
}


#define QueryFilterInfoReleaseGraph(fi) if ((fi).pGraph) (fi).pGraph->Release();
#define QueryPinInfoReleaseFilter(pi) if ((pi).pFilter) (pi).pFilter->Release();

void WINAPI myDumpGraph(IFilterGraph *pGraph, DWORD dwLevel)
{
    IEnumFilters *pFilters;
    
    //  DbgLog((LOG_TRACE,dwLevel,TEXT("DumpGraph [%x]"), pGraph));
	traceLog(  TEXT("DumpGraph [%x]"), pGraph  );
    
    if (FAILED(pGraph->EnumFilters(&pFilters))) {
        //  DbgLog((LOG_TRACE,dwLevel,TEXT("EnumFilters failed!")));
		traceLog(  TEXT("EnumFilters failed!")  );
    }
    
    IBaseFilter *pFilter;
    ULONG   n;
    while (pFilters->Next(1, &pFilter, &n) == S_OK) {
        FILTER_INFO info;
        
        if (FAILED(pFilter->QueryFilterInfo(&info))) {
            //  DbgLog((LOG_TRACE,dwLevel,TEXT("    Filter [%x]  -- failed QueryFilterInfo"), pFilter));
			traceLog(  TEXT("    Filter [%x]  -- failed QueryFilterInfo"), pFilter  );
        } else {
            QueryFilterInfoReleaseGraph(info);
            
            // !!! should QueryVendorInfo here!
            
            //  DbgLog((LOG_TRACE,dwLevel,TEXT("    Filter [%x]  '%ls'"), pFilter, info.achName));
			traceLog(  TEXT("    Filter [%x]  '%ls'"), pFilter, info.achName  );
            
            IEnumPins *pins;
            
            if (FAILED(pFilter->EnumPins(&pins))) {
                //  DbgLog((LOG_TRACE,dwLevel,TEXT("EnumPins failed!")));
				traceLog(  TEXT("EnumPins failed!")  );
            } else {
                
                IPin *pPin;
                while (pins->Next(1, &pPin, &n) == S_OK) {
                    PIN_INFO    info;
                    
                    if (FAILED(pPin->QueryPinInfo(&info))) {
                        //  DbgLog((LOG_TRACE,dwLevel,TEXT("          Pin [%x]  -- failed QueryPinInfo"), pPin));
						traceLog(  TEXT("          Pin [%x]  -- failed QueryPinInfo"), pPin  );
                    } else {
                        QueryPinInfoReleaseFilter(info);
                        
                        IPin *pPinConnected = NULL;
                        
                        HRESULT hr = pPin->ConnectedTo(&pPinConnected);
                        
                        if (pPinConnected) {
                            //  DbgLog((LOG_TRACE,dwLevel,TEXT("          Pin [%x]  '%ls' [%sput]")TEXT("  Connected to pin [%x]"),  pPin, info.achName,  info.dir == PINDIR_INPUT ? TEXT("In") : TEXT("Out"),  pPinConnected));
							traceLog(  TEXT("          Pin [%x]  '%ls' [%sput]")TEXT("  Connected to pin [%x]"),  pPin, info.achName,  info.dir == PINDIR_INPUT ? TEXT("In") : TEXT("Out"),  pPinConnected  );
                            
                            pPinConnected->Release();
                            
                            // perhaps we should really dump the type both ways as a sanity
                            // check?
                            if (info.dir == PINDIR_OUTPUT) {
                                AM_MEDIA_TYPE mt;
                                
                                hr = pPin->ConnectionMediaType(&mt);
                                
                                if (SUCCEEDED(hr)) {
                                    myDisplayType(  _T(  "Connection type"  ), &mt);
                                    
                                    myFreeMediaType(mt);
                                }
                            }
                        } else {
                            //  DbgLog((LOG_TRACE,dwLevel,TEXT("          Pin [%x]  '%ls' [%sput]"),  pPin, info.achName,  info.dir == PINDIR_INPUT ? TEXT("In") : TEXT("Out")));
							traceLog(  TEXT("          Pin [%x]  '%ls' [%sput]"),  pPin, info.achName,  info.dir == PINDIR_INPUT ? TEXT("In") : TEXT("Out")  );
                        }
                    }
                    
                    pPin->Release();
                    
                }
                
                pins->Release();
            }
            
        }
        
        pFilter->Release();
    }
    
    pFilters->Release();
    
}

void WINAPI myDisplayType(LPCTSTR label, const AM_MEDIA_TYPE *pmtIn)
{
    
    /* Dump the GUID types and a short description */
    
    traceLog(  TEXT("")  );
    //  traceLogA(  ("%hs  M type %s  S type %s"), label,GuidNames[pmtIn->majortype],GuidNames[pmtIn->subtype]  );
    //  traceLog(  TEXT("Subtype description %s"),  GetSubtypeName(&pmtIn->subtype)  );
    
    /* Dump the generic media types */
    
    if (pmtIn->bTemporalCompression) {
        traceLog(  TEXT("Temporally compressed")  );
    } else {
        traceLog(  TEXT("Not temporally compressed")  );
    }
    
    if (pmtIn->bFixedSizeSamples) {
        traceLog(  TEXT("Sample size %d"),pmtIn->lSampleSize  );
    } else {
        traceLog(  TEXT("Variable size samples")  );
    }
    
    if (pmtIn->formattype == FORMAT_VideoInfo) {
        /* Dump the contents of the BITMAPINFOHEADER structure */
        BITMAPINFOHEADER *pbmi = HEADER(pmtIn->pbFormat);
        VIDEOINFOHEADER *pVideoInfo = (VIDEOINFOHEADER *)pmtIn->pbFormat;
        
        traceLog(  TEXT("Source rectangle (Left %d Top %d Right %d Bottom %d)"),
            pVideoInfo->rcSource.left,
            pVideoInfo->rcSource.top,
            pVideoInfo->rcSource.right,
            pVideoInfo->rcSource.bottom  );
        
        traceLog(  TEXT("Target rectangle (Left %d Top %d Right %d Bottom %d)"),
            pVideoInfo->rcTarget.left,
            pVideoInfo->rcTarget.top,
            pVideoInfo->rcTarget.right,
            pVideoInfo->rcTarget.bottom  );
        
        traceLog(  TEXT("Size of BITMAPINFO structure %d"),pbmi->biSize  );
        if (pbmi->biCompression < 256) {
            traceLog(  TEXT("%dx%dx%d bit  (%d)"),
                pbmi->biWidth, pbmi->biHeight,
                pbmi->biBitCount, pbmi->biCompression  );
        } else {
            traceLog(  TEXT("%dx%dx%d bit '%4.4hs'"),
                pbmi->biWidth, pbmi->biHeight,
                pbmi->biBitCount, &pbmi->biCompression  );
        }
        
        traceLog(  TEXT("Image size %d"),pbmi->biSizeImage  );
        traceLog(  TEXT("Planes %d"),pbmi->biPlanes  );
        traceLog(  TEXT("X Pels per metre %d"),pbmi->biXPelsPerMeter  );
        traceLog(  TEXT("Y Pels per metre %d"),pbmi->biYPelsPerMeter  );
        traceLog(  TEXT("Colours used %d"),pbmi->biClrUsed  );
        
    } else if (pmtIn->majortype == MEDIATYPE_Audio) {
        //  traceLog(  TEXT("     Format type %s"),  GuidNames[pmtIn->formattype]  );
        //  traceLog(  TEXT("     Subtype %s"),  GuidNames[pmtIn->subtype]  );
        
        if ((pmtIn->subtype != MEDIASUBTYPE_MPEG1Packet)
            && (pmtIn->cbFormat >= sizeof(PCMWAVEFORMAT)))
        {
            /* Dump the contents of the WAVEFORMATEX type-specific format structure */
            
            WAVEFORMATEX *pwfx = (WAVEFORMATEX *) pmtIn->pbFormat;
            traceLog(  TEXT("wFormatTag %u"), pwfx->wFormatTag  );
            traceLog(  TEXT("nChannels %u"), pwfx->nChannels  );
            traceLog(  TEXT("nSamplesPerSec %lu"), pwfx->nSamplesPerSec  );
            traceLog(  TEXT("nAvgBytesPerSec %lu"), pwfx->nAvgBytesPerSec  );
            traceLog(  TEXT("nBlockAlign %u"), pwfx->nBlockAlign  );
            traceLog(  TEXT("wBitsPerSample %u"), pwfx->wBitsPerSample  );
            
            /* PCM uses a WAVEFORMAT and does not have the extra size field */
            
            if (pmtIn->cbFormat >= sizeof(WAVEFORMATEX)) {
                traceLog(  TEXT("cbSize %u"), pwfx->cbSize  );
            }
        } else {
        }
        
    } else {
        //  traceLog(  TEXT("     Format type %s"),  GuidNames[pmtIn->formattype]  );
        // !!!! should add code to dump wave format, others
    }
}

#endif
