#include "stdafx.h"
#include "Commands.h"
#include "Connection.h"
#include "Session.h"

using namespace std;

// Recognize the command and make it
BOOL Command::Make(ConData InfoVar, std::string CommandVar)
{
	string CommandType = Recognize(CommandVar);
	string arg1 = CutArg(CommandVar, 1);

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
		
		Ssn.CreateSession(InfoVar, target);
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
	if (CommandVar.find(space) < 0)
		return NULL;

	for (int i = 1; i <= ArgNumber; i++)
	{
		int pos = CommandVar.find(space);
		CommandVar = CommandVar.substr(pos + 1);
	}
	int pos = CommandVar.find(space);
	if (pos > 0)
		CommandVar = CommandVar.substr(0, pos);
	
	return CommandVar;
}
