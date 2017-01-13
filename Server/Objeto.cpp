#include "Objeto.h"

//Clase general de los objetos circulo, rectangulo y poligono regular.
Objeto::Objeto() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
	this->elegido = false;
}

Objeto::~Objeto(){
	
}

bool Objeto::solapaConAlgunaTierra(vectorChains* vectorDeChains, int alto_px, int ancho_px, float alto_un, float ancho_un){
	for (unsigned int i=0;i < vectorDeChains->size();i++){
		if (solapaConTierra(vectorDeChains->at(i), alto_px, ancho_px, alto_un, ancho_un)){
			return true;
		}
	}
	return false;
}

void Objeto::dibujarConColor(SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, 
							 float factorDeZoom, float offsetX, float offsetY){
}

void Objeto::incluirEnMundo(b2World* unWorld){
}

void Objeto::imprimirMensaje(){
}

b2Body* Objeto::getCuerpo(){return NULL;}

void Objeto::setElegido(bool eleg){
	this->elegido = eleg;
}


bool Objeto::solapaConTierra(b2Body* contornoTierra, int altoPixelesDeLaImagen, int anchoPixelesDeLaImagen, float altoUnidades, float anchoUnidades){
	
	bool solapa = false;
	b2ChainShape* cadenaForma = (b2ChainShape*)(contornoTierra->GetFixtureList()->GetShape()); //obtengo forma de la tierra
	b2EdgeShape linea; //
	float xCuerpo = this->getCuerpo()->GetWorldCenter().x; //coordenada x del centro de masa del cuerpo

	
	//Itero hasta encontrar la recta exacta
	//cadenaForma->GetChildEdge(&linea, indiceInicial);
	
	int i = 0;
	cadenaForma->GetChildEdge(&linea, i);

	while( (linea.m_vertex2.x < xCuerpo) && (i < cadenaForma->GetChildCount()-1 )){
		i++;
		cadenaForma->GetChildEdge(&linea, i);
	}

	float altura = this->getCuerpo()->GetWorldCenter().y; //altura del centro de masa del cuerpo


	//std::cout << "x: "  << linea.m_vertex1.x << " " << linea.m_vertex2.x << " " << xCuerpo << std::endl;
	//std::cout << "y: " << linea.m_vertex1.y << " " << linea.m_vertex2.y << " " << altura << std::endl;

	if(xCuerpo = linea.m_vertex2.x){
		if (linea.m_vertex2.y >= altura) solapa = true; //si las alturas coinciden, se solapan
	}
	else{ 
		//calculo la altura de la recta en el x del centro de masa del cuerpo
		float pendiente = (linea.m_vertex2.y - linea.m_vertex1.y) / (linea.m_vertex2.x - linea.m_vertex1.x);
		float alturaRecta = linea.m_vertex1.y + pendiente * (xCuerpo - linea.m_vertex1.x);
		if (alturaRecta >= altura)
			solapa = true;
	}
	return solapa;
}