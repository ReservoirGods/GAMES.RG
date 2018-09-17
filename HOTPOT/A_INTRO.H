#ifndef	INCLUDED_A_INTRO_H
#define	INCLUDED_A_INTRO_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>

#include	<GODLIB\AUDIO\AUDIO.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eAINTRO_CHING,

	eAINTRO_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	AudioIntro_Init( void );
void	AudioIntro_DeInit( void );
void	AudioIntro_IntroInit( void );
void	AudioIntro_LevelInit( void );
void	AudioIntro_Update( void );

void	AudioIntro_PlaySample( const U16 aIndex );



/* ################################################################################ */

#endif	/*	INCLUDED_A_INTRO_H	*/ 