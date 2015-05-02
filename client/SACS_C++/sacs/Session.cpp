#include "stdafx.h"
#include "Session.h"
#include "ConsoleLogger.h"

using namespace std;

// Init
UINT Session::SessionIDCounter = 0;

Session::Session()
{
	this->SessionID = SessionIDCounter;
	SessionIDCounter++;
}


Session::~Session()
{

}

//Set the parameters of session
bool Session::SetParameters(ConData _InfoVar, std::wstring _target)
{
	string query = "GET /gate.php?user=" + _InfoVar.nick;
	query += "&whoisonline=1";
	query += " HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";
	
	wstring list = Connection::SendNewQuery(_InfoVar.SERVER_IP, _InfoVar.PORT, (char*)query.c_str());
	if (list.find(_target+L"\n") == list.npos)
	{
		wcout << L"User named: \"" << _target << L"\" is not online." << endl;
		return FALSE;
	}

	this->InfoVar = _InfoVar;
	this->Target = _target;
	wcout << L"Parameters set!" << endl;
	return TRUE;
}


// Create new session
bool Session::CreateSession(ConData ConnectionInfo, std::wstring TargetName)
{
	if (!SetParameters(ConnectionInfo, TargetName))
		return FALSE;
	
	STARTUPINFOW SI;
	PROCESS_INFORMATION PI;
	ZeroMemory(&SI, sizeof(SI));
	ZeroMemory(&PI, sizeof(PI));

	string _tgt(TargetName.begin(), TargetName.end());
	string SessionTitle = "Session with " + _tgt;
	
	CConsoleLogger SessionWindow;
	SessionWindow.Create(SessionTitle.c_str());

	return TRUE;
}
