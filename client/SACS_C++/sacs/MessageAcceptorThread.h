#pragma once
#include "Connection.h"
#include "SessionManager.h"

class MessageAcceptorThread
{
private:
	ConData InfoVar;
	SessionManager* SessMgr;
	void _cdecl MessageAcceptorThr(void);
public:
	MessageAcceptorThread(ConData,SessionManager&);
	~MessageAcceptorThread();
	
	static void threadaddr(void * ptr) {
		reinterpret_cast<MessageAcceptorThread *>(ptr)->MessageAcceptorThr();
	}
};