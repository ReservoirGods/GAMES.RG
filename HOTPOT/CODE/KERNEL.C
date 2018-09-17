/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"KERNEL.H"

#include	"BUILD.H"
#include	"CLOCK2.H"
#include	"DATALOG.H"
#include	"DEMO.H"
#include	"GAMESAVE.H"
#include	"INTRO.H"
#include	"FRONTEND.H"
#include	"GAME.H"
#include	"HISCORE.H"
#include	"RESOURCE.H"

#include	"A_MAIN.H"
#include	"A_MUSIC.H"
#include	"R_MAIN.H"

#include	<GODLIB\PLATFORM\PLATFORM.H>


/* ###################################################################################
#  DATA
################################################################################### */

U16		gKernelShutdownFlag;
U16		gKernelState;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Kernel_DoLogic( void );
void	Kernel_DoProcess( void );

U16		Kernel_GetState( void );
void	Kernel_SetState( const U16 aState );
U16		Kernel_GetShutdownFlag( void );
void	Kernel_SetShutdownFlag( const U16 aState );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HotPotKernel_Init( void )
{
	char	lString[ 40 ];
	Platform_Init();

	Build_CliInit();

	Build_CliPrintLine( "HotPot CLI" );
	sprintf( lString, "BUILD : %d.%02d", dBUILD_NUMBER_HI, dBUILD_NUMBER_LO );
	Build_CliPrintLine( lString );
	sprintf( lString, "DATE  : %s", __DATE__ );
	Build_CliPrintLine( lString );
	sprintf( lString, "TIME  : %s", __TIME__ );
	Build_CliPrintLine( lString );

	Resource_Init();

	DataLog_Init();
	HiScore_Init();
	GameSave_Load();
	Clock_Init();
	Demo_Init();
	FrontEnd_Init();
	Game_Init();
	Intro_Init();
	RenderMain_Init();
	AudioMain_Init();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HotPotKernel_DeInit( void )
{
	AudioMain_DeInit();
	Clock_DeInit();
	Demo_DeInit();
	FrontEnd_DeInit();
	Game_DeInit();
	HiScore_DeInit();
	Intro_DeInit();

	DataLog_DeInit();
	Resource_DeInit();

	RenderMain_DeInit();
	Build_CliDeInit();
	Platform_DeInit();
	GameSave_Save();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_Main( void )
* ACTION   : main kernel loop
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HotPotKernel_Main( void )
{
	Kernel_SetShutdownFlag( 0 );
	Kernel_SetState( eKERNELSTATE_INTRO );

/*	Resource_LogGenerate();*/


	Clocks_StartClock( eCLOCK_APP );
	while( !Kernel_GetShutdownFlag() )
	{
		Kernel_DoProcess();
		Kernel_DoLogic();
	}
	Clocks_StopClock( eCLOCK_APP );

	Resource_LeaveSection( eSECTION_GLOBAL );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_DoLogic()
* ACTION   : work out what to do
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Kernel_DoLogic()
{

	switch( Kernel_GetState() )
	{

	case	eKERNELSTATE_INTRO:
		Kernel_SetState( eKERNELSTATE_FRONTEND );
		break;

	case	eKERNELSTATE_FRONTEND:
		Kernel_SetState( eKERNELSTATE_GAME     );
		break;

	case	eKERNELSTATE_GAME:
/* check for quit, if so goto fe */
		Kernel_SetState( eKERNELSTATE_HIGHSCORES     );
		break;

	case	eKERNELSTATE_HIGHSCORES:
		Kernel_SetState( eKERNELSTATE_FRONTEND );
		break;

	case	eKERNELSTATE_DEMO:
		Kernel_SetState( eKERNELSTATE_FRONTEND );
		break;

	case	eKERNELSTATE_EXIT:
		HotPotKernel_RequestShutdown();
		break;

	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_DoProcess()
* ACTION   : execute sub processes
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Kernel_DoProcess()
{

	switch( Kernel_GetState() )
	{

	case	eKERNELSTATE_INTRO:
		Resource_EnterSection( eSECTION_INTRO );
		Intro_Main();
		Resource_LeaveSection( eSECTION_INTRO );
		Resource_EnterSection( eSECTION_GLOBAL );
		break;

	case	eKERNELSTATE_FRONTEND:
		FrontEnd_Main();
		break;

	case	eKERNELSTATE_GAME:
		Game_Main();
		break;

	case	eKERNELSTATE_HIGHSCORES:
		HiScore_Main();
		break;

	case	eKERNELSTATE_DEMO:
		Demo_Main();
		break;

	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_GetState( void )
* ACTION   : requests that kernel be shutdown on next kernel loop
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HotPotKernel_RequestShutdown( void )
{
	gKernelShutdownFlag = 1;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_GetState( void )
* ACTION   : returns kernel state
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16		Kernel_GetState( void )
{
	return( gKernelState );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_SetState( const U16 aState )
* ACTION   : sets kernel state
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Kernel_SetState( const U16 aState )
{
	gKernelState = aState;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_GetShutdownFlag( void )
* ACTION   : returns shutdown flag
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16		Kernel_GetShutdownFlag( void )
{
	return( gKernelShutdownFlag );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Kernel_SetShutdownFlag( const U16 aShutdown )
* ACTION   : sets shutdown flag
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Kernel_SetShutdownFlag( const U16 aShutdown )
{
	gKernelShutdownFlag = aShutdown;
}


/* ################################################################################ */
