#include "SoundManager.h"

using namespace std;

SoundManager SoundManager::m_instance = SoundManager();

SoundManager::SoundManager()
{
	cout << "Creation SoundManager" << endl;
}

SoundManager::~SoundManager()
{
	cout << "Destruction SoundManager" << endl;
}

SoundManager& SoundManager::Instance()
{
	return m_instance;
}

void SoundManager::initFMOD()
{
	FMOD_System_Create(&(this->mSys));
	FMOD_System_Init(this->mSys, 2, FMOD_INIT_NORMAL, nullptr);

	FMOD_System_Close(this->mSys);
	FMOD_System_Release(this->mSys);
}
void SoundManager::freeFMOD()
{
	FMOD_System_Close(this->mSys);
	FMOD_System_Release(this->mSys);
}