#include "stdafx.h"
#include "Commands.h"
#include "Connection.h"

using namespace std;

// Recognize the command and make it
BOOL Command::Make(ConData InfoVar, std::string CommandVar)
{
	string CommandType = Recognize(CommandVar);
	if (CommandType == "test")
	{
		cout << "Test command recognized successfully!" << endl;
		return TRUE;
	}
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


	if (CommandType == "quit" || CommandType == "q")
	{
		exit(1);
	}
	else
		cout << "Cannot recognise command \"" << CommandVar << "\"" << endl;
	
	return FALSE;
}

std::string Command::Recognize(std::string CommandVar)
{
	string first_space = " ";
	int pos = CommandVar.find(first_space);
	return CommandVar.substr(0, pos);
}
