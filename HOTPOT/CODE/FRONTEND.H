#ifndef	INCLUDED_FRONTEND_H
#define	INCLUDED_FRONTEND_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUMS
################################################################################### */


enum
{
	eFEBUTTYPE_LINK,
	eFEBUTTYPE_SELECTION,
	eFEBUTTYPE_TOGGLE,

	eFEBUTTYPE_LIMIT
};

enum
{
	eFE_SUBTYPE_NONE,
	eFE_SUBTYPE_GAME,
	eFE_SUBTYPE_CONTROLLER,

	eFE_SUBTYPE_LIMIT
};

enum
{
	eFE_PAGE_MAIN,
	eFE_PAGE_INFO,
	eFE_PAGE_OPTIONS,
	eFE_PAGE_GAME,

	eFE_PAGE_LIMIT
};


enum
{
	eFEGAME_CONTROL_SEL_IKBD,
	eFEGAME_CONTROL_SEL_JOY0,
	eFEGAME_CONTROL_SEL_JOY1,
	eFEGAME_CONTROL_SEL_PADA,
	eFEGAME_CONTROL_SEL_PADB,

	eFEGAME_CONTROL_SEL_LIMIT
};

enum
{
	eFEGAME_TYPE_SEL_A,
	eFEGAME_TYPE_SEL_B,

	eFEGAME_TYPE_SEL_LIMIT
};

enum
{
	eFEOPTIONS_MUSIC_SEL_OFF,
	eFEOPTIONS_MUSIC_SEL_ON,

	eFEOPTIONS_MUSIC_SEL_LIMIT
};

enum
{
	eFEOPTIONS_SFX_SEL_OFF,
	eFEOPTIONS_SFX_SEL_ON,

	eFEOPTIONS_SFX_SEL_LIMIT
};

enum
{
	eFEOPTIONS_SPEAKER_SEL_OFF,
	eFEOPTIONS_SPEAKER_SEL_ON,

	eFEOPTIONS_SPEAKER_SEL_LIMIT
};


enum
{
	eFEOPTIONS_SPEED_SEL_SLOW,
	eFEOPTIONS_SPEED_SEL_NORMAL,
	eFEOPTIONS_SPEED_SEL_FAST,

	eFEOPTIONS_SPEED_SEL_LIMIT
};



enum
{
	eFEBUTTON_MAIN_INFO,
	eFEBUTTON_MAIN_OPTIONS,
	eFEBUTTON_MAIN_PLAY,
	eFEBUTTON_MAIN_EXIT,

	eFEBUTTON_MAIN_LIMIT
};

enum
{
	eFEBUTTON_OPTIONS_MUSIC,
	eFEBUTTON_OPTIONS_SFX,
	eFEBUTTON_OPTIONS_SPEAKER,

	eFEBUTTON_OPTIONS_MENU,

	eFEBUTTON_OPTIONS_LIMIT
};

enum
{
	eFEBUTTON_GAME_TYPE,
	eFEBUTTON_GAME_CONTROL,
	eFEBUTTON_GAME_PLAY,
	eFEBUTTON_GAME_MENU,

	eFEBUTTON_GAME_LIMIT
};


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	U16		Type;
	U16		Value;
	U16		SelectedFlag;
	U16		ChoiceCount;
	U16		RedrawFlag;
	U32		SubType;
	char *	pTitleTxt;
	char **	ppChoiceTxts;
} sFeButton;


typedef	struct
{
	U16			CursorPos;
	U16			ButtonCount;
	U16			RedrawFlag;
	char *		pTitle;
	sFeButton *	pButtons;
} sFeButtonPage;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void			FrontEnd_Init( void );
void			FrontEnd_DeInit( void );
void			FrontEnd_Main( void );

U16				FrontEnd_GetButtonIndex( void );
void			FrontEnd_SetButtonIndex( U16 aIndex );

U16				FrontEnd_GetPageIndex( void );
void			FrontEnd_SetPageIndex( const U16 aPageIndex );

sFeButtonPage *	FrontEnd_GetpPage( const U16 aPageIndex );
sFeButton	 *	FrontEnd_GetpButton( const U16 aPageIndex, const U16 ButtonIndex );

sFeButtonPage *	FrontEnd_GetpCurrentPage( void );
sFeButton	 *	FrontEnd_GetpCurrentButton( void );

U16				FrontEnd_GetDestination( void );
void			FrontEnd_SetDestination( const U16 aDest );


/* ################################################################################ */

#endif	/*	INCLUDED_FRONTEND_H	*/