/*
 * ezsecuritymgrodbc.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: mohanraj
 */

#include <ezbusiness/ezsecuritymgrodbc.h>

int EzSecurityMgrODBC :: initEzSecurityMgrODBC( const char *TaskName, EzDebugUtil *dptr )
{
	this->dptr = dptr;
	if( initODBCUtil( TaskName, dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Initializing the EzODBCUtil");
		return -1;
	}

	if( DBConnect( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
		return -1;
	}
	return 1;
}

int EzSecurityMgrODBC :: getATMCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZATMINFO" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZATMINFO - Count[%d]", count);

    return count;
}

int EzSecurityMgrODBC :: getEzNetworkCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZNETWORKKEY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZNETWORKKEY - Count[%d]", count);

    return count;
}

int EzSecurityMgrODBC :: getDeviceKeyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZDEVICEKEY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZDEVICEKEY - Count[%d]", count);

    return count;
}

int EzSecurityMgrODBC :: getSecurityCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZSECURITY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZSECURITY - Count[%d]", count);

    return count;
}

int EzSecurityMgrODBC :: getSecurityPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZSECURITYPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZSECURITYPROPERTY - Count[%d]", count);

    return count;
}

int EzSecurityMgrODBC :: getHSMCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZHSMINFO" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZHSMINFO - Count[%d]", count);

    return count;
}

