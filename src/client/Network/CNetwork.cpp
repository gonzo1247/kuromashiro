#include "CNetwork.h"


CNetwork::CNetwork() : m_sock(0)
{
    CNetwork cnetwork;
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
        cnetwork.CreateConnect();
        

}

CNetwork::~CNetwork()
{
    ::closesocket(m_sock);
    
}

void CNetwork::CreateConnect()
{
    WSADATA wsaData;
    CNetwork cnetwork;

    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
        cnetwork.ConnectFail(iResult);

    struct addrinfo *result = NULL,
        *ptr = NULL,
        hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server adress and port
    iResult = getaddrinfo(SERVER_NAME, DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        cnetwork.ConnectFail(iResult);
        WSACleanup();
    }

    SOCKET ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connection to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        cnetwork.ConnectFail(ConnectSocket);
        WSACleanup();
    }

    // Connect to server
    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        cnetwork.ConnectFail(ConnectSocket);
        WSACleanup();
    }
    cnetwork.SendData(ConnectSocket);
}

void CNetwork::SendData(SOCKET ConnectSocket)
{
    CNetwork cnetwork;   

    char *sendbuf = "this is a test";
    
    int iResult;

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        WSACleanup();
    }

    cnetwork.CloseConnect(ConnectSocket, iResult);
    cnetwork.ReceiveData(ConnectSocket, iResult);
                                        
}

void CNetwork::CloseConnect(SOCKET ConnectSocket, int Result)
{
    // shutdown the connection for sending since no more data will be sent
    // the client can still use the ConnectSocket for receiving data

    Result = shutdown(ConnectSocket, SD_SEND);
    if (Result == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        WSACleanup();
    }

    if (Result == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        WSACleanup();
    }

    if (Result == INVALID_SOCKET)
    {
        closesocket(ConnectSocket);
        WSACleanup();
    }

    if (ConnectSocket == INVALID_SOCKET)
    {
        closesocket(ConnectSocket);
        WSACleanup();
    }

    closesocket(ConnectSocket);
    WSACleanup();

}

void CNetwork::ReceiveData(SOCKET ConnectSocket, int Result)
{
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Receive data until the server closes the connect
    do
    {
        Result = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        //if (Result > 0)

    } while (Result > 0);
}

int CNetwork::CloseConnect(SOCKET ConnectSocket)
{
    closesocket(ConnectSocket);
    return 1;

}

int CNetwork::ConnectFail(SOCKET ConnectSocket)
{
    CNetwork cnetwork;

    cnetwork.CloseConnect(ConnectSocket);

    return 1;
}

int CNetwork::ConnectFail(int Result)
{
    CNetwork cnetwork;

    WSACleanup();

    return 1;
}