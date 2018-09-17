/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"BALLS.H"

#include	"BUILD.H"
#include	"CLOCK.H"
#include	"DATALOG.H"
#include	"OBJECTS.H"
#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	"A_GAME.H"
#include	"A_SPL.H"

#include	<GODLIB\MFP\MFP.H>


/* ###################################################################################
#  ENUM
################################################################################### */

enum
{
	eBALL_STATE_MOVE,
	eBALL_STATE_BOUNCE,
	eBALL_STATE_DIE,
};


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dBALL_LIMIT	3

#define	dBALL_VEL_MAX		0x10000000L
#define	dBALL_VEL_MIN		0x08000000L
#define	dBALL_VEL_MID		0x0A000000L
#define	dBALL_ACC_MIN		0x00000800L

#define	dBALL_VEL_MAX_B		0x18000000L
#define	dBALL_VEL_MIN_B		0x0A000000L
#define	dBALL_VEL_MID_B		0x10000000L
#define	dBALL_ACC_MIN_B		0x00001000L

#define	dBALL_BOUNCE_WAIT	15

#define	dBALL_FRAMERATE		4L
#define	dBALL_FRAMEMAX		16L


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	uS32	Pos;
	uS32	Vel;
	uS32	Acc;
	uS32	Mid;
	uS32	Max;
	uS32	OldPos;
	U16		Wait;
	U8		Redraw;
	U8		Dir;
	U8		State;
	U8		Frame;
} sBall;


/* ###################################################################################
#  DATA
################################################################################### */

sBall	gBalls[ dBALL_LIMIT ];
U16		gBallsState;
U32		gBallsTime;

S16	gBallsFrameLimits[ dBALL_LIMIT ] =
{
	dOBJ_BALL0_FRAME_LIMIT,
	dOBJ_BALL1_FRAME_LIMIT,
	dOBJ_BALL2_FRAME_LIMIT
};

U16	gBallsLeftCatch[ dBALL_LIMIT ] =
{
	0,1,2
};

