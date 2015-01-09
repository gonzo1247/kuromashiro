#ifndef __CNETWORK
#define __CNETWORK

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif  

#include <stdio.h>
#include <errno.h>

#ifdef _WIN32
/* Headerfiles für Windows */
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <io.h>
#define in_addr_t unsigned long

#else
/* Headerfiles für Unix/Linux */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#define closesocket(s) close(s)
#endif

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define SERVER_NAME "www.google.de"
#define DEFAULT_BUFLEN 512


#ifndef WINSOCK_VERSION
#define WINSOCK_VERSION MAKEWORD(2,2)
#endif

class CNetwork
{
    public:
        CNetwork();
        ~CNetwork();
        void CreateConnect();
        int ConnectFail(int Result);
        int ConnectFail(SOCKET ConnectSocket);
        int CloseConnect(SOCKET ConnectSocket);
        void CloseConnect(SOCKET ConnectSocket, int Result);  // No return type
        void SendData(SOCKET ConnectSocket);
        void ReceiveData(SOCKET ConnectSocket, int Result);

    private:
        int m_sock;
        sockaddr_in m_addr;


};                                                       


#endif __CNETWORK