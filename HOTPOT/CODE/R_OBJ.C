/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_OBJ.H"

#include	"BUILD.H"
#include	"OBJECTS.H"
#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>


/* ###################################################################################
#  DATA
################################################################################### */

sSpriteBlock *	gpRObjectsSprites[ eROBJ_LIMIT ];

sTagString	gRObjFileNames[ eROBJ_LIMIT ] =
{
	{	eROBJ_BALL,				"BALL.BSB"		},
	{	eROBJ_ARM_LEFT_0,		"ARML0.BSB"		},
	{	eROBJ_ARM_LEFT_1,		"ARML1.BSB"		},
	{	eROBJ_ARM_LEFT_2,		"ARML2.BSB"		},
	{	eROBJ_ARM_RIGHT_0,		"ARMR0.BSB"		},
	{	eROBJ_ARM_RIGHT_1,		"ARMR1.BSB"		},
	{	eROBJ_ARM_RIGHT_2,		"ARMR2.BSB"		},
	{	eROBJ_EYE_0,			"EYE0.BSB"		},
	{	eROBJ_EYE_1,			"EYE1.BSB"		},
	{	eROBJ_EYE_2,			"EYE2.BSB"		},
	{	eROBJ_LEG_LEFT_0,		"LEGL0.BSB"		},
	{	eROBJ_LEG_LEFT_1,		"LEGL1.BSB"		},
	{	eROBJ_LEG_RIGHT_0,		"LEGR0.BSB"		},
	{	eROBJ_LEG_RIGHT_1,		"LEGR1.BSB"		},
	{	eROBJ_BALL_CRACKED,		"BALLCRAK.BSB"	},
	{	eROBJ_BALL_SQUISHED,	"BALLSQSH.BSB"	},
	{	eROBJ_BUTTON,			"BUTTON.BSB"	},
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		RenderObjects_Load( void );
U8		RenderObjects_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderObjects_Init( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderObjects_Init( void )
{
	Resource_Attach( eSECTION_GLOBAL, RenderObjects_Load, RenderObjects_UnLoad );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderObjects_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderObjects_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderObjects_GameInit( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderObjects_GameInit( void )
{
	U16			i;
	sObject *	lpObject;

	lpObject = &Objects_GetpObjects()[ dOBJ_BALL0 ];
	for( i=0; i<dOBJ_BALL0_FRAME_LIMIT; i++ )
	{
		lpObject->SpriteIndex0 = eROBJ_BALL;
		lpObject++;
	}

	lpObject = &Objects_GetpObjects()[ dOBJ_BALL1 ];
	for( i=0; i<dOBJ_BALL1_FRAME_LIMIT; i++ )
	{
		lpObject->SpriteIndex0 = eROBJ_BALL;
		lpObject++;
	}

	lpObject = &Objects_GetpObjects()[ dOBJ_BALL2 ];
	for( i=0; i<dOBJ_BALL2_FRAME_LIMIT; i++ )
	{
		lpObject->SpriteIndex0 = eROBJ_BALL;
		lpObject++;
	}

	lpObject = Objects_GetpObjects();
	lpObject[ dOBJ_BALL0 + 0 ].SpriteIndex0 = eROBJ_BALL_CRACKED;
	lpObject[ dOBJ_BALL1 + 0 ].SpriteIndex0 = eROBJ_BALL_CRACKED;
	lpObject[ dOBJ_BALL2 + 0 ].SpriteIndex0 = eROBJ_BALL_CRACKED;

	lpObject[ dOBJ_BALL0 + dOBJ_BALL0_FRAME_LIMIT - 1 ].SpriteIndex0 = eROBJ_BALL_CRACKED;
	lpObject[ dOBJ_BALL1 + dOBJ_BALL1_FRAME_LIMIT - 1 ].SpriteIndex0 = eROBJ_BALL_CRACKED;
	lpObject[ dOBJ_BALL2 + dOBJ_BALL2_FRAME_LIMIT - 1 ].SpriteIndex0 = eROBJ_BALL_CRACKED;


	lpObject = &Objects_GetpObjects()[ dOBJ_ARM_LEFT ];

	lpObject[ 0 ].SpriteIndex0 = eROBJ_ARM_LEFT_0;
	lpObject[ 1 ].SpriteIndex0 = eROBJ_ARM_LEFT_1;
	lpObject[ 2 ].SpriteIndex0 = eROBJ_ARM_LEFT_2;

	lpObject = &Objects_GetpObjects()[ dOBJ_ARM_RIGHT ];
	lpObject[ 0 ].SpriteIndex0 = eROBJ_ARM_RIGHT_0;
	lpObject[ 1 ].SpriteIndex0 = eROBJ_ARM_RIGHT_1;
	lpObject[ 2 ].SpriteIndex0 = eROBJ_ARM_RIGHT_2;

	lpObject = &Objects_GetpObjects()[ dOBJ_EYE_LEFT ];
	lpObject[ 0 ].SpriteIndex0 = eROBJ_EYE_0;
	lpObject[ 1 ].SpriteIndex0 = eROBJ_EYE_1;
	lpObject[ 2 ].SpriteIndex0 = eROBJ_EYE_2;

	lpObject = &Objects_GetpObjects()[ dOBJ_EYE_RIGHT ];
	lpObject[ 0 ].SpriteIndex0 = eROBJ_EYE_0;
	lpObject[ 1 ].SpriteIndex0 = eROBJ_EYE_1;
	lpObject[ 2 ].SpriteIndex0 = eROBJ_EYE_2;

	lpObject = &Objects_GetpObjects()[ dOBJ_LEG_LEFT ];
	lpObject[ 0 ].SpriteIndex0 = eROBJ_LEG_LEFT_1;
	lpObject[ 1 ].SpriteIndex0 = eROBJ_LEG_LEFT_1;
	lpObject[ 2 ].SpriteIndex0 = eROBJ_LEG_LEFT_0;

	lpObject = &Objects_GetpObjects()[ dOBJ_LEG_RIGHT ];
	lpObject[ 0 ].SpriteIndex0 = eROBJ_LEG_RIGHT_1;
	lpObject[ 1 ].SpriteIndex0 = eROBJ_LEG_RIGHT_0;
	lpObject[ 2 ].SpriteIndex0 = eROBJ_LEG_RIGHT_0;

	lpObject = &Objects_GetpObjects()[ dOBJ_BUTTON_LEFT ];
	lpObject->SpriteIndex0 = eROBJ_BUTTON;

	lpObject = &Objects_GetpObjects()[ dOBJ_BUTTON_RIGHT ];
	lpObject->SpriteIndex0 = eROBJ_BUTTON;

	lpObject = Objects_GetpObjects();
	for( i=0; i<dOBJ_LIMIT; i++ )
	{
		lpObject->SpriteIndex1 = lpObject->SpriteIndex0;
		lpObject[ i ].Width  = gpRObjectsSprites[ lpObject[ i ].SpriteIndex0 ]->mpSprite[ 0 ]->mWidth;
		lpObject[ i ].Height = gpRObjectsSprites[ lpObject[ i ].SpriteIndex0 ]->mpSprite[ 0 ]->mHeight;
	}

	lpObject = &Objects_GetpObjects()[ dOBJ_BALL0 ];
	lpObject[ 2 ].SpriteIndex1 = eROBJ_BALL_SQUISHED;
	lpObject[ dOBJ_BALL0_FRAME_LIMIT-3 ].SpriteIndex1 = eROBJ_BALL_SQUISHED;

	lpObject = &Objects_GetpObjects()[ dOBJ_BALL1 ];
	lpObject[ 2 ].SpriteIndex1 = eROBJ_BALL_SQUISHED;
	lpObject[ dOBJ_BALL1_FRAME_LIMIT-3 ].SpriteIndex1 = eROBJ_BALL_SQUISHED;

	lpObject = &Objects_GetpObjects()[ dOBJ_BALL2 ];
	lpObject[ 2 ].SpriteIndex1 = eROBJ_BALL_SQUISHED;
	lpObject[ dOBJ_BALL2_FRAME_LIMIT-3 ].SpriteIndex1 = eROBJ_BALL_SQUISHED;

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderObjects_LevelInit( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderObjects_LevelInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderObjects_Update( void )
* ACTION   : called at end of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderObjects_Update( void )
{
	U16			i;
	U16			lSpriteIndex;
	sObject *	lpObject;

/*	RenderScreen_GetpGraphic()->mpVRAM = RenderScreen_GetpLogic();
*/
	lpObject = Objects_GetpObjects();
	for( i=0; i<dOBJ_LIMIT; i++ )
	{
		if( lpObject->DrawFlag )
		{
			if( lpObject->Frame )
			{
				lSpriteIndex = lpObject->SpriteIndex1;
			}
			else
			{
				lSpriteIndex = lpObject->SpriteIndex0;
			}

			Screen_GetpLogicGraphic()->mpFuncs->DrawSprite(
				Screen_GetpLogicGraphic(),
				(sGraphicPos*)&lpObject->X,
				gpRObjectsSprites[ lSpriteIndex ]->mpSprite[ 0 ]  );

			lpObject->DrawFlag--;
		}
		lpObject++;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void * RenderObjects_GetpBallSprite(void)
* ACTION   : RenderObjects_GetpBallSprite
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void * RenderObjects_GetpBallSprite(void)
{
	return( gpRObjectsSprites[ eROBJ_BALL ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void * RenderObjects_GetpObject(const U16 aIndex)
* ACTION   : RenderObjects_GetpObject
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void * RenderObjects_GetpObject(const U16 aIndex)
{
	return( gpRObjectsSprites[ aIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderObjects_Load( void )
* ACTION   : loads all resources for intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderObjects_Load( void )
{
	U16	i;

	for( i=0; i<eROBJ_LIMIT; i++ )
	{
		gpRObjectsSprites[ i ] = Resource_Load( sTagString_GetpString( i, &gRObjFileNames[ i ], eROBJ_LIMIT ), 0 );
		Sprite_BlockRelocate( gpRObjectsSprites[ i ] );
	}

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderObjects_UnLoad( void )
* ACTION   : releases memory used by intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderObjects_UnLoad( void )
{
	U16	i;

	for( i=0; i<eROBJ_LIMIT; i++ )
	{
		Resource_UnLoad( gpRObjectsSprites[ i ] );
	}

	return( 1 );
}


/* ################################################################################ */
