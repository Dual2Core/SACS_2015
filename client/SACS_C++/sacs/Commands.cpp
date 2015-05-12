#include "stdafx.h"
#include "Commands.h"
#include "Connection.h"
#include "Session.h"
#include "defines.h"

using namespace std;



// Recognize the command and make it
BOOL Command::Make(ConData InfoVar, std::string CommandVar, SessionManager &SMgr)
{
	string CommandType = Recognize(CommandVar);
	string arg1 = CutArg(CommandVar, 1);
	string arg2 = CutArg(CommandVar, MESSAGE_TYPE);

	if (CommandType == "test")
	{
		cout << "Test command recognized successfully!" << endl;
		return TRUE;
	}
	else
	if (CommandType == "whoisonline")
	{
		cout << "Users online:" << endl;
		string query = "GET /gate.php?user=" + InfoVar.nick;
		query += "&whoisonline=1";
		query += " HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";
		wstring list = Connection::SendNewQuery(InfoVar.SERVER_IP, InfoVar.PORT, (char*)query.c_str());
		wcout << list<<endl;
		return TRUE;
	}
	else
	if (CommandType == "startsession")
	{
		Session Ssn;
		wstring target(arg1.begin(), arg1.end());
		cout << "Creating new session..." << endl;
		if (!Ssn.CreateSession(InfoVar, target))
		{
			cout << "Failed to create new session!" << endl;
			return TRUE;
		}

		cout << "New session created!" << endl;
		SMgr.AddSession(Ssn);
		cout << "mh_pipe = " << Ssn.SessionWindow.m_hPipe << endl;
		Ssn.AddMessage("Session created!");
		cout << "mh_pipe = " << Ssn.SessionWindow.m_hPipe << endl;
		return TRUE;
	}
	else
	if (CommandType == "send")
	{
		string Target = arg1;
		string Message = arg2;
		Command::Transform(Message);
		string query = "GET /session.php?user=" + InfoVar.nick;
		query += "&message=" + Message;
		query += "&target=" + Target;
		query += " HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";
		wstring SendStatus = Connection::SendNewQuery(InfoVar.SERVER_IP, InfoVar.PORT, (char*)query.c_str());
		if (SendStatus != L"Done")
			cout << "Error occurred while sending message!" << endl;
		wstring tgt(Target.begin(), Target.end());
		wcout << tgt << endl;
		SMgr.AddMessageToSession(SEND, tgt, Message);
		return TRUE;
	}
	if (CommandType == "nsession")
	{
		cout << SMgr.NumberOfActiveSessions() << endl;
		return TRUE;
	}
	


	if (CommandType == "quit" || CommandType == "q")
	{
		return FALSE;
	}
	else
		cout << "Cannot recognise command \"" << CommandVar << "\"" << endl;
	
	return TRUE;
}

std::string Command::Recognize(std::string CommandVar)
{
	string first_space = " ";
	int pos = CommandVar.find(first_space);
	return CommandVar.substr(0, pos);
}

std::string Command::CutArg(std::string CommandVar, int ArgNumber)
{
	string space = " ";
	int iterator = ArgNumber;
	if (CommandVar.find(space) < 0)
		return NULL;
	if (ArgNumber == MESSAGE_TYPE)
		iterator = 2;
	for (int i = 1; i <= iterator; i++)
	{
		int pos = CommandVar.find(space);
		CommandVar = CommandVar.substr(pos + 1);
	}
	
	if (ArgNumber == MESSAGE_TYPE)
		return CommandVar;

	int pos = CommandVar.find(space);
	if (pos > 0)
		CommandVar = CommandVar.substr(0, pos);
	
	return CommandVar;
}

void Command::Transform(string &Message)
{
	string httpSpace = "%20";
	for (int i = 0; i < Message.length(); i++)
	if (Message[i] == ' ')
		Message.replace(i, 1, httpSpace);
}