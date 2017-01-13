#ifndef OBJETO
#define OBJETO

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Box2D\Box2D.h"
#include "SDL2_gfx-1.0.0\SDL2_gfxPrimitives.h"
#include "Constantes.h"

typedef std::vector<b2Body*> vectorChains;

class Objeto {
	public:

		bool elegido;
		float x, y, a, rot, masa;
		float offsetX, offsetY;
		int r, g, b;
		std::string color;
		std::string estatico;
		bool enMundo;


		Objeto();
		virtual ~Objeto();

		virtual void dibujarConColor(SDL_Renderer* renderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, 
					float factorDeZoom, float offsetX, float offsetY);


		virtual void incluirEnMundo(b2World* unMundo);

		bool solapaConAlgunaTierra(vectorChains* unVector, int alto_px, int ancho_px, float alto_un, float ancho_un);

		virtual void imprimirMensaje();

		void setOffsetX(float unOffset);

		void setOffsetY(float unOffset);

		virtual b2Body* getCuerpo();

		virtual void setElegido(bool eleg);

		bool solapaConTierra(b2Body* contornoTierra, int altoPixelesDeLaImagen, int anchoPixelesDeLaImagen, float altoUnidades, float anchoUnidades);

		virtual bool esGusano(){ return false;};
};

#endif