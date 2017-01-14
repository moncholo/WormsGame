#ifndef __RECORREDORDEIMAGENES__
#define __RECORREDORDEIMAGENES__

#include "SDL.h"
#include <cstdio>
#include <iostream>
#include <Objeto.h>
#include <vector>

const enum Direccion {ABAJO, ARRIBA, DERECHA, IZQUIERDA};

class RecorredorDeImagenes{
	
	private:
		float zoom;

		SDL_Rect* rectanguloRecorredor;

		int anchoDeLaImagen, anchoVentana;

		int altoDeLaImagen, altoVentana;

		int anchoMapa, altoMapa;

		float escalaX, escalaY;

		float offsetX, offsetY;


		void inicializarZoomYRectangulo();

		void recalcularDimensionesDelRectangulo();

		bool cumpleCondicionesDeRango();

		void procesarMovimientoAIzquierda();

		void procesarMovimientoADerecha();

		void procesarMovimientoArriba();

		void procesarMovimientoAbajo();

		
	public: 

		SDL_Rect* getRectangulo();

		RecorredorDeImagenes::RecorredorDeImagenes(int anchoImagen, int altoImagen, int altoVentana, int anchoVentana, int altoMapa,
			int anchoMapa);

		RecorredorDeImagenes();

		float getZoom();
		
		~RecorredorDeImagenes();

		void incrementarZoom();

		void decrementarZoom();
		
		void desplazarHacia(Direccion unaDireccion);

		float getAltoImagen(){ return this->altoDeLaImagen; }
		float getAnchoImagen(){ return this->anchoDeLaImagen; }

};

#endif