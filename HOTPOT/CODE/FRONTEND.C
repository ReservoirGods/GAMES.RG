/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"FRONTEND.H"

#include	"BUILD.H"
#include	"DATALOG.H"
#include	"GAME.H"
#include	"KERNEL.H"

#include	"A_FE.H"
#include	"A_MAIN.H"
#include	"A_MUSIC.H"
#include	"A_SPL.H"

#include	"R_FE.H"

#include	<GODLIB\DEBUGLOG\DEBUGLOG.H>
#include	<GODLIB\FADE\FADE.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\INPUT\INPUT.H>
#include	<GODLIB\SCREEN\SCREEN.H>


/* ###################################################################################
#  DATA
################################################################################### */

sInput	gFrontEndInput;
sInput	gFrontEndInputIKBD;
sInput	gFrontEndInputPadA;
sInput	gFrontEndInputPadB;

U16				gFrontEndDest;
U16				gFrontEndPageIndex;

sFeButton		gFrontEndButtonsGame[    eFEBUTTON_GAME_LIMIT    ];
sFeButton		gFrontEndButtonsMain[    eFEBUTTON_MAIN_LIMIT    ];
sFeButton		gFrontEndButtonsOptions[ eFEBUTTON_OPTIONS_LIMIT ];
sFeButtonPage	gFrontEndPages[ eFE_PAGE_LIMIT ];

char *			gFrontEndGameControlSel[ eFEGAME_CONTROL_SEL_LIMIT ];
char *			gFrontEndGameTypeSel[ eFEGAME_CONTROL_SEL_LIMIT ];

char *			gFrontEndOptionsMusicSel[   eFEOPTIONS_MUSIC_SEL_LIMIT   ];
char *			gFrontEndOptionsSfxSel[     eFEOPTIONS_SFX_SEL_LIMIT     ];
char *			gFrontEndOptionsSpeakerSel[ eFEOPTIONS_SPEAKER_SEL_LIMIT ];

sTagString		gFrontEndMainTitles[ eFEBUTTON_MAIN_LIMIT ] =
{
	{	eFEBUTTON_MAIN_INFO,		"INFO"		},
	{	eFEBUTTON_MAIN_OPTIONS,		"OPTIONS"	},
	{	eFEBUTTON_MAIN_PLAY,		"PLAY"		},
	{	eFEBUTTON_MAIN_EXIT,		"EXIT"		},
};

sTagString		gFrontEndGameTitles[ eFEBUTTON_GAME_LIMIT ] =
{
	{	eFEBUTTON_GAME_TYPE,		"TYPE"		},
	{	eFEBUTTON_GAME_CONTROL,		"CONTROL"	},
	{	eFEBUTTON_GAME_PLAY,		"PLAY"		},
	{	eFEBUTTON_GAME_MENU,		"MENU"		},
};

sTagString		gFrontEndOptionsTitles[ eFEBUTTON_OPTIONS_LIMIT ] =
{
	{	eFEBUTTON_OPTIONS_MUSIC,	"MUSIC"		},
	{	eFEBUTTON_OPTIONS_SFX,		"SFX"		},
	{	eFEBUTTON_OPTIONS_SPEAKER,	"SPEAKER"	},
	{	eFEBUTTON_OPTIONS_MENU,		"MENU"		},
};

sTagString	gFrontEndGameTypeTxts[ eFEGAME_TYPE_SEL_LIMIT ] =
{
	{	eFEGAME_TYPE_SEL_A,	"GAME A"		},
	{	eFEGAME_TYPE_SEL_B,	"GAME B"		},
};

sTagString	gFrontEndGameControlTxts[ eFEGAME_CONTROL_SEL_LIMIT ] =
{
	{	eFEGAME_CONTROL_SEL_IKBD,	"KEYS"			},
	{	eFEGAME_CONTROL_SEL_JOY0,	"JOYSTICK 0"	},
	{	eFEGAME_CONTROL_SEL_JOY1,	"JOYSTICK 1"	},
	{	eFEGAME_CONTROL_SEL_PADA,	"JAG PAD A"		},
	{	eFEGAME_CONTROL_SEL_PADB,	"JAG PAD B"		},
};

