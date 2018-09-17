#ifndef	INCLUDED_R_TEXT_H
#define	INCLUDED_R_TEXT_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>
#include	<GODLIB\SCREEN\SCREEN.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eRFONT_FE,
	eRFONT_HISCORE,

	eRFONT_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderFont_Init( void );
void	RenderFont_DeInit( void );
 
U16		RenderFont_GetWidth( const U16 aFontType, const char * apTxt );
void	RenderFont_Print( const U16 aFont, const char * apString, sGraphicCanvas * apCanvas, const S16 aX, const S16 aY );


/* ################################################################################ */

#endif	/*	INCLUDED_R_TEXT_H	*/