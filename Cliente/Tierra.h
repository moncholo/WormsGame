#ifndef _TIERRA_H_
#define _TIERRA_H_

#include <queue>
#include <Box2D/Box2D.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include "SDL2_gfx-1.0.0\SDL2_gfxPrimitives.h"
#include "Constantes.h"

class Tierra{
private:
	//b2Vec2 puntos[MAX_PIXELES_IMAGEN_TIERRA];
	b2Body *contornoTierra;
	//int cantidadDePuntos;
public:
	Tierra(std::queue<float>* listaPuntos, int altoPixelesDeLaImagen, int anchoPixelesDeLaImagen,
				float altoUnidades, float anchoUnidades, b2World* mundo);
	void setContorno(b2Body *contorno);
	b2Body* getContorno();
	void dibujar(SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa);
};


#endif