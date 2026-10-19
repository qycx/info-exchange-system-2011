
#include	"stdafx.h"
#include	"sp.h"



 __declspec(  dllexport  )  int spDisplay( DISPLAY_DEV *pDisplayDev, SP_STRUCT *pSp )		
{
	int			iErr		=	-1;
	Q_NODE	*	pQNode;

	if  (  pSp->bHideAll  )  return  0;
 
	for ( pQNode = pSp->pSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {

		spDisplayObj( pDisplayDev, ( SP_OBJ * )pQNode->qElemMemory.m_pBuf, 0 );

	}

	for ( pQNode = pSp->pNewSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {
		
		spDisplayObj( pDisplayDev, ( SP_OBJ * )pQNode->qElemMemory.m_pBuf, STATUS_SELECTED );
	
	}
			
	for ( pQNode = pSp->pSelectedSpObjQ->front.pNext; pQNode; pQNode = pQNode->pNext ) {

		spDisplayObj( pDisplayDev, ( SP_OBJ * )( ( SP_SELECT_Q_ELEM * )pQNode->qElemMemory.m_pBuf )->pQNode->qElemMemory.m_pBuf, STATUS_SELECTED );
	
	}



	/* if ( pSp->errNo ) */
	//  TextOut( pDisplayDev->hDc, 10, 10, pSp->info, lstrlen( pSp->info ) );
	RECT	rc;
	SetRect(  &rc,  0,  0,  100,  100  );
	DrawText(  pDisplayDev->hDc,  pSp->info,  lstrlen(  pSp->info  ),  &rc,  DT_LEFT  );
 
#ifdef __SP_DEBUG__
	if  (  0  )  {
		static int j = 0;
		char buf[256];
	
		j++;
		sprintf( buf, "OnDraw() is called %d times", j );
		//  TextOut( pDisplayDev->hDc, 10, 50, CString(  buf  ), strlen( buf ) );
		SetRect(  &rc,  10,  50,  100,  100  );
		DrawText(  pDisplayDev->hDc,  CString(  buf  ),  CString(  buf  ).GetLength(  ),  &rc,  DT_LEFT  );
	}

	//  TextOut( pDisplayDev->hDc, 10,30, CString(  debugStr  ), strlen( debugStr ) );
	SetRect(  &rc,  10,  30,  100,  100  );
	DrawText(  pDisplayDev->hDc,  CString(  debugStr  ),  strlen(  debugStr  ),  &rc,  DT_LEFT  );

#endif

	iErr  =  0;

errLabel:

	return iErr;

}

 

 int spDisplayObj( DISPLAY_DEV *pDisplayDev, SP_OBJ *pSpObj, int flag )
{

	 int iRet = -1;

	 if ( pSpObj->status & STATUS_INVALID ) return 0;

	 switch ( pSpObj->type ) {

		case SP_POINT_TYPE:

			iRet = spDisplayPoint( pDisplayDev, ( SP_POINT * )pSpObj, flag );

			break;

		case SP_SEGMENT_TYPE:

			iRet = spDisplaySegment( pDisplayDev, ( SP_SEGMENT * )pSpObj, flag );

			break;

		case SP_CIRCLE_TYPE:
			
			iRet = spDisplayCircle( pDisplayDev, ( SP_CIRCLE * )pSpObj, flag );

			break;

		case SP_ANGLE_BISECTOR_TYPE:

			iRet = spDisplayAngleBisector( pDisplayDev, ( SP_ANGLE_BISECTOR * )pSpObj, flag );
			
			break;

		default:

			break;

	 }

	
	return iRet;

}

 int spDisplayPoint( DISPLAY_DEV *pDisplayDev, SP_POINT *pSpPoint, int flag )
{
	 int iErr = 0;
	 HPEN hPen = NULL,oldhPen = NULL;


	 if ( flag & STATUS_SELECTED ) {
		
		 hPen = ::CreatePen( PS_SOLID, 2, RGB( 0, 0, 0 ) );
		 if ( !hPen ) { iErr = -1; goto err; }
		 oldhPen = ( HPEN )SelectObject( pDisplayDev->hDc, hPen );
		 if ( !oldhPen ) { iErr = -1; goto err; }
	 }

	 if ( FALSE == Ellipse( pDisplayDev->hDc,  
				pSpPoint->point.rect.x - SP_POINT_DIS_RANGE,
				pSpPoint->point.rect.y - SP_POINT_DIS_RANGE,
				pSpPoint->point.rect.x + SP_POINT_DIS_RANGE,
				pSpPoint->point.rect.y + SP_POINT_DIS_RANGE ) ) {
		 iErr = -1; goto err;
	 }
	
err:
	 if ( oldhPen ) SelectObject( pDisplayDev->hDc, oldhPen );
	 if ( hPen ) DeleteObject( hPen );
		
	 return iErr;
 

}

 int spDisplaySegment( DISPLAY_DEV *pDisplayDev, SP_SEGMENT *pSegment, int flag )
{

	 int iErr = 0;
 	 HPEN hPen = NULL,oldhPen = NULL;

 	 if ( flag & STATUS_SELECTED ) {
		
		 hPen = ::CreatePen( PS_SOLID, 2, RGB( 0, 0, 0 ) );
		 if ( !hPen ) { iErr = -1; goto err; }
		 oldhPen = ( HPEN )SelectObject( pDisplayDev->hDc, hPen );
		 if ( !oldhPen ) { iErr = -1; goto err; }
	 }

	MoveToEx( pDisplayDev->hDc, pSegment->point1.rect.x, pSegment->point1.rect.y, NULL );
	LineTo( pDisplayDev->hDc, pSegment->point2.rect.x, pSegment->point2.rect.y );
	 
#ifdef  __DEBUG__
		//  traceLogA(  "spDisplaySegment: (%d,%d) -> (%d,%d)",  pSegment->point1.rect.x,  pSegment->point1.rect.y,  pSegment->point2.rect.x,  pSegment->point2.rect.y  );
#endif

err:
	 if ( oldhPen ) SelectObject( pDisplayDev->hDc, oldhPen );
	 if ( hPen ) DeleteObject( hPen );

	return iErr;

}

 int spDisplayCircle( DISPLAY_DEV *pDisplayDev, SP_CIRCLE *pCircle, int flag )
{

	 int iErr = 0;
	 SP_POINT *pCenterPoint, *pCirclePoint;
 	 HPEN hPen = NULL,oldhPen = NULL;
	 HBRUSH hBrush = NULL, oldhBrush = NULL;
	 float r = 0.0;

 	 if ( flag & STATUS_SELECTED ) {
		
		 hPen = ::CreatePen( PS_SOLID, 2, RGB( 0, 0, 0 ) );
		 if ( !hPen ) { iErr = -1; goto err; }
		 oldhPen = ( HPEN )SelectObject( pDisplayDev->hDc, hPen );
		 if ( !oldhPen ) { iErr = -1; goto err; }
	 }

	 if ( !( hBrush = (  HBRUSH  )GetStockObject( NULL_BRUSH ) ) ) { 
		 iErr = -1; goto err; 
	 }
	 if ( !( oldhBrush = ( HBRUSH )SelectObject( pDisplayDev->hDc, hBrush ) ) ) { 
		 iErr = -1; goto err; 
	 }
	 

	 pCenterPoint = ( SP_POINT *)( ( Q_NODE * )( pCircle->pCenterQNode ) )->qElemMemory.m_pBuf;
	 pCirclePoint = ( SP_POINT *)( ( Q_NODE * )( pCircle->pCircleQNode ) )->qElemMemory.m_pBuf;
	 r = ( float )getDOf2SpPoints( pCenterPoint, pCirclePoint ) ;
	 Ellipse( pDisplayDev->hDc, ( int )( pCenterPoint->point.rect.x - r ), ( int )( pCenterPoint->point.rect.y - r ),
		 ( int )( pCenterPoint->point.rect.x + r ), ( int )( pCenterPoint->point.rect.y + r ) );
	

err:
	 if ( oldhBrush ) SelectObject ( pDisplayDev->hDc, oldhBrush );
	 if ( oldhPen ) SelectObject( pDisplayDev->hDc, oldhPen );
	 if ( hPen ) DeleteObject( hPen );

	return iErr;


}


  


  int spDisplayAngleBisector( DISPLAY_DEV *pDisplayDev, SP_ANGLE_BISECTOR *pSAB, int flag )
{
	 int iErr = 0;
	 SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )pDisplayDev->pSp;
	 if  (  !pSp  )  return  -1;
	 HPEN hPen = NULL,oldhPen = NULL;
	 SP_RECT_COORD tmpBorderPoint;

 	 if ( flag & STATUS_SELECTED ) {
		
		 hPen = ::CreatePen( PS_SOLID, 2, RGB( 0, 0, 0 ) );
		 if ( !hPen ) { iErr = -1; goto err; }
		 oldhPen = ( HPEN )SelectObject( pDisplayDev->hDc, hPen );
		 if ( !oldhPen ) { iErr = -1; goto err; }
	 }

	 getRayBorderPoint( &( ( SP_POINT * )pSAB->p2->qElemMemory.m_pBuf )->point.rect, &pSAB->rayPoint, pSp->spWidth, pSp->spHeight, &tmpBorderPoint );
	 	 
	 MoveToEx( pDisplayDev->hDc, ( ( SP_POINT * )pSAB->p2->qElemMemory.m_pBuf )->point.rect.x, ( ( SP_POINT * )pSAB->p2->qElemMemory.m_pBuf )->point.rect.y, NULL );
	 LineTo( pDisplayDev->hDc, tmpBorderPoint.x, tmpBorderPoint.y );
	 
err:
	 if ( oldhPen ) SelectObject( pDisplayDev->hDc, oldhPen );
	 if ( hPen ) DeleteObject( hPen );

	return iErr;

}

