#include "Objeto.h"

#ifndef POLIGONOREGULAR
#define POLIGONOREGULAR

class PoligonoRegular : public Objeto {

	private:
		b2Body* cuerpoDelPoligono;
		
		float* verticesX, *verticesY;
		
		short* calcularVerticesX( float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom, float offsetX,
			float offsetY);
		
		short* calcularVerticesY( float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom, float offsetX,
			float offsetY);
		
		
	public:
		int numeroDeLados;
		float escala;

		PoligonoRegular();
		
		PoligonoRegular(int numLados);

		~PoligonoRegular();

		void dibujarConColor(SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, 
			float factorDeZoom, float offsetX, float offsetY);

		void incluirEnMundo(b2World* unMundo);

		void imprimirMensaje();

		b2Body* getCuerpo();

		bool esGusano();

		void setPosX(float x);
		void setPosY(float y);

		void setEscala (float esc);
		void setNumLados(int numLados);

};

#endif