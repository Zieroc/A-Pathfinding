#include "CC_Texture.h"
#include <iostream>

CC_Texture::CC_Texture(SDL_Texture* texture)
{
	m_p_Texture = texture;

	SDL_QueryTexture(m_p_Texture, NULL, NULL, &m_Width, &m_Height);
}

CC_Texture::CC_Texture(SDL_Renderer* renderer, const char* filepath)
{
	m_p_Texture = IMG_LoadTexture(renderer, filepath);

	if(m_p_Texture == 0)
	{
		DEBUG_MSG("ERROR LOADING TEXTURE:");
		DEBUG_MSG(filepath);
	}

	SDL_QueryTexture(m_p_Texture, NULL, NULL, &m_Width, &m_Height);
}


CC_Texture::~CC_Texture()
{
	DEBUG_MSG("DESTROyED");
	SDL_DestroyTexture(m_p_Texture);
}

int CC_Texture::GetWidth()
{
	return m_Width; 
}

int CC_Texture::GetHeight()
{
	return m_Height;
}

SDL_Texture* CC_Texture::GetTexture()
{
	return m_p_Texture;
}
