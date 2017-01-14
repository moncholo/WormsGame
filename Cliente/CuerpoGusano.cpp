#include "CuerpoGusano.h"

CuerpoGusano::CuerpoGusano(float posX, float posY, float r, float g, float b){
	
	this->cuerpo1 = new PoligonoRegular();
	this->cuerpo1->setNumLados(8);
	this->cuerpo1->escala =1.7f;
	this->cuerpo1->r = r;
	this->cuerpo1->g = g;
	this->cuerpo1->b = b;

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
}

CuerpoGusano::~CuerpoGusano(){
	delete cuerpo1;
}

b2Body* CuerpoGusano::getParte(int parte){
	if(parte == 1) return this->cuerpo1->getCuerpo();
}

void CuerpoGusano::setElegido(bool eleg){
	this->cuerpo1->setElegido(eleg);
}

float CuerpoGusano::getX(){
	return this->cuerpo1->x;
}