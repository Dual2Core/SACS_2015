#include "stdafx.h"
#include "Connection.h"

using namespace std;

SOCKET Connection::InitializeSocket()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata))
		return WSA_FAILED;
	else
		return WSA_SUCCESS;
}

wstring Connection::SendNewQuery(TCHAR* server_ip, TCHAR* port, char* msg)
{
	struct addrinfoW *res, *ptr, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (GetAddrInfo(server_ip, port, &hints, &res))
	{
#ifdef DEBUG
		std::cout << "[!] Failed to resolve host info!" << std::endl;
#endif
		return L"";
	}
	ptr = res;
	SOCKET sacsSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (sacsSocket == INVALID_SOCKET)
	{
#ifdef DEBUG
		std::cout << "[!] The created socket is INVALID." << std::endl;
#endif		
		return L"";
	}
	if (connect(sacsSocket, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR)
	{
#ifdef DEBUG
		std::cout << "[!] Failed on connect." << std::endl;
#endif		
		closesocket(sacsSocket);
		FreeAddrInfo(res);
		return L"";
	}

	int bytescount = send(sacsSocket, msg, (int)strlen(msg), NULL);
	if (bytescount == SOCKET_ERROR)
	{
#ifdef DEBUG
		std::cout << "[!] Sending message failed." << std::endl;
#endif		
		closesocket(sacsSocket);
		FreeAddrInfo(res);
		return L"";
	}
#ifdef DEBUG
	cout << "[+] Bytes Sent: " << bytescount << endl;
#endif

	if (shutdown(sacsSocket, SD_SEND) == SOCKET_ERROR)
	{
#ifdef DEBUG
		cout << "[!] Shutdown failed." << endl;
#endif		
		closesocket(sacsSocket);
		FreeAddrInfo(res);
		WSACleanup();
		return L"";
	}

	// Attempt to receive data
	int RecvResult = NULL;
	const int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
	int container_size;
	do
	{
		RecvResult = recv(sacsSocket, recvbuf, recvbuflen, NULL);
		if (RecvResult > 0)
		{
#ifdef DEBUG
			cout << "[+] Bytes received: " << RecvResult << endl;
#endif		
			container_size = RecvResult;
		} 
		else if (RecvResult == NULL)
		{
#ifdef DEBUG
			cout << "[+] Connection closed." << endl;
#endif
		}
		else
		{
#ifdef DEBUG
			cout << "[!] Failed to receive data!" << endl;
#endif		
			closesocket(sacsSocket);
			FreeAddrInfo(res);
			WSACleanup();
			return L"";
		}
	} while (RecvResult > 0);

	recvbuf[container_size] = '\0';
	container_size++;
	TCHAR *rcvmsg = new TCHAR[container_size];
	mbstowcs(rcvmsg, recvbuf, container_size);
	wstring tres = rcvmsg;
	int pos = tres.find(L"\r\n\r\n");
	tres = tres.substr(pos + 4);
	return tres;
}

std::wstring Connection::Test(ConData &InfoVar)
{
	wstring res = Connection::SendNewQuery(InfoVar.SERVER_IP, InfoVar.PORT, "GET /test.php HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n");
	
	if (res == L"Success")
		return SUCCESS;
	
	return FAILED;
}

BOOL Connection::IsNicknameAvailable(ConData& InfoVar, std::string Nickname)
{
	string query = "GET /gate.php?user=NULL&whoisonline=1 HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";
	wstring wres = SendNewQuery(InfoVar.SERVER_IP, InfoVar.PORT, (char*)query.c_str());
	string res(wres.begin(), wres.end());
	if (res.find(Nickname) == res.npos)
		return TRUE;

	return FALSE;
}

// "GET /gate.php?user=clienta HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n"