#include "Explosion.h"
#include <iostream>

Explosion::Explosion(int arma, SDL_Renderer *unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa,
					 float factorDeZoom, float offsetX, float offsetY, float posXExplosion, float posYExplosion) {

	std::cout << "IDarma: " << arma << std::endl;
	this->renderer = unRenderer;
	float escalaX = anchoVentana / anchoMapa ;
	float escalaY = altoVentana / altoMapa;
	posX = posXExplosion;
	posY = posYExplosion;
	this->fotograma = 0;

	clips = new std::vector<SDL_Rect>;

	if( (arma == 1) || (arma == 2)){
		this->surfaceExplosion = IMG_Load("private/explosion.png");
		this->textureExplosion = SDL_CreateTextureFromSurface(this->renderer, this->surfaceExplosion);
		
		iW = 162; 
		iH = 70;
		/*int x = SCREEN_WIDTH / 2 - iW / 2;
		int y = SCREEN_HEIGHT / 2 - iH / 2;*/

		rectangulo = new SDL_Rect;
		if(arma == 1){
			rectangulo->h = iH * escalaY * factorDeZoom;
			rectangulo->w = iH * escalaX * factorDeZoom;
		}
		if(arma == 2){
			rectangulo->h = iH * escalaY * factorDeZoom + 20;
			rectangulo->w = iH * escalaX * factorDeZoom + 20;
		}
		rectangulo->x = posX * escalaX * factorDeZoom - offsetX - rectangulo->w / 2;
		rectangulo->y = (altoVentana - (posY + 10) * escalaY) * factorDeZoom - offsetY - rectangulo->h / 2;
		//SDL_RenderCopy(renderer, aDibujar, NULL, &rectangulo);

		//Setup the clips for our image
		
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 3; i++){
				SDL_Rect unClip;
				unClip.x = i * iW;
				unClip.y = j * iH;
				unClip.w = iW;
				unClip.h = iH;
				clips->push_back(unClip);
			}
		}
	}
	if((arma == 3) || (arma == 4)){
		this->surfaceExplosion = IMG_Load("private/explosionsprite1.png");
		this->textureExplosion = SDL_CreateTextureFromSurface(this->renderer, this->surfaceExplosion);
        iW = iH = 96;
        
        rectangulo = new SDL_Rect;
		rectangulo->h = iH * escalaY * factorDeZoom + 20;
		rectangulo->w = iW * escalaX * factorDeZoom + 20;
		if(arma == 3){
			rectangulo->h += 20;
			rectangulo->w += 20;
		}
        rectangulo->x = posX * escalaX * factorDeZoom - offsetX - rectangulo->w / 2;
        rectangulo->y = (altoVentana - (posY+15)* escalaY) * factorDeZoom - offsetY - rectangulo->h / 2;
        //SDL_RenderCopy(renderer, aDibujar, NULL, &rectangulo);

        //Setup the clips for our image
        for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 5; i++){
                        SDL_Rect unClip;
                        unClip.x = i * iW;
                        unClip.y = j * iH;
                        unClip.w = iW;
                        unClip.h = iH;
                        clips->push_back(unClip);
                }
        }
	}
}

void Explosion::dibujar(){
	int indice = (int)(this->fotograma / 5);
	if((indice < 12)&& (this->clips->size() != 0)){
		SDL_Rect rect = this->clips->at((int)(this->fotograma / 5));
		this->renderTexture(this->textureExplosion, this->renderer, this->posX, this->posY, rect);
	}
	this->fotograma++;
}

bool Explosion::terminoAnimacion(){
	return ((int)(this->fotograma / 5) > 11);
}
void Explosion::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip) {
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void Explosion::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, float x, float y, SDL_Rect clip) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//if (clip != nullptr){
	dst.w = clip.w;
	dst.h = clip.h;
	//} else SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

	renderTexture(tex, ren, *rectangulo, &clip);
}

int sprite(void* explosion_){
	Explosion* explosion = (Explosion*)explosion_;
	explosion->surfaceExplosion = IMG_Load("private/explosionsprite1.png");
	explosion->textureExplosion = SDL_CreateTextureFromSurface(explosion->renderer, explosion->surfaceExplosion);
	SDL_Delay(100);
	for (int i= 0; i < 15; i++) {
		explosion->renderTexture(explosion->textureExplosion, explosion->renderer, explosion->posX, explosion->posY,(explosion->clips->at(i)));
		
		SDL_RenderPresent(explosion->renderer);
		SDL_Delay(500);
	}
	return 0;
}

void Explosion::explotar(){
	SDL_Thread* explosion = SDL_CreateThread(sprite, "sprite", (void*)this);
}

Explosion::~Explosion(){
	delete rectangulo;
	//for (int i= 0; i < 15; i++) delete clips->at(i);
	delete clips;
}