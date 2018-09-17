#ifndef	INCLUDED_R_FRONTEND_H
#define	INCLUDED_R_FRONTEND_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderFrontEnd_Init( void );
void	RenderFrontEnd_DeInit( void );
void	RenderFrontEnd_Update( void );

void	RenderFrontEnd_FadeIn( void );
void	RenderFrontEnd_FadeOut( void );

U16 *	RenderFrontEnd_GetpPal( void );

void	RenderFrontEnd_DisplayHelp( const U16 aIndex );
void	RenderFrontEnd_DisplayDialog( char * apTitle, char * apTxt );

void	RenderFrontEnd_ButtonDisable( const U16 aPageIndex, const U16 aButtonIndex );
void	RenderFrontEnd_ButtonEnable( const U16 aPageIndex, const U16 aButtonIndex );
void	RenderFrontEnd_DrawCredits( void );

void *	RenderFrontEnd_GetpButtonSprites( void );
 

/* ################################################################################ */

#endif	/*	INCLUDED_R_FRONTEND_H	*/