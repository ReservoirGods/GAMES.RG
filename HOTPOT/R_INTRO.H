#ifndef	INCLUDED_R_INTRO_H
#define	INCLUDED_R_INTRO_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eRINTRO_TEAMHOT,	
	eRINTRO_PRESENTS,
	eRINTRO_RGPROD,
	eRINTRO_DBLOGO,
	eRINTRO_VBLOGO,
	eRINTRO_THIS,

	eRINTRO_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderIntro_Init( void );
void	RenderIntro_DeInit( void );
void	RenderIntro_Update( void );

void	RenderIntro_RgFadeIn( const U16 aIndex );

 
/* ################################################################################ */

#endif	/*	INCLUDED_R_INTRO_H	*/