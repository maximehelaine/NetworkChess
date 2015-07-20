#include "chatServer.h"

#include <Ws2tcpip.h>
#include <iostream>

ChatServer::ChatServer(unsigned short port)
    : m_port(port),
    m_isBind(false),
    m_socket(INVALID_SOCKET)
{
    WSADATA data;

    int err = WSAStartup(MAKEWORD(2, 2), &data);

    if (err != 0)
    {
        throw std::exception("Can't load Win32 dll");
    }
}

void ChatServer::bind()
{
    if (m_isBind || m_socket != INVALID_SOCKET)
    {
        ::closesocket(m_socket);
        m_isBind = false;
    }

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_socket == INVALID_SOCKET)
    {
        throw std::exception("Can't create socket");
    }

    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);

    int error = ::bind(m_socket, (SOCKADDR*)&addr, sizeof(sockaddr_in));

    if (error == SOCKET_ERROR)
    {
        throw std::exception("Can't connect");
    }

    unsigned long iMode = 1;
    ioctlsocket(m_socket, FIONBIO, &iMode);
    error = ::listen(m_socket, SOMAXCONN);

    if (error != 0)
    {
        throw std::exception("Can't listen");
    }
	std::cout << "Binded" << std::endl;
    m_isBind = true;
}

void ChatServer::run()
{
    if (!m_isBind)
        return;
	std::cout << "Runned" << std::endl;
    while (m_isBind)
    {
        getClient();
        m_room.getMessageAllFromClient();
    }
}

void ChatServer::getClient()
{
    sockaddr adr;
    int len = sizeof(sockaddr);
    
    SOCKET newClient = ::accept(m_socket, &adr, &len);

    if (newClient != INVALID_SOCKET)
    {
        m_room.addClient(newClient);
    }
}