sTagString	gFrontEndOptionsMusicTxts[ eFEOPTIONS_MUSIC_SEL_LIMIT ] =
{
	{	eFEOPTIONS_MUSIC_SEL_OFF,	"OFF"	},
	{	eFEOPTIONS_MUSIC_SEL_ON,	"ON"	},
};

sTagString	gFrontEndOptionsSfxTxts[ eFEOPTIONS_SFX_SEL_LIMIT ] =
{
	{	eFEOPTIONS_SFX_SEL_OFF,	"OFF"	},
	{	eFEOPTIONS_SFX_SEL_ON,	"ON"	},
};

sTagString	gFrontEndOptionsSpeakerTxts[ eFEOPTIONS_SPEAKER_SEL_LIMIT ] =
{
	{	eFEOPTIONS_SPEAKER_SEL_OFF,	"OFF"	},
	{	eFEOPTIONS_SPEAKER_SEL_ON,	"ON"	},
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	FrontEnd_GetOptions( void );
void	FrontEnd_SetOptions( void );
void	FrontEnd_CursorMove( const S16 aDir );
void	FrontEnd_SelectMove( const S16 aDir );

void	FrontEnd_DoInfo( void );
void	FrontEnd_InputInit( void );
void	FrontEnd_InputUpdate( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	FrontEnd_Init( void )
{
	U16	i,j;

	gFrontEndPages[ eFE_PAGE_INFO ].ButtonCount = 0;

	gFrontEndPages[ eFE_PAGE_MAIN ].ButtonCount = eFEBUTTON_MAIN_LIMIT;
	gFrontEndPages[ eFE_PAGE_MAIN ].pTitle      = "DOUBLE JUGGLE";
	gFrontEndPages[ eFE_PAGE_MAIN ].pButtons    = &gFrontEndButtonsMain[0];
	gFrontEndPages[ eFE_PAGE_MAIN ].CursorPos   = eFEBUTTON_MAIN_PLAY;

	gFrontEndPages[ eFE_PAGE_OPTIONS ].ButtonCount = eFEBUTTON_OPTIONS_LIMIT;
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pTitle      = "OPTIONS";
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons    = &gFrontEndButtonsOptions[0];
	gFrontEndPages[ eFE_PAGE_OPTIONS ].CursorPos   = eFEBUTTON_OPTIONS_MENU;

	gFrontEndPages[ eFE_PAGE_GAME ].ButtonCount = eFEBUTTON_GAME_LIMIT;
	gFrontEndPages[ eFE_PAGE_GAME ].pTitle      = "GAME";
	gFrontEndPages[ eFE_PAGE_GAME ].pButtons    = &gFrontEndButtonsGame[0];
	gFrontEndPages[ eFE_PAGE_GAME ].CursorPos   = eFEBUTTON_GAME_PLAY;

	for( i=0; i<eFE_PAGE_LIMIT; i++ )
	{
		for( j=0; j<gFrontEndPages[ i ].ButtonCount; j++ )
		{
			gFrontEndPages[ i ].pButtons[ j ].ChoiceCount  = 1;
			gFrontEndPages[ i ].pButtons[ j ].ppChoiceTxts = 0;
			gFrontEndPages[ i ].pButtons[ j ].SelectedFlag = 0;
			gFrontEndPages[ i ].pButtons[ j ].Type         = eFEBUTTYPE_LINK;
			gFrontEndPages[ i ].pButtons[ j ].Value        = 0;
			gFrontEndPages[ i ].pButtons[ j ].SubType      = eFE_SUBTYPE_NONE;
		}
		gFrontEndPages[ i ].RedrawFlag = 0;
	}

	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_TYPE    ].ppChoiceTxts = &gFrontEndGameTypeSel[ 0 ];
	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_CONTROL ].ppChoiceTxts = &gFrontEndGameControlSel[ 0 ];

	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_TYPE    ].Type = eFEBUTTYPE_SELECTION;
	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_CONTROL ].Type = eFEBUTTYPE_SELECTION;

	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_TYPE    ].ChoiceCount = eFEGAME_TYPE_SEL_LIMIT;
	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_CONTROL ].ChoiceCount = eFEGAME_CONTROL_SEL_LIMIT;

	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_TYPE    ].SubType = eFE_SUBTYPE_GAME;
	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_CONTROL ].SubType = eFE_SUBTYPE_CONTROLLER;

	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_MUSIC ].ppChoiceTxts = &gFrontEndOptionsMusicSel[ 0 ];
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SPEAKER ].ppChoiceTxts = &gFrontEndOptionsSpeakerSel[ 0 ];
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SFX ].ppChoiceTxts = &gFrontEndOptionsSfxSel[ 0 ];

	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_MUSIC   ].Type = eFEBUTTYPE_TOGGLE;
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SFX     ].Type = eFEBUTTYPE_TOGGLE;
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SPEAKER ].Type = eFEBUTTYPE_TOGGLE;

	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_MUSIC   ].ChoiceCount = eFEOPTIONS_MUSIC_SEL_LIMIT;
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SFX     ].ChoiceCount = eFEOPTIONS_SFX_SEL_LIMIT;
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SPEAKER ].ChoiceCount = eFEOPTIONS_SPEAKER_SEL_LIMIT;

	for( i=0; i<eFEBUTTON_MAIN_LIMIT; i++ )
	{
		gFrontEndButtonsMain[ i ].pTitleTxt    = sTagString_GetpString( i, gFrontEndMainTitles, eFEBUTTON_MAIN_LIMIT );
	}

	for( i=0; i<eFEBUTTON_OPTIONS_LIMIT; i++ )
	{
		gFrontEndButtonsOptions[ i ].pTitleTxt    = sTagString_GetpString( i, gFrontEndOptionsTitles, eFEBUTTON_OPTIONS_LIMIT );
	}
	for( i=0; i<eFEBUTTON_GAME_LIMIT; i++ )
	{
		gFrontEndButtonsGame[ i ].pTitleTxt    = sTagString_GetpString( i, gFrontEndGameTitles, eFEBUTTON_GAME_LIMIT );
	}


	for( i=0; i<eFEOPTIONS_MUSIC_SEL_LIMIT; i++ )
	{
		gFrontEndOptionsMusicSel[ i ] = sTagString_GetpString( i, &gFrontEndOptionsMusicTxts[0], eFEOPTIONS_MUSIC_SEL_LIMIT );
	}
	for( i=0; i<eFEOPTIONS_SFX_SEL_LIMIT; i++ )
	{
		gFrontEndOptionsSfxSel[ i ] = sTagString_GetpString( i, &gFrontEndOptionsSfxTxts[0], eFEOPTIONS_SFX_SEL_LIMIT );
	}
	for( i=0; i<eFEOPTIONS_SPEAKER_SEL_LIMIT; i++ )
	{
		gFrontEndOptionsSpeakerSel[ i ] = sTagString_GetpString( i, &gFrontEndOptionsSpeakerTxts[0], eFEOPTIONS_SPEAKER_SEL_LIMIT );
	}


	for( i=0; i<eFEGAME_TYPE_SEL_LIMIT; i++ )
	{
		gFrontEndGameTypeSel[ i ] = sTagString_GetpString( i, &gFrontEndGameTypeTxts[0], eFEGAME_TYPE_SEL_LIMIT );
	}

	for( i=0; i<eFEGAME_CONTROL_SEL_LIMIT; i++ )
	{
		gFrontEndGameControlSel[ i ] = sTagString_GetpString( i, &gFrontEndGameControlTxts[0], eFEGAME_CONTROL_SEL_LIMIT );
	}

	gFrontEndInputIKBD.mScanCodes[ eINPUTKEY_LEFT  ]  = eIKBDSCAN_LEFTARROW;
	gFrontEndInputIKBD.mScanCodes[ eINPUTKEY_RIGHT ] = eIKBDSCAN_RIGHTARROW;
	gFrontEndInputIKBD.mScanCodes[ eINPUTKEY_DOWN  ] = eIKBDSCAN_DOWNARROW;
	gFrontEndInputIKBD.mScanCodes[ eINPUTKEY_UP    ] = eIKBDSCAN_UPARROW;
	gFrontEndInputIKBD.mScanCodes[ eINPUTKEY_FIREA ] = eIKBDSCAN_SPACE;
	gFrontEndInputIKBD.mScanCodes[ eINPUTKEY_FIREB ] = eIKBDSCAN_UNDO;
	gFrontEndInputIKBD.mScanCodes[ eINPUTKEY_QUIT  ] = eIKBDSCAN_F10;
	gFrontEndInputIKBD.mInputType                       = eINPUTTYPE_IKBD;
	gFrontEndInputPadA.mInputType                       = eINPUTTYPE_PADA;
	gFrontEndInputPadB.mInputType                       = eINPUTTYPE_PADB;

	FrontEnd_InputInit();
	FrontEnd_InputUpdate();

	gFrontEndPageIndex = eFE_PAGE_MAIN;

	RenderFrontEnd_Init();
	AudioFrontEnd_Init();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	FrontEnd_DeInit( void )
{
	RenderFrontEnd_DeInit();
	AudioFrontEnd_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_Main( void )
* ACTION   : main frontend loop
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	FrontEnd_Main( void )
{
	U16	lExitFlag;

	DebugLog_Printf0( "FrontEnd_Main" );

	lExitFlag = 0;

	FrontEnd_GetOptions();
	FrontEnd_SetOptions();

	Fade_Main( Fade_GetpBlackPal(), 16 );
	FrontEnd_SetPageIndex( eFE_PAGE_MAIN );

	while( !lExitFlag )
	{
		Screen_Update();
		RenderFrontEnd_Update();
		FrontEnd_InputUpdate();

		if( gFrontEndInput.mKeyStatus[ eINPUTKEY_UP ] & eINPUTKEYSTATUS_HIT )
		{
			FrontEnd_CursorMove( -1 );
		}

		if( gFrontEndInput.mKeyStatus[ eINPUTKEY_DOWN ] & eINPUTKEYSTATUS_HIT )
		{
			FrontEnd_CursorMove( 1 );
		}

		if( gFrontEndInput.mKeyStatus[ eINPUTKEY_LEFT ] & eINPUTKEYSTATUS_HIT )
		{
			FrontEnd_SelectMove( -1 );
		}

		if( gFrontEndInput.mKeyStatus[ eINPUTKEY_RIGHT ] & eINPUTKEYSTATUS_HIT )
		{
			FrontEnd_SelectMove( 1 );
		}

		if( gFrontEndInput.mKeyStatus[ eINPUTKEY_FIREB ] & eINPUTKEYSTATUS_HIT )
		{
			switch( FrontEnd_GetPageIndex() )
			{
			case	eFE_PAGE_GAME:
				FrontEnd_SetPageIndex( eFE_PAGE_MAIN );
				break;
			case	eFE_PAGE_INFO:
				FrontEnd_SetPageIndex( eFE_PAGE_MAIN );
				break;
			case	eFE_PAGE_OPTIONS:
				FrontEnd_SetPageIndex( eFE_PAGE_MAIN );
				break;
			}
		}
		else if( gFrontEndInput.mKeyStatus[ eINPUTKEY_FIREA ] & eINPUTKEYSTATUS_HIT )
		{
			switch( FrontEnd_GetpCurrentButton()->Type )
			{
			case	eFEBUTTYPE_SELECTION:
			case	eFEBUTTYPE_TOGGLE:
				FrontEnd_SelectMove( 1 );
				break;

			case	eFEBUTTYPE_LINK:

				switch( FrontEnd_GetPageIndex() )
				{

				case	eFE_PAGE_MAIN:
					switch( FrontEnd_GetButtonIndex() )
					{
					case	eFEBUTTON_MAIN_INFO:
						FrontEnd_DoInfo();
						break;
					case	eFEBUTTON_MAIN_OPTIONS:
						FrontEnd_SetPageIndex( eFE_PAGE_OPTIONS );
						break;
					case	eFEBUTTON_MAIN_PLAY:
						FrontEnd_SetPageIndex( eFE_PAGE_GAME );
						break;
					case	eFEBUTTON_MAIN_EXIT:
						lExitFlag = 1;
						HotPotKernel_RequestShutdown();
						break;
					}
					break;

				case	eFE_PAGE_OPTIONS:
					switch( FrontEnd_GetButtonIndex() )
					{
					case	eFEBUTTON_OPTIONS_MENU:
						FrontEnd_SetPageIndex( eFE_PAGE_MAIN );
						break;
					}
					break;

				case	eFE_PAGE_GAME:
					switch( FrontEnd_GetButtonIndex() )
					{
					case	eFEBUTTON_GAME_PLAY:
						lExitFlag = 1;
						break;

					case	eFEBUTTON_GAME_MENU:
						FrontEnd_SetPageIndex( eFE_PAGE_MAIN );
						break;


					}
					break;


				}

				break;
			}
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_GetButtonIndex( void )
* ACTION   : returns current cursor index
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16		FrontEnd_GetButtonIndex( void )
{
	return( gFrontEndPages[ gFrontEndPageIndex ].CursorPos );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_SetButtonIndex( U16 aIndex )
* ACTION   : sets current cursor pos
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	FrontEnd_SetButtonIndex( U16 aIndex )
{
	gFrontEndPages[ gFrontEndPageIndex ].CursorPos = aIndex;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_GetPageIndex( void )
* ACTION   : returns curretn page index
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16			FrontEnd_GetPageIndex( void )
{
	return( gFrontEndPageIndex );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_SetPageIndex( const U16 aPageIndex )
* ACTION   : sets page index
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void		FrontEnd_SetPageIndex( const U16 aPageIndex )
{
	AudioFrontEnd_PlaySampleDirect( eAFRONTEND_MENU_ENTER, eASPL_PAN_CENTRE );
	gFrontEndPageIndex = aPageIndex;
	gFrontEndPages[ gFrontEndPageIndex ].RedrawFlag = 2;

	FrontEnd_GetpCurrentButton()->RedrawFlag   = 2;
	FrontEnd_GetpCurrentButton()->SelectedFlag = 1;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_GetpPage( const U16 aPageIndex )
* ACTION   : returns pointer to page aPageIndex
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

sFeButtonPage *	FrontEnd_GetpPage( const U16 aPageIndex )
{
	return( &gFrontEndPages[ aPageIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_GetpButton( const U16 aPageIndex, const U16 aButtonIndex )
* ACTION   : returns pointer to button aButtonIndex on page aPageIndex
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

sFeButton	 *	FrontEnd_GetpButton( const U16 aPageIndex, const U16 aButtonIndex )
{
	return( &gFrontEndPages[ aPageIndex ].pButtons[ aButtonIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_GetpCurrentPage( void )
* ACTION   : returns pointer to current page
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

sFeButtonPage *	FrontEnd_GetpCurrentPage( void )
{
	return( &gFrontEndPages[ gFrontEndPageIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_GetpCurrentButton( void )
* ACTION   : returns pointer to current page
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

sFeButton	 *	FrontEnd_GetpCurrentButton( void )
{
	return( &gFrontEndPages[ gFrontEndPageIndex ].pButtons[ gFrontEndPages[ gFrontEndPageIndex ].CursorPos ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_CursorMove( const S16 aDir )
* ACTION   : moves cursor
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	FrontEnd_CursorMove( const S16 aDir )
{
	sFeButton *	lpButton;
	S16			lButtonIndex;

	AudioFrontEnd_PlaySampleDirect( eAFRONTEND_CURSOR_MOVE, eASPL_PAN_CENTRE );

	lButtonIndex = FrontEnd_GetButtonIndex();
	lpButton     = FrontEnd_GetpCurrentButton();

	lpButton->SelectedFlag = 0;
	lpButton->RedrawFlag   = 2;

	lButtonIndex += aDir;

	if( lButtonIndex < 0 )
	{
		lButtonIndex = 0;
	}

	if( lButtonIndex >= (S16)gFrontEndPages[ gFrontEndPageIndex ].ButtonCount )
	{
		lButtonIndex = gFrontEndPages[ gFrontEndPageIndex ].ButtonCount-1;
	}

	FrontEnd_SetButtonIndex( lButtonIndex );
	lpButton     = FrontEnd_GetpCurrentButton();

	lpButton->SelectedFlag = 1;
	lpButton->RedrawFlag   = 2;

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_SelectMove( const S16 aDir )
* ACTION   : moves selection
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	FrontEnd_SelectMove( const S16 aDir )
{
	S16			lButtonIndex;
	S16			lChoice;

	AudioFrontEnd_PlaySampleDirect( eAFRONTEND_ITEM_SELECT, eASPL_PAN_CENTRE );

	lButtonIndex = gFrontEndPages[ gFrontEndPageIndex ].CursorPos;

	gFrontEndPages[ gFrontEndPageIndex ].pButtons[ lButtonIndex ].SelectedFlag = 1;
	gFrontEndPages[ gFrontEndPageIndex ].pButtons[ lButtonIndex ].RedrawFlag   = 2;

	if( (gFrontEndPages[ gFrontEndPageIndex ].pButtons[ lButtonIndex ].Type == eFEBUTTYPE_SELECTION )
		|| (gFrontEndPages[ gFrontEndPageIndex ].pButtons[ lButtonIndex ].Type == eFEBUTTYPE_TOGGLE )
		)
	{
		lChoice  = gFrontEndPages[ gFrontEndPageIndex ].pButtons[ lButtonIndex ].Value;
		lChoice += aDir;
		if( lChoice < 0 )
		{
			lChoice = gFrontEndPages[ gFrontEndPageIndex ].pButtons[ lButtonIndex ].ChoiceCount-1;
		}
		if( lChoice >= (S16)gFrontEndPages[ gFrontEndPageIndex ].pButtons[ lButtonIndex ].ChoiceCount )
		{
			lChoice = 0;
		}
		gFrontEndPages[ gFrontEndPageIndex ].pButtons[ lButtonIndex ].Value = lChoice;
	}
	FrontEnd_SetOptions();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void FrontEnd_DoInfo(void)
* ACTION   : FrontEnd_DoInfo
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void FrontEnd_DoInfo(void)
{
	U8	lExitFlag;

	RenderFrontEnd_DrawCredits();
	FrontEnd_InputUpdate();

	lExitFlag = 0;
	while( !lExitFlag )
	{
		Screen_Update();
		FrontEnd_InputUpdate();
		if( gFrontEndInput.mKeyStatus[ eINPUTKEY_FIREA ] & eINPUTKEYSTATUS_HIT )
		{
			lExitFlag = 1;
		}
	}
	Fade_Main( Fade_GetpBlackPal(), 16 );
	FrontEnd_SetPageIndex( eFE_PAGE_MAIN );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void FrontEnd_InputUpdate(void)
* ACTION   : FrontEnd_InputUpdate
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void FrontEnd_InputUpdate(void)
{
	U16	i;

	IKBD_Update();

	Input_Update( &gFrontEndInputIKBD );
	Input_Update( &gFrontEndInputPadA );
	Input_Update( &gFrontEndInputPadB );

	for( i=0; i<eINPUTKEY_LIMIT; i++ )
	{
		if( gFrontEndInputIKBD.mKeyStatus[ i ] )
		{
			gFrontEndInput.mKeyStatus[ i ] = gFrontEndInputIKBD.mKeyStatus[ i ];
		}
		else if( gFrontEndInputPadA.mKeyStatus[ i ] )
		{
			gFrontEndInput.mKeyStatus[ i ] = gFrontEndInputPadA.mKeyStatus[ i ];
		}
		else if( gFrontEndInputPadB.mKeyStatus[ i ] )
		{
			gFrontEndInput.mKeyStatus[ i ] = gFrontEndInputPadB.mKeyStatus[ i ];
		}
		else
		{
			gFrontEndInput.mKeyStatus[ i ] = eINPUTKEYSTATUS_NONE;
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void FrontEnd_InputInit(void)
* ACTION   : FrontEnd_InputInit
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void FrontEnd_InputInit(void)
{
	Input_Init( &gFrontEndInputIKBD );
	Input_Init( &gFrontEndInputPadA );
	Input_Init( &gFrontEndInputPadB );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_GetOptions( void )
* ACTION   : gets options from datalog
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	FrontEnd_GetOptions( void )
{
	U16	lControl;

	lControl = (U16)DataLog_GetEntry( eDATALOG_CONTROL );
	switch( lControl )
	{
	case eINPUTTYPE_IKBD:
		lControl = eFEGAME_CONTROL_SEL_IKBD;
		break;
	case eINPUTTYPE_MOUSE:
		lControl = eFEGAME_CONTROL_SEL_IKBD;
		break;
	case eINPUTTYPE_JOY0:
		lControl = eFEGAME_CONTROL_SEL_JOY0;
		break;
	case eINPUTTYPE_JOY1:
		lControl = eFEGAME_CONTROL_SEL_JOY1;
		break;
	case eINPUTTYPE_PADA:
		lControl = eFEGAME_CONTROL_SEL_PADA;
		break;
	case eINPUTTYPE_PADB:
		lControl = eFEGAME_CONTROL_SEL_PADB;
		break;
	default:
		lControl = eFEGAME_CONTROL_SEL_IKBD;
		break;
	}
	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_CONTROL ].Value = lControl;
	gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_TYPE ].Value = (U16)DataLog_GetEntry( eDATALOG_GAMETYPE );

	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_MUSIC   ].Value = (U16)DataLog_GetEntry( eDATALOG_MUSICONFLAG   );
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SFX     ].Value = (U16)DataLog_GetEntry( eDATALOG_SFXONFLAG     );
	gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SPEAKER ].Value = (U16)DataLog_GetEntry( eDATALOG_SPEAKERONFLAG );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : FrontEnd_SetOptions( void )
* ACTION   : sets options in datalog
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	FrontEnd_SetOptions( void )
{
	U32	lControl;

	switch( gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_CONTROL ].Value )
	{
		case eFEGAME_CONTROL_SEL_IKBD:
			lControl = eINPUTTYPE_IKBD;
			break;
		case eFEGAME_CONTROL_SEL_JOY0:
			lControl = eINPUTTYPE_JOY0;
			break;
		case eFEGAME_CONTROL_SEL_JOY1:
			lControl = eINPUTTYPE_JOY1;
			break;
		case eFEGAME_CONTROL_SEL_PADA:
			lControl = eINPUTTYPE_PADA;
			break;
		case eFEGAME_CONTROL_SEL_PADB:
			lControl = eINPUTTYPE_PADB;
			break;
		default:
			lControl = eINPUTTYPE_IKBD;
			break;
	}
	DataLog_SetEntry( eDATALOG_CONTROL, lControl );

	DataLog_SetEntry( eDATALOG_GAMETYPE,   gFrontEndPages[ eFE_PAGE_GAME ].pButtons[ eFEBUTTON_GAME_TYPE ].Value );

	DataLog_SetEntry( eDATALOG_MUSICONFLAG,   gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_MUSIC ].Value );
	DataLog_SetEntry( eDATALOG_SFXONFLAG,     gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SFX   ].Value );
	DataLog_SetEntry( eDATALOG_SPEAKERONFLAG, gFrontEndPages[ eFE_PAGE_OPTIONS ].pButtons[ eFEBUTTON_OPTIONS_SPEAKER ].Value );

	if( DataLog_GetEntry( eDATALOG_SPEAKERONFLAG ) )
	{
		AudioMain_SpeakerEnable();
	}
	else
	{
		AudioMain_SpeakerDisable();
	}

	if( DataLog_GetEntry( eDATALOG_MUSICONFLAG ) )
	{
		AudioMusic_Enable();
	}
	else
	{
		AudioMusic_Disable();
	}
}


/* ################################################################################ */
