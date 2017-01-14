#include "PoligonoRegular.h"
#include <math.h>

PoligonoRegular::PoligonoRegular (){
	this->cuerpoDelPoligono = NULL;
	this->verticesX = NULL;
	this->verticesY = NULL;
}

PoligonoRegular::PoligonoRegular(int numLados) {
	}

PoligonoRegular::~PoligonoRegular(){
	
	delete[] verticesX;
	delete[] verticesY;
}

short* PoligonoRegular::calcularVerticesX(float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom,
										  float offsetX, float offsetY){
		

		float escalaX = anchoVentana/anchoMapa ;


		short* vectorADevolver = new short[this->numeroDeLados];

		//b2PolygonShape* polyDef =(b2PolygonShape*) this->cuerpoDelPoligono->GetFixtureList()->GetShape();

		float posX = this->x;
		for( int i = 0; i < this->numeroDeLados; i++ ){
			float x = verticesX[i];
			float valorX = posX - x;
			valorX = (-1)* (valorX) * escalaX * factorDeZoom;
			valorX += (this->x * escalaX * factorDeZoom);
			valorX -= offsetX;
			vectorADevolver[i] = (short)valorX;
		}

	return vectorADevolver;
	

}

bool PoligonoRegular::esGusano(){
	return false;
}

short* PoligonoRegular::calcularVerticesY( float altoVentana, float anchoVentana, float altoMapa, float anchoMapa, float factorDeZoom,
										  float offsetX, float offsetY){
	
	float escalaY = altoVentana/altoMapa;

	short* vectorADevolver = new short[this->numeroDeLados];
	float posY = this->y;

	for (int i=0; i<this->numeroDeLados; i++){
		float y = this->verticesY[i];
		float valY = (posY - y);
		valY = (altoVentana - (posY - valY) * escalaY) * factorDeZoom - offsetY;
		vectorADevolver[i] = (short) (valY);
	}

	return vectorADevolver;
}


void PoligonoRegular::dibujarConColor(SDL_Renderer* renderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa,
									  float factorDeZoom, float offsetX, float offsetY){
	
	this->calcularVertices();
	
	short* vertX = this->calcularVerticesX(altoVentana, anchoVentana, altoMapa, anchoMapa, factorDeZoom, offsetX, offsetY);
	short* vertY = this->calcularVerticesY(altoVentana, anchoVentana, altoMapa, anchoMapa, factorDeZoom, offsetX, offsetY);
	filledPolygonRGBA(renderer, vertX,vertY,this->numeroDeLados,this->r,this->g,this->b,this->a);
	if(this->elegido == true){
		polygonRGBA(renderer, vertX,vertY,this->numeroDeLados,255, 0, 0, 255);
	}

	//A liberar memoria ..
	delete[] vertX;
	delete[] vertY;
}

//Override
void PoligonoRegular::imprimirMensaje(){
	std::cout << "Es un Poligono " << std::endl;
}

void PoligonoRegular::calcularVertices(){
	
	if(verticesX == NULL){
		this->verticesX = new float[this->numeroDeLados];
		this->verticesY = new float[this->numeroDeLados];
	}
	float incrementador = M_PI*2 / this->numeroDeLados;
	float angulo = M_PI/4.0f + this->rot;
	float mod = this->escala; //tamaño del semi eje, dependera del factor de escala
	//b2Vec2* vertices = new b2Vec2[this->numeroDeLados];
	
	/*Geometria Pura*/
		for (int j=0; j< this->numeroDeLados; j++){
			float x = cos(angulo)*mod + this->x;
			float y = sin(angulo)*mod + this->y;
			angulo = angulo + incrementador;
			//vertices[j].Set(x,y);
			this->verticesX[j] = x;
			this->verticesY[j] = y;
		}

}

void PoligonoRegular::incluirEnMundo(b2World* unMundo){
	
	this->verticesX = new float[this->numeroDeLados];
	this->verticesY = new float[this->numeroDeLados];
	b2BodyDef definicionDelPoligono;
	
	if (!strcmp(this->estatico.c_str(), "si")){
		definicionDelPoligono.type = b2_staticBody;
	}else{
		definicionDelPoligono.type = b2_dynamicBody;
	}
	
	definicionDelPoligono.position.Set(this->x,this->y);
	definicionDelPoligono.bullet = true;
	this->cuerpoDelPoligono = unMundo->CreateBody(&definicionDelPoligono);
	
	b2PolygonShape polyDef;
	
	float incrementador = M_PI*2 / this->numeroDeLados;
	float angulo = M_PI/4;
	float mod = this->escala; //tamaño del semi eje, dependera del factor de escala
	b2Vec2* vertices = new b2Vec2[this->numeroDeLados];
	
	/*Geometria Pura*/
		for (int j=0; j< this->numeroDeLados; j++){
			float x = cos(angulo)*mod; 
			float y = sin(angulo)*mod;
			angulo = angulo + incrementador;
			vertices[j].Set(x,y);
			this->verticesX[j] = x;
			this->verticesY[j] = y;
			}

	
	polyDef.Set(vertices,this->numeroDeLados);
	
	b2FixtureDef unFixture;
	unFixture.shape = &polyDef;
	unFixture.density = DENSIDAD_OBJETOS;
	unFixture.friction = FRICCION_OBJETOS;
	unFixture.restitution = REBOTE_OBJETOS;
	this->cuerpoDelPoligono->CreateFixture(&unFixture);
	this->cuerpoDelPoligono->SetUserData(this);
}

b2Body* PoligonoRegular::getCuerpo(){
	return this->cuerpoDelPoligono;
}

void PoligonoRegular::setPosX(float posX){
	this->x = posX;
}

void PoligonoRegular::setPosY(float posY){
	this->y = posY;
}

void PoligonoRegular::setEscala(float esc){
	this->escala = esc;
}

void PoligonoRegular::setNumLados(int numLados){
	this->numeroDeLados = numLados;
}