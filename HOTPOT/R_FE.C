/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_FE.H"

#include	"R_FADE.H"
#include	"R_FONT.H"
#include	"R_OBJ.H"

#include	"BUILD.H"
#include	"FRONTEND.H"
#include	"RESOURCE.H"

#include	<GODLIB\ASSERT\ASSERT.H>
#include	<GODLIB\DEBUGLOG\DEBUGLOG.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\FADE\FADE.H>
#include	<GODLIB\GRAPHIC\GRAPHIC.H>
#include	<GODLIB\PICTYPES\DEGAS.H>
#include	<GODLIB\MEMORY\MEMORY.H>
#include	<GODLIB\VIDEO\VIDEO.H>
#include	<GODLIB\VBL\VBL.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dRFE_FONT_TITLE		eRFONT_FE
#define	dRFE_FONT_OPTION	eRFONT_FE
#define	dRFE_FONT_SELECTION	eRFONT_FE
#define	dRFE_FONT_CURSOR	eRFONT_FE

#define	dRFE_CURSOR_X		40
#define	dRFE_TITLE_Y		0
#define	dRFE_BUTTON_X		160
#define	dRFE_BUTTON_TITLE_X	180
#define	dRFE_TOGGLE_X		250
#define	dRFE_SEL_Y			16
#define	dRFE_BUTTON_MIN_Y	20
#define	dRFE_BUTTON_MAX_Y	110

#define	dRFE_EYE_X0			20
#define	dRFE_EYE_Y0			117
#define	dRFE_EYE_X1			33
#define	dRFE_EYE_Y1			117

#define	dRFE_BALL_X			92
#define	dRFE_BALL_MIN_Y		60
#define	dRFE_BALL_MAX_Y		118

#define	dRFE_POS			0L
#define	dRFE_VEL			0x00020000L
#define	dRFE_ACC			0xFFFFF000L

#define	dRFE_CONTROLLER_X		250
#define	dRFE_CONTROLLER_NUM_X	280
#define	dRFE_CONTROLLER_WIDTH	64
#define	dRFE_CONTROLLER_HEIGHT	21

#define	dRFE_A_X	250
#define	dRFE_B_X	270


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eRFE_CONTROLLER_KEYS,
	eRFE_CONTROLLER_JAG,
	eRFE_CONTROLLER_JOY,

	eRFE_CONTROLLER_LIMIT
};


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef struct
{
	uS32	Pos;
	uS32	Vel;
	uS32	Acc;
} sRFeParticle;


/* ###################################################################################
#  DATA
################################################################################### */

sGraphicCanvas	gRFECanvas;
sSpriteBlock *	gpRFeButtonSprites;
sSpriteBlock *	gpRFeToggleSprites;
sSpriteBlock *	gpRFeEyeSprites;
sSpriteBlock *	gpRFeControllerSprites[ eRFE_CONTROLLER_LIMIT ];
sSpriteBlock *	gpRFe12Sprites;
sSpriteBlock *	gpRFeABSprites;
sDegas *		gpRFeBackGround;
sDegas *		gpRFeCredits;
sGraphicPos		gRFeBallPos[ 2 ];
sRFeParticle	gRFeBall;

