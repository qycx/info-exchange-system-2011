
#ifndef __QYHK_H__
#define __QYHK_H__	/* { */

#ifdef __cplusplus
 extern "C" {
#endif

// Use Current Window routines for PGPtray's CBThook
HWND qyReadCurrentFocus(void);
void qySetHook(void);
void qyDeleteHook(void);

#ifdef __cplusplus
 }
#endif


#endif /* } */


