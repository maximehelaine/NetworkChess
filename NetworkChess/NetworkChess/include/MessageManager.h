#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <iostream>
#include <string>

#include "chatClient.h"

using namespace std;

class MessageManager
{
public:
	static MessageManager& Instance();
	ChatClient getClient();
	void connect(string pseudo, string ip, int port);
	unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch);
	void parseCommand(string command);

	bool isConnected();
	bool isPlayer();
	void setStatue(bool value);
	void close();

private:
	MessageManager& operator= (const MessageManager&){}
	MessageManager(const MessageManager&){}

	static MessageManager m_instance;
	MessageManager();
	~MessageManager();

	ChatClient mClient;
	bool mIsPlayer = false;
};

static MessageManager& MESSAGEMANAGER = MessageManager::Instance();
#endif