sTagString		gRFEControllerFileNames[ eRFE_CONTROLLER_LIMIT ] =
{
	{	eRFE_CONTROLLER_KEYS,	"FE_KEYS.BSB"	},
	{	eRFE_CONTROLLER_JAG,	"FE_JAG.BSB"	},
	{	eRFE_CONTROLLER_JOY,	"FE_JOY.BSB"	},
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderFrontEnd_DrawTitle( char * apTitle, S16 aY, sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawButtonTitle( sFeButton * apButton, S16 aY, sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawButtonSelection( sFeButton * apButton, S16 aY, sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawButton( sFeButton * apButton, S16 aY, sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawPage( sFeButtonPage * apPage, sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawCursor( S16 aY, sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawEye( U16 aIndex, S16 aX, S16 aY, sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawEyes( sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawBall( sGraphicCanvas * apCanvas );
void	RenderFrontEnd_UnDrawCursor( S16 aY, sGraphicCanvas * apCanvas );
void	RenderFrontEnd_DrawButtonToggle( sFeButton * apButton, S16 aY, sGraphicCanvas * apCanvas );
U8		RenderFrontEnd_Load( void );
U8		RenderFrontEnd_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_Init(void)
* ACTION   : RenderFrontEnd_Init
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_Init(void)
{
	U16	i;

	Resource_Attach( eSECTION_GLOBAL, RenderFrontEnd_Load, RenderFrontEnd_UnLoad );
	GraphicCanvas_Init( &gRFECanvas, eGRAPHIC_COLOURMODE_4PLANE, 320, 200 );

	for( i=0; i<2; i++ )
	{
		gRFeBallPos[ i ].mX = 0;
		gRFeBallPos[ i ].mY = 0;
	}

	gRFeBall.Pos.l = 0;
	gRFeBall.Vel.l = dRFE_VEL;
	gRFeBall.Acc.l = dRFE_ACC;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DeInit(void)
* ACTION   : RenderFrontEnd_DeInit
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DeInit(void)
{
	
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_Update(void)
* ACTION   : RenderFrontEnd_Update
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_Update(void)
{
	sFeButtonPage *	lpPage;
	U16				j;
	S16				lY;
	S16				lStepY;

	lpPage = FrontEnd_GetpCurrentPage();
	if( lpPage->RedrawFlag )
	{
		if( lpPage->RedrawFlag == 2 )
		{
			RenderFade_StartVblFade( RenderFade_GetpBlackPal(), 16 );
/*			RenderScreen_ClearScreen( RenderScreen_GetpBack() );*/
			Screen_GetpBackGraphic()->mpFuncs->ClearScreen( Screen_GetpBackGraphic() );
			RenderFrontEnd_DrawPage( lpPage, Screen_GetpBackGraphic() );
		}
		else
		{
			RenderFade_StartVblFade( &gpRFeBackGround->mHeader.mPalette[ 0 ], 16 );
		}
/*		RenderScreen_ClearScreen( RenderScreen_GetpLogic() );*/
		Screen_GetpLogicGraphic()->mpFuncs->ClearScreen( Screen_GetpLogicGraphic() );
		RenderFrontEnd_DrawPage( lpPage, Screen_GetpLogicGraphic() );
		RenderFrontEnd_DrawEyes( Screen_GetpLogicGraphic() );
		lpPage->RedrawFlag--;
	}
	else
	{
		lStepY  = dRFE_BUTTON_MAX_Y-dRFE_BUTTON_MIN_Y;
		lStepY /= lpPage->ButtonCount;
		lY      = dRFE_BUTTON_MIN_Y;

		for( j=0; j<lpPage->ButtonCount; j++ )
		{
			if( lpPage->pButtons[ j ].RedrawFlag )
			{
				RenderFrontEnd_DrawButton( &lpPage->pButtons[ j ], lY, Screen_GetpLogicGraphic() );
				lpPage->pButtons[ j ].RedrawFlag--;
			}
			lY += lStepY;
		}
		RenderFrontEnd_DrawEyes( Screen_GetpLogicGraphic() );
	}
	RenderFrontEnd_DrawBall( Screen_GetpLogicGraphic() );

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawTitle(char * apTitle,S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawTitle
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawTitle(char * apTitle,S16 aY,sGraphicCanvas * apCanvas)
{
	S16	lX;

	lX  = 160;
	lX -= (RenderFont_GetWidth( dRFE_FONT_TITLE, apTitle )>>1);
	RenderFont_Print( dRFE_FONT_TITLE, apTitle, apCanvas, lX,  aY );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawButtonTitle(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawButtonTitle
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawButtonTitle(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
{
	S16	lX;

/*	lX  = 160;
	lX -= (RenderFont_GetWidth( dRFE_FONT_OPTION, apButton->pTitleTxt )>>1);*/

	lX = dRFE_BUTTON_TITLE_X;
	RenderFont_Print( dRFE_FONT_OPTION, apButton->pTitleTxt, apCanvas, lX,  aY );	
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawGame(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawGame
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawGame(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;
	U16				lIndexA,lIndexB;

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();
*/
	lPos.mY = aY-3;

	if( apButton->Value )
	{
		lIndexA = 1;
		lIndexB = 2;
	}
	else
	{
		lIndexA = 0;
		lIndexB = 3;
	}

	lPos.mX = dRFE_A_X;

	lRect.mX      = lPos.mX;
	lRect.mY      = lPos.mY;
	lRect.mWidth  = gpRFeABSprites->mpSprite[ 0 ]->mWidth;
	lRect.mHeight = gpRFeABSprites->mpSprite[ 0 ]->mHeight;
	apCanvas->mpFuncs->Blit(
		apCanvas,
		&lPos,
		&lRect,
		Screen_GetpBackGraphic() );

	apCanvas->mpFuncs->DrawSprite(
		apCanvas,
		&lPos,
		gpRFeABSprites->mpSprite[ lIndexA ] );

	lPos.mX = dRFE_B_X;

	lRect.mX      = lPos.mX;
	apCanvas->mpFuncs->Blit(
		apCanvas,
		&lPos,
		&lRect,
		Screen_GetpBackGraphic() );

	apCanvas->mpFuncs->DrawSprite(
		apCanvas,
		&lPos,
		gpRFeABSprites->mpSprite[ lIndexB ] );

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawController(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawController
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawController(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;
	U16				lConIndex;
	U16				lNumIndex;

	(void)apCanvas;
	lPos.mX = dRFE_CONTROLLER_X;
	lPos.mY = aY-8;

	lRect.mX = lPos.mX;
	lRect.mY = lPos.mY;
	lRect.mHeight = gpRFeControllerSprites[ eRFE_CONTROLLER_KEYS ]->mpSprite[ 0 ]->mHeight;
	lRect.mWidth  = gpRFeControllerSprites[ eRFE_CONTROLLER_KEYS ]->mpSprite[ 0 ]->mWidth;

	gRFECanvas.mpVRAM = &gpRFeBackGround->mPixels[ 0 ];
/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();
*/
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		&gRFECanvas );

	switch( apButton->Value )
	{
	case	eFEGAME_CONTROL_SEL_IKBD:
		lConIndex = eRFE_CONTROLLER_KEYS;
		lNumIndex = 0;
		break;
	case	eFEGAME_CONTROL_SEL_JOY0:
		lConIndex = eRFE_CONTROLLER_JOY;
		lNumIndex = 0;
		break;
	case	eFEGAME_CONTROL_SEL_JOY1:
		lConIndex = eRFE_CONTROLLER_JOY;
		lNumIndex = 1;
		break;
	case	eFEGAME_CONTROL_SEL_PADA:
		lConIndex = eRFE_CONTROLLER_JAG;
		lNumIndex = 0;
		break;
	case	eFEGAME_CONTROL_SEL_PADB:
		lConIndex = eRFE_CONTROLLER_JAG;
		lNumIndex = 1;
		break;
	default:
		lConIndex = eRFE_CONTROLLER_KEYS;
		lNumIndex = 0;
		break;
	}

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();
*/
	Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
		Screen_GetpLogicGraphic(),
		&lPos,
		gpRFeControllerSprites[ lConIndex ]->mpSprite[ 0 ] );


	lPos.mX = dRFE_CONTROLLER_NUM_X;
	lPos.mY = aY-8;

	lRect.mX = lPos.mX;
	lRect.mY = lPos.mY;
	lRect.mHeight = gpRFe12Sprites->mpSprite[ 0 ]->mHeight;
	lRect.mWidth  = gpRFe12Sprites->mpSprite[ 0 ]->mWidth;


	gRFECanvas.mpVRAM = &gpRFeBackGround->mPixels[ 0 ];
/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();
*/
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		&gRFECanvas );

	if( lConIndex != eRFE_CONTROLLER_KEYS )
	{
/*		RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
		Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
			Screen_GetpLogicGraphic(),
			&lPos,
			gpRFe12Sprites->mpSprite[ lNumIndex ] );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawButtonSelection(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawButtonSelection
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawButtonSelection(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
{
	if( apButton->Type == eFEBUTTYPE_SELECTION )
	{
		switch( (U16)apButton->SubType )
		{
		case	eFE_SUBTYPE_GAME:
			RenderFrontEnd_DrawGame( apButton, aY, apCanvas );
			break;
		case	eFE_SUBTYPE_CONTROLLER:
			RenderFrontEnd_DrawController( apButton, aY, apCanvas );
			break;
		}

	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawButtonToggle(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawButtonToggle
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawButtonToggle(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;
	U16				lIndex;

	(void)apCanvas;
	if( apButton->Type == eFEBUTTYPE_TOGGLE )
	{
		lPos.mX = dRFE_TOGGLE_X;
		lPos.mY = aY+2;

		lRect.mX = lPos.mX;
		lRect.mY = lPos.mY;
		lRect.mHeight = gpRFeToggleSprites->mpSprite[ 0 ]->mHeight;
		lRect.mWidth  = gpRFeToggleSprites->mpSprite[ 0 ]->mWidth;

		gRFECanvas.mpVRAM = &gpRFeBackGround->mPixels[ 0 ];
/*		RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
		Screen_GetpLogicGraphic()->mpFuncs->Blit(
			Screen_GetpLogicGraphic(),
			&lPos,
			&lRect,
			&gRFECanvas );

		if( apButton->Value )
		{
			lIndex = 0;
		}
		else
		{
			lIndex = 1;
		}

/*		RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
		Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
			Screen_GetpLogicGraphic(),
			&lPos,
			gpRFeToggleSprites->mpSprite[ lIndex ] );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawCursor(S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawCursor
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawCursor(S16 aY,sGraphicCanvas * apCanvas)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;

	(void)apCanvas;
	lPos.mX = dRFE_BUTTON_X;
	lPos.mY = aY-2;

	lRect.mX = lPos.mX;
	lRect.mY = lPos.mY;
	lRect.mHeight = gpRFeButtonSprites->mpSprite[ 0 ]->mHeight;
	lRect.mWidth  = gpRFeButtonSprites->mpSprite[ 0 ]->mWidth;

	gRFECanvas.mpVRAM = &gpRFeBackGround->mPixels[ 0 ];
/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		&gRFECanvas );

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
		Screen_GetpLogicGraphic(),
		&lPos,
		gpRFeButtonSprites->mpSprite[ 1 ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_UnDrawCursor(S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_UnDrawCursor
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_UnDrawCursor(S16 aY,sGraphicCanvas * apCanvas)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;

	(void)apCanvas;
	lPos.mX = dRFE_BUTTON_X;
	lPos.mY = aY-2;

	lRect.mX = lPos.mX;
	lRect.mY = lPos.mY;
	lRect.mHeight = gpRFeButtonSprites->mpSprite[ 0 ]->mHeight;
	lRect.mWidth  = gpRFeButtonSprites->mpSprite[ 0 ]->mWidth;

	gRFECanvas.mpVRAM = &gpRFeBackGround->mPixels[ 0 ];
/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		&gRFECanvas );

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
		Screen_GetpLogicGraphic(),
		&lPos,
		gpRFeButtonSprites->mpSprite[ 0 ] );

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawEye(U16 aIndex,S16 aX,S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawEye
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawEye(U16 aIndex,S16 aX,S16 aY,sGraphicCanvas * apCanvas)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;

	(void)apCanvas;
	lPos.mX = aX;
	lPos.mY = aY;

	lRect.mX = lPos.mX;
	lRect.mY = lPos.mY;
	lRect.mHeight = gpRFeEyeSprites->mpSprite[ 0 ]->mHeight;
	lRect.mWidth  = gpRFeEyeSprites->mpSprite[ 0 ]->mWidth;

	gRFECanvas.mpVRAM = &gpRFeBackGround->mPixels[ 0 ];
/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&lPos,
		&lRect,
		&gRFECanvas );

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
		Screen_GetpLogicGraphic(),
		&lPos,
		gpRFeEyeSprites->mpSprite[ aIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawEyes(sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawEyes
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawEyes(sGraphicCanvas * apCanvas)
{

	U16	lIndex;

	lIndex = 3-FrontEnd_GetButtonIndex();

	if( lIndex >= gpRFeEyeSprites->mHeader.mSpriteCount )
	{
		lIndex = 0;
	}

	RenderFrontEnd_DrawEye( lIndex, dRFE_EYE_X0, dRFE_EYE_Y0, apCanvas );
	RenderFrontEnd_DrawEye( lIndex, dRFE_EYE_X1, dRFE_EYE_Y1, apCanvas );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawButton(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawButton
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawButton(sFeButton * apButton,S16 aY,sGraphicCanvas * apCanvas)
{
	RenderFrontEnd_DrawButtonTitle( apButton, aY, apCanvas );
	RenderFrontEnd_DrawButtonSelection( apButton, aY, apCanvas );
	RenderFrontEnd_DrawButtonToggle( apButton, aY, apCanvas );

	if( apButton->SelectedFlag )
	{
		RenderFrontEnd_DrawCursor( aY, apCanvas );
	}
	else
	{
		RenderFrontEnd_UnDrawCursor( aY, apCanvas );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawBall(sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawBall
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawBall(sGraphicCanvas * apCanvas)
{
	sGraphicPos		lPos;
	sGraphicRect	lRect;
	U16				lScreenIndex;
	sSpriteBlock *	lpBlock;

	(void)apCanvas;
	lpBlock = (sSpriteBlock *)RenderObjects_GetpBallSprite();

	gRFeBall.Pos.l += gRFeBall.Vel.l;
	gRFeBall.Vel.l += gRFeBall.Acc.l;

	if( gRFeBall.Pos.l < 0 )
	{
		gRFeBall.Pos.l = dRFE_POS;
		gRFeBall.Vel.l = dRFE_VEL;
		gRFeBall.Acc.l = dRFE_ACC;
	}


	lScreenIndex = Screen_GetLogicIndex();

	lRect.mX      = gRFeBallPos[ lScreenIndex ].mX;
	lRect.mY      = gRFeBallPos[ lScreenIndex ].mY;
	lRect.mHeight = lpBlock->mpSprite[ 0 ]->mHeight;
	lRect.mWidth  = lpBlock->mpSprite[ 0 ]->mWidth;

	gRFECanvas.mpVRAM = &gpRFeBackGround->mPixels[ 0 ];
/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	Screen_GetpLogicGraphic()->mpFuncs->Blit(
		Screen_GetpLogicGraphic(),
		&gRFeBallPos[ lScreenIndex ],
		&lRect,
		&gRFECanvas );

	lPos.mX = dRFE_BALL_X;
	lPos.mY = dRFE_BALL_MAX_Y - gRFeBall.Pos.w.w1;
	if( lPos.mY < dRFE_BALL_MIN_Y )
	{
		lPos.mY = dRFE_BALL_MIN_Y;
	}
	gRFeBallPos[ lScreenIndex ].mX = lPos.mX;
	gRFeBallPos[ lScreenIndex ].mY = lPos.mY;

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();*/
	Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
		Screen_GetpLogicGraphic(),
		&lPos,
		lpBlock->mpSprite[ 0 ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawPage(sFeButtonPage * apPage,sGraphicCanvas * apCanvas)
* ACTION   : RenderFrontEnd_DrawPage
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawPage(sFeButtonPage * apPage,sGraphicCanvas * apCanvas)
{
	U16	i;
	S16	lY;
	S16	lStepY;

/*	RenderScreen_CopyScreen( &gpRFeBackGround->mPixels[ 0 ], apScreen );*/
	apCanvas->mpFuncs->CopyScreen( apCanvas, &gpRFeBackGround->mPixels[ 0 ] );

/*	RenderFrontEnd_DrawTitle( apPage->pTitle, dRFE_TITLE_Y, apScreen );
*/
	lStepY  = dRFE_BUTTON_MAX_Y-dRFE_BUTTON_MIN_Y;
	lStepY /= apPage->ButtonCount;
	lY      = dRFE_BUTTON_MIN_Y;

	for( i=0; i<apPage->ButtonCount; i++ )
	{
		RenderFrontEnd_DrawButton( &apPage->pButtons[ i ], lY, apCanvas );
		lY += lStepY;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : U16 * RenderFrontEnd_GetpPal(void)
* ACTION   : RenderFrontEnd_GetpPal
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

U16 * RenderFrontEnd_GetpPal(void)
{
	return( &gpRFeBackGround->mHeader.mPalette[ 0 ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void * RenderFrontEnd_GetpButtonSprites(void)
* ACTION   : RenderFrontEnd_GetpButtonSprites
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void * RenderFrontEnd_GetpButtonSprites(void)
{
	return( gpRFeButtonSprites );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderFrontEnd_DrawCredits(void)
* ACTION   : RenderFrontEnd_DrawCredits
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderFrontEnd_DrawCredits(void)
{
	RenderFade_Main( RenderFade_GetpBlackPal(), 16 );
/*	RenderScreen_CopyScreen( &gpRFeCredits->mPixels[ 0 ], RenderScreen_GetpLogic() );*/
	Screen_GetpLogicGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(), &gpRFeCredits->mPixels[ 0 ] );
	Screen_Update();
/*	RenderScreen_CopyScreen( &gpRFeCredits->mPixels[ 0 ], RenderScreen_GetpLogic() );*/
	Screen_GetpLogicGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(), &gpRFeCredits->mPixels[ 0 ] );
	RenderFade_Main( &gpRFeCredits->mHeader.mPalette[ 0 ], 16 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : U8 RenderFrontEnd_Load(void)
* ACTION   : RenderFrontEnd_Load
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

U8 RenderFrontEnd_Load(void)
{
	U16	i;

	gpRFeBackGround    = Resource_Load( "FRONT.PI1", 0 );
	gpRFeButtonSprites = Resource_Load( "FE_BUTN.BSB", 0 );
	gpRFeToggleSprites = Resource_Load( "FE_DOT.BSB", 0 );
	gpRFeEyeSprites    = Resource_Load( "FE_EYES.BSB", 0 );
	gpRFe12Sprites     = Resource_Load( "FE_12.BSB", 0 );
	gpRFeABSprites     = Resource_Load( "FE_AB.BSB", 0 );
	gpRFeCredits       = Resource_Load( "BALL-CR.PI1", 0 );
	
	for( i=0; i<eRFE_CONTROLLER_LIMIT; i++ )
	{
		gpRFeControllerSprites[ i ] = Resource_Load( sTagString_GetpString( i, &gRFEControllerFileNames[ 0 ], eRFE_CONTROLLER_LIMIT ), 0 );
		Sprite_BlockRelocate( gpRFeControllerSprites[ i ] );
	}

	Sprite_BlockRelocate( gpRFeABSprites );
	Sprite_BlockRelocate( gpRFe12Sprites );
	Sprite_BlockRelocate( gpRFeButtonSprites );
	Sprite_BlockRelocate( gpRFeToggleSprites );
	Sprite_BlockRelocate( gpRFeEyeSprites );

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : U8 RenderFrontEnd_UnLoad(void)
* ACTION   : RenderFrontEnd_UnLoad
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

U8 RenderFrontEnd_UnLoad(void)
{
	U16	i;

	Resource_UnLoad( gpRFeABSprites );
	Resource_UnLoad( gpRFeBackGround );
	Resource_UnLoad( gpRFeButtonSprites );
	Resource_UnLoad( gpRFeEyeSprites );
	Resource_UnLoad( gpRFeToggleSprites );
	Resource_UnLoad( gpRFe12Sprites );
	Resource_UnLoad( gpRFeCredits );

	for( i=0; i<eRFE_CONTROLLER_LIMIT; i++ )
	{
		Resource_UnLoad( gpRFeControllerSprites[ i ] );
	}

	return( 1 );
}


/* ################################################################################ */
