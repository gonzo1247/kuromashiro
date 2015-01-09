/*Socket.h for Windows and UNIX/Linux*/

#ifndef __CSOCKET_H
#define __CSOCKET_H

#ifdef WIN32
#include <string>
#include <WinSock2.h>
#include <io.h>

#else
/* Headerfiles für Unix/Linux */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#endif

using namespace std;

// Max. Connections to same time
const int MAXCONNECTIONS = 10;

// Max. file can recieve in same time
const int MAXRECV = 1024;

class CSocket
{
    private:
        // Socketnuber
        int m_sock;

        // Structur sockaddr_in
        sockaddr_in m_addr;

    public:
        // Konstruktor
        CSocket();

        // virtual Destructor
        virtual ~CSocket();

        // Create Socket - TCP
        bool tcp_create();
        // Create Socket - UDP
        bool udp_create();
        bool bind(const int port);
        bool listen() const;
        bool accept(CSocket&) const;
        bool connect(const string host, const int port);

        // Send File - TCP
        bool send(const string) const;
        int recv(string&) const;

        // Send File - UDP
        bool udp_send(const string, const string, const int port) const;
        int upd_recv(string&) const;

        // Socket close
        bool close() const;

        // WSACleanup
        void cleanup() const;
        bool is_valid() const { return m_sock != -1; }



};



#endif __CSOCKET_H