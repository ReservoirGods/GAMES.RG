#ifndef	INCLUDED_A_MUSIC_H
#define	INCLUDED_A_MUSIC_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eAMUSIC_SONG_MAIN,

	eAMUSIC_SONG_LIMIT
};

enum
{
	eAMUSIC_VOICESET_GENERAL,

	eAMUSIC_VOICESET_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	AudioMusic_Init( void );
void	AudioMusic_DeInit( void );
void	AudioMusic_Update( void );

void	AudioMusic_PlayTune( U16 aVoiceSetID, U16 aSongID );
void	AudioMusic_StopTune( void );
 
void	AudioMusic_Enable( void );
void	AudioMusic_Disable( void );


/* ################################################################################ */

#endif	/*	INCLUDED_A_MUSIC_H	*/ 