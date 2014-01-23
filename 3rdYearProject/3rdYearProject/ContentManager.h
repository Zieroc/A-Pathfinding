#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H
#include "Debug.h"
#include "CC_Texture.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <string>

using std::string;
using std::map;

class ContentManager
{
public:
	ContentManager(SDL_Renderer* m_p_Renderer);
	~ContentManager();
	void LoadTexture(string filepath);
	void LoadMusic(string filepath);
	void LoadSoundEffect(string filepath);
	CC_Texture* GetTexture(string name);
	Mix_Music* GetMusic(string name);
	Mix_Chunk* GetSoundEffect(string name);
private:
	map<string, CC_Texture*> m_p_Textures;
	map<string, Mix_Music*> m_p_Music;
	map<string, Mix_Chunk*> m_p_SoundEffects;
	SDL_Renderer* m_p_Renderer;
};

#endif

