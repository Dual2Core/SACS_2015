#pragma once
#include "stdafx.h"
#include "Connection.h"
class Session
{
private:
	ConData InfoVar;
	
	//Set the parameters of session
	bool SetParameters(ConData _InfoVar, std::wstring _target);

public:	
	Session();
	~Session();
	//Counts number of opened session
	static UINT SessionIDCounter;

	//Session personal identification number
	UINT SessionID;
	//Target of messages(Second user)
	std::wstring Target;
	// Create new session
	bool CreateSession(ConData ConnectionInfo, std::wstring TargetName);
};