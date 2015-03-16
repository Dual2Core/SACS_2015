// sacs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Connection.h"

using namespace std;



// Default setting, change if you need
TCHAR SERVER_IP[] = L"127.0.0.1";
TCHAR PORT[] = L"80";
//  [3/15/2015 DualCore]


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
	if (Connection::InitializeSocket() == WSA_FAILED)
		cout << "[!] WSA initialization failed." << endl;
	
	TCHAR* result = Connection::SendNewQuery(SERVER_IP, PORT, "GET /gate.php?user=clienta HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n");
	wcout <<"Final: "<< result << endl;
	return 0;
	// Maintain connection
	while (!cin.eof())
	{
		//ConnectToServer(SERVER_IP, PORT);
	}
	return 0;
}

