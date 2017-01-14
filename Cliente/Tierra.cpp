#include "Tierra.h"
#include <iostream>

void Tierra::setContorno(b2Body *contorno){
	this->contornoTierra = contorno;
}

b2Body* Tierra::getContorno(){
	return this->contornoTierra;
}

//Crea el contorno de la tierra y ya lo agrega al mundo que se le pasa por parámetro
Tierra::Tierra(std::queue<float>* listaPuntos, int altoPixelesDeLaImagen, int anchoPixelesDeLaImagen,
				float altoUnidades, float anchoUnidades, b2World* mundo){
	
	//definiciones para tierra en Box2d
	b2BodyDef contornoDef;
	contornoDef.type = b2_staticBody;
	this->contornoTierra = mundo->CreateBody(&contornoDef);

	//Hago el escalamiento de coordenadas mientras almaceno las cosas en un vector
	int cantidadDePuntos = listaPuntos->size();
	b2Vec2 puntos[MAX_PIXELES_IMAGEN_TIERRA];

	//primer punto bien abajo, para cerrar dsp la cadena de puntos
	puntos[0].Set(0, -1 * (altoUnidades+50));

	if ((cantidadDePuntos) < MAX_PIXELES_IMAGEN_TIERRA){
		for(float i = 1; i <= cantidadDePuntos; i++){
			double x = (i -1) * (anchoUnidades  / anchoPixelesDeLaImagen) ;
			double y = listaPuntos->front() * (altoUnidades/ altoPixelesDeLaImagen) ;
			if( y == 0){
				puntos[(int)i].Set(x,  -(altoUnidades));
			}
			else{
				puntos[(int)i].Set(x, y); //escalo las coordenadas y las almaceno en un vector
			}
			listaPuntos->pop();
			
		}
		
		//ultimo punto bien abajo, para cerrar la cadena de puntos
		puntos[cantidadDePuntos+1].Set(cantidadDePuntos* (anchoUnidades  / anchoPixelesDeLaImagen) , -(altoUnidades+50));

	}

	//creo la forma de la cadena, para colisiones en Box2D
	b2ChainShape cadenaForma;
	cadenaForma.CreateLoop(puntos, (cantidadDePuntos) +2);
	this->contornoTierra->CreateFixture(&cadenaForma, 0.0f);

	// escribir su imagen es demasiado grande si es mayor al maximo, en el log	
}


//dibuja el contorno de la tierra. usado para pruebas
void Tierra::dibujar(SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa){
	float escalaX = anchoVentana / anchoMapa;
	float escalaY = altoVentana / altoMapa;
	
	b2Fixture *fixture = this->contornoTierra->GetFixtureList();

	
	b2ChainShape *cadenaForma = (b2ChainShape*)fixture->GetShape();
	b2EdgeShape linea;
	SDL_SetRenderDrawColor(unRenderer, 0, 0, 0, 255);

	for(int i=0; i < cadenaForma->GetChildCount(); i++){
		cadenaForma->GetChildEdge(&linea, i);
		SDL_RenderDrawLine(unRenderer,(escalaX) * ((&linea)->m_vertex1.x), altoVentana - (escalaY)*(&linea)->m_vertex1.y, 
			(escalaX)*((&linea)->m_vertex2.x),  altoVentana - (escalaY)*(&linea)->m_vertex2.y);
	}
}