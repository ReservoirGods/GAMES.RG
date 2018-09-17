#ifndef	INCLUDED_BUILD_H
#define	INCLUDED_BUILD_H

/* ###################################################################################
#  DEFINES
################################################################################### */


#define	dBUILD_NUMBER_HI	0
#define	dBUILD_NUMBER_LO	5

/*#define	dBUILD_CLI_ACTIVE*/
/* #define	dBUILD_PROFILER_ACTIVE */

/* ###################################################################################
#  PROTOTYPES
################################################################################### */

extern	char	gBuildString[ 1024 ];


/* ###################################################################################
#  BUILD SPECIFIC MODULES
################################################################################### */

#ifdef	dBUILD_CLI_ACTIVE

#include	<GODLIB\CLI\CLI.H>

#define	Build_CliInit()						Cli_Init()
#define	Build_CliDeInit()					Cli_DeInit()
#define	Build_CliUpdate()					Cli_Update()
#define	Build_CliMain()						Cli_Main()
#define	Build_CliCmdInit( apName,afCmd )	Cli_CmdInit( apName, afCmd, "cli" )
#define	Build_CliCmdDeInit( apName )		Cli_CmdDeInit( apName )
#define	Build_CliPrintLine( apTxt )			Cli_PrintLine( apTxt )

#define	Build_CliPrintfLine1( apTxt, apVal0 )									sprintf( gBuildString, apTxt, apVal0 );									Cli_PrintLine( gBuildString )
#define	Build_CliPrintfLine2( apTxt, apVal0, apVal1 )							sprintf( gBuildString, apTxt, apVal0, apVal1 );							Cli_PrintLine( gBuildString )
#define	Build_CliPrintfLine3( apTxt, apVal0, apVal1, apVal2 )					sprintf( gBuildString, apTxt, apVal0, apVal1, apVal2 );					Cli_PrintLine( gBuildString )
#define	Build_CliPrintfLine4( apTxt, apVal0, apVal1, apVal2, apVal3 )			sprintf( gBuildString, apTxt, apVal0, apVal1, apVal2, apVal3 );			Cli_PrintLine( gBuildString )
#define	Build_CliPrintfLine5( apTxt, apVal0, apVal1, apVal2, apVal3, apVal4 )	sprintf( gBuildString, apTxt, apVal0, apVal1, apVal2, apVal3, apVal4 ); Cli_PrintLine( gBuildString )

#else


#define	Build_CliInit()
#define	Build_CliDeInit()
#define	Build_CliUpdate()
#define	Build_CliMain()
#define	Build_CliCmdInit( apName,afCmd )
#define	Build_CliCmdDeInit( apName )
#define	Build_CliPrintLine( apTxt )

#define	Build_CliPrintfLine1( apTxt, apVal0 )
#define	Build_CliPrintfLine2( apTxt, apVal0, apVal1 )
#define	Build_CliPrintfLine3( apTxt, apVal0, apVal1, apVal2 )
#define	Build_CliPrintfLine4( apTxt, apVal0, apVal1, apVal2, apVal3 )
#define	Build_CliPrintfLine5( apTxt, apVal0, apVal1, apVal2, apVal3, apVal4 )

#endif


/* ################################################################################ */

#endif	/*	INCLUDED_BUILD_H	*/