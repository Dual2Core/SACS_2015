#include "stdafx.h"
#include "SessionManager.h"
#include "Session.h"

using namespace std;

SessionManager::SessionManager()
{
}


SessionManager::~SessionManager()
{
}


bool SessionManager::IsSessionActiveWith(std::wstring Target)
{
	for (auto Session : SDB)
	{
		if (Session.Target == Target)
			return TRUE;
	}
	return false;
}


void SessionManager::AddSession(Session &SessionObject)
{
	SDB.push_back(SessionObject);
}


void SessionManager::DestroySession(std::wstring Target)
{
	bool dest = 0;
	for (auto Session = SDB.begin(); Session != SDB.end(); ++Session)
	{
		if (Session->Target == Target)
		{
			SDB.erase(Session);
			dest = 1;
		}
	}
	if (!dest)
		std::cout << "The session couldn't be destroyed!" << endl;
}


int SessionManager::NumberOfActiveSessions()
{
	return SDB.size();
}

void SessionManager::AddMessageToSession(short int MODE, std::wstring Target, std::string msg)
{
	for (auto Session : SDB)
	{
		if (Session.Target == Target)
		{
			std::cout << "SMgr mhpipe = " << Session.SessionWindow.m_hPipe << endl;
			switch (MODE)
			{
			case SEND:
				Session.AddMessage(Session.InfoVar.nick + ": " + msg);
				break;
			case RECEIVE:
				string tgt(Target.begin(), Target.end());
				Session.AddMessage(tgt + ": " + msg);
				break;
			}
		}
	}

}
