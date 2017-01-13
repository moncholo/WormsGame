#include "CuerpoGusano.h"


CuerpoGusano::CuerpoGusano(float posX, float posY, int r, int g, int b){
	
	this->cuerpo1 = new PoligonoRegular();
	this->cuerpo1->setNumLados(8);
	this->cuerpo1->escala = TAMANO_GUSANO_EN_MUNDO;
	this->cuerpo1->r = r;
	this->cuerpo1->g = g;
	this->cuerpo1->b = b;
	//this->cuerpo1->actualizar();

	cuerpo1->x = posX;
	cuerpo1->y = posY;

}

void CuerpoGusano::incluirEnMundo(b2World* unMundo){
	this->cuerpo1->incluirEnMundo(unMundo);
	this->cuerpo1->getCuerpo()->SetFixedRotation(true);
}

void CuerpoGusano::dibujar(SDL_Renderer* renderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa,
							 float factorDeZoom, float offsetX, float offsetY){
	this->cuerpo1->dibujarConColor(renderer, altoVentana, anchoVentana, altoMapa, anchoMapa, factorDeZoom, offsetX, offsetY);
	//this->cuerpo2->dibujarConColor(renderer, altoVentana, anchoVentana, altoMapa, anchoMapa, factorDeZoom);
	//this->cabeza->dibujarConColor(renderer, altoVentana, anchoVentana, altoMapa, anchoMapa, factorDeZoom);
}

CuerpoGusano::~CuerpoGusano(){
	delete cuerpo1;
	//delete cuerpo2;
	//delete cabeza;
}

b2Body* CuerpoGusano::getParte(int parte){
	if(parte == 1) return this->cuerpo1->getCuerpo();
	return NULL;
	//if(parte == 2) return this->cuerpo2->getCuerpo();
	//if(parte == 3) return this->cabeza->getCuerpo();
}

void CuerpoGusano::setElegido(bool eleg){
	this->cuerpo1->setElegido(eleg);
}