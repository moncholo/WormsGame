#ifndef SDL_
#define SDL_
#include "SDL.h"
#include "SDL_thread.h"
#include <SDL_image.h>
#include <vector>
#endif

class Explosion {
	public:
	std::vector<SDL_Rect>* clips;
	SDL_Rect* rectangulo;
	SDL_Renderer* renderer;
	SDL_Surface* surfaceExplosion;
	SDL_Texture* textureExplosion;
	int iW, iH;
	float posX, posY;
	int fotograma;

	Explosion(int arma, SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom, float offsetX, float offsetY, float posXExplosion, float posYExplosion);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, float x, float y, SDL_Rect clip);
	void explotar();
	void dibujar();
	bool terminoAnimacion();
	~Explosion();
};