int EzSecurityMgrODBC :: LoadATMKey( struct EzATMKey *ezatmkey_ptr, int *SqlErr )
{
    char ATMId[ 33 ];
    char ATMMasterKey[ 65 ];
    char ATMCommKey[ 65 ];
    int ATMKeyLen;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
	    *SqlErr = -1;
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT RTRIM(ATMID),RTRIM(ATMMASTERKEY),RTRIM(ATMCOMMKEY),ATMKEYLEN FROM EZATMINFO;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadATMKey [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, ATMId, sizeof(ATMId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(ATMId) in EZATMINFO [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, ATMMasterKey, sizeof(ATMMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(ATMMasterKey) in EZATMINFO [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, ATMCommKey, sizeof(ATMCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(ATMCommKey) in EZATMINFO [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &ATMKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(ATMKeyLen) in EZATMINFO [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }
    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( ezatmkey_ptr + i ), 0, sizeof( struct EzATMKey ) );
        strcpy( ( ezatmkey_ptr + i )->ATMId, ATMId );
        strcpy( ( ezatmkey_ptr + i )->ATMMasterKey, ATMMasterKey );
        strcpy( ( ezatmkey_ptr + i )->ATMCommKey, ATMCommKey );
        ( ezatmkey_ptr + i )->ATMKeyLen = ATMKeyLen;
		i++;
		memset( ATMId, 0, sizeof( ATMId ) );
		memset( ATMMasterKey, 0, sizeof( ATMMasterKey ) );
		memset( ATMCommKey, 0, sizeof( ATMCommKey ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityMgrODBC :: LoadEzNetworkKey( struct EzNetworkKey *eznetworkkey_ptr, int *SqlErr )
{
	char NetworkId[ 17 ];
    char NetworkMasterKey[ 65 ];
    char NetworkAcqCommKey[ 65 ];
    char NetworkIssCommKey[ 65 ];
    int NetworkKeyLen;
    char KeyProperty;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
	    *SqlErr = -1;
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(NETWORKID), \
        RTRIM(NETWORKMASTERKEY), \
        RTRIM(NETWORKACQCOMMKEY), \
        RTRIM(NETWORKISSCOMMKEY), \
		NETWORKKEYLEN, \
		KEYPROPERTY \
	FROM EZNETWORKKEY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetworkKey [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, NetworkMasterKey, sizeof(NetworkMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkMasterKey) in EZNETWORKKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, NetworkAcqCommKey, sizeof(NetworkAcqCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkAcqCommKey) in EZNETWORKKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, NetworkIssCommKey, sizeof(NetworkIssCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkIssCommKey) in EZNETWORKKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &NetworkKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkKeyLen) in EZNETWORKKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &KeyProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(KeyProperty) in EZNETWORKKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( eznetworkkey_ptr + i ), 0, sizeof( struct EzNetworkKey ) );
        strcpy( ( eznetworkkey_ptr + i )->NetworkId, NetworkId );
        strcpy( ( eznetworkkey_ptr + i )->NetworkMasterKey, NetworkMasterKey );
        strcpy( ( eznetworkkey_ptr + i )->NetworkAcqCommKey, NetworkAcqCommKey );
        strcpy( ( eznetworkkey_ptr + i )->NetworkIssCommKey, NetworkIssCommKey );
        ( eznetworkkey_ptr + i )->NetworkKeyLen = NetworkKeyLen;
        ( eznetworkkey_ptr + i )->KeyProperty = KeyProperty;
		i++;
		memset( NetworkId, 0, sizeof( NetworkId ) );
		memset( NetworkMasterKey, 0, sizeof( NetworkMasterKey ) );
		memset( NetworkAcqCommKey, 0, sizeof( NetworkAcqCommKey ) );
		memset( NetworkIssCommKey, 0, sizeof( NetworkIssCommKey ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityMgrODBC :: LoadDeviceKey( struct DeviceKey *ezdevicekey_ptr, int *SqlErr )
{
    char DeviceId[ 33 ];
    char DeviceMasterKey[ 65 ];
    char DeviceCommKey[ 65 ];
    int DeviceKeyLen;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
	    *SqlErr = -1;
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT RTRIM(DEVICEID),RTRIM(DEVICEMASTERKEY),RTRIM(DEVICECOMMKEY),DEVICEKEYLEN FROM EZDEVICEKEY" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadDeviceKey [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, DeviceId, sizeof(DeviceId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceId) in EZDEVICEKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, DeviceMasterKey, sizeof(DeviceMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceMasterKey) in EZDEVICEKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, DeviceCommKey, sizeof(DeviceCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceCommKey) in EZDEVICEKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &DeviceKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceKeyLen) in EZDEVICEKEY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }
    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( ezdevicekey_ptr + i ), 0, sizeof( struct DeviceKey ) );
        strcpy( ( ezdevicekey_ptr + i )->DeviceId, DeviceId );
        strcpy( ( ezdevicekey_ptr + i )->DeviceMasterKey, DeviceMasterKey );
        strcpy( ( ezdevicekey_ptr + i )->DeviceCommKey, DeviceCommKey );
        ( ezdevicekey_ptr + i )->DeviceKeyLen = DeviceKeyLen;
		i++;
		memset( DeviceId, 0, sizeof( DeviceId ) );
		memset( DeviceMasterKey, 0, sizeof( DeviceMasterKey ) );
		memset( DeviceCommKey, 0, sizeof( DeviceCommKey ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityMgrODBC :: LoadSecurity( struct EzSecurity *ezsecurity_ptr, int *SqlErr )
{
	char InstId[ 13 ];
	char SecurityId[ 11 ];
	char PINVerificationMethod;
	char EPVK[ 65 ];
	char DecimilizationTable[ 17 ];
	char PINPadChar;
	char PANPadChar;
	short PINLen;
	short PANLen;
	short PANValidationOffset;
	char PINBlockFormat[ 3 ];
	short PANValidationLength;
	char CVKA[ 65 ];
	char CVKB[ 65 ];

	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
	    *SqlErr = -1;
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT RTRIM(INSTID), RTRIM(SECURITYID), PINVERIFICATIONMETHOD, RTRIM(EPVK), RTRIM(DECIMILIZATIONTABLE), PINPADCHAR, PANPADCHAR, PINLEN, PANLEN, PANVALIDATIONOFFSET, RTRIM(PINBLOCKFORMAT), PANVALIDATIONLENGTH, RTRIM(CVKA), RTRIM(CVKB) FROM EZSECURITY" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadSecurity [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, SecurityId, sizeof(SecurityId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(SecurityId) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_BINARY, &PINVerificationMethod, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(PINVerificationMethod) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, EPVK, sizeof(EPVK), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(EPVK) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, DecimilizationTable, sizeof(DecimilizationTable), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(DecimilizationTable) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &PINPadChar, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(PINPadChar) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &PANPadChar, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(PANPadChar) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SHORT, &PINLen, sizeof(short), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(PINLen) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SHORT, &PANLen, sizeof(short), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(PANLen) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SHORT, &PANValidationOffset, sizeof(short), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(PANValidationOffset) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }


    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, PINBlockFormat, sizeof(PINBlockFormat), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(PINBlockFormat) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_SHORT, &PANValidationLength, sizeof(short), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(PANValidationLength) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, CVKA, sizeof(CVKA), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(CVKA) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, CVKB, sizeof(CVKB), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(CVKB) in EZSECURITY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( ezsecurity_ptr + i ), 0, sizeof( struct EzSecurity ) );

        dptr->trace(  "InstId[ %s ]\n", InstId );
        dptr->trace(  "SecurityId[ %s ]\n", SecurityId);
        dptr->trace(  "PINVerificationMethod[ %c ]\n", PINVerificationMethod);
        dptr->trace(  "EPVK[ %s ]\n",EPVK);
        dptr->trace(  "DecimilizationTable[ %s ]\n",DecimilizationTable);
        dptr->trace(  "PINPadChar[%c]\n",PINPadChar);
        dptr->trace(  "PANPadChar[%c]\n",PANPadChar);
        dptr->trace(  "PINLen[%d]\n",PINLen);
        dptr->trace(  "PANLen[%d]\n",PANLen);
        dptr->trace(  "PANValidationOffset[%d]\n",PANValidationOffset);
        dptr->trace(  "PINBlockFormat[ %s ]\n",PINBlockFormat);
        dptr->trace(  "PANValidationLength[%d]\n",PANValidationLength);
        dptr->trace(  "CVKA[ %s ]\n",CVKA);
        dptr->trace(  "CVKB[ %s ]\n",CVKB);

        strcpy( ( ezsecurity_ptr + i )->SecurityId, SecurityId );
        ( ezsecurity_ptr + i )->PINVerificationMethod = PINVerificationMethod;
        strcpy( ( ezsecurity_ptr + i )->EPVK, EPVK );
        strcpy( ( ezsecurity_ptr + i )->DecimilizationTable, DecimilizationTable );
        ( ezsecurity_ptr + i )->PINPadChar = PINPadChar;
        ( ezsecurity_ptr + i )->PANPadChar = PANPadChar;
        ( ezsecurity_ptr + i )->PINLen = PINLen;
        ( ezsecurity_ptr + i )->PANLen = PANLen;
        ( ezsecurity_ptr + i )->PANValidationOffset = PANValidationOffset;
        strcpy( ( ezsecurity_ptr + i )->PINBlockFormat, PINBlockFormat );
        ( ezsecurity_ptr + i )->PANValidationLength = PANValidationLength;
		strcpy( ( ezsecurity_ptr + i )->CVKA, CVKA );
		strcpy( ( ezsecurity_ptr + i )->CVKB, CVKB );
		i++;
		memset( InstId, 0, sizeof( InstId ) );
		memset( SecurityId, 0, sizeof( SecurityId ) );
		memset( EPVK, 0, sizeof( EPVK ) );
		memset( DecimilizationTable, 0, sizeof( DecimilizationTable ) );
		memset( PINBlockFormat, 0, sizeof( PINBlockFormat ) );
		memset( CVKA, 0, sizeof( CVKA ) );
		memset( CVKB, 0, sizeof( CVKB ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityMgrODBC :: LoadSecurityProperty( struct EzSecurityProperty *ezsecurityproperty_ptr, int *SqlErr )
{
    char RecordId[ 11 ];
	char InstSecurityGroupId[ 17 ];
	char SecurityProtocol[ 17 ];
	char SecurityChannel[ 33 ];
	int Priority;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
	    *SqlErr = -1;
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(RECORDID), \
        RTRIM(INSTSECURITYGROUPID), \
        RTRIM(SECURITYPROTOCOL), \
        RTRIM(SECURITYCHANNEL), \
        PRIORITY \
	FROM EZSECURITYPROPERTY" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadSecurityProperty [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstSecurityGroupId, sizeof(InstSecurityGroupId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstSecurityGroupId) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, SecurityProtocol, sizeof(SecurityProtocol), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(SecurityProtocol) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, SecurityChannel, sizeof(SecurityChannel), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(SecurityChannel) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &Priority, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(Priority) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( ezsecurityproperty_ptr + i ), 0, sizeof( struct EzSecurityProperty ) );
        strcpy( ( ezsecurityproperty_ptr + i )->RecordId, RecordId );
        strcpy( ( ezsecurityproperty_ptr + i )->InstSecurityGroupId, InstSecurityGroupId );
        strcpy( ( ezsecurityproperty_ptr + i )->SecurityProtocol, SecurityProtocol );
        strcpy( ( ezsecurityproperty_ptr + i )->SecurityChannel, SecurityChannel );
        ( ezsecurityproperty_ptr + i )->Priority = Priority;
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( InstSecurityGroupId, 0, sizeof( InstSecurityGroupId ) );
		memset( SecurityProtocol, 0, sizeof( SecurityProtocol ) );
		memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityMgrODBC :: LoadHSMInfo( struct EzHSMInfo *ezhsminfo_ptr, int *SqlErr )
{
	char HSMName[ 33 ];
	char HSMProtocol[ 17 ];
	char HSMType[ 17 ];
	char HSMAddress[ 33 ];
	int HSMPortNo;
	int HeaderLen;
	char HeaderType[ 9 ];
	int HSMHeaderLen;
	int HSMTimeOut;
	int ConnectionInterval;
	int HSMStatus;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
	    *SqlErr = -1;
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(HSMNAME), \
        RTRIM(HSMPROTOCOL), \
        RTRIM(HSMTYPE), \
        RTRIM(HSMADDRESS), \
        HSMPORT, \
        HEADERLEN, \
		RTRIM(HEADERTYPE), \
		HSMHEADERLEN, \
		HSMTIMEOUT, \
		CONNECTIONINTERVAL, \
		HSMSTATUS \
    FROM EZHSMINFO;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadHSMInfo [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, HSMName, sizeof(HSMName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HSMName) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, HSMProtocol, sizeof(HSMProtocol), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HSMProtocol) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, HSMType, sizeof(HSMType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HSMType) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, HSMAddress, sizeof(HSMAddress), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HSMAddress) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &HSMPortNo, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HSMPortNo) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_SLONG, &HeaderLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HeaderLen) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, HeaderType, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HeaderType) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &HSMHeaderLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HSMHeaderLen) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &HSMTimeOut, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HSMTimeOut) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &ConnectionInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(ConnectionInterval) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &HSMStatus, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Binding Column(HSMStatus) in EZSECURITYPROPERTY [ %d ]", odbcret );
	    getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	    *SqlErr = -1;
            return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( ezhsminfo_ptr + i ), 0, sizeof( struct EzHSMInfo ) );
        strcpy( ( ezhsminfo_ptr + i )->HSMName, HSMName );
        strcpy( ( ezhsminfo_ptr + i )->HSMProtocol, HSMProtocol );
        strcpy( ( ezhsminfo_ptr + i )->HSMType, HSMType );
        strcpy( ( ezhsminfo_ptr + i )->HSMAddress, HSMAddress );
        ( ezhsminfo_ptr + i )->HSMPortNo = HSMPortNo;
        ( ezhsminfo_ptr + i )->HeaderLen = HeaderLen;
        strcpy( ( ezhsminfo_ptr + i )->HeaderType, HeaderType );
        ( ezhsminfo_ptr + i )->HSMHeaderLen = HSMHeaderLen;
        ( ezhsminfo_ptr + i )->HSMTimeOut = HSMTimeOut;
        ( ezhsminfo_ptr + i )->ConnectionInterval = ConnectionInterval;
        ( ezhsminfo_ptr + i )->HSMStatus = 0;
        i++;
		memset( HSMName, 0, sizeof( HSMName ) );
		memset( HSMProtocol, 0, sizeof( HSMProtocol ) );
		memset( HSMType, 0, sizeof( HSMType ) );
		memset( HSMAddress, 0, sizeof( HSMAddress ) );
		memset( HeaderType, 0, sizeof( HeaderType ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityMgrODBC :: updateEzNetworkAcqKeyTable( const char *I_NetworkId, const char * I_NetworkAcqCommKey, int *SqlErr )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZNETWORKKEY SET NETWORKACQCOMMKEY='%s' WHERE RTRIM(NETWORKID)='%s'", I_NetworkAcqCommKey, I_NetworkId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSecurityMgrODBC :: updateEzNetworkIssKeyTable( const char *I_NetworkId, const char * I_NetworkIssCommKey, int *SqlErr )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZNETWORKKEY SET NETWORKISSCOMMKEY='%s' WHERE RTRIM(NETWORKID)='%s'", I_NetworkIssCommKey, I_NetworkId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSecurityMgrODBC :: updateDeviceKeyTable( const char *I_DeviceId, const char * I_DeviceCommKey, int *SqlErr )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZDEVICEKEY SET DEVICEOMMKEY='%s' WHERE RTRIM(DEVICEID)='%s'", I_DeviceCommKey, I_DeviceId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSecurityMgrODBC :: updateATMKeyTable( const char *I_ATMId, const char * I_ATMCommKey, int *SqlErr )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZATMINFO SET ATMCOMMKEY='%s' WHERE RTRIM(ATMID)='%s'", I_ATMCommKey, I_ATMId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSecurityMgrODBC :: updateHSMInfoTable( const char *I_HSMName, int I_HSMStatus, int *SqlErr )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZHSMINFO SET HSMSTATUS='%d' WHERE RTRIM(HSMNAME)='%s'", I_HSMStatus, I_HSMName );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}
