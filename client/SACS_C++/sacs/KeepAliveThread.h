#pragma once
#include "Connection.h"
class KeepAliveThread
{
private:
	// Keep-alive thread
	void __cdecl KeepAliveThr(void);
	ConData ConInfo;
public:
	KeepAliveThread(ConData);
	~KeepAliveThread();

	static void threadaddr(void * ptr) {
		reinterpret_cast<KeepAliveThread *>(ptr)->KeepAliveThr();
	}
};

