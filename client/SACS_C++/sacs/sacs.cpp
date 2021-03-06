// sacs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Connection.h"
#include "Commands.h"
#include "KeepAliveThread.h"
#include "SessionManager.h"
#include "MessageAcceptorThread.h"

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
	for (;;)
	{
		cout << "Maximum length of nickname is 32.\nSelect nickname: ";
		string nick;
		cin >> nick;
		cin.sync();
		if (Connection::IsNicknameAvailable(conInfo, nick))
		{
			conInfo.nick = nick;
			break;
		}
		else
			cout << "Nickname " + nick + " is already taken!" << endl;
	}
	// Begin keep-alive thread
	KeepAliveThread KAThread(conInfo);
	// Activate Session Manager
	SessionManager SMgr;
	// Begin message acceptor thread
	MessageAcceptorThread MAThread(conInfo, SMgr);

	// Maintain connection
	for (;;)
	{
		string command;
		cout << "sacs> ";
		getline(cin,command);
		cin.clear();
		cin.sync();
		if(Command::Make(conInfo,command,SMgr) == FALSE)
			break;
	}
	return 0;
}

