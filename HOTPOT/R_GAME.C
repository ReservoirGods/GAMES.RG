/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_GAME.H"

#include	"BUILD.H"
#include	"CLOCK.H"
#include	"DATALOG.H"
#include	"GAME.H"
#include	"PLAYER.H"

#include	"R_ACROBT.H"
#include	"R_BG.H"
#include	"R_FADE.H"
#include	"R_OBJ.H"
#include	"R_PAUSE.H"
#include	"R_SCORE.H"

#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\VIDEO\VIDEO.H>


/* ###################################################################################
#  DATA
################################################################################### */

U8	gRGameTimeMinutes;
U8	gRGameTimeSeconds;


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderGame_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderGame_Init( void )
{
	RenderAcrobats_Init();
	RenderBackGround_Init();
	RenderObjects_Init();
	RenderPause_Init();
	RenderScore_Init();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderGame_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderGame_DeInit( void )
{
	RenderAcrobats_DeInit();
	RenderBackGround_DeInit();
	RenderObjects_DeInit();
	RenderPause_DeInit();
	RenderScore_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderGame_GameInit( void )
* ACTION   : called at start of game
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderGame_GameInit( void )
{
	RenderAcrobats_GameInit();
	RenderBackGround_GameInit();
	RenderObjects_GameInit();
	RenderPause_GameInit();
	RenderScore_GameInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderGame_Init( void )
* ACTION   : called at start of level
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderGame_LevelInit( void )
{
	RenderAcrobats_LevelInit();
	RenderBackGround_LevelInit();
	RenderObjects_LevelInit();
	RenderPause_LevelInit();
	RenderScore_LevelInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderGame_LevelDeInit( void )
* ACTION   : called at end of level
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderGame_LevelDeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderGame_Main( void )
* ACTION   : main game loop
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderGame_Update( void )
{
	Screen_Update();

	RenderBackGround_Update();
	RenderAcrobats_Update();
	RenderObjects_Update();
	RenderScore_Update();
	RenderPause_Update();
}


/* ################################################################################ */
