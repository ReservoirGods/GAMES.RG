/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"OBJECTS.H"

#include	"RESOURCE.H"


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	S16	X;
	S16	Y;
} sObjPos;


/* ###################################################################################
#  DATA
################################################################################### */

sObject		gObjects[ dOBJ_LIMIT ];

sObjPos		gObjectBall0Pos[ dOBJ_BALL0_FRAME_LIMIT ] =
{
	{	62,		188	},
	{	64,		160	},
	{	64,		120	},
	{	64,		96	},
	{	71,		70	},
	{	84,		48	},
	{	105,	31	},
	{	131,	24	},
	{	161,	24	},
	{	187,	31	},
	{	208,	48	},
	{	221,	70	},
	{	228,	96	},
	{	228,	120	},
	{	228,	160	},
	{	226,	188	},
};

sObjPos		gObjectBall1Pos[ dOBJ_BALL0_FRAME_LIMIT ] =
{
	{	86,		188	},
	{	88,		160	},
	{	88,		120	},
	{	90,		100	},
	{	95,		77	},
	{	110,	58	},
	{	133,	48	},
	{	159,	48	},
	{	182,	58	},
	{	197,	77	},
	{	202,	100	},
	{	204,	120	},
	{	204,	160	},
	{	202,	188	},
};

sObjPos		gObjectBall2Pos[ dOBJ_BALL0_FRAME_LIMIT ] =
{
	{	110,	188	},
	{	112,	160	},
	{	112,	120	},
	{	113,	102	},
	{	121,	84	},
	{	136,	72	},
	{	156,	72	},
	{	171,	84	},
	{	179,	102	},
	{	180,	120	},
	{	180,	160	},
	{	178,	188	},
};

sObjPos		gObjectArmLeftPos[ dOBJ_ARM_LEFT_FRAME_LIMIT ] =
{
	{	61,	128	},
	{	85,	128	},
	{	90,	128	},
};

sObjPos		gObjectArmRightPos[ dOBJ_ARM_RIGHT_FRAME_LIMIT ] =
{
	{	177,	128	},
	{	201,	128	},
	{	206,	128	},
};

sObjPos		gObjectEyeLeftPos[ dOBJ_EYE_LEFT_FRAME_LIMIT ] =
{
	{	137,	121	},
	{	137,	121	},
	{	137,	121	},
};

sObjPos		gObjectEyeRightPos[ dOBJ_EYE_LEFT_FRAME_LIMIT ] =
{
	{	150,	121	},
	{	150,	121	},
	{	150,	121	},
};

sObjPos		gObjectLegLeftPos[ dOBJ_LEG_LEFT_FRAME_LIMIT ] =
{
	{	136,	184	},
	{	136,	184	},
	{	126,	181	},
};

sObjPos		gObjectLegRightPos[ dOBJ_LEG_RIGHT_FRAME_LIMIT ] =
{
	{	159,	181	},
	{	151,	184	},
	{	151,	184	},
};

sObjPos		gObjectButtonLeftPos[ dOBJ_BUTTON_LEFT_FRAME_LIMIT ] =
{
	{	19,158	}
};

sObjPos		gObjectButtonRightPos[ dOBJ_BUTTON_RIGHT_FRAME_LIMIT ] =
{
	{	259,158	}
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8	Objects_Load( void );
U8	Objects_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Objects_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Objects_Init( void )
{
	U16			i;
	sObject *	lpObject;

	Resource_Attach( eSECTION_GLOBAL, Objects_Load, Objects_UnLoad );

	lpObject = &gObjects[ dOBJ_BALL0 ];
	for( i=0; i<dOBJ_BALL0_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectBall0Pos[ i ].X;
		lpObject->Y      = gObjectBall0Pos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_BALL0;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_BALL1 ];
	for( i=0; i<dOBJ_BALL1_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectBall1Pos[ i ].X;
		lpObject->Y      = gObjectBall1Pos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_BALL1;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_BALL2 ];
	for( i=0; i<dOBJ_BALL2_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectBall2Pos[ i ].X;
		lpObject->Y      = gObjectBall2Pos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_BALL2;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_ARM_LEFT ];
	for( i=0; i<dOBJ_ARM_LEFT_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectArmLeftPos[ i ].X;
		lpObject->Y      = gObjectArmLeftPos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_ARMLEFT;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_ARM_RIGHT ];
	for( i=0; i<dOBJ_ARM_RIGHT_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectArmRightPos[ i ].X;
		lpObject->Y      = gObjectArmRightPos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_ARMRIGHT;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_EYE_LEFT ];
	for( i=0; i<dOBJ_EYE_LEFT_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectEyeLeftPos[ i ].X;
		lpObject->Y      = gObjectEyeLeftPos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_EYELEFT;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_EYE_RIGHT ];
	for( i=0; i<dOBJ_EYE_RIGHT_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectEyeRightPos[ i ].X;
		lpObject->Y      = gObjectEyeRightPos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_EYERIGHT;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_LEG_LEFT ];
	for( i=0; i<dOBJ_LEG_LEFT_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectLegLeftPos[ i ].X;
		lpObject->Y      = gObjectLegLeftPos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_LEGLEFT;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_LEG_RIGHT ];
	for( i=0; i<dOBJ_LEG_RIGHT_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectLegRightPos[ i ].X;
		lpObject->Y      = gObjectLegRightPos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_LEGRIGHT;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_BUTTON_LEFT ];
	for( i=0; i<dOBJ_BUTTON_LEFT_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectButtonLeftPos[ i ].X;
		lpObject->Y      = gObjectButtonLeftPos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_BUTTONLEFT;
		lpObject++;
	}

	lpObject = &gObjects[ dOBJ_BUTTON_RIGHT ];
	for( i=0; i<dOBJ_BUTTON_RIGHT_FRAME_LIMIT; i++ )
	{
		lpObject->X      = gObjectButtonRightPos[ i ].X;
		lpObject->Y      = gObjectButtonRightPos[ i ].Y;
		lpObject->Entity = eOBJ_ENTITY_BUTTONRIGHT;
		lpObject++;
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Objects_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Objects_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Objects_GameInit(void)
* ACTION   : Objects_GameInit
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Objects_GameInit(void)
{
	U16	i;

	for( i=0; i<dOBJ_LIMIT; i++ )
	{
		gObjects[ i ].DrawFlag   = 0;
		gObjects[ i ].UnDrawFlag = 0;
		gObjects[ i ].Frame      = 0;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Objects_LevelInit(void)
* ACTION   : Objects_LevelInit
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Objects_LevelInit(void)
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Objects_Update(void)
* ACTION   : Objects_Update
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Objects_Update(void)
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : sObject * Objects_GetpObjects(void)
* ACTION   : Objects_GetpObjects
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

sObject * Objects_GetpObjects(void)
{
	return( &gObjects[ 0 ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Objects_Load( void )
* ACTION   : loads all resources for intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	Objects_Load( void )
{
	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Objects_UnLoad( void )
* ACTION   : releases memory used by intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	Objects_UnLoad( void )
{
	return( 1 );
}


/* ################################################################################ */
