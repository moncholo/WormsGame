#ifndef _GUSANO_H
#define _GUSANO_H

#include "Box2D\Box2D.h"
#include "Objeto.h"
#include "CuerpoGusano.h"
#include "Tierra.h"
#include "SDL_image.h"
#include "Constantes.h"


class Gusano : public Objeto{

private:
	CuerpoGusano* cuerpoGusano;
	

	short* calcularVerticesY( float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom);
	short* calcularVerticesX( float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom);
	float* verticesX, *verticesY;
	std::string nombre;

	bool solapaConOtroCuerpo(b2World* unMundo);

public:

	bool entroAlAgua;

	char vida;
	SDL_Surface* imagenGusano;
	SDL_Texture *textureDelGusano;
	int idGusano;
	bool pintarEnColor;
	bool enMundo;
	int equipo;
	bool miraADerecha;

	Gusano(std::string nombreGusano, int equipo, int id);
	~Gusano();
	bool estaApoyado();
	void moverIzq();
	void moverDer();
	bool saltar();
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
	bool estaMuerto(float nivelAgua);
	void caeDeGranAltura();
};

#endif // !_GUSANO_H
