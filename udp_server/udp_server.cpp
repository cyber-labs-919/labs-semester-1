/*
	UDP Server
*/

#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef _WIN32
using SOCKET = int
#define WSAGetLastError() 1
#else
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif


#include "crypto.h"
#include "matrixEnc.h"
#include "substitutionCipher.h"
#include "rle.h"

//#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 	1024		    //Max length of buffer
#define PORT    8888			//The port on which to listen for incoming data

int main(int argc, char* argv[])
{
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	char msg[BUFLEN];

#ifdef WIN32
	WSADATA wsa;

	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("  Initialized.\n");
#endif //WIN32

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	//	printf("Socket created.\n");

		//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (1 == argc)
	{
		server.sin_port = htons(PORT);
		printf("1: Listen port=%d\n", PORT);
	}
	else
	{
		server.sin_port = htons(atoi(argv[1]));
		printf("2: Listen port=%d\n", atoi(argv[1]));
	}

	//Bind
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	//	puts("Bind done");

		//keep listening for data
	while (1)
	{
		printf("Waiting for data...   ");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n", buf);

		MatrixEncCrypto matrixCrypto;
		SubstitutionCipherCrypto subCrypto;
		RLECompressor rleCompressor;

		std::string decoded = subCrypto.decrypt(buf, { {"keyFrom", "abcdefghijklmnopqrstuvwxyz"}, {"keyTo", "zyxwvutsrqponmlkjihgfedcba" } });
		decoded = matrixCrypto.decrypt(decoded);
		
		printf("Decrypted: %s\n", decoded.c_str());

		decoded = rleCompressor.decrypt(decoded);

		printf("Decompressed: %s\n", decoded.c_str());

		printf("\nAnswer : ");
		gets_s(msg, BUFLEN);

		std::string processed = rleCompressor.encrypt(msg);
		printf("Compressed: %s\n", processed.c_str());

		processed = matrixCrypto.encrypt(processed);
		processed = subCrypto.encrypt(processed, { {"keyFrom", "abcdefghijklmnopqrstuvwxyz"}, {"keyTo", "zyxwvutsrqponmlkjihgfedcba" } });

		printf("Encrypted: %s\n", processed.c_str());

		//now reply the client with the same data
		if (sendto(s, processed.c_str(), processed.length(), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

#ifdef _WIN32
	closesocket(s);
	WSACleanup();
#endif //_WIN32
	return 0;
}
