#ifndef _CHATSERVER_H_
#define _CHATSERVER_H_

#include <Winsock2.h>
#include <string>
#include <thread>

#include "chatRoom.h"

class ChatServer
{
public:
    ChatServer(unsigned short port);
    void bind();

    void run();

protected:
    SOCKET m_socket;
    unsigned short m_port;

    bool m_isBind;

    ChatRoom m_room;

    void getClient();
};

#endif //_CHATSERVER_H_