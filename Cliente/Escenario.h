#ifndef ESCENARIO
#define ESCENARIO

#include "Constantes.h"
#include <iostream>
#include <SDL.h>
#include "PoligonoRegular.h"
#include <cstdio>
#include <SDL_image.h>
#include "Tierra.h"
#include "RecorredorDeImagenes.h"
#include "ProcesadorDeTierra.h"
#include "Circulo.h"
#include "Rectangulo.h"
#include <sstream>
#include <fstream>
#include <time.h>
#include "SDL_log.h"
#include "Objeto.h"
#include "Log.h"
#include "SDL2_gfx-1.0.0\SDL2_rotozoom.h"
#include "Gusano.h"
#include <random>
#include "Sonido.h"
#include "Explosion.h"

class Escenario {
	private:
		void inicializarGusanos();

	public:

		Explosion* miExplosion;

		Sonido* manejadorSonido;
		int equipoGanador;
		int equiposPermitidos, equiposEnEscenario;
		int alto_px;
		int ancho_px;
		float posXExplosion;
		float posYExplosion;
		int radioDeExplosion;
		float posXExplosionAnt, posYExplosionAnt, xDisparo, yDisparo;
		bool dibujarBomba;
		int radioDeExplosionAnt;
		float alto_un;
		float ancho_un;
		float nivel_agua;
		float zoom;
		float offsetX, offsetY;
		SDL_Renderer* renderer;
		SDL_Texture* textureDelCielo;
		SDL_Texture* texturaDeFondo;
		SDL_Rect* rectanguloAgua;
		SDL_Surface* surfaceDeFondo;
		SDL_Surface* surfaceDelCirculo;
		Tierra *miTierra;
		SDL_Texture* unaTextura;
		RecorredorDeImagenes* recorredorDeImagenes;
		SDL_Rect rectanguloBomba;
		int idArma;
		int tiempoDeVidaArma;
		//acordarse de poner las surface de armas
		SDL_Rect rectanguloMira;
		float32 xMira;
		float32 yMira;
		int turnoDe;
		SDL_Rect rectanguloTurno;
		SDL_Rect rectanguloTextoTurnoDe;
		SDL_Surface* textoTurnoDe;
		SDL_Texture* textureTurnoDe;
		TTF_Font* letra;
		int tiempoTurnoRestante;
		int idCliente;
		SDL_Surface* surfaceTiempo;
		SDL_Texture* textureTiempo;
		SDL_Rect rectanguloTiempoTurno;

		SDL_Surface* surfaceTiempoArma;
		SDL_Texture* textureTiempoArma;
		SDL_Rect rectanguloTiempoArma;

		SDL_Surface* surfaceEquipoGanador;
		SDL_Texture* textureEquipoGanador;
		SDL_Rect rectanguloEquipoGanador;

		SDL_Rect rectanguloIdCliente;

		SDL_semaphore* semaforoRenderer;

		std::string imagen_tierra;
		std::string imagen_cielo;
		std::vector<Gusano*>* gusanos;
		std::vector<Objeto*>* objetos; //Los objetos pueden ser cuadrados, circulos ,etc	
		Escenario();
		virtual ~Escenario();
		void inicializarRecursosImagenes();
		void dibujarObjetos();
		void dibujarEscenario();
		ProcesadorDeTierra* miProcesador;
		void incrementarZoom();
		void decrementarZoom();
		void desplazarHacia(Direccion unaDireccion);
		SDL_Texture* texturasDeArmas[NUMERO_DE_ARMAS+1]; //mas la mira


		float getZoom();
		float getOffsetX(){ return this->offsetX;}
		float getOffsetY(){ return this->offsetY;}

		//void agregarNuevoEquipo(std::string nombreJugador, b2World* unMundo);
		void resetEquipos();

		void recortarImagenEnPosicion(float posicionX, float posicionY, float radio, SDL_semaphore* semaforoRenderer);

		void playSonido(char numeroDeSonido);
};

#endif