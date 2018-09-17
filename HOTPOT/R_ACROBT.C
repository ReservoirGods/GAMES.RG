/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_ACROBT.H"

#include	"BUILD.H"
#include	"OBJECTS.H"

#include	"R_FADE.H"

#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	<GODLIB\GRAPHIC\GRAPHIC.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\PICTYPES\DEGAS.H>

#include	<MATH.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dRACROBATS_LIMIT		2
#define	dRACROBATS_VEL0			0x10000L
#define	dRACROBATS_VEL1			0x0DDDDL
#define	dRACROBATS_POS_LIMIT	512
#define	dRACROBATS_Y			3
#define	dRACROBATS_LEFT_MIN_X	56
#define	dRACROBATS_LEFT_MAX_X	160
#define	dRACROBATS_RIGHT_MIN_X	160
#define	dRACROBATS_RIGHT_MAX_X	(245-34)


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	uU32	PosIndex;
	uU32	Vel;
} sAcrobat;


/* ###################################################################################
#  DATA
################################################################################### */

sSpriteBlock *			gpRAcrobatsSprites;
sGraphicPos				gRAcrobatPos[ 2 ][ dRACROBATS_LIMIT ];
sAcrobat				gRAcrobats[ dRACROBATS_LIMIT ];
S16						gRAcrobatLeftPos[  dRACROBATS_POS_LIMIT ];
S16						gRAcrobatRightPos[ dRACROBATS_POS_LIMIT ];


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		RenderAcrobats_Load( void );
U8		RenderAcrobats_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderAcrobats_Init( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderAcrobats_Init( void )
{
	FP32	lX;
	FP32	lSin;
	FP32	lT,lStep;
	U16		i,j;

	Resource_Attach( eSECTION_GLOBAL, RenderAcrobats_Load, RenderAcrobats_UnLoad );

	lT    = 0.f;
	lStep = 6.283185307f / dRACROBATS_POS_LIMIT;

	for( i=0; i<dRACROBATS_POS_LIMIT; i++ )
	{
		lSin  = (FP32)sin( lT );

		lX    = lSin * ((dRACROBATS_LEFT_MAX_X-dRACROBATS_LEFT_MIN_X)/2);
		lX   += dRACROBATS_LEFT_MIN_X +((dRACROBATS_LEFT_MAX_X-dRACROBATS_LEFT_MIN_X)/2);
		gRAcrobatLeftPos[ i ] = (S16)lX;

		lSin  = (FP32)cos( lT );
		lX    = lSin * ((dRACROBATS_RIGHT_MAX_X-dRACROBATS_RIGHT_MIN_X)/2);
		lX   += dRACROBATS_RIGHT_MIN_X + ((dRACROBATS_RIGHT_MAX_X-dRACROBATS_RIGHT_MIN_X)/2);
		gRAcrobatRightPos[ i ] = (S16)lX;

		lT   += lStep;
	}

	for( i=0; i<2; i++ )
	{
		for( j=0; j<dRACROBATS_LIMIT; j++ )
		{
			gRAcrobatPos[ i ][ j ].mX = 0;
			gRAcrobatPos[ i ][ j ].mY = 0;
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderAcrobats_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderAcrobats_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderAcrobats_GameInit( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderAcrobats_GameInit( void )
{
	U16	i;

	for( i=0; i<dRACROBATS_LIMIT; i++ )
	{
		gRAcrobats[ i ].PosIndex.l = 0;
	}

	gRAcrobats[ 0 ].Vel.l = dRACROBATS_VEL0;
	gRAcrobats[ 1 ].Vel.l = dRACROBATS_VEL0;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderAcrobats_LevelInit( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderAcrobats_LevelInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderAcrobats_Update( void )
* ACTION   : called at end of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderAcrobats_Update( void )
{
	U16				i;
	U16				lScreenIndex;
	U16				lFrame;
	sGraphicRect	lRect;

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();
*/
	lScreenIndex = Screen_GetLogicIndex();

	for( i=0; i<dRACROBATS_LIMIT; i++ )
	{

		lRect.mHeight = gpRAcrobatsSprites->mpSprite[ 0 ]->mHeight;
		lRect.mWidth  = gpRAcrobatsSprites->mpSprite[ 0 ]->mWidth;
		lRect.mX      = gRAcrobatPos[ lScreenIndex ][ i ].mX;
		lRect.mY      = gRAcrobatPos[ lScreenIndex ][ i ].mY;

		Screen_GetpLogicGraphic()->mpFuncs->Blit(
			Screen_GetpLogicGraphic(),
			&gRAcrobatPos[ lScreenIndex ][ i ],
			&lRect,
			Screen_GetpBackGraphic() );
	}


	for( i=0; i<dRACROBATS_LIMIT; i++ )
	{
		gRAcrobats[ i ].PosIndex.l += gRAcrobats[ i ].Vel.l;
		if( gRAcrobats[ i ].PosIndex.w.w1 >= dRACROBATS_POS_LIMIT )
		{
			gRAcrobats[ i ].PosIndex.w.w1 = 0;
		}
	
		if( i )
		{
			gRAcrobatPos[ lScreenIndex ][ i ].mX = gRAcrobatLeftPos[ gRAcrobats[ i ].PosIndex.w.w1 ];
			gRAcrobatPos[ lScreenIndex ][ i ].mY = dRACROBATS_Y;
			lFrame  = gRAcrobatPos[ lScreenIndex ][ i ].mX;
			lFrame -= dRACROBATS_LEFT_MIN_X;
		}
		else
		{
			gRAcrobatPos[ lScreenIndex ][ i ].mX = gRAcrobatRightPos[ gRAcrobats[ i ].PosIndex.w.w1 ];
			gRAcrobatPos[ lScreenIndex ][ i ].mY = dRACROBATS_Y;
			lFrame =  gRAcrobatPos[ lScreenIndex ][ i ].mX;
			lFrame -= dRACROBATS_RIGHT_MIN_X;
		}

		lFrame >>= 3;
		lFrame &=  3;

		Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
			Screen_GetpLogicGraphic(),
			&gRAcrobatPos[ lScreenIndex ][ i ],
			gpRAcrobatsSprites->mpSprite[ lFrame ]  );
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderAcrobats_Load( void )
* ACTION   : loads all resources for intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderAcrobats_Load( void )
{
	gpRAcrobatsSprites = Resource_Load( "ACROBATS.BSB", 0 );

	Sprite_BlockRelocate( gpRAcrobatsSprites );

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderAcrobats_UnLoad( void )
* ACTION   : releases memory used by intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderAcrobats_UnLoad( void )
{
	Resource_UnLoad( gpRAcrobatsSprites );

	return( 1 );
}


/* ################################################################################ */
