#ifndef	INCLUDED_A_SPL_H
#define	INCLUDED_A_SPL_H

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
	eASPL_PAN_RIGHT  = 0xFF,
	eASPL_PAN_CENTRE = 0x7F,
	eASPL_PAN_LEFT   = 0x00
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	AudioSample_Init( void );
void	AudioSample_DeInit( void );
void	AudioSample_Update( void );

void	AudioSample_QueueClear( void );

void	AudioSample_PlaySample( sAudioDmaSound * apSound, const U16 aPriority, const U8 aPan );
void	AudioSample_PlaySampleDirect( sAudioDmaSound * apSound, const U8 aPan );

void	AudioSample_Enable( void );
void	AudioSample_Disable( void );

/* ################################################################################ */

#endif	/*	INCLUDED_A_SPL_H	*/ 