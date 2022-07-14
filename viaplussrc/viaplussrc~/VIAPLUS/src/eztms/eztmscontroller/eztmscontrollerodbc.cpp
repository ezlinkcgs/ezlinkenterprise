/*
 * eztmscontrollerodbc.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: mohanraj
 */

#include <eztms/eztmscontrollerodbc.h>

int EzTMSControllerODBC :: initEzTMSControllerODBC( const char *TaskName, EzDebugUtil *dptr )
{
	this->dptr = dptr;
	if( initODBCUtil( TaskName, dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Initializing the EzODBCUtil");
		return -1;
	}
	return 1;
}

int EzTMSControllerODBC :: ConnectDB()
{
	if( DBConnect( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
		return -1;
	}
	return 1;
}

int EzTMSControllerODBC :: CloseDB()
{
	if( DBClose( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Dis-Connecting the Database");
		return -1;
	}
	return 1;
}

int EzTMSControllerODBC :: updateNewConfigId( const char *I_MachineId, const char *I_ConfigId )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZMMS_TERMINALPROFILE SET CONFIG_ID='%s' WHERE RTRIM(MACHINE_ID)='%s';", I_ConfigId, I_MachineId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}


