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
	if (CommandType == "quit")
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
