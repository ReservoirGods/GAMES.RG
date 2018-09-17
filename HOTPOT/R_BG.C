/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_OBJ.H"

#include	"BUILD.H"
#include	"OBJECTS.H"

#include	"R_FADE.H"
#include	"R_FE.H"

#include	"DATALOG.H"
#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	<GODLIB\GRAPHIC\GRAPHIC.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\PICTYPES\DEGAS.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

#define	dRBG_BUTTON_X	258
#define	dRBG_GAMEA_Y	11
#define	dRBG_GAMEB_Y	25


/* ###################################################################################
#  DATA
################################################################################### */

sDegas *		gpRBGPic;
/*sGraphicCanvas	gRBGCanvas;*/


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		RenderBackGround_Load( void );
U8		RenderBackGround_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderBackGround_Init( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderBackGround_Init( void )
{
	Resource_Attach( eSECTION_GLOBAL, RenderBackGround_Load, RenderBackGround_UnLoad );
/*	GraphicCanvas_Init( &gRBGCanvas, eGRAPHIC_COLOURMODE_4PLANE, 320, 200 );*/
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderBackGround_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderBackGround_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderBackGround_GameInit( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderBackGround_GameInit( void )
{
	sGraphicPos	lPos;
	sSpriteBlock *	lpSprite;

/*	RenderScreen_CopyScreen( &gpRBGPic->mPixels[ 0 ], RenderScreen_GetpBack() );*/
	Screen_GetpBackGraphic()->mpFuncs->CopyScreen( Screen_GetpBackGraphic(), &gpRBGPic->mPixels[ 0 ] );


	lPos.mX = dRBG_BUTTON_X;

	if( DataLog_GetEntry( eDATALOG_GAMETYPE ) )
	{
		lPos.mY = dRBG_GAMEB_Y;
	}
	else
	{
		lPos.mY = dRBG_GAMEA_Y;
	}
	lpSprite = (sSpriteBlock*)RenderFrontEnd_GetpButtonSprites();
	Screen_GetpBackGraphic()->mpFuncs->DrawSprite(
		Screen_GetpBackGraphic(),
		&lPos,
		lpSprite->mpSprite[ 1 ] );


/*	RenderScreen_CopyScreen( RenderScreen_GetpBack(), RenderScreen_GetpLogic() );
	RenderScreen_CopyScreen( RenderScreen_GetpBack(), RenderScreen_GetpPhysic() );*/

	Screen_GetpBackGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(),  Screen_GetpBack() );
	Screen_GetpBackGraphic()->mpFuncs->CopyScreen( Screen_GetpPhysicGraphic(), Screen_GetpBack() );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderBackGround_LevelInit( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderBackGround_LevelInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderBackGround_Update( void )
* ACTION   : called at end of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderBackGround_Update( void )
{
	U16				i;
	sGraphicRect	lRect;
	sObject *		lpObject;

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
/*	gRBGCanvas.mpVRAM                  = RenderScreen_GetpBack();*/

	lpObject = Objects_GetpObjects();
	for( i=0; i<dOBJ_LIMIT; i++ )
	{
		if( lpObject->UnDrawFlag )
		{
			lRect.mHeight = lpObject->Height;
			lRect.mWidth  = lpObject->Width;
			lRect.mX      = lpObject->X;
			lRect.mY      = lpObject->Y;

			Screen_GetpLogicGraphic()->mpFuncs->Blit(
				Screen_GetpLogicGraphic(),
				(sGraphicPos*)&lpObject->X,
				&lRect,
				Screen_GetpBackGraphic() );

			lpObject->UnDrawFlag--;
		}
		lpObject++;
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderBackGround_FadeDown(void)
* ACTION   : RenderBackGround_FadeDown
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderBackGround_FadeDown(void)
{
	RenderFade_Main( RenderFade_GetpBlackPal(), 16 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderBackGround_FadeUp(void)
* ACTION   : RenderBackGround_FadeUp
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderBackGround_FadeUp(void)
{
	RenderFade_Main( &gpRBGPic->mHeader.mPalette[ 0 ], 16 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : sDegas * RenderBackGround_GetpPic(void)
* ACTION   : RenderBackGround_GetpPic
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

sDegas * RenderBackGround_GetpPic(void)
{
	return( gpRBGPic );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderBackGround_Load( void )
* ACTION   : loads all resources for intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderBackGround_Load( void )
{
	gpRBGPic = Resource_Load( "BALL-GB.PI1", 0 );

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderBackGround_UnLoad( void )
* ACTION   : releases memory used by intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderBackGround_UnLoad( void )
{
	Resource_UnLoad( gpRBGPic );

	return( 1 );
}


/* ################################################################################ */
