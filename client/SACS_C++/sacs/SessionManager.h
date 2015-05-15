#pragma once
#include "stdafx.h"
#include "Session.h"
class SessionManager
{
private:
	std::vector <Session> SDB;

public:
	SessionManager();
	~SessionManager();
	bool IsSessionActiveWith(std::wstring Target);
	void AddSession(Session &SessionObject);
	void AddMessageToSession(short int MODE,std::wstring Target,std::string msg);
	void DestroySession(std::wstring Target);
	int NumberOfActiveSessions();
};