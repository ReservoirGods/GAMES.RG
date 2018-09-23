/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_HISCOR.H"

#include	"R_FE.H"
#include	"R_FONT.H"

#include	"BUILD.H"
#include	"DATALOG.H"
#include	"HISCORE.H"
#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	<GODLIB\FADE\FADE.H>
#include	<GODLIB\INPUT\INPUT.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\PICTYPES\DEGAS.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dRHISCORE_ENTRY_Y		20
#define	dRHISCORE_ENTRY_HEIGHT	14
#define	dRHISCORE_SPEED			2
#define	dRHISCORE_FONT			eRFONT_HISCORE
#define	dRHISCORE_TITLE_FONT	eRFONT_HISCORE
#define	dRHISCORE_NAME_FONT		eRFONT_HISCORE
#define	dRHISCORE_SCORE_FONT	eRFONT_HISCORE

#define	dRHISCORE_TITLE_Y		10
#define	dRHISCORE_ENTRY_Y0		40
#define	dRHISCORE_ENTRY_Y1		180
#define	dRHISCORE_NAME_X		64
#define	dRHISCORE_SCORE_X		(320-64)


/* ###################################################################################
#  DATA
################################################################################### */

sDegas *	gpRHiScoreBG;

sTagString	gRHiScoreTableNames[ eHISCORE_TABLE_LIMIT ] =
{
	{	eHISCORE_TABLE_A,	"GAME A"	},
	{	eHISCORE_TABLE_B,	"GAME B"	},
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		RenderHiScore_Load( void );
U8		RenderHiScore_UnLoad( void );

void	RenderHiScore_DrawBackground( U16 aTableIndex, sGraphicCanvas * apCanvas );

/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderHiScore_Init( void )
* ACTION   : called at start of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderHiScore_Init( void )
{
	Resource_Attach( eSECTION_GLOBAL, RenderHiScore_Load, RenderHiScore_UnLoad );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderHiScore_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderHiScore_DeInit( void )
{
}



/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderHiScore_Update( void )
* ACTION   : called at every frame
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderHiScore_Update( void )
{
}

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderHiScore_Main( const U16 aTableIndex )
* ACTION   : main hiscore loop
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderHiScore_Main( const U16 aTableIndex )
{	
	U8	lExitFlag;
	U16	lTableIndex;

	(void)aTableIndex;
	lTableIndex = (U16)DataLog_GetEntry( eDATALOG_GAMETYPE );

/*	RenderScreen_ClearScreen( RenderScreen_GetpBack() );*/
	Screen_GetpBackGraphic()->mpFuncs->ClearScreen( Screen_GetpBackGraphic() );
	RenderHiScore_DrawBackground( lTableIndex, Screen_GetpBackGraphic() );
/*	RenderScreen_CopyScreen( RenderScreen_GetpBack(), RenderScreen_GetpLogic() );*/
	Screen_GetpBackGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(), Screen_GetpBack() );
	Screen_Update();
/*	RenderScreen_CopyScreen( RenderScreen_GetpBack(), RenderScreen_GetpLogic() );*/
	Screen_GetpBackGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(), Screen_GetpBack() );
	Fade_Main( RenderFrontEnd_GetpPal(), 16 );

	Player_InputUpdate();

	lExitFlag = 0;
	while( !lExitFlag )
	{
		Screen_Update();
		RenderHiScore_Update();
		Player_InputUpdate();

		if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_FIREA ] & eINPUTKEYSTATUS_HIT )
		{
			lExitFlag = 1;
		}
		if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_FIREB ] & eINPUTKEYSTATUS_HIT )
		{
			lExitFlag = 1;
		}
		if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_QUIT ] & eINPUTKEYSTATUS_HIT )
		{
			lExitFlag = 1;
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderHiScore_DrawBackground(U16 aTableIndex,U16 * apScreen)
* ACTION   : RenderHiScore_DrawBackground
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderHiScore_DrawBackground(U16 aTableIndex,sGraphicCanvas * apCanvas)
{
	char	lString[ 32 ];
	char *	lpTitle;
	U16	i;
	S16	lX;
	S16	lY;

/*	RenderScreen_CopyScreen( &gpRHiScoreBG->mPixels[ 0 ], apScreen );*/
	apCanvas->mpFuncs->CopyScreen( apCanvas, &gpRHiScoreBG->mPixels[ 0 ] );

	lpTitle = sTagString_GetpString( aTableIndex, &gRHiScoreTableNames[ 0 ], eHISCORE_TABLE_LIMIT );

	lY  = dRHISCORE_ENTRY_Y0;
	lX  = 160 - (RenderFont_GetWidth( dRHISCORE_TITLE_FONT, lpTitle)>>1);

	RenderFont_Print( dRHISCORE_TITLE_FONT, lpTitle, apCanvas, lX, dRHISCORE_TITLE_Y );

	lY = dRHISCORE_ENTRY_Y0;
	for( i=0; i<dHISCORE_ENTRY_LIMIT; i++ )
	{
		RenderFont_Print( dRHISCORE_TITLE_FONT, &HiScore_GetpEntry( aTableIndex, i )->Name[ 0 ], apCanvas, dRHISCORE_NAME_X, lY );

		sprintf( lString, "%ld", HiScore_GetpEntry( aTableIndex, i )->Score );


		lX = dRHISCORE_SCORE_X - RenderFont_GetWidth( dRHISCORE_SCORE_FONT, lString );
		RenderFont_Print( dRHISCORE_SCORE_FONT, lString, apCanvas, lX, lY );

		lY += (dRHISCORE_ENTRY_Y1-dRHISCORE_ENTRY_Y0)/dHISCORE_ENTRY_LIMIT;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderHiScore_Load( void )
* ACTION   : loads all resources for HiScore
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderHiScore_Load( void )
{
	gpRHiScoreBG = Resource_Load( "BORDER.PI1", 0 );

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderHiScore_UnLoad( void )
* ACTION   : releases memory used by HiScore
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderHiScore_UnLoad( void )
{
	Resource_UnLoad( gpRHiScoreBG );

	return( 1 );
}


/* ################################################################################ */
