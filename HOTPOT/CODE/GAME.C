/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"GAME.H"

#include	"BALLS.H"
#include	"BUILD.H"
#include	"CLOCK2.H"
#include	"DATALOG.H"
#include	"HISCORE.H"
#include	"OBJECTS.H"
#include	"PLAYER.H"
#include	"RANDOM.H"

#include	"A_GAME.H"
#include	"A_MUSIC.H"

#include	"R_BG.H"
#include	"R_GAME.H"
#include	"R_PAUSE.H"

#include	"KERNEL.H"

#include	<GODLIB\DEBUGLOG\DEBUGLOG.H>
#include	<GODLIB\FADE\FADE.H>
#include	<GODLIB\INPUT\INPUT.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\PROFILER\PROFILER.H>
#include	<GODLIB\SCREEN\SCREEN.H>


/* ###################################################################################
#  DATA
################################################################################### */

U16	gGameMode;
U16	gGameState;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Game_DoPause( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_Init( void )
{
	DebugLog_Printf0( "Game_Init" );
	Balls_Init();
	Objects_Init();
	Player_Init();
	Random_Init();
	AudioGame_Init();
	RenderGame_Init();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_DeInit( void )
{
	Balls_DeInit();
	Objects_DeInit();
	Player_DeInit();
	Random_DeInit();
	AudioGame_DeInit();
	RenderGame_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_GameInit( void )
* ACTION   : called at start of game
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_GameInit( void )
{
	Balls_GameInit();
	Objects_GameInit();
	Player_GameInit();
	AudioGame_GameInit();
	RenderGame_GameInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_Init( void )
* ACTION   : called at start of level
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_LevelInit( void )
{
	Balls_LevelInit();
	Objects_LevelInit();
	Clocks_LevelInit();
	Player_LevelInit();
	Random_LevelInit();
	AudioGame_LevelInit();
	RenderGame_LevelInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_LevelDeInit( void )
* ACTION   : called at end of level
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_LevelDeInit( void )
{
	RenderGame_LevelDeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_Update( void )
* ACTION   : called ever game frame
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_Update( void )
{
	Balls_Update();
	Objects_Update();
	Player_Update();
	Random_Update();
	Clocks_Update();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_Main( void )
* ACTION   : main game loop
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_Main( void )
{
	U8	lExitFlag;
	U16	i;

	RenderBackGround_FadeDown();
	Game_GameInit();
	Game_LevelInit();

	RenderGame_Update();
	RenderGame_Update();

	RenderBackGround_FadeUp();

	lExitFlag = 0;

	Clocks_StartClock( eCLOCK_GAME );
	while( !lExitFlag )
	{
		RenderGame_Update();
		AudioGame_Update();
		Game_Update();

		if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_QUIT ] & eINPUTKEYSTATUS_HIT )
		{
			lExitFlag = 1;
		}

		if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_PAUSE ] & eINPUTKEYSTATUS_HIT )
		{
			Game_DoPause();
		}

		if( Balls_GetState() == eBALLS_STATE_DEAD )
		{
			lExitFlag = 1;

			for( i=0; i<77; i++ )
			{
				RenderGame_Update();
				AudioGame_Update();
			}
		}
	}
	Clocks_StopClock( eCLOCK_GAME );



	Fade_Main( Fade_GetpBlackPal(), 16 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Game_DoPause(void)
* ACTION   : Game_DoPause
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Game_DoPause(void)
{
	U8	lExitFlag;

	Clocks_PauseClock( eCLOCK_GAME );

	RenderPause_Draw();	
	Screen_Update();

	lExitFlag = 0;
	while( !lExitFlag )
	{
		Player_InputUpdate();

		if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_FIREA ] & eINPUTKEYSTATUS_HIT )
		{
			lExitFlag = 1;
		}
		if( Player_GetpPlayer()->Input.mKeyStatus[ eINPUTKEY_PAUSE ] & eINPUTKEYSTATUS_HIT )
		{
			lExitFlag = 1;
		}
	}

	Screen_Update();
	RenderPause_UnDraw();	

	Clocks_UnPauseClock( eCLOCK_GAME );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_GetState( void )
* ACTION   : returns game state
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16		Game_GetState( void )
{
	return( gGameState );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_SetState( U16 aState )
* ACTION   : sets game state to aState
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_SetState( U16 aState )
{
	gGameState = aState;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_GetMode( void )
* ACTION   : returns game mode
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16		Game_GetMode( void )
{
	return( gGameMode );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Game_SetMode( U16 aMode )
* ACTION   : sets game mode to aMode
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Game_SetMode( U16 aMode )
{
	gGameMode = aMode;
}


/* ################################################################################ */
