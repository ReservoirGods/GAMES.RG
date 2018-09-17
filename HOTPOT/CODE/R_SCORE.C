/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_INTRO.H"

#include	"R_FONT.H"

#include	"BUILD.H"
#include	"GAME.H"
#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	<GODLIB\DEBUGLOG\DEBUGLOG.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\GRAPHIC\GRAPHIC.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dRSCORE_X		11
#define	dRSCORE_Y		22

#define	dRSCORE_FONT	eRFONT_DARK0


/* ###################################################################################
#  DATA
################################################################################### */

sSpriteBlock *	gpRScoreLedFont;
sGraphicCanvas	gRScoreCanvas;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		RenderScore_Load( void );
U8		RenderScore_UnLoad( void );

void	RenderScore_Print( char * apString, sGraphicCanvas * apCanvas, S16 aX, S16 aY );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderScore_Init( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderScore_Init( void )
{
	Resource_Attach( eSECTION_GLOBAL, RenderScore_Load, RenderScore_UnLoad );
	GraphicCanvas_Init( &gRScoreCanvas, eGRAPHIC_COLOURMODE_4PLANE, 320, 200 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderScore_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderScore_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderScore_GameInit( void )
* ACTION   : called at start of level
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderScore_GameInit( void )
{	
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderScore_LevelInit( void )
* ACTION   : called at start of level
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderScore_LevelInit( void )
{	
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderScore_Update( void )
* ACTION   : called at end of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderScore_Update( void )
{
	char			lString[ 8 ];
	sGraphicRect	lRect;
	sGraphicPos		lPos;

	lPos.mX       = dRSCORE_X;
	lPos.mY       = dRSCORE_Y;

	lRect.mX      = dRSCORE_X;
	lRect.mY      = dRSCORE_Y;
	lRect.mWidth  = (10*3);
	lRect.mHeight = gpRScoreLedFont->mpSprite[ 0 ]->mHeight;

	sprintf( lString, "%03d", Player_GetpPlayer()->Score );

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	gRScoreCanvas.mpVRAM = Screen_GetpBack();
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		&gRScoreCanvas );
		
	RenderScore_Print( lString, Screen_GetpLogicGraphic(), dRSCORE_X, dRSCORE_Y );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderScore_Print(char * apString,sGraphicCanvas * apCanvas,S16 aX,S16 aY)
* ACTION   : RenderScore_Print
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderScore_Print(char * apString,sGraphicCanvas * apCanvas,S16 aX,S16 aY)
{
	sGraphicPos	lPos;
	U8			lNum;
	U8			lLen;


/*	RenderScreen_GetpGraphic()->mpVRAM = apScreen;
*/

	lPos.mX = aX;
	lPos.mY = aY;

	lLen = 0;

	while( apString[ lLen ] )
	{
		lLen++;
	}

	if( lLen > 3 )
	{
		lLen = 3;
	}

	lLen = 3-lLen;

	lPos.mX += lLen * 10;

	while( *apString )
	{
		lNum  = *apString++;
		lNum -= '0';

		if( lNum <= 9 )
		{
		apCanvas->mpFuncs->DrawSprite(
			apCanvas,
			&lPos,
			gpRScoreLedFont->mpSprite[ lNum ] );

		}

		lPos.mX += 10;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderScore_Load( void )
* ACTION   : loads all resources for score
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderScore_Load( void )
{
	gpRScoreLedFont = Resource_Load( "LEDNUMS.BSB", 0 );

	Sprite_BlockRelocate( gpRScoreLedFont );

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderScore_UnLoad( void )
* ACTION   : releases memory used by score
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderScore_UnLoad( void )
{
	Resource_UnLoad( gpRScoreLedFont );

	return( 1 );
}


/* ################################################################################ */
