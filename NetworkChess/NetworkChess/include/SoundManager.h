#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <string>

#include "fmod.h"

using namespace std;

class SoundManager
{
public:
	static SoundManager& Instance();
	void initFMOD();
	void freeFMOD();
private:
	SoundManager& operator= (const SoundManager&){}
	SoundManager(const SoundManager&){}

	static SoundManager m_instance;
	SoundManager();
	~SoundManager();

	FMOD_SYSTEM* mSys;
};
#endif