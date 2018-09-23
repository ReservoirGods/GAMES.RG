/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_ENTRY.H"

#include	"R_BG.H"
#include	"R_FONT.H"
#include	"R_OBJ.H"

#include	"A_GAME.H"
#include	"A_SPL.H"

#include	"BUILD.H"
#include	"OBJECTS.H"
#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	<GODLIB\FADE\FADE.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\GRAPHIC\GRAPHIC.H>

#include	<MATH.H>
#include	<STRING.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eRENTRY_MODE_NORMAL,
	eRENTRY_MODE_GRAB,
	eRENTRY_MODE_THROW,

	eRENTRY_MODE_LIMIT
};


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dRENTRY_NAME_LIMIT			8
#define	dRENTRY_BOUNCE_LIMIT		64
#define	dRENTRY_BOUNCE_MASK			(dRENTRY_BOUNCE_LIMIT-1)
#define	dRENTRY_BOUNCE_Y0			170
#define	dRENTRY_BOUNCE_Y1			190
#define	dRENTRY_BOUNCE_MIDY			(dRENTRY_BOUNCE_Y0+((dRENTRY_BOUNCE_Y1-dRENTRY_BOUNCE_Y0)/2))
#define	dRENTRY_BOUNCE_FONT			eRFONT_HISCORE
#define	dRENTRY_BOX_Y0				170
#define	dRENTRY_BOX_Y1				170

#define	dRENTRY_JUGGLEPOS_LIMIT		128
#define	dRENTRY_JUGGLEBALL_LIMIT	3

#define	dRENTRY_JUGGLE_Y0			120
#define	dRENTRY_JUGGLE_X0			88
#define	dRENTRY_JUGGLE_X1			204
#define	dRENTRY_JUGGLE_WIDTH		(dRENTRY_JUGGLE_X1-dRENTRY_JUGGLE_X0)

#define	dRENTRY_JUGGLE_COEFF_A		(-0.02f)
#define	dRENTRY_JUGGLE_COEFF_B		(2.32f)
#define	dRENTRY_JUGGLE_COEFF_C		(0.f)

#define	dRENTRY_TITLE_Y				0
#define	dRENTRY_TITLE_FONT			eRFONT_HISCORE
#define	dRENTRY_JUGGLE_FONT			eRFONT_HISCORE

#define	dRENTRY_GRAB_WAIT			5
#define	dRENTRY_THROW_WAIT			5

#define	dRENTRY_CENTRE_X			148

/* nowhere - desertion : top tune!
*/

/* ###################################################################################
#  DATA
################################################################################### */

char	gREntryName[ dRENTRY_NAME_LIMIT + 2 ];
char	gREntryChar;

sGraphicPos	gREntryJugglePos[ dRENTRY_JUGGLEPOS_LIMIT ];
sGraphicPos	gREntryJuggleUnDrawPos[ 2 ][ dRENTRY_JUGGLEBALL_LIMIT ];

S16		gREntryBounceY[ dRENTRY_BOUNCE_LIMIT ];
U16		gREntryBounceIndex[ dRENTRY_NAME_LIMIT ];
S16		gREntryJuggleIndex[ dRENTRY_JUGGLEBALL_LIMIT ];
S16		gRentryJuggleStep[ dRENTRY_JUGGLEBALL_LIMIT ];
U16		gREntryManPos;
U16		gREntryCursorPos;
U16		gREntryMode;
U16		gREntryWait;
U8		gREntryLetter;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		RenderEntry_Load( void );
U8		RenderEntry_UnLoad( void );

void	RenderEntry_DrawBackGround( sGraphicCanvas * apCanvas );
void	RenderEntry_DrawName( sGraphicCanvas * apCanvas );
void	RenderEntry_BounceUpdate( void );
void	RenderEntry_DrawMan( void );
void	RenderEntry_UnDrawMan( void );
void	RenderEntry_UnDrawBalls( sGraphicCanvas * apCanvas );
void	RenderEntry_DrawBalls( sGraphicCanvas * apCanvas );
void	RenderEntry_BallsUpdate( void );

