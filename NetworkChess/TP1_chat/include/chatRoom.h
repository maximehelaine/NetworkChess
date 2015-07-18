#ifndef _CHATROOM_H_
#define _CHATROOM_H_

#define MAXCLIENT 10

#include <Winsock2.h>
#include <memory>
#include <vector>

#include "Tools.h"
#include "chatClient.h"

class ChatRoom
{
public:
    ChatRoom();

    void getMessageAllFromClient();
	void sendMessage(std::string message);
    bool addClient(SOCKET sock);
private:
	std::string mActionListMessage = "";
protected:
    typedef std::vector<std::shared_ptr<ChatClient>> VecUser;
    VecUser m_clients;

    struct Message
    {
        const std::string& data;
        VecUser::iterator sender;
        VecUser::iterator receiver;

        Message(const std::string& _data, VecUser::iterator _sender, VecUser::iterator _receiver = VecUser::iterator())
            : data(_data),
            sender(_sender),
            receiver(_receiver)
        {}

        Message& operator=(const Message& m)
        {
            ARGUNUSED(m);
            return *this;
        }
    };

    void processMessage(const Message& message);
    void dispatchMessage(const Message& message);

    void sendMessage(const Message&);
    
    VecUser::iterator userByName(const std::string&);

    bool userHasAlreadyName(const std::string&);
};

#endif //_CHATROOM_H_