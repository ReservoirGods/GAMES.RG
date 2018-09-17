#ifndef	INCLUDED_OBJECTS_H
#define	INCLUDED_OBJECTS_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

#define	dOBJ_BALL0_FRAME_LIMIT			(12+4)
#define	dOBJ_BALL1_FRAME_LIMIT			(10+4)
#define	dOBJ_BALL2_FRAME_LIMIT			(8+4)
#define	dOBJ_ARM_LEFT_FRAME_LIMIT		3
#define	dOBJ_ARM_RIGHT_FRAME_LIMIT		3
#define	dOBJ_EYE_LEFT_FRAME_LIMIT		3
#define	dOBJ_EYE_RIGHT_FRAME_LIMIT		3
#define	dOBJ_LEG_LEFT_FRAME_LIMIT		3
#define	dOBJ_LEG_RIGHT_FRAME_LIMIT		3
#define	dOBJ_BUTTON_LEFT_FRAME_LIMIT	1
#define	dOBJ_BUTTON_RIGHT_FRAME_LIMIT	1

#define	dOBJ_BALL0			0
#define	dOBJ_BALL1			( dOBJ_BALL0        + dOBJ_BALL0_FRAME_LIMIT        )
#define	dOBJ_BALL2			( dOBJ_BALL1        + dOBJ_BALL1_FRAME_LIMIT        )
#define	dOBJ_ARM_LEFT		( dOBJ_BALL2        + dOBJ_BALL2_FRAME_LIMIT        )
#define	dOBJ_ARM_RIGHT		( dOBJ_ARM_LEFT     + dOBJ_ARM_LEFT_FRAME_LIMIT     )
#define	dOBJ_EYE_LEFT		( dOBJ_ARM_RIGHT    + dOBJ_ARM_RIGHT_FRAME_LIMIT    )
#define	dOBJ_EYE_RIGHT		( dOBJ_EYE_LEFT     + dOBJ_EYE_LEFT_FRAME_LIMIT     )
#define	dOBJ_LEG_LEFT		( dOBJ_EYE_RIGHT    + dOBJ_EYE_RIGHT_FRAME_LIMIT    )
#define	dOBJ_LEG_RIGHT		( dOBJ_LEG_LEFT     + dOBJ_LEG_LEFT_FRAME_LIMIT     )
#define	dOBJ_BUTTON_LEFT	( dOBJ_LEG_RIGHT    + dOBJ_LEG_RIGHT_FRAME_LIMIT    )
#define	dOBJ_BUTTON_RIGHT	( dOBJ_BUTTON_LEFT  + dOBJ_BUTTON_LEFT_FRAME_LIMIT  )
#define	dOBJ_LIMIT			( dOBJ_BUTTON_RIGHT + dOBJ_BUTTON_RIGHT_FRAME_LIMIT )

enum
{
	eOBJ_ENTITY_BALL0,
	eOBJ_ENTITY_BALL1,
	eOBJ_ENTITY_BALL2,
	eOBJ_ENTITY_ARMLEFT,
	eOBJ_ENTITY_ARMRIGHT,
	eOBJ_ENTITY_EYELEFT,
	eOBJ_ENTITY_EYERIGHT,
	eOBJ_ENTITY_LEGLEFT,
	eOBJ_ENTITY_LEGRIGHT,
	eOBJ_ENTITY_BUTTONLEFT,
	eOBJ_ENTITY_BUTTONRIGHT,

	eOBJ_ENTITY_LIMIT
};

enum
{
	eOBJ_FLAG_OFF,
	eOBJ_FLAG_ON
};


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	S16	X;
	S16	Y;
	S16	Width;
	S16	Height;
	U8	UnDrawFlag;
	U8	DrawFlag;
	U8	Entity;
	U8	Frame;
	U16	SpriteIndex0;
	U16	SpriteIndex1;
} sObject;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void		Objects_Init( void );
void		Objects_DeInit( void );
void		Objects_GameInit( void );
void		Objects_LevelInit( void );
void		Objects_Update( void );

sObject *	Objects_GetpObjects( void );


/* ################################################################################ */

#endif	/*	INCLUDED_INTRO_H	*/