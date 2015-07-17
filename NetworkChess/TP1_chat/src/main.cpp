#include <iostream>

#include "chatClient.h"
#include "chatServer.h"

typedef struct Options
{
    bool isServer;
    unsigned short port;
    std::string ip;


    Options()
        : isServer(false),
        port(0),
        ip("127.0.0.1")
    {}

}Options;


int main(int argc, char**argv)
{
	int port;
	std::cout << "Enter a port: ";
	std::cin >> port;
	try
	{
		ChatServer server(port);
		server.bind();
		server.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

    return 0;
}