/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_PAUSE.H"

#include	"R_FE.H"

#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dRPAUSE_X		(148-40)
#define	dRPAUSE_Y		0

#define	dRPAUSE_BUTTON_X	258
#define	dRPAUSE_BUTTON_Y	39

#define	dRPAUSE_CLEAR_X			54
#define	dRPAUSE_CLEAR_Y			0
#define	dRPAUSE_CLEAR_WIDTH		192	
#define	dRPAUSE_CLEAR_HEIGHT	21


/* ###################################################################################
#  DATA
################################################################################### */

sSpriteBlock *	gpRPauseSprite;
U8				gRPauseFlag;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		RenderPause_Load( void );
U8		RenderPause_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_Init( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderPause_Init( void )
{
	Resource_Attach( eSECTION_GLOBAL, RenderPause_Load, RenderPause_UnLoad );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderPause_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_GameInit( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderPause_GameInit( void )
{
	gRPauseFlag = 0;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_LevelInit( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderPause_LevelInit( void )
{
	gRPauseFlag = 0;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_Update( void )
* ACTION   : called at end of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderPause_Update( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderPause_Draw(void)
* ACTION   : RenderPause_Draw
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderPause_Draw(void)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;
	sSpriteBlock *	lpSprite;

	lPos.mX       = dRPAUSE_CLEAR_X;
	lPos.mY       = dRPAUSE_CLEAR_Y;

	lRect.mX      = dRPAUSE_CLEAR_X;
	lRect.mY      = dRPAUSE_CLEAR_Y;
	lRect.mWidth  = dRPAUSE_CLEAR_WIDTH;
	lRect.mHeight = dRPAUSE_CLEAR_HEIGHT;

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();
*/
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		Screen_GetpBackGraphic() );

	lPos.mX = dRPAUSE_X;
	lPos.mY = dRPAUSE_Y;

	Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
		Screen_GetpLogicGraphic(),
		&lPos,
		gpRPauseSprite->mpSprite[ 0 ] );

	lpSprite = (sSpriteBlock*)RenderFrontEnd_GetpButtonSprites();
	lPos.mX = dRPAUSE_BUTTON_X;
	lPos.mY = dRPAUSE_BUTTON_Y;
	Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
		Screen_GetpLogicGraphic(),
		&lPos,
		lpSprite->mpSprite[ 1 ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderPause_UnDraw(void)
* ACTION   : RenderPause_UnDraw
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderPause_UnDraw(void)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;
	sSpriteBlock *	lpSprite;

	lPos.mX       = dRPAUSE_CLEAR_X;
	lPos.mY       = dRPAUSE_CLEAR_Y;

	lRect.mX      = dRPAUSE_CLEAR_X;
	lRect.mY      = dRPAUSE_CLEAR_Y;
	lRect.mWidth  = dRPAUSE_CLEAR_WIDTH;
	lRect.mHeight = dRPAUSE_CLEAR_HEIGHT;

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();
*/
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		Screen_GetpBackGraphic() );

	lpSprite = (sSpriteBlock*)RenderFrontEnd_GetpButtonSprites();
	lPos.mX  = dRPAUSE_BUTTON_X;
	lPos.mY  = dRPAUSE_BUTTON_Y;

	lRect.mX = lPos.mX;
	lRect.mY = lPos.mY;
	lRect.mWidth = lpSprite->mpSprite[ 0 ]->mWidth;
	lRect.mHeight = lpSprite->mpSprite[ 0 ]->mHeight;
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		Screen_GetpBackGraphic() );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_Enable( void )
* ACTION   : enables pause rendering
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderPause_Enable( void )
{
	gRPauseFlag = 1;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_Disable( void )
* ACTION   : disables pause rendering
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderPause_Disable( void )
{
	gRPauseFlag = 0;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_Load( void )
* ACTION   : loads all resources for intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderPause_Load( void )
{
	gpRPauseSprite = Resource_Load( "PAUSE.BSB", 0 );

	Sprite_BlockRelocate( gpRPauseSprite );

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderPause_UnLoad( void )
* ACTION   : releases memory used by intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderPause_UnLoad( void )
{
	Resource_UnLoad( gpRPauseSprite );

	return( 1 );
}


/* ################################################################################ */
