#include "ContentManager.h"


ContentManager::ContentManager(SDL_Renderer* renderer)
{
	m_p_Renderer = renderer;
}


ContentManager::~ContentManager()
{
	for(map<string, CC_Texture*>::const_iterator iter = m_p_Textures.begin(); iter != m_p_Textures.end(); ++iter)
	{
		delete(iter->second);
	}

	for(map<string, Mix_Music*>::const_iterator iter = m_p_Music.begin(); iter != m_p_Music.end(); ++iter)
	{
		Mix_FreeMusic(iter->second);
	}

	for(map<string, Mix_Chunk*>::const_iterator iter = m_p_SoundEffects.begin(); iter != m_p_SoundEffects.end(); ++iter)
	{
		Mix_FreeChunk(iter->second);
	}
}

void ContentManager::LoadTexture(string filepath)
{
	string key = filepath;
	filepath.insert(0, "data/Images/");
	m_p_Textures[key] = new CC_Texture(m_p_Renderer, filepath.c_str());
}

void ContentManager::LoadMusic(string filepath)
{
	string key = filepath;
	filepath.insert(0, "data/Audio/Music/");
	m_p_Music[key] = Mix_LoadMUS(filepath.c_str());
}

void ContentManager::LoadSoundEffect(string filepath)
{
	string key = filepath;
	filepath.insert(0, "data/Audio/SoundEffect/");
	m_p_SoundEffects[key] = Mix_LoadWAV(filepath.c_str());
}

CC_Texture* ContentManager::GetTexture(string name)
{
	return m_p_Textures[name];
}

Mix_Music* ContentManager::GetMusic(string name)
{
	return m_p_Music[name];
}

Mix_Chunk* ContentManager::GetSoundEffect(string name)
{
	return m_p_SoundEffects[name];
}
