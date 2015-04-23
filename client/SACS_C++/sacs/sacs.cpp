// sacs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Connection.h"
#include "Commands.h"

using namespace std;



// Default setting, change if you need
TCHAR SERVER_IP[64] = L"127.0.0.1";
TCHAR PORT[5] = L"80";
//  [3/15/2015 DualCore]


// Use like:
// sacs "127.0.0.1" 80
int _tmain(int argc, _TCHAR* argv[])
{
	// Check for parameters
	switch (argc)
	{
	case PORT_SET:
		wcscpy(PORT, argv[2]);
	case SERVER_IP_SET:
		wcscpy(SERVER_IP, argv[1]);
		break;
	}
	// Load params
	ConData conInfo;
	wcscpy(conInfo.SERVER_IP,SERVER_IP);
	wcscpy(conInfo.PORT,PORT);

	// Run Winsock
	if (Connection::InitializeSocket() == WSA_FAILED)
		cout << "[!] WSA initialization failed." << endl;

	wcout << L"IP: " << conInfo.SERVER_IP << L" PORT: " << conInfo.PORT << Connection::Test(conInfo) << endl;
	
	// Maintain connection
	for (;;)
	{
		string command;
		cout << "sacs> ";
		getline(cin,command);
		Command::Make(conInfo,command);
	}
	return 0;
}

