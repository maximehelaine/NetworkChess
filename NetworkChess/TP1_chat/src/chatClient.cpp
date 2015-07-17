#include "chatClient.h"

#include <Ws2tcpip.h>

#include <iostream>
#include <vector>

ChatClient::ChatClient(const std::string& ip, unsigned short port)
    : m_ip(ip),
    m_port(port),
    m_isConnect(false),
    m_sock(INVALID_SOCKET),
    m_thread(nullptr),
    m_threadRunning(false)
{
    WSADATA data;

    int err = WSAStartup(MAKEWORD(2, 2), &data);

    if (err != 0)
    {
        throw std::exception("Can't load Win32 dll");
    }
}

ChatClient::ChatClient(SOCKET sock, const std::string& name)
    :m_sock(sock),
    m_name(name),
    m_isConnect(true),
    m_thread(nullptr),
    m_threadRunning(false)
{}

static void startListening(ChatClient* instance)
{
    instance->receiveLoop();
}

void ChatClient::connect()
{
    if (m_isConnect || m_sock != INVALID_SOCKET)
    {
        ::closesocket(m_sock);
        m_isConnect = false;
    }

    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_sock == INVALID_SOCKET)
    {
        throw std::exception("Error occur");
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    //InetPton(AF_INET, (PCTSTR)m_ip.c_str(), &addr.sin_addr.s_addr);
    inet_pton(AF_INET, m_ip.c_str(), &(addr.sin_addr.s_addr));
    
    int error = ::connect(m_sock, (SOCKADDR*)&addr, sizeof(addr));

    if (error == SOCKET_ERROR)
    {
        throw std::exception("Can't connect");
    }
    
    m_threadRunning = true;
    m_thread = new std::thread(startListening, this);

    m_isConnect = true;

    std::cout << "Connecting to server..." << std::endl;
    Sleep(1500);

    if (!send(m_name))
    {
        throw std::exception("Can't send name to server");
    }

    std::cout << "Connect to server" << std::endl;
}

ChatClient::~ChatClient()
{
    close();
}

void ChatClient::close()
{
    ::closesocket(m_sock);

    if (m_thread != nullptr)
    {
        m_threadRunning = false;
        m_thread->join();
        delete m_thread;
    }

    m_isConnect = false;
}

bool ChatClient::send(const std::string& data)
{
    if (!m_isConnect)
        return false;

    unsigned int dataSize = data.length();
    const char* dataPtr = data.c_str();

    if (dataSize > 0)
    {
        unsigned int alreadySent = 0;
        
        do
        {
            int curSend = ::send(m_sock, dataPtr + alreadySent, dataSize - alreadySent, 0);

            if (curSend == 0)
            {
                m_isConnect = false;
                return false;
            }

            alreadySent += curSend;
        
        } while (alreadySent < dataSize);
    }

    return true;
}

bool ChatClient::receive(std::string& buffer)
{
    if (!m_isConnect)
        return false;

    static char buf[MAX_BUFFER] = { 0 };
    memset(buf, '\0', MAX_BUFFER);

    int lastReceiveSize = 0;

    buffer = "";

    do
    {
        lastReceiveSize = ::recv(m_sock, buf, MAX_BUFFER, 0);

        if (lastReceiveSize > 0)
            buffer += buf;

    } while (lastReceiveSize == MAX_BUFFER);

    if (lastReceiveSize == -1)
    {
        int error = WSAGetLastError();

        if (error != EWOULDBLOCK && error != WSAEWOULDBLOCK)
        {
            m_isConnect = false;
            return false;
        }
    }

    return true;
}

SOCKET ChatClient::getSocket() const
{
    return m_sock;
}

std::string ChatClient::getIp() const
{
    return m_ip;
}

unsigned short ChatClient::getPort() const
{
    return m_port;
}

const std::string& ChatClient::getName() const
{
    return m_name;
}

std::string& ChatClient::getName()
{
    return m_name;
}

bool ChatClient::isConnect() const
{
    return m_isConnect;
}

void ChatClient::setIp(const std::string& ip)
{
    m_ip = ip;
}

void ChatClient::setPort(const unsigned short port)
{
    m_port = port;
}

void ChatClient::setName(const std::string& name)
{
    m_name = name;
}

void ChatClient::receiveLoop()
{
    std::string buf;

    while (m_threadRunning)
    {
        if (receive(buf))
        {
            if (buf.size() > 0)
            {
                processClientSideMessage(buf);
            }
        }
    }
}

bool ChatClient::processCommandLine(const std::string& command)
{
    if (command.find("/h") != command.npos)
    {
        std::cout << "Liste des commandes" << std::endl
            << "/name name (Changement de nom)" << std::endl
            << "/w name message (Envoi un message privé à l'utiliateur name)" << std::endl
            << "/quit (Quit le chat)" << std::endl
            << "/list (Affiche la liste des utilisateurs connecté" << std::endl;
    }
    else
    {
        if (!send(command))
        {
            std::cerr << "Connection reset" << std::endl;
        }
    }

    return true;
}

void ChatClient::processClientSideMessage(const std::string& message)
{
    std::cout << message << std::endl;
}