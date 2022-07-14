#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <stdio.h>

#define MAX_IFS	64

int main()
{
	void ChangeMachineId( char *MachineId );
	int getMachineId( char *MachineId );

	char MachineId[ 50 ];

	printf( "\n\n\t\t$$$$$$$$$$$$$$$$$$$$$$$$License Utility Version 1.0$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n" );

	if( getMachineId( MachineId ) < 0 )
	{
		printf("\nError in Generating MachineId\n\n\n" );
		return 1;
	}

	printf("\n\t\t\t\t\tLicense Id : [%s]\n\n\n", MachineId );
	printf( "\n\n\t\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n" );
	return 1;
}


void ChangeMachineId( char *MachineId )
{
	for( int i = 0; i < strlen( MachineId ); i++ )
	{
		switch ( MachineId[ i ] )
		{
			case '0':
				MachineId[ i ] = '9';
			break;

			case '1':
				MachineId[ i ] = '8';
			break;

			case '2':
				MachineId[ i ] = '7';
			break;

			case '3':
				MachineId[ i ] = '6';
			break;

			case '4':
				MachineId[ i ] = '5';
			break;

			case '5':
				MachineId[ i ] = '4';
			break;

			case '6':
				MachineId[ i ] = '3';
			break;

			case '7':
				MachineId[ i ] = '2';
			break;

			case '8':
				MachineId[ i ] = '1';
			break;

			case '9':
				MachineId[ i ] = '0';
			break;

			case 'a':
				MachineId[ i ] = 'f';
			break;

			case 'A':
				MachineId[ i ] = 'F';
			break;

			case 'b':
				MachineId[ i ] = 'e';
			break;

			case 'B':
				MachineId[ i ] = 'E';
			break;

			case 'c':
				MachineId[ i ] = 'd';
			break;

			case 'C':
				MachineId[ i ] = 'D';
			break;

			case 'd':
				MachineId[ i ] = 'c';
			break;

			case 'D':
				MachineId[ i ] = 'C';
			break;

			case 'e':
				MachineId[ i ] = 'b';
			break;

			case 'E':
				MachineId[ i ] = 'B';
			break;

			case 'f':
				MachineId[ i ] = 'a';
			break;

			case 'F':
				MachineId[ i ] = 'A';
			break;

			default:
			break;

		}
	}
}

int getMachineId( char *MachineId )
{
	struct ifreq *ifr, *ifend;
	struct ifreq ifreq;
	struct ifconf ifc;
	struct ifreq ifs[MAX_IFS];
	int SockFD;
	char TempMachineId[ 20 ];
	SockFD = socket(AF_INET, SOCK_DGRAM, 0);
	ifc.ifc_len = sizeof(ifs);
	ifc.ifc_req = ifs;

	if (ioctl( SockFD, SIOCGIFCONF, &ifc) < 0)
	{
		printf( "ioctl error...while getting the machine id.....SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		return -1;
	}

	ifend = ifs + (ifc.ifc_len / sizeof(struct ifreq));
	for (ifr = ifc.ifc_req; ifr < ifend; ifr++)
	{
		//if (ifr->ifr_addr.sa_family == AF_INET && !strncmp( ifr->ifr_name, "eth", 3 ) )
		if (ifr->ifr_addr.sa_family == AF_INET )
		{
			strncpy(ifreq.ifr_name, ifr->ifr_name,sizeof(ifreq.ifr_name));
			if (ioctl (SockFD, SIOCGIFHWADDR, &ifreq) < 0)
			{
				printf( "ioctl error...while getting the machine id.....SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
				return -1;
			}
			memset( TempMachineId, 0, sizeof( TempMachineId ) );
			sprintf( TempMachineId,"%02x%02x%02x%02x%02x%02x", (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[0], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[1], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[2], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[3], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[4], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[5] );
			if( strcmp( TempMachineId, "000000000000" ) )
			{
				strcpy( MachineId, TempMachineId );
				break;
			}
		}
	}
    ChangeMachineId( MachineId );
    return 1;
}




