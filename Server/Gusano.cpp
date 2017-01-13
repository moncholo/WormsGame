#include "Gusano.h"
#include <random>



Gusano::Gusano(std::string nombreGusano, int equipo, int id){
	this->entroAlAgua = false;
	this->vida = 100;
	this->elegido = false;
	this->miraADerecha = false;
	this->nombre = nombreGusano;
	this->cuerpoGusano = new CuerpoGusano(this->x, this->y, this->r, this->g, this->b);
	this->enMundo = false;
	this->pintarEnColor = true;
	this->idGusano = id;
	this->x = 1000;
	this->y = 1000;

	this->rot = 1;
	this->masa = 100;
	this->estatico = "no";
	this->equipo = equipo;
	this->imagenGusano = NULL;
	
	switch(equipo){
	case 1:
		this->imagenGusano = IMG_Load("private/1.png");
		break;
	case 2:
		this->imagenGusano = IMG_Load("private/2.png");
		break;
	case 3:
		this->imagenGusano = IMG_Load("private/3.png");
		break;
	case 4:
		this->imagenGusano = IMG_Load("private/4.png");
		break;
	default:
		break;
	}
	
}

Gusano::~Gusano(){
	if (this->cuerpoGusano != NULL) delete this->cuerpoGusano;
	if (this->imagenGusano != NULL)delete this->imagenGusano;
	if (this->textureDelGusano != NULL)delete this->textureDelGusano;
}

void Gusano::actualizar(){
	this->enMundo = true;
	this->rot = 1;
	this->masa = 100;
	this->estatico = "no";
	
	switch(equipo){
	case 1:
		this->b = 255;
		break;
	case 2:
		this->g = 255;
		break;
	case 3:
		this->r = 200;
		this->g = 100;
		break;
	case 4:
		this->r = 200;
		this->b = 200;
		break;
	default:
		break;
	}
}

bool Gusano::estaMuerto(float nivelAgua) {

	bool muerto = false;

	if(this->getCuerpoGusano()->getParte(1)){
		float posyGusano = this->getCuerpoGusano()->getParte(1)->GetPosition().y;
		if ((int)vida == 0 || (posyGusano < nivelAgua)) {
		
			this->getCuerpoGusano()->getParte(1)->SetActive(false);
			muerto = true;
		}
	}
	return muerto;
}

bool Gusano::estaApoyado(){
	bool apoyado = false;
	if(this->cuerpoGusano != NULL){
		for( b2ContactEdge* contacto = this->getCuerpo()->GetContactList(); contacto; contacto=contacto->next){
			if( ( this->getCuerpo()->GetFixtureList() == contacto->contact->GetFixtureA()) && (this->getCuerpo()->GetFixtureList()->GetBody()->GetPosition().y 
				> contacto->contact->GetFixtureB()->GetBody()->GetPosition().y) ) {
					apoyado = true;
			}
			if(  (this->getCuerpo()->GetFixtureList() == contacto->contact->GetFixtureB()) && (this->getCuerpo()->GetFixtureList()->GetBody()->GetPosition().y 
				> contacto->contact->GetFixtureA()->GetBody()->GetPosition().y) ){
					apoyado = true;
			}
		}

	}
	return apoyado;

}

/*
bool Gusano::estaApoyado(){
	bool apoyado = false;
	if(this->cuerpoGusano != NULL){
		for(int i=1; i<2; i++){
			for( b2ContactEdge* contacto = this->cuerpoGusano->getParte(i)->GetContactList(); contacto; contacto = contacto->next){
			
					if( ( (this->cuerpoGusano->getParte(i)->GetFixtureList() == contacto->contact->GetFixtureA()) && (this->cuerpoGusano->getParte(i)->GetFixtureList()->GetBody()->GetPosition().y 
						> contacto->contact->GetFixtureB()->GetBody()->GetPosition().y) ) ){
							apoyado = true;
					}
					else if( ( (this->cuerpoGusano->getParte(i)->GetFixtureList() == contacto->contact->GetFixtureB()) && (this->cuerpoGusano->getParte(i)->GetFixtureList()->GetBody()->GetPosition().y 
						> contacto->contact->GetFixtureA()->GetBody()->GetPosition().y) ) ){
							apoyado = true;
					}
			
			}
		}
	}
	return apoyado;
}
*/

