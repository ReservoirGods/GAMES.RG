#ifndef	INCLUDED_A_FRONTEND_H
#define	INCLUDED_A_FRONTEND_H

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
	eAFRONTEND_CURSOR_MOVE,
	eAFRONTEND_MENU_ENTER,
	eAFRONTEND_MENU_LEAVE,
	eAFRONTEND_ITEM_SELECT,

	eAFRONTEND_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	AudioFrontEnd_Init( void );
void	AudioFrontEnd_DeInit( void );
void	AudioFrontEnd_FrontEndInit( void );
void	AudioFrontEnd_LevelInit( void );
void	AudioFrontEnd_Update( void );

void	AudioFrontEnd_PlaySample( const U16 aIndex, const U16 aPriority, const U8 aPan );
void	AudioFrontEnd_PlaySampleDirect( const U16 aIndex, const U8 aPan );

U8		AudioFrontEnd_GetTilePan( const U16 aBoardIndex, const U16 aTileCol );
U8		AudioFrontEnd_GetBoardPan( const U16 aBoardIndex );


/* ################################################################################ */

#endif	/*	INCLUDED_A_FRONTEND_H	*/ 