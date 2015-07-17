#include "chatRoom.h"

#include <iostream>

ChatRoom::ChatRoom()
{}

void ChatRoom::processMessage(const Message& message)
{
    if (message.data.substr(0, 9) == "/initName")
    {
        std::string clientName(message.data);
        clientName.replace(0, 9, "");

        (*message.sender)->setName(clientName);
    }
    else if (message.data.substr(0, 2) == "/w")
    {
        std::string buf(message.data);
        buf.replace(0, 3, "");
        
        std::string::size_type separatorIndex = buf.find(" ");
        
        if (separatorIndex == buf.npos)
        {
            sendMessage(Message("Error commande wisp", message.sender, message.sender));
        }
        else
        {
            std::string destName = buf.substr(0, separatorIndex);
            std::string destData = buf.substr(separatorIndex + 1);

            VecUser::iterator dest = userByName(destName);

            std::string wisp = "<";
            wisp += (*message.sender)->getName();
            wisp += ">";
            wisp += destData;

            if (dest != m_clients.end())
                sendMessage(Message(wisp, message.sender, dest));
            else
            {
                sendMessage(Message(std::string("user : ") + destName + std::string(" not found"), message.sender, message.sender));
            }
        }
    }
    else if (message.data.substr(0, 5) == "/list")
    {
        std::string messageList("User list :\n");

        for (auto it = m_clients.begin(); it != m_clients.end(); ++it)
        {
            messageList += (*it)->getName() + "\n";
        }

        messageList += "\n";

        sendMessage(Message(messageList, message.sender, message.sender));
    }
    else if (message.data.substr(0, 5) == "/name")
    {
        std::string clientName(message.data);
        clientName.replace(0, 6, "");

        if (userHasAlreadyName(clientName))
        {
            sendMessage(Message("Name already exist !", message.sender, message.sender));
        }
        else
        {
            std::string nameChangeMessage((*message.sender)->getName());
            nameChangeMessage += " change name to ";
            nameChangeMessage += clientName;

            (*message.sender)->setName(clientName);

            dispatchMessage(Message(nameChangeMessage, message.sender));
        }
    }
    else if (message.data.substr(0, 5) == "/quit")
    {
        std::string leaveMessage(" has quit !");
        dispatchMessage(Message((*message.sender)->getName() + leaveMessage, message.sender));
    }
    else
    {
        dispatchMessage(Message((*message.sender)->getName() + std::string(">") + message.data, message.sender));
    }
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
				newClient->send("Start Player White SwithTurn");
			else if (m_clients.size() == 2)
				newClient->send("Start Player Black");
			else if (m_clients.size() > 2)
				newClient->send("Start Spectator");
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
        std::string buf((*message.sender)->getName());
        buf += ">";
        buf += message.data;

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