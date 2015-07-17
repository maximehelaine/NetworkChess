#ifndef _CHATCLIENT_H_
#define _CHATCLIENT_H_

#include <Winsock2.h>
#include <string>
#include <vector>
#include <thread>

#define MAX_BUFFER 255

class ChatClient
{
public:
	ChatClient();
    ChatClient(const std::string& ip, unsigned short port);
    ChatClient(SOCKET sock, const std::string&);

    virtual ~ChatClient();

    void connect();
    void close();

    bool send(const std::string& data);
    bool receive(std::string& buffer);
    
    SOCKET getSocket() const;
    std::string getIp() const;
    unsigned short getPort() const;
    const std::string& getName() const;
    std::string& getName();

    bool isConnect() const;

    void setIp(const std::string&);
    void setPort(const unsigned short);
    void setName(const std::string&);

    void receiveLoop();
    bool processCommandLine(const std::string&);

protected:
    std::string m_name;
    SOCKET m_sock;
    std::string m_ip;
    unsigned short m_port;

    bool m_threadRunning;
    std::thread* m_thread;

    bool m_isConnect;

    void processClientSideMessage(const std::string&);
};

#endif //_CHATCLIENT_H_