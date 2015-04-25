// sacs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Connection.h"
#include "Commands.h"
#include "KeepAliveThread.h"

using namespace std;



// Default setting, change if you need
TCHAR SERVER_IP[64] = L"127.0.0.1";
TCHAR PORT[5] = L"80";
//  [3/15/2015 DualCore]


// Use like:
// sacs 127.0.0.1 80
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
	wstring conTest = Connection::Test(conInfo);
	
	// Print out General Info
	wcout << L"IP: " << conInfo.SERVER_IP << L" PORT: " << conInfo.PORT << conTest << endl;
	
	// Quit if the connection is not present
	if (conTest == FAILED)
	{
		wcout << L"Connecting to server failed, quiting the application..." << endl;
		exit(1);
	}

	// Select nickname
	cout << "Maximum length of nickname is 32.\nSelect nickname: ";
	cin >> conInfo.nick;
	cin.sync();
	// Begin keep-alive thread
	KeepAliveThread KAThread(conInfo);

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

