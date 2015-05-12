#pragma once
#include "stdafx.h"
#include "Connection.h"
#include "ConsoleLogger.h"
class Session
{
private:
	
	
	//Set the parameters of session
	bool SetParameters(ConData _InfoVar, std::wstring _target);

public:	
	ConData InfoVar;
	Session();
	~Session();
	//Counts number of opened session
	static UINT SessionIDCounter;

	// Session Window Handle
	CConsoleLogger SessionWindow;

	void AddMessage(std::string msg);

	//Session personal identification number
	UINT SessionID;
	//Target of messages(Second user)
	std::wstring Target;
	// Create new session
	bool CreateSession(ConData ConnectionInfo, std::wstring TargetName);
};