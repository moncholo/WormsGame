#include "Rectangulo.h"

Rectangulo::Rectangulo(){
	//por ahora nada
}

Rectangulo::Rectangulo(float x, float y, float ancho, float alto){//, float factorDeEscalaX, float factorDeEscalaY){
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
	//this->factorDeEscalaX = factorDeEscalaX;
	//this->factorDeEscalaY = factorDeEscalaY;
}

//Override
void Rectangulo::imprimirMensaje(){
	std::cout << "Es un Rectangulo " << std::endl;
}

bool Rectangulo::esGusano(){
	return false;
}

void Rectangulo::dibujarConColor(SDL_Renderer* unRenderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa,
								 float factorDeZoom, float offsetX, float offsetY){
	float escalaX = anchoVentana / anchoMapa;
	float escalaY = altoVentana / altoMapa;

	short *xVert = new short[4];
	short *yVert = new short[4];
	

	b2PolygonShape* polyDef =(b2PolygonShape*) this->cuerpoDelRectangulo->GetFixtureList()->GetShape();
		
	float posX= this->cuerpoDelRectangulo->GetPosition().x;
	for (int i=0; i<4; i++){
		b2Vec2 p0 = this->cuerpoDelRectangulo->GetWorldPoint(  polyDef->GetVertex( i ) );
		float valorDeX = (-1) *(posX - p0.x);
		valorDeX = ( valorDeX * factorDeZoom * escalaX);
		valorDeX += (this->cuerpoDelRectangulo->GetPosition().x * escalaX * factorDeZoom);
		valorDeX -= offsetX;
		xVert[i] =(short)(valorDeX) ;
	}

	float posY = this->cuerpoDelRectangulo->GetPosition().y;
	for (int i=0; i<4; i++){
		b2Vec2 p0 = this->cuerpoDelRectangulo->GetWorldPoint(  polyDef->GetVertex( i ) );
		float valorDeY = (posY - p0.y);
		valorDeY = (altoVentana - (posY - valorDeY) * escalaY) * factorDeZoom - offsetY;
		yVert[i] = (short) (valorDeY);
	}

			b2Vec2 p0 = this->cuerpoDelRectangulo->GetWorldPoint(  polyDef->GetVertex( 0 ) );

	
     filledPolygonRGBA(unRenderer,xVert,yVert, 4, this->r,this->g, this->b, 255);
	 //el cuatro es porques es un poligono de 4 lados, ojo!!!
	 if(this->elegido == true){
		 polygonRGBA(unRenderer, xVert, yVert, 4, 255, 0, 0, 255);
	 }

	delete[] xVert;
	delete[] yVert;
}

void Rectangulo::incluirEnMundo(b2World* unMundo){
	//Definicion del rectangulo
	b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(this->x, this->y); //set the starting position
    myBodyDef.angle = (float32)(this->rot*M_PI/180.0f);               
	myBodyDef.bullet = true;
	if (!strcmp(this->estatico.c_str(), "si")) { //Da cero si son iguales, por eso pongo el negador
		myBodyDef.type = b2_staticBody;
	}else {
		myBodyDef.type = b2_dynamicBody;			
	}        
    this->cuerpoDelRectangulo = unMundo->CreateBody(&myBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox((this->ancho)/2, (this->alto)/2);
 
                
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = DENSIDAD_OBJETOS;
	boxFixtureDef.friction = FRICCION_OBJETOS;
	boxFixtureDef.restitution = REBOTE_OBJETOS;
    this->cuerpoDelRectangulo->CreateFixture(&boxFixtureDef);
	this->cuerpoDelRectangulo->SetUserData(this);	
}

b2Body* Rectangulo::getCuerpo(){
	return this->cuerpoDelRectangulo;
}

Rectangulo::~Rectangulo(){
	//Implementar
}