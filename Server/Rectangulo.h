#include "Objeto.h"

#ifndef RECTANGULO
#define RECTANGULO

class Rectangulo : public Objeto {

	public:
		b2Body* cuerpoDelRectangulo;
		float alto;
		float ancho;
		Rectangulo();
		
		Rectangulo(float x, float y, float ancho, float alto); //, float escalaX, float escalaY);

		void incluirEnMundo(b2World* unMundo);

		void dibujarConColor(SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa,
					float factorDeZoom, float offsetX, float offsetY);

		void imprimirMensaje();

		b2Body* getCuerpo();

		bool esGusano();

		~Rectangulo();

};


#endif