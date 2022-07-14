#include <ezmms/ezmmscmd.h>

int EzMMSCmd :: initMMSCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmmscmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^ezmmscmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	//if( initODBCUtil( "ezmmscmd", this, "EZMMS" ) < 0 )
	if( initODBCUtil( "ezmmscmd", this ) < 0 )
	{
		trace( "Error in Initializing initODBCUtil..." );
		printf("\nError in Initializing initODBCUtil ..." );
		exit( 0 );
	}

	if( initMMSUtil( this ) < 0 )
	{
		trace( "Error in Initializing MMSServerUtil...." );
		printf("\nError in Initializing MMSServerUtil...." );
		exit( 0 );
	}
	return 1;
}

int EzMMSCmd :: serviceAddMerchantProfile( const char *InstId, const char *MerchantId )
{
	struct EzMMSMerchantProfile merchantprofile_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &merchantprofile_rec, 0, sizeof( struct EzMMSMerchantProfile ) );
	retval = readEzMMSMerchantProfile( InstId, MerchantId, &merchantprofile_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantId[%s] from EzMMSMerchantProfile....OraErr[%05d]", InstId, MerchantId, retval );
		printf( "\nError in Reading InstId[%s] MerchantId[%s] from EzMMSMerchantProfile....OraErr[%05d]", InstId, MerchantId, retval );
		DBClose();
		return -1;
	}

	if( addMerchantProfile( merchantprofile_rec ) < 0 )
	{
		trace( "Error in Adding InstId[%s] MerchantId[%s] in MerchantProfile Memory...", InstId, MerchantId );
		printf( "\nError in Adding InstId[%s] MerchantId[%s] in MerchantProfile Memory...", InstId, MerchantId );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceUpdateMerchantProfile( const char *InstId, const char *MerchantId )
{
	struct EzMMSMerchantProfile merchantprofile_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &merchantprofile_rec, 0, sizeof( struct EzMMSMerchantProfile ) );
	retval = readEzMMSMerchantProfile( InstId, MerchantId, &merchantprofile_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantId[%s] from EzMMSMerchantProfile....OraErr[%05d]", InstId, MerchantId, retval );
		printf( "\nError in Reading InstId[%s] MerchantId[%s] from EzMMSMerchantProfile....OraErr[%05d]", InstId, MerchantId, retval );
		DBClose();
		return -1;
	}

	if( updateMerchantProfile( merchantprofile_rec ) < 0 )
	{
		trace( "Error in Updating InstId[%s] MerchantId[%s] in MerchantProfile Memory...", InstId, MerchantId );
		printf( "\nError in Updating InstId[%s] MerchantId[%s] in MerchantProfile Memory...", InstId, MerchantId );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceDeleteMerchantProfile( const char *InstId, const char *MerchantId )
{
	if( deleteMerchantProfile( InstId, MerchantId ) < 0 )
	{
		trace( "Error in Deleting InstId[%s] MerchantId[%s] from MerchantProfile Memory..", InstId, MerchantId );
		printf( "\nError in Deleting InstId[%s] MerchantId[%s] from MerchantProfile Memory..", InstId, MerchantId );
		return -1;
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantProfile()
{
	for( int i = 0, j = 0; i < MaxMerchantProfile; i++ )
	{
		if( strcmp( ( MerchantProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) )
		{
			printf( "\n***************Merchant %d**************************", j + 1);
			printf( "\nInstId<%s>", ( MerchantProfileShmPtr + i )->InstId );
			printf( "\nMerchantId<%s>", ( MerchantProfileShmPtr + i )->MerchantId );
			printf( "\nMCCList<%s>", ( MerchantProfileShmPtr + i )->MCCList );
			printf( "\nMerchantTypeId<%s>", ( MerchantProfileShmPtr + i )->MerchantTypeId );
			printf( "\nParentMerchantId<%s>", ( MerchantProfileShmPtr + i )->ParentMerchantId );
			printf( "\nMerchantName<%s>", ( MerchantProfileShmPtr + i )->MerchantName );
			printf( "\nAddr1<%s>", ( MerchantProfileShmPtr + i )->Addr1 );
			printf( "\nAddr2<%s>", ( MerchantProfileShmPtr + i )->Addr2 );
			printf( "\nDOB<%s>", ( MerchantProfileShmPtr + i )->DOB );
			printf( "\nPMobileNo<%s>", ( MerchantProfileShmPtr + i )->PMobileNo );
			printf( "\nSMobileNo<%s>", ( MerchantProfileShmPtr + i )->SMobileNo );
			printf( "\nPMailAddr<%s>", ( MerchantProfileShmPtr + i )->PMailAddr );
			printf( "\nSMailAddr<%s>", ( MerchantProfileShmPtr + i )->SMailAddr );
			printf( "\nSettCurrCode<%s>", ( MerchantProfileShmPtr + i )->SettCurrCode );
			printf( "\nCurrList<%s>", ( MerchantProfileShmPtr + i )->CurrList );
			printf( "\nCardIssuanceFlag<%c>", ( MerchantProfileShmPtr + i )->CardIssuanceFlag );
			printf( "\nStatus<%c>", ( MerchantProfileShmPtr + i )->Status );
			j++;
		}
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantProfile( const char *InstId )
{
	for( int i = 0, j = 0; i < MaxMerchantProfile; i++ )
	{
		if( strcmp( ( MerchantProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) )
		{
			if( strcmp( ( MerchantProfileShmPtr + i )->InstId, InstId ) )
			{
				printf( "\n***************Merchant %d**************************", j + 1 );
				printf( "\nInstId<%s>", ( MerchantProfileShmPtr + i )->InstId );
				printf( "\nMerchantId<%s>", ( MerchantProfileShmPtr + i )->MerchantId );
				printf( "\nMCCList<%s>", ( MerchantProfileShmPtr + i )->MCCList );
				printf( "\nMerchantTypeId<%s>", ( MerchantProfileShmPtr + i )->MerchantTypeId );
				printf( "\nParentMerchantId<%s>", ( MerchantProfileShmPtr + i )->ParentMerchantId );
				printf( "\nMerchantName<%s>", ( MerchantProfileShmPtr + i )->MerchantName );
				printf( "\nAddr1<%s>", ( MerchantProfileShmPtr + i )->Addr1 );
				printf( "\nAddr2<%s>", ( MerchantProfileShmPtr + i )->Addr2 );
				printf( "\nDOB<%s>", ( MerchantProfileShmPtr + i )->DOB );
				printf( "\nPMobileNo<%s>", ( MerchantProfileShmPtr + i )->PMobileNo );
				printf( "\nSMobileNo<%s>", ( MerchantProfileShmPtr + i )->SMobileNo );
				printf( "\nPMailAddr<%s>", ( MerchantProfileShmPtr + i )->PMailAddr );
				printf( "\nSMailAddr<%s>", ( MerchantProfileShmPtr + i )->SMailAddr );
				printf( "\nSettCurrCode<%s>", ( MerchantProfileShmPtr + i )->SettCurrCode );
				printf( "\nCurrList<%s>", ( MerchantProfileShmPtr + i )->CurrList );
				printf( "\nCardIssuanceFlag<%c>", ( MerchantProfileShmPtr + i )->CardIssuanceFlag );
				printf( "\nStatus<%c>", ( MerchantProfileShmPtr + i )->Status );
				j++;
			}
		}
	}
	return 1;
}


int EzMMSCmd :: serviceListMerchantProfile( const char *InstId, const char *MerchantId )
{
	for( int i = 0, j = 0; i < MaxMerchantProfile; i++ )
	{
		if( strcmp( ( MerchantProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) )
		{
			if( strcmp( ( MerchantProfileShmPtr + i )->InstId, InstId ) && strcmp( ( MerchantProfileShmPtr + i )->MerchantId, MerchantId ) )
			{
				printf( "\n***************Merchant %d**************************", j + 1 );
				printf( "\nInstId<%s>", ( MerchantProfileShmPtr + i )->InstId );
				printf( "\nMerchantId<%s>", ( MerchantProfileShmPtr + i )->MerchantId );
				printf( "\nMCCList<%s>", ( MerchantProfileShmPtr + i )->MCCList );
				printf( "\nMerchantTypeId<%s>", ( MerchantProfileShmPtr + i )->MerchantTypeId );
				printf( "\nParentMerchantId<%s>", ( MerchantProfileShmPtr + i )->ParentMerchantId );
				printf( "\nMerchantName<%s>", ( MerchantProfileShmPtr + i )->MerchantName );
				printf( "\nAddr1<%s>", ( MerchantProfileShmPtr + i )->Addr1 );
				printf( "\nAddr2<%s>", ( MerchantProfileShmPtr + i )->Addr2 );
				printf( "\nDOB<%s>", ( MerchantProfileShmPtr + i )->DOB );
				printf( "\nPMobileNo<%s>", ( MerchantProfileShmPtr + i )->PMobileNo );
				printf( "\nSMobileNo<%s>", ( MerchantProfileShmPtr + i )->SMobileNo );
				printf( "\nPMailAddr<%s>", ( MerchantProfileShmPtr + i )->PMailAddr );
				printf( "\nSMailAddr<%s>", ( MerchantProfileShmPtr + i )->SMailAddr );
				printf( "\nSettCurrCode<%s>", ( MerchantProfileShmPtr + i )->SettCurrCode );
				printf( "\nCurrList<%s>", ( MerchantProfileShmPtr + i )->CurrList );
				printf( "\nCardIssuanceFlag<%c>", ( MerchantProfileShmPtr + i )->CardIssuanceFlag );
				printf( "\nStatus<%c>", ( MerchantProfileShmPtr + i )->Status );
				j++;
			}
		}
	}
	return 1;
}

/*int EzMMSCmd :: serviceAddMerchantType( const char *InstId, const char *MerchantTypeId )
{
	struct EzMMSMerchantType merchanttype_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &merchanttype_rec, 0, sizeof( struct EzMMSMerchantType ) );
	retval = readEzMMSMerchantType( InstId, MerchantTypeId, &merchanttype_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantTypeId[%s] from EzMMSMerchantType....OraErr[%05d]", InstId, MerchantTypeId, retval );
		printf( "\nError in Reading InstId[%s] MerchantTypeId[%s] from EzMMSMerchantType....OraErr[%05d]", InstId, MerchantTypeId, retval );
		DBClose();
		return -1;
	}

	if( addMerchantType( merchanttype_rec ) < 0 )
	{
		trace( "Error in Adding InstId[%s] MerchantTypeId[%s] in MerchantType Memory...", InstId, MerchantTypeId );
		printf( "\nError in Adding InstId[%s] MerchantTypeId[%s] in MerchantType Memory...", InstId, MerchantTypeId );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceUpdateMerchantType( const char *InstId, const char *MerchantTypeId )
{
	struct EzMMSMerchantType merchanttype_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &merchanttype_rec, 0, sizeof( struct EzMMSMerchantType ) );
	retval = readEzMMSMerchantType( InstId, MerchantTypeId, &merchanttype_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantTypeId[%s] from EzMMSMerchantType....OraErr[%05d]", InstId, MerchantTypeId, retval );
		printf( "\nError in Reading InstId[%s] MerchantTypeId[%s] from EzMMSMerchantType....OraErr[%05d]", InstId, MerchantTypeId, retval );
		DBClose();
		return -1;
	}

	if( updateMerchantType( merchanttype_rec ) < 0 )
	{
		trace( "Error in Updating InstId[%s] MerchantTypeId[%s] in MerchantType Memory...", InstId, MerchantTypeId );
		printf( "\nError in Updating InstId[%s] MerchantTypeId[%s] in MerchantType Memory...", InstId, MerchantTypeId );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceDeleteMerchantType( const char *InstId, const char *MerchantTypeId )
{
	if( deleteMerchantType( InstId, MerchantTypeId ) < 0 )
	{
		trace( "Error in Deleting InstId[%s] MerchantTypeId[%s] from MerchantType Memory..", InstId, MerchantTypeId );
		printf( "\nError in Deleting InstId[%s] MerchantTypeId[%s] from MerchantType Memory..", InstId, MerchantTypeId );
		return -1;
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantType()
{
	printf( "\n%15s%16s%25s%15s%15s", "INSTID", "MERCHANTTYPEID", "TXNALLOWED", "LOYALTYREQ", "MAXPINRETRY" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxMerchantType; i++ )
	{
		if( strcmp( ( MerchantTypeShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantTypeShmPtr + i )->MerchantTypeId, MMS_RECORD_STRINGINIT_VAL ) )
			printf( "\n%15s%16s%25s%15c%15d", ( MerchantTypeShmPtr + i )->InstId, ( MerchantTypeShmPtr + i )->MerchantTypeId, ( MerchantTypeShmPtr + i )->TxnAllowed, ( MerchantTypeShmPtr + i )->LoyaltyReq, ( MerchantTypeShmPtr + i )->MaxPINRetryCount );
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantType( const char *InstId )
{
	printf( "\n%15s%16s%25s%15s%15s", "INSTID", "MERCHANTTYPEID", "TXNALLOWED", "LOYALTYREQ", "MAXPINRETRY" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxMerchantType; i++ )
	{
		if( strcmp( ( MerchantTypeShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantTypeShmPtr + i )->MerchantTypeId, MMS_RECORD_STRINGINIT_VAL ) )
			if( !strcmp( ( MerchantTypeShmPtr + i )->InstId, InstId ) )
				printf( "\n%15s%16s%25s%15c%15d", ( MerchantTypeShmPtr + i )->InstId, ( MerchantTypeShmPtr + i )->MerchantTypeId, ( MerchantTypeShmPtr + i )->TxnAllowed, ( MerchantTypeShmPtr + i )->LoyaltyReq, ( MerchantTypeShmPtr + i )->MaxPINRetryCount );
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantType( const char *InstId, const char *MerchantTypeId )
{
	printf( "\n%15s%16s%25s%15s%15s", "INSTID", "MERCHANTTYPEID", "TXNALLOWED", "LOYALTYREQ", "MAXPINRETRY" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxMerchantType; i++ )
	{
		if( strcmp( ( MerchantTypeShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantTypeShmPtr + i )->MerchantTypeId, MMS_RECORD_STRINGINIT_VAL ) )
			if( !strcmp( ( MerchantTypeShmPtr + i )->InstId, InstId ) && !strcmp( ( MerchantTypeShmPtr + i )->MerchantTypeId, MerchantTypeId ) )
				printf( "\n%15s%16s%25s%15c%15d", ( MerchantTypeShmPtr + i )->InstId, ( MerchantTypeShmPtr + i )->MerchantTypeId, ( MerchantTypeShmPtr + i )->TxnAllowed, ( MerchantTypeShmPtr + i )->LoyaltyReq, ( MerchantTypeShmPtr + i )->MaxPINRetryCount );
	}
	return 1;
}*/

int EzMMSCmd :: serviceAddStoreProfile( const char *InstId, const char *MerchantId, const char *StoreId )
{
	struct EzMMSStoreProfile storeprofile_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &storeprofile_rec, 0, sizeof( struct EzMMSStoreProfile ) );
	retval = readEzMMSStoreProfile( InstId, MerchantId, StoreId, &storeprofile_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantId[%s] StoreId[%s] from EzMMSStoreProfile....OraErr[%05d]", InstId, MerchantId, StoreId, retval );
		printf( "\nError in Reading InstId[%s] MerchantId[%s] StoreId[%s] from EzMMSStoreProfile....OraErr[%05d]", InstId, MerchantId, StoreId, retval );
		DBClose();
		return -1;
	}

	if( addStoreProfile( storeprofile_rec ) < 0 )
	{
		trace( "Error in Adding InstId[%s] MerchantId[%s] StoreId[%s] in StoreProfile Memory...", InstId, MerchantId, StoreId );
		printf( "\nError in Adding InstId[%s] MerchantId[%s] StoreId[%s] in StoreProfile Memory...", InstId, MerchantId, StoreId );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceUpdateStoreProfile( const char *InstId, const char *MerchantId, const char *StoreId )
{
	struct EzMMSStoreProfile storeprofile_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &storeprofile_rec, 0, sizeof( struct EzMMSStoreProfile ) );
	retval = readEzMMSStoreProfile( InstId, MerchantId, StoreId, &storeprofile_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantId[%s] StoreId[%s] from EzMMSStoreProfile....OraErr[%05d]", InstId, MerchantId, StoreId, retval );
		printf( "\nError in Reading InstId[%s] MerchantId[%s] StoreId[%s] from EzMMSStoreProfile....OraErr[%05d]", InstId, MerchantId, StoreId, retval );
		DBClose();
		return -1;
	}

	if( updateStoreProfile( storeprofile_rec ) < 0 )
	{
		trace( "Error in Updating InstId[%s] MerchantId[%s] StoreId[%s] in StoreProfile Memory...", InstId, MerchantId, StoreId );
		printf( "\nError in Updating InstId[%s] MerchantId[%s] StoreId[%s] in StoreProfile Memory...", InstId, MerchantId, StoreId );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceDeleteStoreProfile( const char *InstId, const char *MerchantId, const char *StoreId )
{
	if( deleteStoreProfile( InstId, MerchantId, StoreId ) < 0 )
	{
		trace( "Error in Deleting InstId[%s] MerchantId[%s] StoreId[%s] from StoreProfile Memory..", InstId, MerchantId, StoreId );
		printf( "\nError in Deleting InstId[%s] MerchantId[%s] StoreId[%s] from StoreProfile Memory..", InstId, MerchantId, StoreId );
		return -1;
	}
	return 1;
}

int EzMMSCmd :: serviceListStoreProfile()
{
	for( int i = 0, j = 0; i < MaxStoreProfile; i++ )
	{
		if( strcmp( ( StoreProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( StoreProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( StoreProfileShmPtr + i )->StoreId, MMS_RECORD_STRINGINIT_VAL ) )
		{
			printf( "\n***************Store No:%d**********************", j + 1 );
			printf( "\nInstId<%s>", ( StoreProfileShmPtr + i )->InstId );
			printf( "\nMerchantId<%s>", ( StoreProfileShmPtr + i )->MerchantId );
			printf( "\nStoreId<%s>", ( StoreProfileShmPtr + i )->StoreId );
			printf( "\nStatus<%d>", ( StoreProfileShmPtr + i )->Status );
			printf( "\nStoreName<%s>", ( StoreProfileShmPtr + i )->StoreName );
			printf( "\nStoreLocation<%s>", ( StoreProfileShmPtr + i )->StoreLocation );
			printf( "\nCityName<%s>", ( StoreProfileShmPtr + i )->CityName );
			printf( "\nCityCode<%s>", ( StoreProfileShmPtr + i )->CityCode );
			printf( "\nStateName<%s>", ( StoreProfileShmPtr + i )->StateName );
			printf( "\nCountryName<%s>", ( StoreProfileShmPtr + i )->CountryName );
			printf( "\nLandLine1<%s>", ( StoreProfileShmPtr + i )->LandLine1 );
			printf( "\nLandLine2<%s>", ( StoreProfileShmPtr + i )->LandLine2 );
			printf( "\nPMobileNo<%s>", ( StoreProfileShmPtr + i )->PMobileNo );
			printf( "\nSMobileNo<%s>", ( StoreProfileShmPtr + i )->SMobileNo );
			printf( "\nWorkingHrs<%d>", ( StoreProfileShmPtr + i )->WorkingHrs );
			printf( "\nOpeningTime<%s>", ( StoreProfileShmPtr + i )->OpeningTime );
			printf( "\nClosingTime<%s>", ( StoreProfileShmPtr + i )->ClosingTime );
			j++;
		}
	}
	return 1;
}

int EzMMSCmd :: serviceListStoreProfile( const char *InstId )
{
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0, j = 0; i < MaxStoreProfile; i++ )
	{
		if( strcmp( ( StoreProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( StoreProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( StoreProfileShmPtr + i )->StoreId, MMS_RECORD_STRINGINIT_VAL ) )
		{
			if( !strcmp( ( StoreProfileShmPtr + i )->InstId, InstId ) )
			{
				printf( "\n***************Store No:%d**********************", j + 1 );
				printf( "\nInstId<%s>", ( StoreProfileShmPtr + i )->InstId );
				printf( "\nMerchantId<%s>", ( StoreProfileShmPtr + i )->MerchantId );
				printf( "\nStoreId<%s>", ( StoreProfileShmPtr + i )->StoreId );
				printf( "\nStatus<%d>", ( StoreProfileShmPtr + i )->Status );
				printf( "\nStoreName<%s>", ( StoreProfileShmPtr + i )->StoreName );
				printf( "\nStoreLocation<%s>", ( StoreProfileShmPtr + i )->StoreLocation );
				printf( "\nCityName<%s>", ( StoreProfileShmPtr + i )->CityName );
				printf( "\nCityCode<%s>", ( StoreProfileShmPtr + i )->CityCode );
				printf( "\nStateName<%s>", ( StoreProfileShmPtr + i )->StateName );
				printf( "\nCountryName<%s>", ( StoreProfileShmPtr + i )->CountryName );
				printf( "\nLandLine1<%s>", ( StoreProfileShmPtr + i )->LandLine1 );
				printf( "\nLandLine2<%s>", ( StoreProfileShmPtr + i )->LandLine2 );
				printf( "\nPMobileNo<%s>", ( StoreProfileShmPtr + i )->PMobileNo );
				printf( "\nSMobileNo<%s>", ( StoreProfileShmPtr + i )->SMobileNo );
				printf( "\nWorkingHrs<%d>", ( StoreProfileShmPtr + i )->WorkingHrs );
				printf( "\nOpeningTime<%s>", ( StoreProfileShmPtr + i )->OpeningTime );
				printf( "\nClosingTime<%s>", ( StoreProfileShmPtr + i )->ClosingTime );
				j++;
			}
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzMMSCmd :: serviceListStoreProfile( const char *InstId, const char *MerchantId )
{
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0, j = 0; i < MaxStoreProfile; i++ )
	{
		if( strcmp( ( StoreProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( StoreProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( StoreProfileShmPtr + i )->StoreId, MMS_RECORD_STRINGINIT_VAL ) )
		{
			if( !strcmp( ( StoreProfileShmPtr + i )->InstId, InstId ) && !strcmp( ( StoreProfileShmPtr + i )->MerchantId, MerchantId ) )
			{
				printf( "\n***************Store No:%d**********************", j + 1 );
				printf( "\nInstId<%s>", ( StoreProfileShmPtr + i )->InstId );
				printf( "\nMerchantId<%s>", ( StoreProfileShmPtr + i )->MerchantId );
				printf( "\nStoreId<%s>", ( StoreProfileShmPtr + i )->StoreId );
				printf( "\nStatus<%d>", ( StoreProfileShmPtr + i )->Status );
				printf( "\nStoreName<%s>", ( StoreProfileShmPtr + i )->StoreName );
				printf( "\nStoreLocation<%s>", ( StoreProfileShmPtr + i )->StoreLocation );
				printf( "\nCityName<%s>", ( StoreProfileShmPtr + i )->CityName );
				printf( "\nCityCode<%s>", ( StoreProfileShmPtr + i )->CityCode );
				printf( "\nStateName<%s>", ( StoreProfileShmPtr + i )->StateName );
				printf( "\nCountryName<%s>", ( StoreProfileShmPtr + i )->CountryName );
				printf( "\nLandLine1<%s>", ( StoreProfileShmPtr + i )->LandLine1 );
				printf( "\nLandLine2<%s>", ( StoreProfileShmPtr + i )->LandLine2 );
				printf( "\nPMobileNo<%s>", ( StoreProfileShmPtr + i )->PMobileNo );
				printf( "\nSMobileNo<%s>", ( StoreProfileShmPtr + i )->SMobileNo );
				printf( "\nWorkingHrs<%d>", ( StoreProfileShmPtr + i )->WorkingHrs );
				printf( "\nOpeningTime<%s>", ( StoreProfileShmPtr + i )->OpeningTime );
				printf( "\nClosingTime<%s>", ( StoreProfileShmPtr + i )->ClosingTime );
				j++;
			}
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzMMSCmd :: serviceListStoreProfile( const char *InstId, const char *MerchantId, const char *StoreId )
{
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0, j = 0; i < MaxStoreProfile; i++ )
	{
		if( strcmp( ( StoreProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( StoreProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( StoreProfileShmPtr + i )->StoreId, MMS_RECORD_STRINGINIT_VAL ) )
		{
			if( !strcmp( ( StoreProfileShmPtr + i )->InstId, InstId ) && !strcmp( ( StoreProfileShmPtr + i )->MerchantId, MerchantId ) && !strcmp( ( StoreProfileShmPtr + i )->StoreId, StoreId ) )
			{
				printf( "\n***************Store No:%d**********************", j + 1 );
				printf( "\nInstId<%s>", ( StoreProfileShmPtr + i )->InstId );
				printf( "\nMerchantId<%s>", ( StoreProfileShmPtr + i )->MerchantId );
				printf( "\nStoreId<%s>", ( StoreProfileShmPtr + i )->StoreId );
				printf( "\nStatus<%d>", ( StoreProfileShmPtr + i )->Status );
				printf( "\nStoreName<%s>", ( StoreProfileShmPtr + i )->StoreName );
				printf( "\nStoreLocation<%s>", ( StoreProfileShmPtr + i )->StoreLocation );
				printf( "\nCityName<%s>", ( StoreProfileShmPtr + i )->CityName );
				printf( "\nCityCode<%s>", ( StoreProfileShmPtr + i )->CityCode );
				printf( "\nStateName<%s>", ( StoreProfileShmPtr + i )->StateName );
				printf( "\nCountryName<%s>", ( StoreProfileShmPtr + i )->CountryName );
				printf( "\nLandLine1<%s>", ( StoreProfileShmPtr + i )->LandLine1 );
				printf( "\nLandLine2<%s>", ( StoreProfileShmPtr + i )->LandLine2 );
				printf( "\nPMobileNo<%s>", ( StoreProfileShmPtr + i )->PMobileNo );
				printf( "\nSMobileNo<%s>", ( StoreProfileShmPtr + i )->SMobileNo );
				printf( "\nWorkingHrs<%d>", ( StoreProfileShmPtr + i )->WorkingHrs );
				printf( "\nOpeningTime<%s>", ( StoreProfileShmPtr + i )->OpeningTime );
				printf( "\nClosingTime<%s>", ( StoreProfileShmPtr + i )->ClosingTime );
				j++;
			}
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzMMSCmd :: serviceAddTerminalProfile( const char *MachineId )
{
	struct EzMMSTerminalProfile terminalprofile_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
	retval = readEzMMSTerminalProfile( MachineId, &terminalprofile_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MachineId[%s] from EzMMSTerminalProfile....OraErr[%05d]", MachineId, retval );
		printf( "\nError in Reading MachineId[%s] from EzMMSTerminalProfile....OraErr[%05d]", MachineId, retval );
		DBClose();
		return -1;
	}

	if( addTerminalProfile( terminalprofile_rec ) < 0 )
	{
		trace( "Error in Adding MachineId[%s] in TerminalProfile Memory...", MachineId );
		printf( "\nError in Adding MachineId[%s] in TerminalProfile Memory...", MachineId );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceUpdateTerminalProfile( const char *MachineId )
{
	struct EzMMSTerminalProfile terminalprofile_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
	retval = readEzMMSTerminalProfile( MachineId, &terminalprofile_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MachineId[%s] from EzMMSTerminalProfile....OraErr[%05d]", MachineId, retval );
		printf( "\nError in Reading MachineId[%s] from EzMMSTerminalProfile....OraErr[%05d]", MachineId, retval );
		DBClose();
		return -1;
	}

	if( updateTerminalProfile( terminalprofile_rec ) < 0 )
	{
		trace( "Error in Updating MachineId[%s] in TerminalProfile Memory...", MachineId );
		printf( "\nError in Updating MachineId[%s] in TerminalProfile Memory...", MachineId );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceDeleteTerminalProfile( const char *MachineId )
{
	if( deleteTerminalProfile( MachineId ) < 0 )
	{
		trace( "Error in Deleting MachineId[%s] in TerminalProfile Memory...", MachineId );
		printf( "\nError in Deleting MachineId[%s] in TerminalProfile Memory...", MachineId );
		return -1;
	}
	return 1;
}

int EzMMSCmd :: serviceListTerminalProfile()
{
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0, j = 0; i < MaxTerminalProfile; i++ )
	{
		if( strcmp( ( TerminalProfileShmPtr + i )->MachineId, MMS_RECORD_STRINGINIT_VAL ) )
		{
			printf( "\n***************Terminal No:%d**********************", j + 1 );
			printf( "\nMachineId<%s>", ( TerminalProfileShmPtr + i )->MachineId );
			printf( "\nInstId<%s>", ( TerminalProfileShmPtr + i )->InstId );
			printf( "\nMerchantId<%s>", ( TerminalProfileShmPtr + i )->MerchantId );
			printf( "\nStoreId<%s>", ( TerminalProfileShmPtr + i )->StoreId );
			printf( "\nTerminalId<%s>", ( TerminalProfileShmPtr + i )->TerminalId );
			printf( "\nTerminalName<%s>", ( TerminalProfileShmPtr + i )->TerminalName );
			printf( "\nTermLocation<%s>", ( TerminalProfileShmPtr + i )->TerminalLocation );
			printf( "\nTerminalStatus<%c>", ( TerminalProfileShmPtr + i )->TerminalStatus );
			printf( "\nWorkingHrs<%d>", ( TerminalProfileShmPtr + i )->WorkingHrs );
			printf( "\nOpeningTime<%s>", ( TerminalProfileShmPtr + i )->OpeningTime );
			printf( "\nClosingTime<%s>", ( TerminalProfileShmPtr + i )->ClosingTime );
			printf( "\nCountryCode<%s>", ( TerminalProfileShmPtr + i )->CountryCode );
			printf( "\nChipEnabled<%c>", ( TerminalProfileShmPtr + i )->ChipEnabled );
			printf( "\nTermMasterKey<%s>", ( TerminalProfileShmPtr + i )->TermMasterKey );
			printf( "\nTermPINKey<%s>", ( TerminalProfileShmPtr + i )->TermPINKey );
			printf( "\nTermMACKey<%s>", ( TerminalProfileShmPtr + i )->TermMACKey );
			printf( "\nBatchId<%s>", ( TerminalProfileShmPtr + i )->BatchId );
			printf( "\nTermBatchId<%s>", ( TerminalProfileShmPtr + i )->TermBatchId );
			j++;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzMMSCmd :: serviceListTerminalProfile( const char *MachineId )
{
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0, j = 0; i < MaxTerminalProfile; i++ )
	{
		if( strcmp( ( TerminalProfileShmPtr + i )->MachineId, MachineId ) )
		{
			printf( "\n***************Terminal No:%d**********************", j + 1 );
			printf( "\nMachineId<%s>", ( TerminalProfileShmPtr + i )->MachineId );
			printf( "\nInstId<%s>", ( TerminalProfileShmPtr + i )->InstId );
			printf( "\nMerchantId<%s>", ( TerminalProfileShmPtr + i )->MerchantId );
			printf( "\nStoreId<%s>", ( TerminalProfileShmPtr + i )->StoreId );
			printf( "\nTerminalId<%s>", ( TerminalProfileShmPtr + i )->TerminalId );
			printf( "\nTerminalName<%s>", ( TerminalProfileShmPtr + i )->TerminalName );
			printf( "\nTermLocation<%s>", ( TerminalProfileShmPtr + i )->TerminalLocation );
			printf( "\nTerminalStatus<%c>", ( TerminalProfileShmPtr + i )->TerminalStatus );
			printf( "\nWorkingHrs<%d>", ( TerminalProfileShmPtr + i )->WorkingHrs );
			printf( "\nOpeningTime<%s>", ( TerminalProfileShmPtr + i )->OpeningTime );
			printf( "\nClosingTime<%s>", ( TerminalProfileShmPtr + i )->ClosingTime );
			printf( "\nCountryCode<%s>", ( TerminalProfileShmPtr + i )->CountryCode );
			printf( "\nChipEnabled<%c>", ( TerminalProfileShmPtr + i )->ChipEnabled );
			printf( "\nTermMasterKey<%s>", ( TerminalProfileShmPtr + i )->TermMasterKey );
			printf( "\nTermPINKey<%s>", ( TerminalProfileShmPtr + i )->TermPINKey );
			printf( "\nTermMACKey<%s>", ( TerminalProfileShmPtr + i )->TermMACKey );
			printf( "\nBatchId<%s>", ( TerminalProfileShmPtr + i )->BatchId );
			printf( "\nTermBatchId<%s>", ( TerminalProfileShmPtr + i )->TermBatchId );
			j++;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

/*int EzMMSCmd :: serviceAddMerchantRelation( const char *InstId, const char *MerchantId, const char *AccountNo )
{
	struct EzMMSMerchantRelation merchantrelation_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &merchantrelation_rec, 0, sizeof( struct EzMMSMerchantRelation ) );
	retval = readEzMMSMerchantRelation( InstId, MerchantId, AccountNo, &merchantrelation_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantId[%s] AccountNo[%s] from EzMMSMerchantRelation....OraErr[%05d]", InstId, MerchantId, AccountNo, retval );
		printf( "\nError in Reading InstId[%s] MerchantId[%s] AccountNo[%s] from EzMMSMerchantRelation....OraErr[%05d]", InstId, MerchantId, AccountNo, retval );
		DBClose();
		return -1;
	}
	if( addMerchantRelation( merchantrelation_rec ) < 0 )
	{
		trace( "Error in Adding InstId[%s] MerchantId[%s] AccountNo[%s] in MerchantRelation Memory...", InstId, MerchantId, AccountNo );
		printf( "\nError in Adding InstId[%s] MerchantId[%s] AccountNo[%s] in MerchantRelation Memory...", InstId, MerchantId, AccountNo );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceUpdateMerchantRelation( const char *InstId, const char *MerchantId, const char *AccountNo )
{
	struct EzMMSMerchantRelation merchantrelation_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		trace( "\nError in Connecting with MMS Database" );
		printf( "\nError in Connecting with MMS Database" );
		return -1;
	}

	memset( &merchantrelation_rec, 0, sizeof( struct EzMMSMerchantRelation ) );
	retval = readEzMMSMerchantRelation( InstId, MerchantId, AccountNo, &merchantrelation_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantId[%s] AccountNo[%s] from EzMMSMerchantRelation....OraErr[%05d]", InstId, MerchantId, AccountNo, retval );
		printf( "\nError in Reading InstId[%s] MerchantId[%s] AccountNo[%s] from EzMMSMerchantRelation....OraErr[%05d]", InstId, MerchantId, AccountNo, retval );
		DBClose();
		return -1;
	}

	if( updateMerchantRelation( merchantrelation_rec ) < 0 )
	{
		trace( "Error in Updating InstId[%s] MerchantId[%s] AccountNo[%s] in MerchantRelation Memory...", InstId, MerchantId, AccountNo );
		printf( "\nError in Updating InstId[%s] MerchantId[%s] AccountNo[%s] in MerchantRelation Memory...", InstId, MerchantId, AccountNo );
		DBClose();
		return -1;
	}
	DBClose();
	return 1;
}

int EzMMSCmd :: serviceDeleteMerchantRelation( const char *InstId, const char *MerchantId, const char *AccountNo )
{
	if( deleteMerchantRelation( InstId, MerchantId, AccountNo ) < 0 )
	{
		trace( "Error in Deleting InstId[%s] MerchantId[%s] AccountNo[%s] from MerchantRelation Memory..", InstId, MerchantId, AccountNo );
		printf( "\nError in Deleting InstId[%s] MerchantId[%s] AccountNo[%s] from MerchantRelation Memory..", InstId, MerchantId, AccountNo );
		return -1;
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantRelation()
{
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%32s%10s%10s%10s", "INSTID", "MERCHANTID", "ACCOUNTNO", "CURR-CODE", "STATUS", "PRIORITY" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxMerchantRelation; i++ )
	{
		if( strcmp( ( MerchantRelationShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantRelationShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantRelationShmPtr + i )->AccountNo, MMS_RECORD_STRINGINIT_VAL ) )
			printf( "\n%15s%20s%32s%10s%10c%10d", ( MerchantRelationShmPtr + i )->InstId, ( MerchantRelationShmPtr + i )->MerchantId, ( MerchantRelationShmPtr + i )->AccountNo, ( MerchantRelationShmPtr + i )->CurrCode, ( MerchantRelationShmPtr + i )->AccountStatus, ( MerchantRelationShmPtr + i )->AccountPriority );
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantRelation( const char *InstId )
{
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%32s%10s%10s%10s", "INSTID", "MERCHANTID", "ACCOUNTNO", "CURR-CODE", "STATUS", "PRIORITY" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxMerchantRelation; i++ )
	{
		if( strcmp( ( MerchantRelationShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantRelationShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantRelationShmPtr + i )->AccountNo, MMS_RECORD_STRINGINIT_VAL ) )
		{
			if( !strcmp( ( MerchantRelationShmPtr + i )->InstId, InstId ) )
				printf( "\n%15s%20s%32s%10s%10c%10d", ( MerchantRelationShmPtr + i )->InstId, ( MerchantRelationShmPtr + i )->MerchantId, ( MerchantRelationShmPtr + i )->AccountNo, ( MerchantRelationShmPtr + i )->CurrCode, ( MerchantRelationShmPtr + i )->AccountStatus, ( MerchantRelationShmPtr + i )->AccountPriority );
		}
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantRelation( const char *InstId, const char *MerchantId )
{
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%32s%10s%10s%10s", "INSTID", "MERCHANTID", "ACCOUNTNO", "CURR-CODE", "STATUS", "PRIORITY" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxMerchantRelation; i++ )
	{
		if( strcmp( ( MerchantRelationShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantRelationShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantRelationShmPtr + i )->AccountNo, MMS_RECORD_STRINGINIT_VAL ) )
		{
			if( !strcmp( ( MerchantRelationShmPtr + i )->InstId, InstId ) && !strcmp( ( MerchantRelationShmPtr + i )->MerchantId, MerchantId ) )
				printf( "\n%15s%20s%32s%10s%10c%10d", ( MerchantRelationShmPtr + i )->InstId, ( MerchantRelationShmPtr + i )->MerchantId, ( MerchantRelationShmPtr + i )->AccountNo, ( MerchantRelationShmPtr + i )->CurrCode, ( MerchantRelationShmPtr + i )->AccountStatus, ( MerchantRelationShmPtr + i )->AccountPriority );
		}
	}
	return 1;
}

int EzMMSCmd :: serviceListMerchantRelation( const char *InstId, const char *MerchantId, const char *AccountNo )
{
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%32s%10s%10s%10s", "INSTID", "MERCHANTID", "ACCOUNTNO", "CURR-CODE", "STATUS", "PRIORITY" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxMerchantRelation; i++ )
	{
		if( strcmp( ( MerchantRelationShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantRelationShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL ) && strcmp( ( MerchantRelationShmPtr + i )->AccountNo, MMS_RECORD_STRINGINIT_VAL ) )
		{
			if( !strcmp( ( MerchantRelationShmPtr + i )->InstId, InstId ) && !strcmp( ( MerchantRelationShmPtr + i )->MerchantId, MerchantId ) && !strcmp( ( MerchantRelationShmPtr + i )->AccountNo, AccountNo ) )
				printf( "\n%15s%20s%32s%10s%10c%10d", ( MerchantRelationShmPtr + i )->InstId, ( MerchantRelationShmPtr + i )->MerchantId, ( MerchantRelationShmPtr + i )->AccountNo, ( MerchantRelationShmPtr + i )->CurrCode, ( MerchantRelationShmPtr + i )->AccountStatus, ( MerchantRelationShmPtr + i )->AccountPriority );
		}
	}
	return 1;
}*/

int EzMMSCmd :: serviceMMSCmd( int argc, char **argv )
{
	char InstId[ 50 ], command[ 100 ], command1[ 100 ];
	printf( "\n******************Ezlink Terminal Merchant System Command Interface****************");
	while( 1 )
	{
		printf( "\n\neztmscmd>" );
		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;
		if( !strcasecmp( command, "Merchant" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceAddMerchantProfile( InstId, command );
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceUpdateMerchantProfile( InstId, command );
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceDeleteMerchantProfile( InstId, command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListMerchantProfile();
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					serviceListMerchantProfile( InstId );
					continue;
				}
				serviceListMerchantProfile( InstId, command );
			}
		}
		/*else if( !strcasecmp( command, "MerchantType" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceAddMerchantType( InstId, command );
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceUpdateMerchantType( InstId, command );
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceDeleteMerchantType( InstId, command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListMerchantType();
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					serviceListMerchantType( InstId );
					continue;
				}
				serviceListMerchantType( InstId, command );
			}
		}*/
		else if( !strcasecmp( command, "Store" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 5 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceAddStoreProfile( InstId, command, command1 );
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 5 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceUpdateStoreProfile( InstId, command, command1 );
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 5 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceDeleteStoreProfile( InstId, command, command1 );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListStoreProfile();
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					serviceListStoreProfile( InstId );
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 5 );
				if( strlen( command1 ) == 0 )
				{
					serviceListStoreProfile( InstId, command );
					continue;
				}
				serviceListStoreProfile( InstId, command, command1 );
			}
		}
		else if( !strcasecmp( command, "Terminal" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceAddTerminalProfile( command );
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceUpdateTerminalProfile( command );
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceDeleteTerminalProfile( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTerminalProfile();
					continue;
				}
				serviceListTerminalProfile( command );
			}
		}
		/*else if( !strcasecmp( command, "Relation" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 5 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceAddMerchantRelation( InstId, command, command1 );
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 5 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceUpdateMerchantRelation( InstId, command, command1 );
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 5 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceDeleteMerchantRelation( InstId, command, command1 );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListMerchantRelation();
					continue;
				}
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					serviceListMerchantRelation( InstId );
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 5 );
				if( strlen( command1 ) == 0 )
				{
					serviceListMerchantRelation( InstId, command );
					continue;
				}
				serviceListMerchantRelation( InstId, command, command1 );
			}
		}*/
		else if( !strcmp( command, "help" ) )
		{
			printf("\n <Terminal> <Add> <MachineId>" );
			printf("\n <Terminal> <Update> <MachineId>" );
			printf("\n <Terminal> <Delete> <MachineId>" );
			printf("\n <Terminal> <List> <MachineId>" );
			printf("\n <Terminal> <List>" );
			printf("\n <Merchant> <Add> <InstId> <MerchantId>" );
			printf("\n <Merchant> <Update> <InstId> <MerchantId>" );
			printf("\n <Merchant> <Delete> <InstId> <MerchantId>" );
			printf("\n <Merchant> <List> <InstId> <MerchantId>" );
			printf("\n <Merchant> <List> <InstId>" );
			printf("\n <Merchant> <List>" );
			/*printf("\n <MerchantType> <Add> <InstId> <MerchantTypeId>" );
			printf("\n <MerchantType> <Update> <InstId> <MerchantTypeId>" );
			printf("\n <MerchantType> <Delete> <InstId> <MerchantTypeId>" );
			printf("\n <MerchantType> <List> <InstId> <MerchantTypeId>" );
			printf("\n <MerchantType> <List> <InstId>" );
			printf("\n <MerchantType> <List>" );*/
			printf("\n <Store> <Add> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <Update> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <Delete> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <List> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <List> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <List> <InstId> <StoreId>" );
			printf("\n <Store> <List>" );
			/*printf("\n <Relation> <Add> <InstId> <MerchantId> <AccountNo>" );
			printf("\n <Relation> <Update> <InstId> <MerchantId> <AccountNo>" );
			printf("\n <Relation> <Delete> <InstId> <MerchantId> <AccountNo>" );
			printf("\n <Relation> <List> <InstId> <MerchantId> <AccountNo>" );
			printf("\n <Relation> <List> <InstId> <MerchantId>" );
			printf("\n <Relation> <List> <InstId>" );
			printf("\n <Relation> <List>" );*/
		}
		else if( !strcmp( command, "quit" )  || !strcmp( command, "exit" ) )
			break;
		else
		{
			printf("\n invaild command ..type help for more" );
			continue;
		}
	}
	return 0;
}

int EzMMSCmd :: readEzMMSMerchantProfile( const char *I_InstId, const char *I_MerchantId, struct EzMMSMerchantProfile *merchantprofile_ptr )
{
	char InstId[ 13 ];
	char MerchantId[ 16 ];
	char MCCList[ 33 ];
	char MerchantTypeId[ 17 ];
	char ParentMerchantId[ 16 ];
	char MerchantName[ 33 ];
	char Addr1[ 65 ];
	char Addr2[ 65 ];
	char Status;
	char DOB[ 11 ];
	char PMobileNo[ 17 ];
	char SMobileNo[ 17 ];
	char PMailAddr[ 33 ];
	char SMailAddr[ 33 ];
	char SettCurrCode[ 5 ];
	char CurrList[ 33 ];
	char CardIssuanceFlag;
	char tempdate[ 11 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzMerchantProfile [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt,  "SELECT \
			RTRIM(INST_ID),\
			RTRIM(MERCH_ID),\
			RTRIM( ISNULL( MCC_LIST, 'NA' ) ),\
			RTRIM( ISNULL( MERCH_TYPE_ID, 'NA' ) ),\
			RTRIM( ISNULL( PARENT_MERCH_ID, 'NA' ) ),\
			RTRIM( ISNULL( MERCH_NAME, 'NA' ) ),\
			RTRIM( ISNULL( PRIM_MAIL_ADDR, 'NA' ) ),\
			RTRIM( ISNULL( SEC_MAIL_ADDR, 'NA' ) ),\
			ISNULL( STATUS, '0' ),\
			RTRIM( ISNULL( convert(varchar,DOB, 105 ), 'NA' ) ),\
			RTRIM( ISNULL( PRIM_MOBILE_NO, 'NA' ) ),\
			RTRIM( ISNULL( SEC_MOBILE_NO, 'NA' ) ),\
			RTRIM( ISNULL( PRIM_EMAIL_ID, 'NA' ) ),\
			RTRIM( ISNULL( SEC_EMAIL_ID, 'NA' ) ),\
			RTRIM( ISNULL( SETT_CURR_CODE, 'NA' ) ),\
			RTRIM( ISNULL( CURR_LIST, 'NA' ) ),\
			ISNULL( CARD_ISSUED_FLAG, 'N' ) \
		FROM EZMMS_MERCHANTPROFILE WHERE RTRIM(INST_ID) ='%s' AND RTRIM(MERCH_ID)='%s';", I_InstId, I_MerchantId);
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzMerchantProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MCCList, sizeof(MCCList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(AtmId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MerchantTypeId, sizeof(MerchantTypeId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(MerchantTypeId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, ParentMerchantId, sizeof(ParentMerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ParentMerchantId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, MerchantName, sizeof(MerchantName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(MerchantName) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, Addr1, sizeof(Addr1), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(Addr1) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, Addr2, sizeof(Addr2), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(Addr2) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &Status, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(Status) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, DOB, sizeof(DOB), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(DOB) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, PMobileNo, sizeof(PMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(PMobileNo) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, SMobileNo, sizeof(SMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SMobileNo) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, PMailAddr, sizeof(PMailAddr), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(PMailAddr) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, SMailAddr, sizeof(SMailAddr), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SMailAddr) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_CHAR, SettCurrCode, sizeof(SettCurrCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SettCurrCode) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_CHAR, CurrList, sizeof(CurrList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CurrList) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_BINARY, &CardIssuanceFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CardIssuanceFlag) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( MCCList, 0, sizeof( MCCList ) );
	memset( MerchantTypeId, 0, sizeof( MerchantTypeId ) );
	memset( ParentMerchantId, 0, sizeof( ParentMerchantId ) );
	memset( MerchantName, 0, sizeof( MerchantName ) );
	memset( Addr1, 0, sizeof( Addr1 ) );
	memset( Addr2, 0, sizeof( Addr2 ) );
	memset( DOB, 0, sizeof( DOB ) );
	memset( PMobileNo, 0, sizeof( PMobileNo ) );
	memset( SMobileNo, 0, sizeof( SMobileNo ) );
	memset( PMailAddr, 0, sizeof( PMailAddr ) );
	memset( SMailAddr, 0, sizeof( SMailAddr ) );
	memset( SettCurrCode, 0, sizeof( SettCurrCode ) );
	memset( CurrList, 0, sizeof( CurrList ) );

	if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( merchantprofile_ptr, 0, sizeof( struct EzMMSMerchantProfile ) );
        strcpy( merchantprofile_ptr->InstId, InstId );
        strcpy( merchantprofile_ptr->MerchantId, MerchantId );
        strcpy( merchantprofile_ptr->MCCList, MCCList );
        strcpy( merchantprofile_ptr->MerchantTypeId, MerchantTypeId );
        strcpy( merchantprofile_ptr->ParentMerchantId, ParentMerchantId );
      	strcpy( merchantprofile_ptr->MerchantName, MerchantName );
      	strcpy( merchantprofile_ptr->Addr1, Addr1 );
      	strcpy( merchantprofile_ptr->Addr2, Addr2 );
      	merchantprofile_ptr->Status = Status;
      	if( !strcasecmp( DBType, SQLSERVER ) )
		{
			memset( tempdate, 0, sizeof( tempdate ) );
			getSwitchDateFmt( DOB, "DDMMYY", tempdate );
			strcpy( merchantprofile_ptr->DOB, tempdate );
		}
      	strcpy( merchantprofile_ptr->PMobileNo, PMobileNo );
      	strcpy( merchantprofile_ptr->SMobileNo, SMobileNo );
      	strcpy( merchantprofile_ptr->PMailAddr, PMailAddr );
      	strcpy( merchantprofile_ptr->SMailAddr, SMailAddr );
      	strcpy( merchantprofile_ptr->SettCurrCode, SettCurrCode );
      	strcpy( merchantprofile_ptr->CurrList, CurrList );
      	merchantprofile_ptr->CardIssuanceFlag = CardIssuanceFlag;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzMMSCmd :: readEzMMSStoreProfile( const char *I_InstId, const char *I_MerchantId, const char *I_StoreId, struct EzMMSStoreProfile *storeprofile_ptr )
{
	char InstId[ 13 ];
	char MerchantId[ 16 ];
	char StoreId[ 33 ];
	char Status;
	char StoreName[ 33 ];
	char StoreLocation[ 65 ];
	char CityName[ 33 ];
	char CityCode[ 17 ];
	char StateName[ 33 ];
	char CountryName[ 33 ];
	char LandLine1[ 17 ];
	char LandLine2[ 17 ];
	char PMobileNo[ 17 ];
	char SMobileNo[ 17 ];
	int WorkingHrs;
	char OpeningTime[ 7 ];
	char ClosingTime[ 7 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzStoreProfile [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt,  "SELECT \
			RTRIM(INST_ID),\
			RTRIM(MERCH_ID),\
			RTRIM(STORE_ID),\
			ISNULL( STORE_STATUS, '0' ),\
			RTRIM( ISNULL( STORE_NAME, 'NA' ) ),\
			RTRIM( ISNULL( STORE_LOCATION, 'NA' ) ),\
			RTRIM( ISNULL( CITY_NAME, 'NA' ) ),\
			RTRIM( ISNULL( CITY_CODE, 'NA' ) ),\
			RTRIM( ISNULL( STATE_NAME, 'NA' ) ),\
			RTRIM( ISNULL( COUNTRY_NAME, 'NA' ) ),\
			RTRIM( ISNULL( PRIM_LAND_LINE_NO, 'NA' ) ),\
			RTRIM( ISNULL( SEC_LAND_LINE_NO, 'NA' ) ),\
			RTRIM( ISNULL( PRIM_MOBILE_NUM, 'NA' ) ),\
			RTRIM( ISNULL( SEC_MOBILE_NUM, 'NA' ) ),\
			ISNULL( WORKING_HRS, '24' ),\
			RTRIM( ISNULL( OPENING_TIME, '000000' ) ),\
			RTRIM( ISNULL( CLOSING_TIME, '235959' ) )\
		FROM EZMMS_STOREPROFILE WHERE RTRIM(INST_ID) ='%s' AND RTRIM(MERCH_ID)='%s' AND RTRIM(STORE_ID)='%s';", I_InstId, I_MerchantId, I_StoreId );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzStoreProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, StoreId, sizeof(StoreId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(StoreId) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_BINARY, &Status, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(Status) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, StoreName, sizeof(StoreName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(StoreName) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, StoreLocation, sizeof(StoreLocation), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(StoreLocation) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, CityName, sizeof(CityName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CityName) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, CityCode, sizeof(CityCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CityCode) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, StateName, sizeof(StateName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(StateName) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, CountryName, sizeof(CountryName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(DOB) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, LandLine1, sizeof(LandLine1), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(LandLine1) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, LandLine2, sizeof(LandLine2), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(LandLine2) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, PMobileNo, sizeof(PMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(PMobileNo) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, SMobileNo, sizeof(SMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SMobileNo) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_SLONG, &WorkingHrs, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(WorkingHrs) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_CHAR, OpeningTime, sizeof(OpeningTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(OpeningTime) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_CHAR, ClosingTime, sizeof(ClosingTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ClosingTime) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

   	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( StoreName, 0, sizeof( StoreName ) );
	memset( StoreLocation, 0, sizeof( StoreLocation ) );
	memset( CityName, 0, sizeof( CityName ) );
	memset( CityCode, 0, sizeof( CityCode ) );
	memset( StateName, 0, sizeof( StateName ) );
	memset( CountryName, 0, sizeof( CountryName ) );
	memset( LandLine1, 0, sizeof( LandLine1 ) );
	memset( LandLine2, 0, sizeof( LandLine2 ) );
	memset( PMobileNo, 0, sizeof( PMobileNo ) );
	memset( SMobileNo, 0, sizeof( SMobileNo ) );
	memset( OpeningTime, 0, sizeof( OpeningTime ) );
	memset( ClosingTime, 0, sizeof( ClosingTime ) );

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( storeprofile_ptr, 0, sizeof( struct EzMMSMerchantProfile ) );
        strcpy( storeprofile_ptr->InstId, InstId );
        strcpy( storeprofile_ptr->MerchantId, MerchantId );
        strcpy( storeprofile_ptr->StoreId, StoreId );
        storeprofile_ptr->Status = Status;
        strcpy( storeprofile_ptr->StoreName, StoreName );
        strcpy( storeprofile_ptr->StoreLocation, StoreLocation );
        strcpy( storeprofile_ptr->CityName, CityName );
        strcpy( storeprofile_ptr->CityCode, CityCode );
        strcpy( storeprofile_ptr->StateName, StateName );
        strcpy( storeprofile_ptr->CountryName, CountryName );
        strcpy( storeprofile_ptr->LandLine1, LandLine1 );
        strcpy( storeprofile_ptr->LandLine2, LandLine2 );
        strcpy( storeprofile_ptr->PMobileNo, PMobileNo );
        strcpy( storeprofile_ptr->SMobileNo, SMobileNo );
        storeprofile_ptr->WorkingHrs = WorkingHrs;
        strcpy( storeprofile_ptr->OpeningTime, OpeningTime );
        strcpy( storeprofile_ptr->ClosingTime, ClosingTime );

		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzMMSCmd :: readEzMMSTerminalProfile( const char *I_MachineId, struct EzMMSTerminalProfile *terminalprofile_ptr )
{
	char MachineId[ 33 ];
	char InstId[ 13 ];
	char MerchantId[ 16 ];
	char StoreId[ 33 ];
	char TerminalId[ 9 ];
	char TerminalType[ 17 ];
	char TerminalName[ 33 ];
	char TermLocation[ 65 ];
	char TerminalStatus;
	int WorkingHrs;
	char OpeningTime[ 7 ];
	char ClosingTime[ 7 ];
	char CountryCode[ 5 ];
	char CurrCode[ 5 ];
	char TermMasterKey[ 65 ];
	char TermPINKey[ 65 ];
	char ChipEnabled;
	char TermMACKey[ 65 ];
	char BatchId[ 13 ];
	int KeyIntvl;
	int TxnKeyIntvl;
	int EchoIntvl;
	int mcc;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTerminalProfile [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt,  "SELECT \
			RTRIM(MACHINE_ID),\
			RTRIM(INST_ID),\
			RTRIM(MERCH_ID),\
			RTRIM(STORE_ID),\
			RTRIM(TERMINAL_ID),\
			RTRIM(TERMINAL_TYPE),\
			RTRIM( ISNULL( TERMINAL_NAME, 'NA' ) ),\
			RTRIM( ISNULL( TERMINAL_LOCATION, 'NA' ) ),\
			ISNULL( TERMINAL_STATUS, '0' ),\
			ISNULL( WORKING_HRS, '24' ),\
			RTRIM( ISNULL( OPENING_TIME, '000000' ) ),\
			RTRIM( ISNULL( CLOSING_TIME, '235959' ) ),\
			RTRIM(COUNTRY_CODE),\
			RTRIM(CURR_CODE),\
			ISNULL( CHIP_ENABLED, 'N' ),\
			RTRIM( TERM_MASTER_KEY ),\
			RTRIM( ISNULL( TERM_PIN_KEY, '1111111111111111' ) ),\
			RTRIM( ISNULL( TERM_MAC_KEY, '1111111111111111' ) ),\
			KEY_INTVL,\
			ECHO_INTVL,\
			TXN_KEY_INTVL,\
			MCC_CODE,\
			RTRIM( ISNULL( BATCHID, 'NOTDEFINED' ) )\
		FROM EZMMS_TERMINALPROFILE WHERE RTRIM(MACHINE_ID) ='%s';", I_MachineId );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTerminalProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }


    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, MachineId, sizeof(MachineId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(MachineId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, StoreId, sizeof(StoreId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(StoreId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TerminalId, sizeof(TerminalId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TerminalId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, TerminalType, sizeof(TerminalType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TerminalType) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, TerminalName, sizeof(TerminalName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TerminalName) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, TermLocation, sizeof(TermLocation), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CityCode) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &TerminalStatus, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TerminalStatus) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &WorkingHrs, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(WorkingHrs) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, OpeningTime, sizeof(OpeningTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(OpeningTime) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, ClosingTime, sizeof(ClosingTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ClosingTime) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, CountryCode, sizeof(CountryCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CountryCode) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, CurrCode, sizeof(CurrCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CurrCode) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_CHAR, TermMasterKey, sizeof(TermMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TermMasterKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_CHAR, TermPINKey, sizeof(TermPINKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TermPINKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_BINARY, &ChipEnabled, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ClosingTime) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_CHAR, TermMACKey, sizeof(TermMACKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TermMACKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 19, SQL_C_CHAR, BatchId, sizeof(BatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(BatchId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 20, SQL_C_SLONG, &KeyIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(KeyIntvl) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 21, SQL_C_SLONG, &TxnKeyIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TxnKeyIntvl) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 22, SQL_C_SLONG, &EchoIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(EchoIntvl) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 23, SQL_C_SLONG, &mcc, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(mcc) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( MachineId, 0, sizeof( MachineId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
	memset( TerminalType, 0, sizeof( TerminalType ) );
	memset( TerminalName, 0, sizeof( TerminalName ) );
	memset( TermLocation, 0, sizeof( TermLocation ) );
	memset( OpeningTime, 0, sizeof( OpeningTime ) );
	memset( ClosingTime, 0, sizeof( ClosingTime ) );
	memset( CountryCode, 0, sizeof( CountryCode ) );
	memset( CurrCode, 0, sizeof( CurrCode ) );
	memset( TermMasterKey, 0, sizeof( TermMasterKey ) );
	memset( TermPINKey, 0, sizeof( TermPINKey ) );
	memset( TermMACKey, 0, sizeof( TermMACKey ) );
	memset( BatchId, 0, sizeof( BatchId ) );

	if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( terminalprofile_ptr, 0, sizeof( struct EzMMSMerchantProfile ) );
        strcpy( terminalprofile_ptr->MachineId, MachineId );
        strcpy( terminalprofile_ptr->InstId, InstId );
        strcpy( terminalprofile_ptr->MerchantId, MerchantId );
        strcpy( terminalprofile_ptr->StoreId, StoreId );
        strcpy( terminalprofile_ptr->TerminalId, TerminalId );
        strcpy( terminalprofile_ptr->TerminalName, TerminalName );
        strcpy( terminalprofile_ptr->TerminalType, TerminalType );
        strcpy( terminalprofile_ptr->TerminalLocation, TermLocation );
       	terminalprofile_ptr->TerminalStatus = TerminalStatus;
       	terminalprofile_ptr->WorkingHrs = WorkingHrs;
       	strcpy( terminalprofile_ptr->OpeningTime, OpeningTime );
        strcpy( terminalprofile_ptr->ClosingTime, ClosingTime );
        terminalprofile_ptr->ChipEnabled = ChipEnabled;
        strcpy( terminalprofile_ptr->CountryCode, CountryCode );
        strcpy( terminalprofile_ptr->CurrCode, CurrCode );
        strcpy( terminalprofile_ptr->TermMasterKey, TermMasterKey );
        strcpy( terminalprofile_ptr->TermPINKey, TermPINKey );
        strcpy( terminalprofile_ptr->TermMACKey, TermMACKey );
		terminalprofile_ptr->KeyIntvl = KeyIntvl;
	 	terminalprofile_ptr->EchoIntvl = EchoIntvl;
	 	terminalprofile_ptr->TxnKeyIntvl = TxnKeyIntvl;
		terminalprofile_ptr->Mcc =  mcc ;
		strcpy( terminalprofile_ptr->BatchId, BatchId );

		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int main( int argc, char **argv )
{
	EzMMSCmd mmscmdobj;
	if( mmscmdobj.initMMSCmd( argv[ 0 ] ) < 0 )
	{
		mmscmdobj.trace( "^^^^^^^^^^^^^^^eztmscmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		mmscmdobj.closeDebug();
		exit( 0 );
	}
	mmscmdobj.serviceMMSCmd( argc, argv );
	return 1;
}
