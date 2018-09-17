#ifndef	INCLUDED_R_FADE_H
#define	INCLUDED_R_FADE_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderFade_Init( void );
void	RenderFade_DeInit( void );
 
void	RenderFade_Main( U16 * apPal, U16 aFrames );
void	RenderFade_Main2( U16 * apPal, U16 * apSrcPal2, U16 * apNewPal2, U16 * apDstPal2, U16 aFrames );

void	RenderFade_StartVblFade( U16 * apPal, const U16 aFrames );
U8		RenderFade_IsVblFadeFinished( void );


U16 *	RenderFade_GetpBlackPal( void );
U16 *	RenderFade_GetpWhitePal( void );


/* ################################################################################ */

#endif	/*	INCLUDED_R_FADE_H	*/