U8		RenderEntry_CharAdd( const U8 aChar );
U8		RenderEntry_CharSub( const U8 aChar );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_Init( void )
* ACTION   : called at start of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderEntry_Init( void )
{
	U16		i,j;
	FP32	lBounce;
	FP32	lY,lStepY;
	FP32	lX;

	Resource_Attach( eSECTION_GLOBAL, RenderEntry_Load, RenderEntry_UnLoad );
	
	for( i=0; i<dRENTRY_NAME_LIMIT; i++ )
	{
		gREntryName[ i ] = 'A';
	}


	lY     = 0.f;
	lStepY = 6.283185307f / dRENTRY_BOUNCE_LIMIT;


	for( i=0; i<dRENTRY_BOUNCE_LIMIT; i++ )
	{
		lBounce  = (FP32)(sin( lY ) * (dRENTRY_BOUNCE_MIDY-dRENTRY_BOUNCE_Y0));
		lBounce += dRENTRY_BOUNCE_MIDY;
		gREntryBounceY[ i ] = (S16)lBounce;
		lY += lStepY;
	}

	for( i=0; i<dRENTRY_NAME_LIMIT; i++ )
	{
		gREntryBounceIndex[ i ] = (dRENTRY_BOUNCE_LIMIT * i) / dRENTRY_NAME_LIMIT;
	}

	lStepY  = dRENTRY_JUGGLE_WIDTH;
	lStepY /= dRENTRY_JUGGLEPOS_LIMIT;

	lX      = 0.f;
	for( i=0; i<dRENTRY_JUGGLEPOS_LIMIT; i++ )
	{
		lY  = (lX*lX*dRENTRY_JUGGLE_COEFF_A);
		lY += (lX*dRENTRY_JUGGLE_COEFF_B);
		lY += (dRENTRY_JUGGLE_COEFF_C);

		gREntryJugglePos[ i ].mX = (S16)( dRENTRY_JUGGLE_X0 + lX );
		gREntryJugglePos[ i ].mY = (S16)( dRENTRY_JUGGLE_Y0 - lY );

		lX += lStepY;
	}

	for( i=0; i<2; i++ )
	{
		for( j=0; j<dRENTRY_JUGGLEBALL_LIMIT; j++ )
		{
			gREntryJuggleUnDrawPos[ i ][ j ].mX = 0;
			gREntryJuggleUnDrawPos[ i ][ j ].mY = 0;
		}
	}

	for( i=0; i<dRENTRY_JUGGLEBALL_LIMIT; i++ )
	{
		gREntryJuggleIndex[ i ] = 0;
		gRentryJuggleStep[ i ] = 1;
	}

	gREntryJuggleIndex[ 0 ] = 0;
	gRentryJuggleStep[ 0 ] = 1;

	gREntryJuggleIndex[ 1 ] = (dRENTRY_JUGGLEPOS_LIMIT/2);
	gRentryJuggleStep[ 1 ] = 1;

	gREntryJuggleIndex[ 2 ] = dRENTRY_JUGGLEPOS_LIMIT-1;
	gRentryJuggleStep[ 2 ] = -1;


	gREntryManPos = 1;
	gREntryCursorPos = 0;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderEntry_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_GameInit( void )
* ACTION   : called at start of level
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderEntry_GameInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_LevelInit( void )
* ACTION   : called at start of level
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderEntry_LevelInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_Update( void )
* ACTION   : called at end of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderEntry_Update( void )
{
	RenderEntry_BallsUpdate();
	RenderEntry_BounceUpdate();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_Main( const U16 aPlayerIndex )
* ACTION   : main entry rendering loop
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderEntry_Main( void )
{	
	U8	lExitFlag;
	U16	i;
	sObject	*	lpObject;


	lpObject =	Objects_GetpObjects();
	for( i=0; i<dOBJ_LIMIT; i++ )
	{
		lpObject->DrawFlag = 0;
		lpObject->UnDrawFlag = 0;
		lpObject++;
	}

	gREntryManPos = 1;
	gREntryCursorPos = (U16)strlen( gREntryName );
	if( gREntryCursorPos )
	{
		gREntryCursorPos--;
	}
	if( gREntryCursorPos >= dRENTRY_NAME_LIMIT )
	{
		gREntryCursorPos = dRENTRY_NAME_LIMIT-1;
	}
	gREntryLetter = 'A';

	RenderEntry_DrawBackGround( Screen_GetpBackGraphic() );
	RenderEntry_DrawName( Screen_GetpBackGraphic() );
/*	RenderScreen_CopyScreen( RenderScreen_GetpBack(), RenderScreen_GetpLogic() );*/
	Screen_GetpLogicGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(), Screen_GetpBack() );

	RenderEntry_DrawName( Screen_GetpLogicGraphic() );
	RenderEntry_DrawMan();
	RenderObjects_Update();
	Screen_Update();
/*	RenderScreen_CopyScreen( RenderScreen_GetpBack(), RenderScreen_GetpLogic() );*/
	Screen_GetpLogicGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(), Screen_GetpBack() );
	RenderObjects_Update();
	RenderEntry_DrawName( Screen_GetpLogicGraphic() );
	Fade_Main( &RenderBackGround_GetpPic()->mHeader.mPalette[ 0 ], 16 );

	Player_InputUpdate();

	lExitFlag = 0;
	while( !lExitFlag )
	{
		Screen_Update();
		RenderEntry_Update();
		RenderBackGround_Update();
		RenderEntry_UnDrawBalls( Screen_GetpLogicGraphic() );
		RenderObjects_Update();
		RenderEntry_DrawName( Screen_GetpLogicGraphic() );
		RenderEntry_DrawBalls( Screen_GetpLogicGraphic() );


		Player_InputUpdate();

		if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_QUIT ] & eINPUTKEYSTATUS_HIT )
		{
			lExitFlag = 1;
		}

		switch( gREntryMode )
		{
		case	eRENTRY_MODE_NORMAL:
			if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_LEFT ] & eINPUTKEYSTATUS_HIT )
			{
				gREntryMode = eRENTRY_MODE_GRAB;
				gREntryWait = dRENTRY_GRAB_WAIT;
				RenderEntry_UnDrawMan();
				gREntryManPos = 0;
				RenderEntry_DrawMan();

				AudioGame_PlaySampleDirect( eAGAME_BALL_MOVE, eASPL_PAN_CENTRE);
				gREntryLetter = RenderEntry_CharSub( gREntryLetter );
			}

			if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_RIGHT ] & eINPUTKEYSTATUS_HIT )
			{
				gREntryMode = eRENTRY_MODE_GRAB;
				gREntryWait = dRENTRY_GRAB_WAIT;
				RenderEntry_UnDrawMan();
				gREntryManPos = 2;
				RenderEntry_DrawMan();

				AudioGame_PlaySampleDirect( eAGAME_BALL_MOVE, eASPL_PAN_CENTRE);
				gREntryLetter = RenderEntry_CharAdd( gREntryLetter );
			}

			if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_DOWN ] & eINPUTKEYSTATUS_HIT )
			{
				gREntryMode = eRENTRY_MODE_THROW;
				gREntryWait = dRENTRY_THROW_WAIT;
				AudioGame_PlaySampleDirect( eAGAME_BALL_CATCH, eASPL_PAN_CENTRE);
			}

			if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_FIREA ] & eINPUTKEYSTATUS_HIT )
			{
				lExitFlag = 1;
			}

			if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_UP ] & eINPUTKEYSTATUS_HIT )
			{
				for( i=gREntryCursorPos; i<dRENTRY_NAME_LIMIT; i++ )
				{
					gREntryName[ i ] = 0;
				}
				if( gREntryCursorPos )
				{
					gREntryCursorPos--;
				}
				AudioGame_PlaySampleDirect( eAGAME_BALL_MOVE, eASPL_PAN_CENTRE);
			}
			break;

		case	eRENTRY_MODE_GRAB:
			if( gREntryWait )
			{
				gREntryWait--;
			}
			else
			{
				RenderEntry_UnDrawMan();
				gREntryManPos = 1;
				RenderEntry_DrawMan();
				gREntryMode = eRENTRY_MODE_NORMAL;
			}
			break;

		case	eRENTRY_MODE_THROW:
			if( gREntryWait )
			{
				gREntryWait--;
			}
			else
			{
				gREntryName[ gREntryCursorPos   ] = gREntryLetter;
				gREntryName[ gREntryCursorPos+1 ] = 0;

				if( (gREntryCursorPos + 1) < dRENTRY_NAME_LIMIT )
				{
					gREntryCursorPos++;
				}
				else
				{
					lExitFlag = 1;
				}
				gREntryMode = eRENTRY_MODE_NORMAL;
			}
			break;
		
		}

	}
	AudioGame_PlaySampleDirect( eAGAME_BALL_DROP, eASPL_PAN_CENTRE);
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_CharSub( const U8 aChar )
* ACTION   : subtracts one from character with cyclical loop
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

