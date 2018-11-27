/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"RESOURCE.H"

#include	"BUILD.H"

#include	<STRING.H>
#include	<GODLIB/FILE/FILE.H>
#include	<GODLIB/LINKFILE/LINKFILE.H>
#include	<GODLIB/MEMORY/MEMORY.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dRESOURCE_FOLDER_LIMIT	128

#define	dRESOURCE_LOADFROM_LINKFILE


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eRESOURCESTATE_UNLOADED,
	eRESOURCESTATE_LOADED
};


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	U16		State;
	U32		Sections;
	U8		(*fLoad)(void);
	U8		(*fUnLoad)(void);
} sResourceFolder;


/* ###################################################################################
#  DATA
################################################################################### */

U16					gResourceCount;
U32					gResourceSection;
sResourceFolder 	gResourceFolders[ dRESOURCE_FOLDER_LIMIT ];

sFileHandle			gResourceLogHandle;
U16					gResourceLogEnableFlag;

sLinkFile *			gpResourceLinkFiles[ eSECTION_LIMIT ];

sTagString			gResourceLinkFileNames[ eSECTION_LIMIT ] =
{
	{	eSECTION_INTRO,				"INTRO.LNK"		},
	{	eSECTION_GLOBAL,			"GEN.LNK"		},

};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Resource_LogUpdate( char * apFileName );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Resource_Init( void )
{
	U16	i;

	gResourceCount   = 0;
	gResourceSection = 0;

	for( i=0; i<dRESOURCE_FOLDER_LIMIT; i++ )
	{
		gResourceFolders[ i ].State    = eRESOURCESTATE_UNLOADED;
		gResourceFolders[ i ].Sections = 0L;
	}

	gResourceLogEnableFlag = 0;

#ifdef	dRESOURCE_LOADFROM_LINKFILE
/*	for( i=0; i<eSECTION_LIMIT; i++ )
	{
		gpResourceLinkFiles[ i ] = LinkFile_InitToRAM( sTagString_GetpString( i, &gResourceLinkFileNames[ i ], eSECTION_LIMIT ) );
	}*/
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Resource_DeInit( void )
{
#ifdef	dRESOURCE_LOADFROM_LINKFILE
	U16	i;

	for( i=0; i<eSECTION_LIMIT; i++ )
	{
		LinkFile_DeInit( gpResourceLinkFiles[ i ] );
	}
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_EnterSection( const U16 aSectionIndex )
* ACTION   : loads all resources needed for a section
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Resource_EnterSection( const U16 aSectionIndex )
{
	sResourceFolder *	lpFolder;
	U32					lNewMask;
	U16					i;

	lNewMask   = 1;
	lNewMask <<= aSectionIndex;

#ifdef	dRESOURCE_LOADFROM_LINKFILE
	if( 0 == (lNewMask & gResourceSection) )
	{
/*		Loading_DisplayEnable();*/
		gpResourceLinkFiles[ aSectionIndex ] = LinkFile_InitToRAM( sTagString_GetpString( aSectionIndex, &gResourceLinkFileNames[ 0 ], eSECTION_LIMIT ) );
/*		Loading_DisplayDisable();*/
	}
#endif

	gResourceSection  |= lNewMask;

	for( i=0; i<gResourceCount; i++ )
	{
		lpFolder = &gResourceFolders[ i ];

		if( lpFolder->Sections & gResourceSection )
		{
			if( lpFolder->State == eRESOURCESTATE_UNLOADED )
			{
				lpFolder->fLoad();
				lpFolder->State = eRESOURCESTATE_LOADED;
			}
		}
		else
		{
			if( lpFolder->State == eRESOURCESTATE_LOADED )
			{
				lpFolder->fUnLoad();
				lpFolder->State = eRESOURCESTATE_UNLOADED;
			}
		}
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_LeaveSection( const U16 aSectionIndex )
* ACTION   : marks section aSectionIndex as left, unloads data from this section
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Resource_LeaveSection( const U16 aSectionIndex )
{
	sResourceFolder *	lpFolder;
	U32					lNewMask;
	U16					i;

	lNewMask   = 1L;
	lNewMask <<= aSectionIndex;

	gResourceSection &= ~lNewMask;


	for( i=0; i<gResourceCount; i++ )
	{
		lpFolder = &gResourceFolders[ i ];

		if( !(lpFolder->Sections & gResourceSection) )
		{
			if( lpFolder->State == eRESOURCESTATE_LOADED )
			{
				lpFolder->fUnLoad();
				lpFolder->State = eRESOURCESTATE_UNLOADED;
			}
		}
	}

#ifdef	dRESOURCE_LOADFROM_LINKFILE
	Build_CliPrintfLine1( "LinkFileDeInit : %s", sTagString_GetpString( aSectionIndex, &gResourceLinkFileNames[ 0 ], eSECTION_LIMIT ) );
	LinkFile_DeInit( gpResourceLinkFiles[ aSectionIndex ] );
	gpResourceLinkFiles[ aSectionIndex ] = 0;
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_Attach( const U16 aSections, U8 (*afLoad)(void), U8 (*afUnLoad)(void) )
* ACTION   : attaches a set of loading routs to the resource manager
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8		Resource_Attach( const U32 aSection, U8 (*afLoad)(void), U8 (*afUnLoad)(void) )
{
	sResourceFolder *	lpFolder;

	if( gResourceCount < dRESOURCE_FOLDER_LIMIT )
	{
		lpFolder = &gResourceFolders[ gResourceCount ];

		lpFolder->fLoad      = afLoad;
		lpFolder->fUnLoad    = afUnLoad;
		lpFolder->Sections   = 1L;
		lpFolder->Sections <<= aSection;
		lpFolder->State      = eRESOURCESTATE_UNLOADED;

		gResourceCount++;
		return( 1 );
	}
	return( 0 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_Alloc(    const U32 aSize, const U8 aFastRamFlag )
* ACTION   : allocates memory - in fast ram in flag is set
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void *	Resource_Alloc(    const U32 aSize, const U8 aFastRamFlag )
{
	void *	lpMem;

	if( aFastRamFlag )
	{
		lpMem = mMEMSCREENCALLOC( aSize );
	}
	else
	{
		lpMem = mMEMALLOC( aSize );
	}

	return( lpMem );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_Calloc(    const U32 aSize, const U8 aFastRamFlag )
* ACTION   : allocates & clears memory - in fast ram in flag is set
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void *	Resource_Calloc(    const U32 aSize, const U8 aFastRamFlag )
{
	void *	lpMem;

	if( aFastRamFlag )
	{
		lpMem = mMEMSCREENCALLOC( aSize );
	}
	else
	{
		lpMem = mMEMCALLOC( aSize );
	}

	return( lpMem );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_Load(   char * apFileName, const U8 aFastRamFlag )
* ACTION   : loads data
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void *	Resource_Load(   char * apFileName, const U8 aFastRamFlag )
{
	void *	lpMem;

#ifdef	dRESOURCE_LOADFROM_LINKFILE
	
	U16 i;
	U32	lMask;


	lMask = 1;
	for( i=0; i<eSECTION_LIMIT; i++ )
	{
		if( gResourceSection & lMask )
		{
			if( gpResourceLinkFiles[ i ] )
			{
				lpMem = LinkFile_FileLoad( gpResourceLinkFiles[ i ], apFileName, 1, aFastRamFlag );
				if( lpMem )
				{
					return( lpMem );
				}
			}
		}
		lMask <<= 1L;
	}
	
	Build_CliPrintfLine1( "File Not Found : %s", apFileName );
	Build_CliMain();
	return( 0 );

#else

	char	lString[ 128 ];

	strcpy( lString, "DATA\\" );
	strcat( lString, apFileName );

	Resource_LogUpdate( lString );

	if( aFastRamFlag )
	{
		lpMem = File_Load( lString );
	}
	else
	{
		lpMem = File_LoadSlowRam( lString );
	}


	if( !lpMem )
	{
		Build_CliPrintfLine1( "File Not Found : %s", apFileName );
		Build_CliMain();
	}

	return( lpMem );
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_LoadAt( char * apFileName, void * apAddress )
* ACTION   : loads data at specified address
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8		Resource_LoadAt( char * apFileName, void * apAddress )
{
#ifdef	dRESOURCE_LOADFROM_LINKFILE

	U16 i;
	U32	lMask;


	lMask = 1;
	for( i=0; i<eSECTION_LIMIT; i++ )
	{
		if( gResourceSection & lMask )
		{
			if( gpResourceLinkFiles[ i ] )
			{
				if( LinkFile_FileExists( gpResourceLinkFiles[ i ], apFileName ) )
				{
					return( LinkFile_FileLoadAt( gpResourceLinkFiles[ i ], apFileName, apAddress, 1 ) );
				}
			}
		}
		lMask <<= 1L;
	}
	
	Build_CliPrintfLine1( "File Not Found : %s", apFileName );
	Build_CliMain();
	return( 0 );


#else
	char	lString[ 128 ];

	strcpy( lString, "DATA\\" );
	strcat( lString, apFileName );

	Resource_LogUpdate( lString );

	return( File_LoadAt( lString, apAddress ) );
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_Free( void * apMem )
* ACTION   : frees memory
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Resource_Free( void * apMem )
{
	mMEMFREE( apMem );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_UnLoad( void * apMem )
* ACTION   : UnLoads memory
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Resource_UnLoad( void * apMem )
{
	(void)apMem;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Resource_GetFileSize( char * apFileName )
* ACTION   : returns size of file apFileName
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

S32		Resource_GetFileSize( char * apFileName )
{
#ifdef	dRESOURCE_LOADFROM_LINKFILE

	U16 i;
	U32	lMask;


	lMask = 1;
	for( i=0; i<eSECTION_LIMIT; i++ )
	{
		if( gResourceSection & lMask )
		{
			if( gpResourceLinkFiles[ i ] )
			{
				if( LinkFile_FileExists( gpResourceLinkFiles[ i ], apFileName ) )
				{
					return( LinkFile_FileGetSize( gpResourceLinkFiles[ i ], apFileName, 1 ) );
				}
			}
		}
		lMask <<= 1L;
	}
	
	return( -1 );


#else
	char	lString[ 128 ];

	strcpy( lString, "DATA\\" );
	strcat( lString, apFileName );

	return( File_GetSize( lString) );
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Resource_LogInit(void)
* ACTION   : Resource_LogInit
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Resource_LogInit(void)
{
	gResourceLogHandle = File_Create( "RESOURCE.LOG" );
	if( gResourceLogHandle >= 0 )
	{
		gResourceLogEnableFlag = 1;
	}
	else
	{
		gResourceLogEnableFlag = 0;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Resource_LogDeInit(void)
* ACTION   : Resource_LogDeInit
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Resource_LogDeInit(void)
{
	File_Close( gResourceLogHandle );
	gResourceLogEnableFlag = 0;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Resource_LogUpdate(char * apFileName)
* ACTION   : Resource_LogUpdate
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Resource_LogUpdate(char * apFileName)
{
	char	lString[ 128 ];

	if( gResourceLogEnableFlag )
	{
		sprintf( lString, "cp C:\\SOURCE\\RG\\GODPEY\\DATA\\%s C:\\SOURCE\\RG\\GODPEY\\PACKED\\\n", apFileName );
		File_Write( gResourceLogHandle, strlen(lString), &lString[0] );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void Resource_LogGenerate(void)
* ACTION   : Resource_LogGenerate
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void Resource_LogGenerate(void)
{
	U16	i;

	Resource_LogInit();
	for( i=0; i<eSECTION_LIMIT; i++ )
	{
		Resource_EnterSection( i );
		Resource_LeaveSection( i );
	}
	Resource_LogDeInit();
}


/* ################################################################################ */
