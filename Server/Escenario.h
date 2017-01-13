#ifndef __ESCENARIO__
#define __ESCENARIO__

#include <iostream>
#include <SDL.h>
#include <Box2D/Box2d.h>
#include "PoligonoRegular.h"
#include <cstdio>
#include <SDL_image.h>
#include "Tierra.h"
#include "RecorredorDeImagenes.h"
#include "ProcesadorDeTierra.h"
#include "Circulo.h"
#include "Rectangulo.h"
#include <sstream>
#include "SDL2_gfx-1.0.0\SDL2_rotozoom.h"
#include <fstream>
#include <time.h>
#include "SDL_log.h"
#include "Objeto.h"
#include "Log.h"
#include "Gusano.h"
#include "Constantes.h"
#include <random>
#include "Sonido.h"

class Escenario {

	private:

		void inicializarGusanos();

	public:
	
		int equiposPermitidos, equiposEnEscenario;
		int alto_px;
		int ancho_px;
		float alto_un;
		float ancho_un;
		float nivel_agua;
		float zoom;
		float offsetX, offsetY;

		b2Body* municionActual;
		
		int posXExplosion;
		int posYExplosion;
		int radioDeExplosion;
		bool dibujarBomba;
		bool explotar;
		int turnoDeEquipo;

		int sonidoActual;

		SDL_Renderer* renderer;
		SDL_Texture* textureDelCielo;
		SDL_Texture* texturaDeFondo;
		SDL_Rect* rectanguloAgua;
		SDL_Surface* surfaceDelCirculo;
		SDL_Surface* surfaceDeFondo;
		Tierra *miTierra;
		SDL_Texture* unaTextura;
		RecorredorDeImagenes* recorredorDeImagenes;
		int idArma;
		int angulo;

		std::string imagen_tierra;
		std::string imagen_cielo;
		std::vector<Gusano*>* gusanos;
		std::vector<Objeto*>* objetos; //Los objetos pueden ser cuadrados, circulos ,etc	


		Escenario();
		virtual ~Escenario();
		void inicializarRecursosImagenes();
		void comprobarSiCuerposEnAgua(b2Body* cuerpos);
		void incluirObjetosEnElMundo(b2World* mundo);
		void dibujarObjetos();
		void dibujarEscenario();
		ProcesadorDeTierra* miProcesador;
		void incrementarZoom();
		void decrementarZoom();
		void desplazarHacia(Direccion unaDireccion);

		float getZoom();
		float getOffsetX(){ return this->offsetX;}
		float getOffsetY(){ return this->offsetY;}

		void agregarNuevoEquipo(std::string nombreJugador, b2World* unMundo);
		void resetEquipos(b2World* unMundo);

		bool verificarMunicionActual();
		void recortarImagenEnPosicion(float posicionX, float posicionY, float radio);

		void avanzarTurno();

		bool equipoTieneGusanosVivos(int equipo);
		Gusano* elegirGusanoVivoDe(int equipo);
};

#endif