void Gusano::moverIzq(){
	if( this->estaApoyado() )  {
		for(int i= 1; i<2; i++){
			this->cuerpoGusano->getParte(i)->SetFixedRotation(false);
			int y = this->cuerpoGusano->getParte(i)->GetLinearVelocity().y;
			this->cuerpoGusano->getParte(i)->SetLinearVelocity(b2Vec2(-5, y));
			this->miraADerecha = false;
			
		}
	}
}

void Gusano::moverDer(){

	if( this->estaApoyado() )  {
		for(int i=1; i<2; i++){
			this->cuerpoGusano->getParte(i)->SetFixedRotation(false);
			int y = this->cuerpoGusano->getParte(i)->GetLinearVelocity().y;
			this->cuerpoGusano->getParte(i)->SetLinearVelocity(b2Vec2(5, y));
			this->miraADerecha = true;		}
	}
}

bool Gusano::saltar(){

	if( this->estaApoyado() ){
		int salto;
		if(this->miraADerecha) {
			salto = 5;
		} else {
			salto = -5;
		}
		for(int i= 1; i<2; i++){
			this->cuerpoGusano->getParte(i)->SetLinearVelocity(b2Vec2(salto, 15));
		}
		return true;
	}
	return false;
}

void Gusano::frenar(){
	this->cuerpoGusano->getParte(1)->SetFixedRotation(true);
	if( this->estaApoyado() ) {
		for(int i=1; i<2; i++){
			this->cuerpoGusano->getParte(i)->SetLinearVelocity(b2Vec2(0,0));
			this->cuerpoGusano->getParte(i)->SetAngularVelocity(0);
		}
		
	}
	
}


void Gusano::dibujarConColor(SDL_Renderer* renderer, float altoVentana, float anchoVentana, float altoMapa, float anchoMapa,
							 float factorDeZoom, float offsetX, float offsetY){

	float escalaX = anchoVentana / anchoMapa ;
	float escalaY = altoVentana / altoMapa;

	if(textureDelGusano == NULL)
		this->textureDelGusano = SDL_CreateTextureFromSurface(renderer, this->imagenGusano);
	SDL_Rect rectangulo;
	rectangulo.h = ALTO_IMAGEN_GUSANO * escalaY * factorDeZoom;
	rectangulo.w = ANCHO_IMAGEN_GUSANO * escalaX * factorDeZoom;
	rectangulo.x = this->x * escalaX * factorDeZoom - offsetX - rectangulo.w / 2;
	rectangulo.y = (altoVentana - this->y * escalaY) * factorDeZoom - offsetY - rectangulo.h / 2;
	SDL_RenderCopy(renderer, textureDelGusano, NULL, &rectangulo);
}

void Gusano::incluirEnMundo(b2World* unMundo){
	this->cuerpoGusano->incluirEnMundo(unMundo);
	this->cuerpoGusano->getParte(1)->SetUserData(this);
}

void Gusano::imprimirMensaje(){
	std::cout << "Soy un gusano" << std::endl;
}

b2Body* Gusano::getCuerpo(){
	return this->cuerpoGusano->getParte(1);
}

CuerpoGusano* Gusano::getCuerpoGusano(){
	return this->cuerpoGusano;
}

bool Gusano::esGusano(){
	return true;
}


void Gusano::setElegido(bool eleg){
	this->elegido = eleg;
	this->cuerpoGusano->setElegido(this->elegido);
}

std::string Gusano::getNombre(){
	return this->nombre;
}

void Gusano::setNombre(std::string unNombre){
	this->nombre = unNombre;
}

int numRandom(int min, int max){
	std::random_device rd;
	return ((rd() % (max-min)) + min);
}

bool nivelAguaMenorATierraEnPos(b2Body* unaCadena, float nivelAgua, int xPos, float escalaX){

	b2ChainShape* cadenaForma = (b2ChainShape*)(unaCadena->GetFixtureList()->GetShape()); //obtengo forma de la tierra
	b2EdgeShape linea;
	
	
	int indiceInicial = (xPos-1) * ((int)(escalaX)); 
	
	if ((indiceInicial < 0) || (indiceInicial >= cadenaForma->GetChildCount())){
		indiceInicial = 0;
	}
	cadenaForma->GetChildEdge(&linea, indiceInicial);
	
	int i = 0;
	cadenaForma->GetChildEdge(&linea, i);
	
	
		while (( linea.m_vertex2.x < xPos )&&(linea.m_vertex1.x > xPos)){
		indiceInicial++;
		i++;
		if (i < cadenaForma->GetChildCount())
			cadenaForma->GetChildEdge(&linea, i);
		}

		float pendiente = (linea.m_vertex2.y - linea.m_vertex1.y) / (linea.m_vertex2.x - linea.m_vertex1.x);
	float alturaRecta = linea.m_vertex1.y + pendiente * (xPos - linea.m_vertex1.x);

	if(alturaRecta < nivelAgua) return false;

	return true;
}


