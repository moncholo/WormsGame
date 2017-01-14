#ifndef CIRCULO
#define CIRCULO


#include "Objeto.h"

class Circulo: public Objeto {

protected:
	b2Body* cuerpoCirculo;

public:
		float escala;
		float radio; //no va. Hay q borrarlo. OJO QUE SE USA EN CIRCULO.CPP
		Circulo();
		 
		Circulo(float,float,float);
		void actualizar();

		void dibujarConColor(SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, 
							float factorDeZoom, float offsetX, float offsetY);
		
		void incluirEnMundo(b2World* unMundo);

		void imprimirMensaje();

		b2Body* getCuerpo();

		bool esGusano();

		~Circulo();
		
};

#endif