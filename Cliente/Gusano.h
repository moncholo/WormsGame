#ifndef _GUSANO_H
#define _GUSANO_H

#include "Box2D\Box2D.h"
#include "Objeto.h"
#include "CuerpoGusano.h"
#include "Tierra.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Gusano : public Objeto{

private:
	CuerpoGusano* cuerpoGusano;
	
	short* calcularVerticesY( float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom);
	short* calcularVerticesX( float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom);
	float* verticesX, *verticesY;
	std::string nombre;

	bool solapaConOtroCuerpo(b2World* unMundo);

public:

	char vida;
	SDL_Surface* imagenGusanoIzq;
	SDL_Surface* imagenGusanoDer;
	SDL_Surface* imagenGusanoGrisDer;
	SDL_Surface* imagenGusanoGrisIzq;
	SDL_Texture* textureDelGusanoIzq;
	SDL_Texture* textureDelGusanoDer;
	SDL_Texture* textureGusanoGrisDer;
	SDL_Texture* textureGusanoGrisIzq;
	SDL_Texture* textureArmaIzq;
	SDL_Texture* textureArmaDer;
	SDL_Surface* surfaceNombre;
	SDL_Texture* textureNombre;
	SDL_Surface* surfaceVida;
	SDL_Texture* textureVida;

	SDL_Surface* imagenGusanoMuerto;
	SDL_Texture* textureDelGusanoMuerto;
	void estaMuerto(float nivelAgua);

	TTF_Font* letraGusano;
	int idGusano;
	bool pintarEnColor;
	bool enMundo;
	bool miraADerecha;
	int equipo;
	bool vivo;

	Gusano(std::string nombreGusano, int equipo, int id);
	~Gusano();
	bool estaApoyado();
	void moverIzq();
	void moverDer();
	void saltar();
	void frenar();
	void actualizar();
	void setElegido(bool eleg);

	bool esGusano();
	void imprimirMensaje();
	void incluirEnMundo(b2World* unMundo);
	b2Body* getCuerpo();
	CuerpoGusano* getCuerpoGusano();
	void dibujarConColor(SDL_Renderer* renderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom,
						float offsetX, float offsetY);

	std::string getNombre();
	void setNombre(std::string unNombre);

	void agregarEnPosAleatoria(b2World* unMundo, Tierra* unaTierra, float altoAgua, int xMin, int xMax, int yMin, int yMax,
		float anchoPx, float altoPx);
	bool estaEnMundo();
};

#endif // !_GUSANO_H
