#include "chatRoom.h"

#include <iostream>

ChatRoom::ChatRoom()
{}

void ChatRoom::processMessage(const Message& message)
{
   
	this->mActionListMessage.append(" " + message.data);
    dispatchMessage(Message(message.data, message.sender));
  
}

void ChatRoom::getMessageAllFromClient()
{
    for (std::vector<std::shared_ptr<ChatClient>>::iterator it = m_clients.begin(); it != m_clients.end(); ++it)
    {
        std::string buf;
        
        if ((*it)->receive(buf))
        {
            if (buf.size() > 0)
                processMessage(Message(buf, it));
        }
        else
        {
            std::string message((*it)->getName());
            message += " connection reset";

            std::cout << message << std::endl;
            dispatchMessage(Message(message, it));

            it = m_clients.erase(it);

            if (it == m_clients.end())
                break;
        }
    }
}

bool ChatRoom::addClient(SOCKET sock)
{
    unsigned long iMode = 0;
    std::string name;

    std::shared_ptr<ChatClient> newClient(std::make_shared<ChatClient>(sock, name));

    ioctlsocket(sock, FIONBIO, &iMode);

    bool haveReceive = newClient->receive(name);

    if (haveReceive && name.size() > 0)
    {
        if (!userHasAlreadyName(name))
        {
            newClient->setName(name);

            std::cout << "New client connect : " << name << std::endl;

            iMode = 1;
            ioctlsocket(sock, FIONBIO, &iMode);

            m_clients.push_back(newClient);	
			if (m_clients.size() == 1)
				newClient->send("Player White Start");
			else if (m_clients.size() == 2)
			{
				m_clients[0]->send("SwitchTurn");
				newClient->send("Player Black Start");
			}	
			else if (m_clients.size() > 2)
			{
				newClient->send("Spectator Start "+ this->mActionListMessage);
			}
				
        }
        else
        {
            newClient->send("Client name already exist !\n Try another");
        }
    }
    else
    {
        std::cerr << "fail add new client" << std::endl;
    }

    return false;
}


void ChatRoom::dispatchMessage(const Message& message)
{
    if (message.data.size() > 0)
    {
        std::string buf;
       
        for (std::vector<std::shared_ptr<ChatClient>>::iterator it = m_clients.begin(); it != m_clients.end(); ++it)
        {
            if (it != message.sender)
            {
                if (!(*it)->send(message.data))
                {

                    std::string errorMessage((*it)->getName());
                    errorMessage += " disconnect !";

                    std::cout << errorMessage << std::endl;

                    dispatchMessage(Message(errorMessage, it));
                    it = m_clients.erase(it);
                }
            }
        }
    }
}

void ChatRoom::sendMessage(const Message& message)
{
    (*message.receiver)->send(message.data);
}

ChatRoom::VecUser::iterator ChatRoom::userByName(const std::string& name)
{
    for (auto it = m_clients.begin(); it != m_clients.end(); ++it)
    {
        if ((*it)->getName() == name)
            return it;
    }

    return m_clients.end();
}

bool ChatRoom::userHasAlreadyName(const std::string& name)
{
    for (auto it = m_clients.begin(); it != m_clients.end(); ++it)
    {
        if ((*it)->getName() == name)
            return true;
    }

    return false;
}