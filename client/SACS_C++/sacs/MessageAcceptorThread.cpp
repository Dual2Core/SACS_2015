#include "stdafx.h"
#include "MessageAcceptorThread.h"

using namespace std;


MessageAcceptorThread::~MessageAcceptorThread()
{
}

MessageAcceptorThread::MessageAcceptorThread(ConData IV, SessionManager &SM) : InfoVar(IV), SessMgr(&SM)
{
	_beginthread(&MessageAcceptorThread::threadaddr, 0, this);
}

void _cdecl MessageAcceptorThread::MessageAcceptorThr(void)
{
	// InfoVar, SessMgr
	for (;; Sleep(3000)) // 3s interval
	{
		string query = "GET /gate.php?user="+ InfoVar.nick +" HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";
		wstring wlist = Connection::SendNewQuery(InfoVar.SERVER_IP, InfoVar.PORT, (char*)query.c_str());
		string list(wlist.begin(), wlist.end());
		if (list.empty())continue;
		string Target = list.substr(0, list.find("\n"));
		Target = Target.erase(Target.find(InfoVar.nick),InfoVar.nick.length());
		list = list.substr(list.find("\n")+2); // list w/o conv title

		wstring wtgt(Target.begin(), Target.end());

		if (!SessMgr->IsSessionActiveWith(wtgt))
		{
			Session NewSession;
			NewSession.CreateSession(InfoVar, wtgt);
			SessMgr->AddSession(NewSession);
		}

		while (list.length()>2)
		{
			string date = list.substr(0, list.find("\n"));
			list = list.substr(list.find("\n") + 1);

			string msg = list.substr(0, list.find("\n"));
			list = list.substr(list.find("\n"));

			SessMgr->AddMessageToSession(RECEIVE, wtgt, msg);
		}
	}
}