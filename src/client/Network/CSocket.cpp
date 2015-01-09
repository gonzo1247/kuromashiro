/*Socket.cpp for Windows*/

#include <cstdlib>
#include <WinSock2.h>
#include <io.h>
#include <iostream>
#include "CSocket.h"

using namespace std;

// Konstruktor 
CSocket::CSocket() : m_sock(0)
{
    WORD VersionRequested;
    WSADATA wsaData;
    VersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(VersionRequested, &wsaData) != 0)
        exit(1);
}

// Destructor 
CSocket::~CSocket()
{
    if (is_valid())
        ::closesocket(m_sock);    
}


// Create Socket - TCP 
bool CSocket::tcp_create()
{
    m_sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0)
    {
        exit(1);
    }
    return true;
}

// Create Socket - UDP
bool CSocket::udp_create()
{
    m_sock = ::socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sock < 0)
    {
        exit(1);
    }
    return true;
}

// Create binding to serveradress, specific Port
bool CSocket::bind(const int port)
{
    if (!is_valid())
    {
        return false;
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);

    int bind_return = ::bind(m_sock, (struct sockaddr *) &m_addr, sizeof(m_addr));
    if (bind_return == -1)
        return false;
    return true;
}

// 
bool CSocket::listen() const
{
    if (!is_valid())
        return false;

    int listen_return = ::listen(m_sock, MAXCONNECTIONS);
    if (listen_return == -1)
        return false;
    return true;
}

// accept() block to client connect

bool CSocket::accept(CSocket& new_socket) const
{
    int addr_length = sizeof(m_addr);

    new_socket.m_sock = ::accept(m_sock, (sockaddr *)&m_addr, (int *) &addr_length);

    if (new_socket.m_sock <= 0)
        return false;
    else
        return true;
}

//  Create the connect to server
bool CSocket::connect(const string host, const int port)
{
    if (!is_valid())
        return false;
    struct hostent *host_info;
    unsigned long addr;
    memset(&m_addr, 0, sizeof(m_addr));

    if ((addr = inet_addr(host.c_str())) != INADDR_NONE)
    {
        memcpy((char *)&m_addr.sin_addr, &addr, sizeof(addr));
    }
    else
    {
        host_info = gethostbyname(host.c_str());
        if (NULL == host_info)
            // unknown server
            exit(1);

        memcpy((char *)&m_addr.sin_addr, host_info->h_addr_list, host_info->h_length);
    }
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);

    int status = ::connect(m_sock, (sockaddr *)&m_addr, sizeof(m_addr));

    if (status == 0)
        return true;
    else
        return false;
}

// Send data via TCP
bool CSocket::send(const string s) const
{
    int status = ::send(m_sock, s.c_str(), s.size(), 0);
    if (status == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
  }

// recieve data via TCP
int CSocket::recv(string& s) const
{
    char buf[MAXRECV + 1];
    s = "";
    memset(buf, 0, MAXRECV + 1);

    int status = ::recv(m_sock, buf, MAXRECV, 0);
    if (status > 0 || status != SOCKET_ERROR)
    {
        s = buf;
        return status;
    }
    else
    {
        // Error in CSocket::recv
        exit(1);
        return 0;
    }            
}

// Send data via UDP
bool CSocket::udp_send(const string addr, const string s, const int port) const
{
    struct sockaddr_in addr_sento;
    struct hostent *h;
    int rc;

    h = gethostbyname(addr.c_str());
    if (h == NULL)
        // Unknown Host?
        exit(1);

    addr_sento.sin_family = h->h_addrtype;
    memcpy((char *)&addr_sento.sin_addr, h->h_addr_list[0], h->h_length);
    addr_sento.sin_port = htons(port);
    rc = sendto(m_sock, s.c_str(), s.size(), 0, (struct sockaddr *) &addr_sento, sizeof(addr_sento));

    if (rc == SOCKET_ERROR)
        // Can not send data - sendto
        exit(1);

    return true;
}

// Recieve data via udp
int CSocket::upd_recv(string& s) const
{
    struct sockaddr_in addr_recvfrom;
    int len, n;

    char buf[MAXRECV + 1];
    s = "";
    memset(buf, 0, MAXRECV + 1);
    len = sizeof(addr_recvfrom);
    n = recvfrom(m_sock, buf, MAXRECV, 0, (struct sockaddr *) &addr_recvfrom, &len);

    if (n == SOCKET_ERROR)
    {
        // Error by recvfrom()
        exit(1);
        return 0;
    }
    else
    {
        s = buf;
        return n;
    }            
}


// winsock.dll free
void CSocket::cleanup() const
{
    WSACleanup();
}

// Close Socket
bool CSocket::close() const
{
    closesocket(m_sock);
    cleanup();
    return true;
}


