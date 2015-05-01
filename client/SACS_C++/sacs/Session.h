#pragma once
#include "stdafx.h"
#include "Connection.h"
class Session
{
private:
	ConData InfoVar;
	std::wstring target;

	//Set the parameters of session
	bool SetParameters(ConData _InfoVar, std::wstring _target);

public:	
	Session();
	~Session();
	// Create new session
	bool CreateSession(ConData ConnectionInfo, std::wstring TargetName);
};