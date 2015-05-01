#include "stdafx.h"
#include "Session.h"

using namespace std;

Session::Session()
{
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
	if (list.find(_target) == list.npos)
	{
		wcout << L"User named: \"" << _target << L"\" is not online." << endl;
		return FALSE;
	}

	this->InfoVar = _InfoVar;
	this->target = _target;
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

	wstring SessionTitle = L"Session with " + TargetName;

	SI.lpTitle = const_cast <wchar_t*> (SessionTitle.c_str());
	wcout << L"Creating new session..." << endl;
	if(CreateProcessW(NULL, NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI))
		cout<<"Session created!";

	return TRUE;
}
