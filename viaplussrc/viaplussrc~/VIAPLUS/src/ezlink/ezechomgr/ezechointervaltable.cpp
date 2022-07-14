#include <ezlink/ezechomanager.h>

int EzEchoIntervalTableUtil :: initEchoIntervalTable( EzDebugUtil *dptr, int MaxNetworks )
{
	this->MaxNetworks = MaxNetworks;
	this->dptr = dptr;
	MaxEchoOffset = 50;
	ezechoint_ptr = ( struct EzEchoIntervalTable * ) malloc( sizeof( struct EzEchoIntervalTable ) * MaxNetworks );
	if( ezechoint_ptr == NULL )
	{
		dptr->trace( "Error in Allocating Memory for EchoIntervalTable.....Malloc Error..." );
		return -1;
	}
	memset( ezechoint_ptr, 0, sizeof( struct EzEchoIntervalTable ) * MaxNetworks );
	for( int i = 0; i < MaxNetworks; i++ )
	{
		memset( ( ezechoint_ptr + i )->NetworkId, 0, sizeof( ( ezechoint_ptr + i )->NetworkId ) );
		strcpy( ( ezechoint_ptr + i )->NetworkId, NETWORKID_INIT_VAL );
	}
	return 1;
}

int EzEchoIntervalTableUtil :: addEchoIntervalTable( struct EzEchoIntervalTable echoint_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxNetworks; i++ )
	{
		if( !strcmp( ( ezechoint_ptr + i )->NetworkId, NETWORKID_INIT_VAL ) )
		{
			memset( ezechoint_ptr + i, 0, sizeof( struct EzEchoIntervalTable ) );
			memcpy( ezechoint_ptr + i, &echoint_rec, sizeof( struct EzEchoIntervalTable ) );
			retval = 1;
			break;
		}
	}
	if( retval < 0 )
	{
		struct EzEchoIntervalTable *temp_ptr;
		int OldMaxNetworks = MaxNetworks;
		temp_ptr = ( struct EzEchoIntervalTable * ) malloc( sizeof( struct EzEchoIntervalTable ) * OldMaxNetworks );
		if( temp_ptr == NULL )
		{
			dptr->trace( "Error in Allocating Memory for Temp...EchoIntervalTable.....Malloc Error..." );
			return -1;
		}
		memset( temp_ptr, 0, sizeof( struct EzEchoIntervalTable ) * OldMaxNetworks );
		memcpy( temp_ptr, ezechoint_ptr, sizeof( struct EzEchoIntervalTable ) * OldMaxNetworks );
		free( ezechoint_ptr );
		MaxNetworks += MaxEchoOffset;
		ezechoint_ptr = ( struct EzEchoIntervalTable * ) malloc( sizeof( struct EzEchoIntervalTable ) * MaxNetworks );
		if( ezechoint_ptr == NULL )
		{
			dptr->trace( "Error in Allocating Memory for New EchoIntervalTable.....Malloc Error..." );
			return -1;
		}
		memset( ezechoint_ptr, 0, sizeof( struct EzEchoIntervalTable ) * MaxNetworks );
		memcpy( ezechoint_ptr, temp_ptr, sizeof( struct EzEchoIntervalTable ) * OldMaxNetworks );
		free( temp_ptr );
		memcpy( ( ezechoint_ptr + OldMaxNetworks ), &echoint_rec, sizeof( struct EzEchoIntervalTable ) );
		for( int i =  OldMaxNetworks + 1 ; i < MaxNetworks; i++ )
		{
			memset( ezechoint_ptr + i, 0, sizeof( struct EzEchoIntervalTable ) );
			strcpy( ( ezechoint_ptr + i )->NetworkId, NETWORKID_INIT_VAL );
		}
		retval = 1;
	}
	return retval;
}

int EzEchoIntervalTableUtil :: updateEchoIntervalTable( struct EzEchoIntervalTable  echoint_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxNetworks; i++ )
	{
		if( !strcmp( ( ezechoint_ptr + i )->NetworkId, echoint_rec.NetworkId ) )
		{
			memset( ezechoint_ptr + i, 0, sizeof( struct EzEchoIntervalTable ) );
			memcpy( ezechoint_ptr + i, &echoint_rec, sizeof( struct EzEchoIntervalTable ) );
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzEchoIntervalTableUtil :: readEchoIntervalTable( const char *NetworkId, struct EzEchoIntervalTable  *echoint_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxNetworks; i++ )
	{
		if( !strcmp( ( ezechoint_ptr + i )->NetworkId, NetworkId ) )
		{
			memcpy( echoint_rec, ezechoint_ptr + i,sizeof( struct EzEchoIntervalTable ) );
			retval = 1;
			break;
		}
	}
	return retval;
}

