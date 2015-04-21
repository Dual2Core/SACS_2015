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

TCHAR* Connection::SendNewQuery(TCHAR* server_ip, TCHAR* port, char* msg)
{
	struct addrinfoW *res, *ptr, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (GetAddrInfo(server_ip, port, &hints, &res))
	{
		std::cout << "[!] Failed to resolve host info!" << std::endl;
		return NULL;
	}
	ptr = res;
	SOCKET sacsSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (sacsSocket == INVALID_SOCKET)
	{
		std::cout << "[!] The created socket is INVALID." << std::endl;
		return NULL;
	}
	if (connect(sacsSocket, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR)
	{
		std::cout << "[!] Failed on connect." << std::endl;
		closesocket(sacsSocket);
		FreeAddrInfo(res);
		return NULL;
	}

	int bytescount = send(sacsSocket, msg, (int)strlen(msg), NULL);
	if (bytescount == SOCKET_ERROR)
	{
		std::cout << "[!] Sending message failed." << std::endl;
		closesocket(sacsSocket);
		FreeAddrInfo(res);
		return NULL;
	}
	cout << "[+] Bytes Sent: " << bytescount << endl;

	if (shutdown(sacsSocket, SD_SEND) == SOCKET_ERROR)
	{
		cout << "[!] Shutdown failed." << endl;
		closesocket(sacsSocket);
		FreeAddrInfo(res);
		WSACleanup();
		return NULL;
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
			cout << "[+] Bytes received: " << RecvResult << endl;
			container_size = RecvResult;
		} 
		else if (RecvResult == NULL)
		{
			cout << "[+] Connection closed." << endl;
		}
		else
		{
			cout << "[!] Failed to receive data!" << endl;
			closesocket(sacsSocket);
			FreeAddrInfo(res);
			WSACleanup();
			return NULL;
		}
	} while (RecvResult > 0);

	recvbuf[container_size] = '\0';
	container_size++;
	TCHAR *rcvmsg = new TCHAR[container_size];
	mbstowcs(rcvmsg, recvbuf, container_size);
	return rcvmsg;
}

// "GET /gate.php?user=clienta HTTP/1.1\r\nHost: \r\nContent-type: application/x-www-form-urlencoded\r\n\r\n"