U8		RenderEntry_CharSub( const U8 aChar )
{
	U8	lChar;

	lChar = aChar-1;

	if( lChar <= 0x1F )
	{
		lChar = 'Z';
	}
	else if( (lChar > ' ') && (lChar < 'A') )
	{
		lChar = ' ';
	}
	else if( lChar > 'Z')
	{
		lChar = 'Z';
	}
	
/*
	if( lChar <= 0x1F )
	{
		lChar = 'Z';
	}
	else if( (lChar>0x20) && (lChar <= 0x2F) )
	{
		lChar = ' ';
	}
	else if( (lChar > 0x39) && (lChar <=0x40) )
	{
		lChar = '9';
	}
	else if( lChar > 0x5A )
	{
		lChar = 'Z';
	}
*/
	return( lChar );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_CharAdd( const U8 aChar )
* ACTION   : adds one to character with cyclical loop
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

U8		RenderEntry_CharAdd( const U8 aChar )
{
	U8	lChar;

	lChar = aChar+1;

	if( lChar < ' ' )
	{
		lChar = ' ';
	}
	else if( (lChar > ' ') && (lChar < 'A') )
	{
		lChar = 'A';
	}
	else if( lChar > 'Z')
	{
		lChar = ' ';
	}

	return( lChar );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : char * RenderEntry_GetpName(void)
* ACTION   : RenderEntry_GetpName
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

char * RenderEntry_GetpName(void)
{
	return( &gREntryName[ 0 ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_SetName(char * apName)
* ACTION   : RenderEntry_SetName
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_SetName(char * apName)
{
	U16	i;

	for( i=0; i<8; i++ )
	{
		gREntryName[ i ] = apName[ i ];
	}
	Build_CliPrintLine( gREntryName );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_UnDrawMan(void)
* ACTION   : RenderEntry_UnDrawMan
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_UnDrawMan(void)
{
	sObject *	lpObject;

	lpObject = Objects_GetpObjects();
	lpObject[ dOBJ_ARM_LEFT  + gREntryManPos ].UnDrawFlag = 2;
	lpObject[ dOBJ_ARM_RIGHT + gREntryManPos ].UnDrawFlag = 2;
	lpObject[ dOBJ_EYE_LEFT  + gREntryManPos ].UnDrawFlag = 2;
	lpObject[ dOBJ_EYE_RIGHT + gREntryManPos ].UnDrawFlag = 2;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_DrawMan(void)
* ACTION   : RenderEntry_DrawMan
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_DrawMan(void)
{
	sObject *	lpObject;

	lpObject = Objects_GetpObjects();
	lpObject[ dOBJ_ARM_LEFT  + gREntryManPos ].DrawFlag = 2;
	lpObject[ dOBJ_ARM_RIGHT + gREntryManPos ].DrawFlag = 2;
	lpObject[ dOBJ_EYE_LEFT  + gREntryManPos ].DrawFlag = 2;
	lpObject[ dOBJ_EYE_RIGHT + gREntryManPos ].DrawFlag = 2;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_DrawBackGround(sGraphicCanvas * apCanvas)
* ACTION   : RenderEntry_DrawBackGround
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_DrawBackGround(sGraphicCanvas * apCanvas)
{
	char *			lpTxt;
	sGraphicRect	lRect;
	S16				lX;

/*	RenderScreen_GetpGraphic()->mpVRAM = apScreen;
*/
/*	RenderScreen_CopyScreen( &RenderBackGround_GetpPic()->mPixels[ 0 ], apScreen );*/
	apCanvas->mpFuncs->CopyScreen( apCanvas, &RenderBackGround_GetpPic()->mPixels[ 0 ] );

	lRect.mX      = 0;
	lRect.mY      = 0;
	lRect.mHeight = 200;
	lRect.mWidth  = 54;
	apCanvas->mpFuncs->DrawBox(
		apCanvas,
		&lRect,
		0 );

	lRect.mX      = 246;
	lRect.mY      = 0;
	lRect.mHeight = 200;
	lRect.mWidth  = (320-246);
	apCanvas->mpFuncs->DrawBox(
		apCanvas,
		&lRect,
		0 );

	lRect.mX      = 134;
	lRect.mY      = 159;
	lRect.mHeight = 200-159;
	lRect.mWidth  = (164-134);
	apCanvas->mpFuncs->DrawBox(
		apCanvas,
		&lRect,
		0 );

	lRect.mX      = 0;
	lRect.mY      = 20;
	lRect.mHeight = 2;
	lRect.mWidth  = 320;
	apCanvas->mpFuncs->DrawBox(
		apCanvas,
		&lRect,
		0 );

	lRect.mX      = dRENTRY_CENTRE_X - 100;
	lRect.mY      = 10;
	lRect.mHeight = 1;
	lRect.mWidth  = 200;
	apCanvas->mpFuncs->DrawBox(
		apCanvas,
		&lRect,
		4 );

	lpTxt = "HI SCORE : ENTER NAME";
	lX = dRENTRY_CENTRE_X - (RenderFont_GetWidth( dRENTRY_TITLE_FONT, lpTxt )>>1);
	RenderFont_Print( dRENTRY_TITLE_FONT, lpTxt, apCanvas, lX, dRENTRY_TITLE_Y );

	lpTxt = "LEFT/RIGHT:SCROLL   DOWN:SELECT";
	lX = dRENTRY_CENTRE_X - (RenderFont_GetWidth( dRENTRY_TITLE_FONT, lpTxt )>>1);
	RenderFont_Print( dRENTRY_TITLE_FONT, lpTxt, apCanvas, lX, dRENTRY_TITLE_Y+14 );

	lpTxt = "UP:DELETE  FIRE:ENTER NAME";
	lX = dRENTRY_CENTRE_X - (RenderFont_GetWidth( dRENTRY_TITLE_FONT, lpTxt )>>1);
	RenderFont_Print( dRENTRY_TITLE_FONT, lpTxt, apCanvas, lX, dRENTRY_TITLE_Y+22 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_BounceUpdate(void)
* ACTION   : RenderEntry_BounceUpdate
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_BounceUpdate(void)
{
	U16	i;

	for( i=0; i<dRENTRY_NAME_LIMIT; i++ )
	{
		gREntryBounceIndex[ i ]++;
		gREntryBounceIndex[ i ] &= dRENTRY_BOUNCE_MASK;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_DrawName(sGraphicCanvas * apCanvas)
* ACTION   : RenderEntry_DrawName
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_DrawName(sGraphicCanvas * apCanvas)
{
	char			lString[ 2 ];
	U16				lLen;
	sGraphicRect	lRect;
	S16				lX;
	S16				lY;
	U16				i;

	lRect.mX      = (dRENTRY_CENTRE_X-(8*5));
	lRect.mY      = dRENTRY_BOUNCE_Y0;
	lRect.mHeight = (dRENTRY_BOUNCE_Y1-dRENTRY_BOUNCE_Y0)+8;
	lRect.mWidth  = 8*10;
	apCanvas->mpFuncs->DrawBox(
		apCanvas,
		&lRect,
		0 );

	lLen   = (U16)strlen( gREntryName );
	lX     = dRENTRY_CENTRE_X - (lLen*5);
	lY     = dRENTRY_BOUNCE_Y0;

	lString[ 1 ] = 0;
	for( i=0; i<lLen; i++ )
	{
		lString[ 0 ] = gREntryName[ i ];
		lY           = gREntryBounceY[ gREntryBounceIndex[ i ] ];
		RenderFont_Print( dRENTRY_BOUNCE_FONT, lString, apCanvas, lX, lY );
		lX += 10;
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_BallsUpdate(void)
* ACTION   : RenderEntry_BallsUpdate
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_BallsUpdate(void)
{
	U16				i;

	for( i=0; i<dRENTRY_JUGGLEBALL_LIMIT; i++ )
	{
		gREntryJuggleIndex[ i ] += gRentryJuggleStep[ i ];

		if( gREntryJuggleIndex[ i ] < 0 )
		{
			gREntryJuggleIndex[ i ] = 0;
			gRentryJuggleStep[ i ]  = 1;
		}
		else if( gREntryJuggleIndex[ i ] >= dRENTRY_JUGGLEPOS_LIMIT )
		{
			gREntryJuggleIndex[ i ] = dRENTRY_JUGGLEPOS_LIMIT-1;
			gRentryJuggleStep[ i ]  = -1;
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_UnDrawBalls(sGraphicCanvas * apCanvas)
* ACTION   : RenderEntry_UnDrawBalls
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_UnDrawBalls(sGraphicCanvas * apCanvas)
{
	sGraphicRect	lRect;
	U16				i;
	U16				lScreenIndex;

	lScreenIndex = Screen_GetLogicIndex();

	for( i=0; i<dRENTRY_JUGGLEBALL_LIMIT; i++ )
	{
		lRect.mX      = gREntryJuggleUnDrawPos[ lScreenIndex ][ i ].mX;
		lRect.mY      = gREntryJuggleUnDrawPos[ lScreenIndex ][ i ].mY;
		lRect.mWidth  = 8;
		lRect.mHeight = 8;

		apCanvas->mpFuncs->Blit(
			apCanvas,
			(sGraphicPos*)&gREntryJuggleUnDrawPos[ lScreenIndex ][ i ],
			&lRect,
			Screen_GetpBackGraphic() );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void RenderEntry_DrawBalls(sGraphicCanvas * apCanvas)
* ACTION   : RenderEntry_DrawBalls
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void RenderEntry_DrawBalls(sGraphicCanvas * apCanvas)
{
	char			lString[ 2 ];
	U16				i;
	U16				lIndex;
	U16				lScreenIndex;

	if( gREntryMode == eRENTRY_MODE_NORMAL )
	{
		lScreenIndex = Screen_GetLogicIndex();

		lString[ 0 ] = gREntryLetter;
		lString[ 1 ] = 0;

		for( i=0; i<dRENTRY_JUGGLEBALL_LIMIT; i++ )
		{
			lIndex = gREntryJuggleIndex[ i ];

			gREntryJuggleUnDrawPos[ lScreenIndex ][ i ].mX = gREntryJugglePos[ lIndex ].mX;
			gREntryJuggleUnDrawPos[ lScreenIndex ][ i ].mY = gREntryJugglePos[ lIndex ].mY;

			RenderFont_Print( dRENTRY_JUGGLE_FONT, lString, apCanvas, gREntryJugglePos[ lIndex ].mX,  gREntryJugglePos[ lIndex ].mY );
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_Load( void )
* ACTION   : loads all resources for Entry
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderEntry_Load( void )
{
	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderEntry_UnLoad( void )
* ACTION   : releases memory used by Entry
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderEntry_UnLoad( void )
{
	return( 1 );
}


/* ################################################################################ */
