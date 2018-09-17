/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"PLAYER.H"

#include	"DATALOG.H"
#include	"GAME.H"
#include	"BUILD.H"
#include	"OBJECTS.H"

#include	"R_SCORE.H"

#include	<GODLIB\ASSERT\ASSERT.H>
#include	<GODLIB\DEBUGLOG\DEBUGLOG.H>
#include	<GODLIB\FILE\FILE.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\VIDEO\VIDEO.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dPLAYER_BUTTON_DRAIN	20


/* ###################################################################################
#  DATA
################################################################################### */

sPlayer	gPlayer;
sInput	gPlayerChosenInput;
sInput	gPlayerKeybdInput;



/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Player_Undraw( void );
void	Player_Draw( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Player_Init( void )
* ACTION   : called at start of app
* CREATION : 14.04.00 PNK
*-----------------------------------------------------------------------------------*/

void	Player_Init( void )
{
	gPlayer.Score  = 0;
	gPlayer.Pos   = 1;

	Input_Init( &gPlayer.Input );
	Input_Init( &gPlayerChosenInput );
	Input_Init( &gPlayerKeybdInput );


	gPlayerChosenInput.mInputType                    = eINPUTTYPE_IKBD;
	gPlayerChosenInput.mScanCodes[ eINPUTKEY_LEFT  ] = eIKBDSCAN_LEFTSHIFT;
	gPlayerChosenInput.mScanCodes[ eINPUTKEY_RIGHT ] = eIKBDSCAN_RIGHTSHIFT;
	gPlayerChosenInput.mScanCodes[ eINPUTKEY_DOWN  ] = eIKBDSCAN_NUMPAD8;
	gPlayerChosenInput.mScanCodes[ eINPUTKEY_UP    ] = eIKBDSCAN_NUMPAD2;
	gPlayerChosenInput.mScanCodes[ eINPUTKEY_FIREA ] = eIKBDSCAN_NUMPADENTER;
	gPlayerChosenInput.mScanCodes[ eINPUTKEY_FIREB ] = eIKBDSCAN_HELP;
	gPlayerChosenInput.mScanCodes[ eINPUTKEY_PAUSE ] = eIKBDSCAN_P;
	gPlayerChosenInput.mScanCodes[ eINPUTKEY_QUIT  ] = eIKBDSCAN_Q;

	gPlayerKeybdInput.mInputType                    = eINPUTTYPE_IKBD;
	gPlayerKeybdInput.mScanCodes[ eINPUTKEY_LEFT  ] = eIKBDSCAN_LEFTARROW;
	gPlayerKeybdInput.mScanCodes[ eINPUTKEY_RIGHT ] = eIKBDSCAN_RIGHTARROW;
	gPlayerKeybdInput.mScanCodes[ eINPUTKEY_DOWN  ] = eIKBDSCAN_DOWNARROW;
	gPlayerKeybdInput.mScanCodes[ eINPUTKEY_UP    ] = eIKBDSCAN_UPARROW;
	gPlayerKeybdInput.mScanCodes[ eINPUTKEY_FIREA ] = eIKBDSCAN_SPACE;
	gPlayerKeybdInput.mScanCodes[ eINPUTKEY_FIREB ] = eIKBDSCAN_UNDO;
	gPlayerKeybdInput.mScanCodes[ eINPUTKEY_PAUSE ] = eIKBDSCAN_F1;
	gPlayerKeybdInput.mScanCodes[ eINPUTKEY_QUIT  ] = eIKBDSCAN_F10;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Player_DeInit( void )
* ACTION   : called at end of app
* CREATION : 14.04.00 PNK
*-----------------------------------------------------------------------------------*/

void	Player_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Player_GameInit( void )
* ACTION   : called at start of game
* CREATION : 14.04.00 PNK
*-----------------------------------------------------------------------------------*/

void	Player_GameInit( void )
{
	gPlayer.Score = 0;

	gPlayerChosenInput.mInputType = (U16)DataLog_GetEntry( eDATALOG_CONTROL );

	Input_Init( &gPlayer.Input );
	Input_Init( &gPlayerChosenInput );
	Input_Init( &gPlayerKeybdInput );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Player_LevelInit( void )
* ACTION   : called at start of level
* CREATION : 14.04.00 PNK
*-----------------------------------------------------------------------------------*/

void	Player_LevelInit( void )
{
	gPlayer.Pos   = 1;
	gPlayer.Score = 0;
	gPlayer.LeftDrain  = 0;
	gPlayer.RightDrain = 0;
	Player_Draw();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Player_InputUpdate(void)
* ACTION   : Player_InputUpdate
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Player_InputUpdate(void)
{
	U16	i;

	IKBD_Update();

	Input_Update( &gPlayerChosenInput );
	Input_Update( &gPlayerKeybdInput );

	for( i=0; i<eINPUTKEY_LIMIT; i++ )
	{
		if( gPlayerChosenInput.mKeyStatus[ i ] )
		{
			gPlayer.Input.mKeyStatus[ i ] = gPlayerChosenInput.mKeyStatus[ i ];
		}
		else if( gPlayerKeybdInput.mKeyStatus[ i ] )
		{
			gPlayer.Input.mKeyStatus[ i ] = gPlayerKeybdInput.mKeyStatus[ i ];
		}
		else
		{
			gPlayer.Input.mKeyStatus[ i ] = eINPUTKEYSTATUS_NONE;
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Player_Update( void )
* ACTION   : called every game frame
* CREATION : 14.04.00 PNK
*-----------------------------------------------------------------------------------*/

void	Player_Update( void )
{
	sObject *	lpObject;

	lpObject = Objects_GetpObjects();

	Player_InputUpdate();

	if( gPlayer.Input.mKeyStatus[ eINPUTKEY_LEFT ] & eINPUTKEYSTATUS_HIT )
	{

		if( gPlayer.Pos )
		{
			Player_Undraw();
			gPlayer.Pos--;
			Player_Draw();
		}
	}
	else if( gPlayer.Input.mKeyStatus[ eINPUTKEY_RIGHT ] & eINPUTKEYSTATUS_HIT )
	{
		if( gPlayer.Pos < 2 )
		{
			Player_Undraw();
			gPlayer.Pos++;
			Player_Draw();
		}
	}

	if( gPlayer.Input.mKeyStatus[ eINPUTKEY_LEFT ] & eINPUTKEYSTATUS_HELD )
	{
		lpObject[ dOBJ_BUTTON_LEFT ].DrawFlag  = 2;
	}
	else
	{
		lpObject[ dOBJ_BUTTON_LEFT ].UnDrawFlag  = 2;
	}

	if( gPlayer.Input.mKeyStatus[ eINPUTKEY_RIGHT ] & eINPUTKEYSTATUS_HELD )
	{
		lpObject[ dOBJ_BUTTON_RIGHT ].DrawFlag  = 2;
	}
	else
	{
		lpObject[ dOBJ_BUTTON_RIGHT ].UnDrawFlag  = 2;
	}
}



/*-----------------------------------------------------------------------------------*
* FUNCTION : Player_AddScore( U16 aPlayerIndex, U32 aScore )
* ACTION   : adds aScore to player score
* CREATION : 14.04.00 PNK
*-----------------------------------------------------------------------------------*/

void	Player_AddScore(  U16 aScore )
{
	gPlayer.Score += aScore;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Player_Undraw(void)
* ACTION   : Player_Undraw
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Player_Undraw(void)
{
	sObject *	lpObject;
	
	lpObject = Objects_GetpObjects();
	lpObject[ dOBJ_ARM_LEFT  + gPlayer.Pos ].UnDrawFlag = 2;
	lpObject[ dOBJ_ARM_RIGHT + gPlayer.Pos ].UnDrawFlag = 2;
	lpObject[ dOBJ_LEG_LEFT  + gPlayer.Pos ].UnDrawFlag = 2;
	lpObject[ dOBJ_LEG_RIGHT + gPlayer.Pos ].UnDrawFlag = 2;
	lpObject[ dOBJ_EYE_LEFT  + gPlayer.Pos ].UnDrawFlag = 2;
	lpObject[ dOBJ_EYE_RIGHT + gPlayer.Pos ].UnDrawFlag = 2;
}

void	Player_Draw( void )
{
	sObject *	lpObject;
	
	lpObject = Objects_GetpObjects();
	lpObject[ dOBJ_ARM_LEFT  + gPlayer.Pos ].DrawFlag = 2;
	lpObject[ dOBJ_ARM_RIGHT + gPlayer.Pos ].DrawFlag = 2;
	lpObject[ dOBJ_LEG_LEFT  + gPlayer.Pos ].DrawFlag = 2;
	lpObject[ dOBJ_LEG_RIGHT + gPlayer.Pos ].DrawFlag = 2;
	lpObject[ dOBJ_EYE_LEFT  + gPlayer.Pos ].DrawFlag = 2;
	lpObject[ dOBJ_EYE_RIGHT + gPlayer.Pos ].DrawFlag = 2;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Player_GetpPlayer( U16 aIndex )
* ACTION   : returns pointer to player aIndex
* CREATION : 14.04.00 PNK
*-----------------------------------------------------------------------------------*/

sPlayer * Player_GetpPlayer( void )
{
	return( &gPlayer );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : U16 Player_GetPos(void)
* ACTION   : Player_GetPos
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

U16 Player_GetPos(void)
{
	return( gPlayer.Pos );
}


/* ################################################################################ */
