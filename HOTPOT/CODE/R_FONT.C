/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_FONT.H"

#include	"RESOURCE.H"

#include	<GODLIB\SPRITE\SPRITE.H>


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	sSpriteBlock *	pSprites;
	U16				Width;
	U16				Height;
	U8				FontMap[ 256 ];
	U8				CharWidths[ 256 ];
} sRFont;


/* ###################################################################################
#  DATA
################################################################################### */

sRFont	gRFonts[ eRFONT_LIMIT ];


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderFont_BuildCharWidthTable( sRFont * apFont );
U8		RenderFont_Load( void );
U8		RenderFont_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFont_Init( void )
* ACTION   : called at start of app
* CREATION : 30.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFont_Init( void )
{
	U16	i,j;

	Resource_Attach( eSECTION_GLOBAL, RenderFont_Load, RenderFont_UnLoad );

	for( i=0; i<eRFONT_LIMIT; i++ )
	{
		for( j=0; j<256; j++ )
		{
			gRFonts[ i ].FontMap[ j ] = 0xFF;
		}
		for( j='!'; j<'?'; j++ )
		{
			gRFonts[ i ].FontMap[ j ] = (U8)(j-'!');
		}
		for( j='A'; j<='Z'; j++ )
		{
			gRFonts[ i ].FontMap[ j           ] = (U8)( (j-'A')+31 );
			gRFonts[ i ].FontMap[ j+('a'-'A') ] = (U8)( (j-'A')+31);
		}
	}


	for( i=0; i<=eRFONT_LIMIT; i++ )
	{
		gRFonts[ i ].Height = 8;
		gRFonts[ i ].Width  = 8;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFont_DeInit( void )
* ACTION   : called at end of app
* CREATION : 30.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFont_DeInit( void )
{
}



/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFont_Print( U16 aFontType, char * apTxt, S16 aX, S16 aY )
* ACTION   : prints using a font
* CREATION : 29.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFont_Print( const U16 aFontType, const char * apTxt, sGraphicCanvas * apCanvas, const S16 aX, const S16 aY )
{
	sGraphicPos	lPos;
	U8			lIndex;
	S16			lX,lY;
	U16			lWidth;
	U8 *		lpWidthTable;

	lX = aX;
	lY = aY;

	lWidth       = gRFonts[ aFontType ].Width;
	lpWidthTable = &gRFonts[ aFontType ].CharWidths[ 0 ];

/*	RenderScreen_GetpGraphic()->mpVRAM = apScreen;*/
	while( *apTxt )
	{
		lIndex = *apTxt++;
		lIndex = gRFonts[ aFontType ].FontMap[ lIndex ];

		if( lIndex < gRFonts[ aFontType ].pSprites->mHeader.mSpriteCount )
		{
			lPos.mX = lX;
			lPos.mY = lY;
			apCanvas->mpFuncs->DrawSprite(
				apCanvas,
				&lPos,
				gRFonts[ aFontType ].pSprites->mpSprite[ lIndex ]  );

			lX += lpWidthTable[ lIndex ];
		}
		else
		{
			lX += lWidth;
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFont_PrintColoured( U16 aFontType, char * apTxt, S16 aX, S16 aY, U8 aColour )
* ACTION   : prints coloured using a font
* CREATION : 29.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFont_PrintColoured( const U16 aFontType, const char * apTxt, sGraphicCanvas * apCanvas, S16 aX, S16 aY, U8 aColour )
{
	sGraphicPos	lPos;
	U8			lIndex;
	S16			lX,lY;
	U16			lWidth;
	U8 *		lpWidthTable;

	(void)aColour;

	lX           = aX;
	lY           = aY;
	lWidth       = gRFonts[ aFontType ].Width;
	lpWidthTable = &gRFonts[ aFontType ].CharWidths[ 0 ];

/*	RenderScreen_GetpGraphic()->mpVRAM = apScreen;
*/
	while( *apTxt )
	{
		lIndex = *apTxt++;
		lIndex = gRFonts[ aFontType ].FontMap[ lIndex ];

		if( lIndex < gRFonts[ aFontType ].pSprites->mHeader.mSpriteCount )
		{
			lPos.mX = lX;
			lPos.mY = lY;
			apCanvas->mpFuncs->DrawSprite(
				apCanvas,
				&lPos,
				gRFonts[ aFontType ].pSprites->mpSprite[ lIndex ]  );
			lX += lpWidthTable[ lIndex ];
		}
		else
		{
			lX += lWidth;
		}
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFont_GetWidth( U16 aFontType, char * apTxt )
* ACTION   : returns pixel width of string in font aFontType
* CREATION : 29.12.00 PNK
*-----------------------------------------------------------------------------------*/

U16		RenderFont_GetWidth( const U16 aFontType, const char * apTxt )
{
	U8		lIndex;
	U16		lX;
	U16		lWidth;
	U8 *	lpWidthTable;

	lX = 0;

	lWidth       = gRFonts[ aFontType ].Width;
	lpWidthTable = &gRFonts[ aFontType ].CharWidths[ 0 ];

	while( *apTxt )
	{
		lIndex = *apTxt++;
		lIndex = gRFonts[ aFontType ].FontMap[ lIndex ];

		if( lIndex < gRFonts[ aFontType ].pSprites->mHeader.mSpriteCount )
		{
			lX += lpWidthTable[ lIndex ];
		}
		else
		{
			lX += lWidth;
		}
	}

	return( lX );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFont_GetWidth( U16 aFontType, char * apTxt )
* ACTION   : builds table of character widths
* CREATION : 29.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFont_BuildCharWidthTable( sRFont * apFont )
{
	U16		lMask;
	U16		lWidth;
	U16		i,j;

	if( apFont )
	{
		for( i=0; i<apFont->pSprites->mHeader.mSpriteCount; i++ )
		{
			lMask = 0xFFFF;
			for( j=0; j<apFont->pSprites->mpSprite[ i ]->mHeight; j++ )
			{
				U16	lPix;
				Endian_ReadBigU16( &apFont->pSprites->mpSprite[ i ]->mpMask[ j ], lPix );
				lMask &= lPix;
			}

			lWidth = 16;

			while( (lWidth) && (lMask&1) )
			{
				lMask >>= 1;
				lWidth--;
			}
			
			apFont->CharWidths[ i ] = (U8)( lWidth+1 );
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFont_Load( void )
* ACTION   : loads all font files
* CREATION : 29.12.00 PNK
*-----------------------------------------------------------------------------------*/

U8		RenderFont_Load( void )
{
	U16	i;

	gRFonts[ eRFONT_FE      ].pSprites = Resource_Load( "FE_FONT.BSB", 0 );
	gRFonts[ eRFONT_HISCORE ].pSprites = Resource_Load( "HI_FONT.BSB", 0 );

	for( i=0; i<eRFONT_LIMIT; i++ )
	{
		Sprite_BlockRelocate( gRFonts[ i  ].pSprites );
		RenderFont_BuildCharWidthTable( &gRFonts[ i  ] );
	}

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFont_UnLoad( void )
* ACTION   : unloads all font files
* CREATION : 29.12.00 PNK
*-----------------------------------------------------------------------------------*/

U8		RenderFont_UnLoad( void )
{
	U16	i;

	for( i=0; i<eRFONT_LIMIT; i++ )
	{
		Resource_UnLoad( &gRFonts[ i  ] );
	}

	return( 1 );
}


/* ################################################################################ */