bool nivelAguaMenorAAlgunaTierraEnPos(std::vector<b2Body*>* vectorDeChains, float nivelAgua, int xPos, float escalaX){

	for (int i= 0; i < vectorDeChains->size(); i++){
		if (vectorDeChains->at(i)->IsActive())
			if (nivelAguaMenorATierraEnPos(vectorDeChains->at(i), nivelAgua, xPos, escalaX))
				return true;
	}
	return false;

}

void Gusano::caeDeGranAltura(){
	int velocidad = 0;
	if(this->getCuerpo()&& this->getCuerpo()->GetContactList())
	{
		velocidad = this->getCuerpo()->GetLinearVelocity().Length();
		if(velocidad > 1){
			if(velocidad > 30){
			if(this->vida >= 3)
					this->vida--;
			}
		}
		
	}


}

bool Gusano::solapaConOtroCuerpo(b2World* unMundo){
	//Compruebo solapamiento con otros objetos (y borde de la tierra, que es un objeto)
	b2Shape* miForma = this->getCuerpo()->GetFixtureList()->GetShape();
	for(b2Body* cuerpos = unMundo->GetBodyList(); cuerpos; cuerpos = cuerpos->GetNext() ){
	
		if(cuerpos->IsActive()){
			for(int j = 0; j < cuerpos->GetFixtureList()->GetShape()->GetChildCount(); j++){
				if((this->getCuerpo() != cuerpos) &&(b2TestOverlap(miForma, 0, cuerpos->GetFixtureList()->GetShape(), j,
					this->getCuerpo()->GetTransform(),cuerpos->GetTransform() ) )){
						return true;
				}
			}
		}
	}
	return false;
}


void Gusano::agregarEnPosAleatoria(b2World* unMundo, Tierra* unaTierra, float altoAgua, int xMin, int xMax, int yMin, int yMax,
								   float anchoPx, float altoPx){
	this->y =100;
	this->x = numRandom(xMin, xMax);
	this->incluirEnMundo(unMundo);
	b2Vec2 pos;
  
	bool posValida = false;

	while (!posValida){
		this->x = numRandom(xMin, xMax);
		this->y = yMax;
		while( (!(this->y < altoAgua)) && (!(unaTierra->tienePuntoAdentroDeLaTierra(this->x, this->y))) ){
			this->y -=10;
			pos.Set(this->x, this->y);
			this->getCuerpo()->SetTransform(pos, 0);
		}

		if( (unaTierra->tienePuntoAdentroDeLaTierra(this->x, this->y)) && (!(this->y < altoAgua))){
			this->y +=20;
			pos.Set(this->x, this->y);
			this->getCuerpo()->SetTransform(pos, 0);
			posValida = true;
		
		}
	
	}

	//while ( //(!nivelAguaMenorAAlgunaTierraEnPos(unaTierra->getContorno(), altoAgua, this->x,(anchoPx/xMax))) &&
	//	(!solapaConAlgunaTierra(unaTierra->getContorno(), altoPx, anchoPx, yMax, xMax))){
	//		std::cout << "POS ALEATORIA X: " << this->x << std::endl;
	//		this->x = numRandom(xMin, xMax);
	//		pos.Set(this->x, this->y);
	//		this->getCuerpo()->SetTransform(pos, 0);
 // 	
	//}

	//while( this->solapaConAlgunaTierra(unaTierra->getContorno(), altoPx, anchoPx, yMax, xMax)  || this->solapaConOtroCuerpo(unMundo) ){
	//	this->y += 1;
	//	pos.Set(this->x, this->y);
	//	this->getCuerpo()->SetTransform(pos, 0);
	//}
	this->pintarEnColor = true;
	this->enMundo = true;
}

bool Gusano::estaEnMundo(){
	return this->enMundo;
}