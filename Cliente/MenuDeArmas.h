#ifndef __MENU_DE_ARMAS__
#define __MENU_DE_ARMAS__

#include "SDL.h"
#include "SDL_image.h"
#include "SDL2_gfx-1.0.0\SDL2_rotozoom.h"
#include <vector>
#include "Constantes.h"

class MenuDeArmas{


	private:

		bool estaActivo;

		SDL_Renderer* rendererDelJuego;

		SDL_Surface* surfaceDelMenu;

		SDL_Surface* surfaceDelMarco, *surfaceDelMarcoGris;

		SDL_Texture* texturaDelMenu;

		SDL_Texture* textureDelMarco, *textureDelMarcoGris;
		
		std::vector<int>* vectorDeMuniciones;

		std::vector<SDL_Surface*>* vectorDeImagenes;

		int armaSeleccionada;

		float porcentajeDedicadoAArmas;

		float porcentajeDedicadoAUsuario;

		void mostrarArmaSeleccionada();
	public:

		MenuDeArmas(int tamanioX, int tamanioY, SDL_Renderer* unRenderer);
		
		~MenuDeArmas();

		void mostrarMenu();

		std::vector<int>* getVectorDeMuniciones();

		bool isActive();

		void setActivo(bool activo);

		void seleccionarArma(int numeroDeArma);

		int seleccionarArma(float posXMouse, float posYMouse);

};










#endif