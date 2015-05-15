#include "stdafx.h"
#include "KeepAliveThread.h"
#include "Connection.h"

using namespace std;


KeepAliveThread::KeepAliveThread(ConData ConInf) : ConInfo(ConInf)
{
	_beginthread(&KeepAliveThread::threadaddr, 0, this);
}

KeepAliveThread::~KeepAliveThread()
{
}

void __cdecl KeepAliveThread::KeepAliveThr(void)
{
	// Prepare GET message
	string msg = "GET /gate.php?user=";
	msg += ConInfo.nick;
	msg += "&keepalive=1";
	msg += " HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";
	
	for (;;Sleep(5000))
	{
		Connection::SendNewQuery(ConInfo.SERVER_IP, ConInfo.PORT, (char*)msg.c_str());
	}
}
