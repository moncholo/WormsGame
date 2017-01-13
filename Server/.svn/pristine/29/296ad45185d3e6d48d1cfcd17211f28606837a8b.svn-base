#ifndef _TIERRA_H_
#define _TIERRA_H_

#include "ProcesadorDeGeometrias.h"
#include "Constantes.h"

class Tierra{
private:

	ProcesadorDeGeometrias* procesadorDeGeometrias;
	
	vectorChains* vectorDeChains;
	
	b2Body* contornoTierra;
	
	vectorPoligonos* vectorDePoligonos;

	polygon poligonoCircular;

	void crearGeometriaDelCirculo();

public:
	
	Tierra(std::queue<float>* listaPuntos, int altoPixelesDeLaImagen, int anchoPixelesDeLaImagen,
				float altoUnidades, float anchoUnidades, b2World* mundo);

	vectorChains* getContorno();

	void dibujar(SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa);


	//se le pasa la de box2d, no seas boludo..
	void explotarTierraEnPosicion(float posicionX, float posicionY, int radioArma);

	void pasarPoligonosAChains(b2World* mundo);

	bool tienePuntoAdentroDeLaTierra(double x, double y);

};


#endif