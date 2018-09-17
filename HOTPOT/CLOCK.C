/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"CLOCK.H"

#include	"BUILD.H"
#include	"DATALOG.H"

#include	<GODLIB\SYSTEM\SYSTEM.H>
#include	<GODLIB\VBL\VBL.H>


/* ###################################################################################
#  DATA
################################################################################### */

sClock		gClocks[ eCLOCK_LIMIT ];


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Clock_Cli_GameSeconds( const char * apArgs );
void	Clock_Cli_Info( const char * apArgs );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_AppInit( void )
* ACTION   : called at start of app
* CREATION : 26.01.01 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_Init( void )
{
	U16		i;

	for( i=0; i<eCLOCK_LIMIT; i++ )
	{
		gClocks[ i ].mState = eCLOCK_STATE_INACTIVE;
	}
	Clock_Init();
	Clocks_StartClock( eCLOCK_APP );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_AppDeInit( void )
* ACTION   : called at end of app
* CREATION : 26.01.01 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_DeInit( void )
{
	Clock_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_GameInit( void )
* ACTION   : called at start of game
* CREATION : 26.01.01 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_GameInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_GameDeInit( void )
* ACTION   : called at end of game
* CREATION : 26.01.01 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_GameDeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_LevelInit( void )
* ACTION   : called start of level
* CREATION : 26.01.01 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_LevelInit( void )
{
	U32			lSecs;
	sClock *	lpClock;

	Clocks_StartClock( eCLOCK_LEVEL );
	Clocks_PauseClock( eCLOCK_LEVEL );

	lpClock = &gClocks[ eCLOCK_LEVEL ];

	lSecs   = 60 * 3;

	lpClock->mCountDownStartTime.mHours        = 0;
	lpClock->mCountDownStartTime.mMinutes      = (U8)(lSecs / 60L);
	lpClock->mCountDownStartTime.mSeconds      = (U8)(lSecs - (lpClock->mCountDownStartTime.mMinutes*60L));
	lpClock->mCountDownStartTime.mMicroSeconds = 0;

	lpClock->mCountDownTime = lpClock->mCountDownStartTime;
	lpClock->mDuration      = Time_ToU32( &lpClock->mCountDownStartTime );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_LevelDeInit( void )
* ACTION   : called end of level
* CREATION : 26.01.01 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_LevelDeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_Update( void )
* ACTION   : called every game frame
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	Clocks_Update( void )
{
	U16			i;

	for( i=0; i<eCLOCK_LIMIT; i++ )
	{
		Clock_Update( &gClocks[ i ] );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_StartClock( U16 aClockIndex )
* ACTION   : starts clock aClockIndex
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_StartClock( const U16 aClockIndex )
{
	Clock_Start( &gClocks[ aClockIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clock_StoptClock( U16 aClockIndex )
* ACTION   : stops clock aClockIndex
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_StopClock( const U16 aClockIndex )
{
	Clock_Stop( &gClocks[ aClockIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_PauseClock( U16 aClockIndex )
* ACTION   : pauses clock aClockIndex
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_PauseClock( const U16 aClockIndex )
{
	Clock_Pause( &gClocks[ aClockIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Clocks_UnPauseClock( U16 aClockIndex )
* ACTION   : unpauses clock aClockIndex
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void			Clocks_UnPauseClock( const U16 aClockIndex )
{
	Clock_UnPause( &gClocks[ aClockIndex ] );
}



/* ################################################################################ */
