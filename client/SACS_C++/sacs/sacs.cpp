// sacs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

#define WSA_FAILED 0
#define WSA_SUCCESS 1

#define SERVER_IP_SET 2
#define PORT_SET 3

// Default setting, change if you need
TCHAR SERVER_IP[] = L"127.0.0.1";
TCHAR PORT[] = L"80";
//  [3/15/2015 DualCore]

SOCKET InitializeSocket()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata))
		return WSA_FAILED;
	else
		return WSA_SUCCESS;
}


// Use like:
// sacs "127.0.0.1" 80
int _tmain(int argc, _TCHAR* argv[])
{
	// Check for parameters
	switch (argc)
	{
	case SERVER_IP_SET:
		wcscpy(SERVER_IP, argv[1]);
		break;
	case PORT_SET:
		wcscpy(PORT, argv[2]);
		break;
	}

	// Run Winsock
	if (InitializeSocket() == WSA_FAILED)
		cout << "[!] WSA initialization failed." << endl;

	return 0;
	// Maintain connection
	while (!cin.eof())
	{
		//ConnectToServer(SERVER_IP, PORT);
	}
	return 0;
}

