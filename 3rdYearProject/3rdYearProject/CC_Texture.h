#ifndef CC_TEXTURE_H
#define CC_TEXTURE_H
#include "Debug.h"
#include <SDL.h>
#include <SDL_image.h>

class CC_Texture
{
public:
	CC_Texture(SDL_Renderer* renderer, const char* filepath);
	~CC_Texture();
	int GetWidth();
	int GetHeight();
	SDL_Texture* GetTexture();
private:
	SDL_Texture* m_p_Texture;
	int m_Width;
	int m_Height;
};

#endif
