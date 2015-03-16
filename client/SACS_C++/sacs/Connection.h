// Connection functions

namespace Connection
{
	// Init socket
	SOCKET InitializeSocket(); 

	// Returns a pointer to serv respond
	// return NULL pointer on fail
	TCHAR* SendNewQuery(TCHAR* server_ip, TCHAR* port, char* msg);
		
}