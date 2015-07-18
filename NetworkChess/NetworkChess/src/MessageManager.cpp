#include "MessageManager.h"
#include "GameManager.h"
#include "windows.h"
using namespace std;

MessageManager MessageManager::m_instance = MessageManager();

MessageManager::MessageManager()
{
	cout << "Creation MessageManager" << endl;
}

MessageManager::~MessageManager()
{
	cout << "Destruction MessageManager" << endl;
}

MessageManager& MessageManager::Instance()
{
	return m_instance;
}

ChatClient MessageManager::getClient()
{
	return this->mClient;
}
void MessageManager::connect(string pseudo, string ip, int port)
{
	this->mClient = ChatClient(ip, port);
	this->mClient.setName(pseudo);
	this->mClient.connect();
}
void MessageManager::parseCommand(string command)
{
	std::vector<std::string> commands;
	this->split(command, commands, ' ');
	for (int i = 0; i < commands.size(); ++i)
	{
		if (commands[i] == "Start")
		{
			GAMEMANAGER.initPositionPiece(WINDOW_HEIGHT / 10, WINDOW_HEIGHT / 10, WINDOW_WIDTH / 2 - (WINDOW_HEIGHT * 80 / 100) / 2, WINDOW_HEIGHT / 2 - (WINDOW_HEIGHT * 80 / 100) / 2);
			GAMEMANAGER.setStart(true);
		}
		else if (commands[i] == "Finish")
		{
			GAMEMANAGER.setFinish(true);
		}
		else if (commands[i] == "White")
		{
			GAMEMANAGER.setColor(ColorClient::White);
		}
		else if (commands[i] == "Black")
		{
			GAMEMANAGER.setColor(ColorClient::Black);
		}
		else if (commands[i] == "SwitchTurn")
		{
			GAMEMANAGER.switchTurn();
		}
		else if (commands[i] == "Player")
		{
			GAMEMANAGER.setType(TypeClient::Player);
		}
		else if (commands[i] == "Spectator")
		{
			GAMEMANAGER.setType(TypeClient::Spectator);
		}
		else if (commands[i] == "Move")
		{
			GAMEMANAGER.setPositionByName(commands[i + 1], static_cast<ColorClient>(stoi(commands[i + 2])), { stoi(commands[i + 3]), stoi(commands[i + 4]), stoi(commands[i + 5]), stoi(commands[i + 6]) });
			GAMEMANAGER.setNeedUpdateDisplay(true);
		}
	}
	
}
bool MessageManager::isConnected()
{
	return this->mClient.isConnect();
}
bool MessageManager::isPlayer()
{
	return this->mIsPlayer;
}
void MessageManager::setStatue(bool value)
{
	this->mIsPlayer = value;
}
void MessageManager::send(string message)
{
	this->mClient.send(message);
}
void MessageManager::close()
{
	this->mClient.close();
}
unsigned int MessageManager::split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, ((pos < txt.size()) ? pos : txt.size()) - initialPos + 1));

	return strs.size();
}