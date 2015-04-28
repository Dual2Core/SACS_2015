// Connection functions
#include "ConData.h"

namespace Connection
{
	// Init socket
	SOCKET InitializeSocket(); 

	// Returns a pointer to server respond
	// return NULL pointer on fail
	std::wstring SendNewQuery(TCHAR* server_ip, TCHAR* port, char* msg);
	
	// Test connection
	std::wstring Test(ConData&);
}