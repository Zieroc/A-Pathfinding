#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "Debug.h"
#include "ContentManager.h"
#include <SDL_mixer.h>
#include <string>

using std::string;

class SoundManager
{
public:
	SoundManager(ContentManager* contentMan);
	~SoundManager();
	void PlayMusic(string name);
	void FadeInMusic(string name, int ms);
	void FadeOutMusic(int ms);
	void PlaySoundEffect(string name);
	void PauseMusic();
	void ResumeMusic();
	void StopMusic();
private:
	ContentManager* m_p_ContentManager; //Reference to the content manager
	int m_MusicVolume;
	int m_SoundEffectVolume;
};

#endif