U16	gBallsRightCatch[ dBALL_LIMIT ] =
{
	2,1,0
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		Balls_Load( void );
U8		Balls_UnLoad( void );

S16		Balls_GetX( const U16 aBallType, const S16 aFrame );

void	Balls_ballsinfo_CLI( const char * apArgs );

void	Balls_Draw( const U16 aBallIndex, const U16 aPos, const U16 aFrame );
void	Balls_UnDraw( const U16 aBallIndex, const U16 aPos );
void	Balls_Move( void );
void	Balls_DrawAll( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Balls_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Balls_Init( void )
{
	U16	i;

	Resource_Attach( eSECTION_GLOBAL, Balls_Load, Balls_UnLoad );

	for( i=0; i<dBALL_LIMIT; i++ )
	{
		gBalls[ i ].Pos.l = 0;
		gBalls[ i ].OldPos.l = 0;
		gBalls[ i ].Vel.l = 0;
		gBalls[ i ].Acc.l = 0;
		gBalls[ i ].Dir   = 0;
		gBalls[ i ].Redraw = 0;
	}

	Build_CliCmdInit( "ballinfo", Balls_ballsinfo_CLI );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Balls_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Balls_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Balls_GameInit(void)
* ACTION   : Balls_GameInit
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Balls_GameInit(void)
{
	U16	i;

	for( i=0; i<dBALL_LIMIT; i++ )
	{
		gBalls[ i ].Pos.l = 0;
		if( DataLog_GetEntry( eDATALOG_GAMETYPE ) )
		{
			gBalls[ i ].Vel.l = dBALL_VEL_MIN_B;
			gBalls[ i ].Acc.l = dBALL_ACC_MIN_B;
			gBalls[ i ].Mid.l = dBALL_VEL_MID_B;
			gBalls[ i ].Max.l = dBALL_VEL_MAX_B;
		}
		else
		{
			gBalls[ i ].Vel.l = dBALL_VEL_MIN;
			gBalls[ i ].Acc.l = dBALL_ACC_MIN;
			gBalls[ i ].Mid.l = dBALL_VEL_MID;
			gBalls[ i ].Max.l = dBALL_VEL_MAX;
		}
		gBalls[ i ].State = eBALL_STATE_MOVE;
	}

	gBalls[ 0 ].Pos.w.w1 = 2;
	gBalls[ 0 ].Dir      = 1;

	gBalls[ 1 ].Pos.w.w1 = gBallsFrameLimits[ 1 ]-3;
	gBalls[ 1 ].Dir      = 0;
		
	gBalls[ 2 ].Pos.w.w1 = 2;
	gBalls[ 2 ].Dir      = 1;

	gBallsState = eBALLS_STATE_NORMAL;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Balls_LevelInit(void)
* ACTION   : Balls_LevelInit
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Balls_LevelInit(void)
{
	U16	i;

	for( i=0; i<dBALL_LIMIT; i++ )
	{
		Balls_Draw( i, gBalls[ i ].Pos.w.w1, 0 );
	}
	gBallsState = eBALLS_STATE_NORMAL;
	gBallsTime  = 0;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Balls_Update(void)
* ACTION   : Balls_Update
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Balls_Update(void)
{
	U32		i;
	U32		lTime;
	U32		lTimeDiff;

	lTime = Clocks_GetElapsedTicks( eCLOCK_GAME );

	if( lTime < gBallsTime )
	{
		gBallsTime = lTime;
	}

	lTimeDiff = lTime - gBallsTime;

	Build_CliPrintfLine3( "T:%lX lTime %lX diff %lX", gBallsTime, lTime, lTimeDiff );

	if( lTimeDiff )
	{
		lTimeDiff /= dBALL_FRAMERATE;


		if( lTimeDiff > dBALL_FRAMEMAX )
		{
			lTimeDiff = dBALL_FRAMEMAX;
		}

		for( i=0; i<dBALL_LIMIT; i++ )
		{
			gBalls[ i ].OldPos.l = gBalls[ i ].Pos.l;
		}

		for( i=0; i<lTimeDiff; i++ )
		{
			Balls_Move();
		}

		gBallsTime += (lTimeDiff*dBALL_FRAMERATE);
		Build_CliPrintfLine2( "moves %lX gbalst %lX", lTimeDiff, gBallsTime );
		
		Balls_DrawAll();
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Balls_Move(void)
* ACTION   : Balls_Move
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Balls_Move(void)
{
	uS32	lVel;
	U16		i;

	for( i=0; i<dBALL_LIMIT; i++ )
	{
		switch( gBalls[ i ].State )
		{
		case	eBALL_STATE_MOVE:
			if( 2 == gBalls[ i ].Pos.w.w1 )
			{
				if( Player_GetPos() == gBallsLeftCatch[ i ] )
				{
					if( 0==gBalls[ i ].Dir )
					{
						Player_AddScore( 1 );
						gBalls[ i ].State = eBALL_STATE_BOUNCE;
						gBalls[ i ].Dir   = 1;
						gBalls[ i ].Wait  = dBALL_BOUNCE_WAIT;
						gBalls[ i ].Redraw = 1;
						if( gBallsState != eBALLS_STATE_DEAD )
						{
							AudioGame_PlaySampleDirect( eAGAME_BALL_CATCH, AudioGame_GetPanX( Balls_GetX( i, gBalls[ i ].Pos.w.w1 ) ) );
						}
					}
				}
			}

			if( gBalls[ i ].Pos.w.w1 == (gBallsFrameLimits[ i ]-3) )
			{
				if( Player_GetPos() == gBallsRightCatch[ i ] )
				{
					if( gBalls[ i ].Dir )
					{
						Player_AddScore( 1 );
						gBalls[ i ].State = eBALL_STATE_BOUNCE;
						gBalls[ i ].Dir = 0;
						gBalls[ i ].Wait  = dBALL_BOUNCE_WAIT;
						gBalls[ i ].Redraw = 1;
						if( gBallsState != eBALLS_STATE_DEAD )
						{
							AudioGame_PlaySampleDirect( eAGAME_BALL_CATCH, AudioGame_GetPanX( Balls_GetX( i, gBalls[ i ].Pos.w.w1 ) ) );
						}
					}
				}
			}


			lVel.w.w0 = gBalls[ i ].Vel.w.w1;
			lVel.w.w1 = 0;
			if( gBalls[ i ].State == eBALL_STATE_MOVE )
			{
				if( gBalls[ i ].Dir )
				{
					gBalls[ i ].Pos.l += lVel.l;
				}
				else
				{
					gBalls[ i ].Pos.l -= lVel.l;
				}
			}

			if( gBallsState != eBALLS_STATE_DEAD )
			{
				if( (gBalls[ i ].Pos.w.w1 <= 1) || (gBalls[ i ].Pos.w.w1 >= (gBallsFrameLimits[ i ]-2)) )
				{
					gBallsState = eBALLS_STATE_FALLING;
				}
			}

			if( gBalls[ i ].Pos.w.w1 <= 0 )
			{
				gBallsState = eBALLS_STATE_DEAD;

				gBalls[ i ].Pos.l = 0;
				gBalls[ i ].State = eBALL_STATE_DIE;
				gBalls[ i ].Redraw = 1;
				AudioGame_PlaySampleDirect( eAGAME_BALL_DROP,AudioGame_GetPanX( Balls_GetX( i, gBalls[ i ].Pos.w.w1 ) ) );
			}
			else if( gBalls[ i ].Pos.w.w1 >= (gBallsFrameLimits[ i ]-1) )
			{
				gBallsState = eBALLS_STATE_DEAD;

				gBalls[ i ].Pos.w.w1 = gBallsFrameLimits[ i ]-1;
				gBalls[ i ].State = eBALL_STATE_DIE;
				gBalls[ i ].Redraw = 1;
				AudioGame_PlaySampleDirect( eAGAME_BALL_DROP, AudioGame_GetPanX( Balls_GetX( i, gBalls[ i ].Pos.w.w1 ) ) );
			}
			break;

		case	eBALL_STATE_BOUNCE:
			if( gBalls[ i ].Wait )
			{
				gBalls[ i ].Wait--;
			}
			else
			{
				gBalls[ i ].Vel.l += gBalls[ i ].Acc.l;
				if( gBalls[ i ].Vel.l > gBalls[ i ].Max.l )
				{
					gBalls[ i ].Vel.l = gBalls[ i ].Mid.l;
				}
				gBalls[ i ].State = eBALL_STATE_MOVE;
			}
			break;

		}
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Balls_DrawAll(void)
* ACTION   : Balls_DrawAll
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Balls_DrawAll(void)
{
	U16	i;
	U16	lFrame;

	for( i=0; i<dBALL_LIMIT; i++ )
	{
		if( (gBalls[ i ].Redraw) || (gBalls[ i ].OldPos.w.w1 != gBalls[ i ].Pos.w.w1) )
		{
			Balls_UnDraw( i, gBalls[ i ].OldPos.w.w1 );

			if( gBalls[ i ].State == eBALL_STATE_BOUNCE )
			{
				lFrame = 1;
			}
			else
			{
				if( gBalls[ i ].State == eBALL_STATE_MOVE )
				{
					if( gBallsState != eBALLS_STATE_DEAD )
					{
						AudioGame_PlaySampleDirect( eAGAME_BALL_MOVE, AudioGame_GetPanX( Balls_GetX( i, gBalls[ i ].Pos.w.w1 ) ) );
					}
				}
				lFrame = 0;
			}

			Balls_Draw( i, gBalls[ i ].Pos.w.w1, lFrame );
			gBalls[ i ].Redraw = 0;
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Balls_UnDraw(const U16 aIndex,const U16 aPos)
* ACTION   : Balls_UnDraw
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Balls_UnDraw(const U16 aIndex,const U16 aPos)
{
	sObject *	lpObject;
	U16			lIndex;
	
	lpObject = Objects_GetpObjects();
	
	switch( aIndex )
	{
	case	0:
		lIndex = dOBJ_BALL0;
		break;
	case	1:
		lIndex = dOBJ_BALL1;
		break;
	case	2:
		lIndex = dOBJ_BALL2;
		break;
	default:
		return;
	}

	lpObject[ lIndex + aPos ].UnDrawFlag = 2;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Balls_Draw(const U16 aIndex,const U16 aPos,const U16 aFrame)
* ACTION   : Balls_Draw
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Balls_Draw(const U16 aIndex,const U16 aPos,const U16 aFrame)
{
	sObject *	lpObject;
	U16			lIndex;
	
	lpObject = Objects_GetpObjects();
	
	switch( aIndex )
	{
	case	0:
		lIndex = dOBJ_BALL0;
		break;
	case	1:
		lIndex = dOBJ_BALL1;
		break;
	case	2:
		lIndex = dOBJ_BALL2;
		break;
	default:
		return;
	}

	lpObject[ lIndex + aPos ].DrawFlag = 2;
	lpObject[ lIndex + aPos ].Frame      = (U8)aFrame;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : U16 Balls_GetState(void)
* ACTION   : Balls_GetState
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

U16 Balls_GetState(void)
{
	return( gBallsState );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : S16 Balls_GetX(const U16 aBallType,const S16 aFrame)
* ACTION   : Balls_GetX
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

S16 Balls_GetX(const U16 aBallType,const S16 aFrame)
{
	sObject *	lpObject;
	S16			lFrame;

	lFrame = aFrame;
	if( lFrame < 0 )
	{
		lFrame = 0;
	}

	switch( aBallType )
	{
	case	0:
		lpObject = &Objects_GetpObjects()[ dOBJ_BALL0 ];
		if( lFrame >= dOBJ_BALL0_FRAME_LIMIT )
		{
			lFrame = dOBJ_BALL0_FRAME_LIMIT-1;
		}
		break;
	case	1:
		lpObject = &Objects_GetpObjects()[ dOBJ_BALL1 ];
		if( lFrame >= dOBJ_BALL1_FRAME_LIMIT )
		{
			lFrame = dOBJ_BALL1_FRAME_LIMIT-1;
		}
		break;
	case	2:
		lpObject = &Objects_GetpObjects()[ dOBJ_BALL2 ];
		if( lFrame >= dOBJ_BALL2_FRAME_LIMIT )
		{
			lFrame = dOBJ_BALL2_FRAME_LIMIT-1;
		}
		break;
	default:
		return( 0 );
	}
	
	lpObject += lFrame;

	return( lpObject->X );
}

void	Balls_ballsinfo_CLI( const char * apArgs )
{
	U16	i;

	(void)apArgs;
	for( i=0; i<dBALL_LIMIT; i++ )
	{
		Build_CliPrintfLine2( "%d VEL : %lX", i, gBalls[ i ].Vel.l );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Balls_Load( void )
* ACTION   : loads all resources for intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	Balls_Load( void )
{
	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Balls_UnLoad( void )
* ACTION   : releases memory used by intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	Balls_UnLoad( void )
{
	return( 1 );
}


/* ################################################################################ */
