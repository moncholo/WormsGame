#include "Gusano.h"
#include <random>

Gusano::Gusano(std::string nombreGusano, int equipo, int id){
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
	this->imagenGusanoIzq = NULL;
	this->imagenGusanoDer = NULL;
	this->textureDelGusanoDer = NULL;
	this->textureDelGusanoIzq = NULL;
	this->surfaceNombre = NULL;
	this->textureNombre = NULL;
	this->surfaceVida = NULL;
	this->textureVida = NULL;

	this->imagenGusanoGrisDer = IMG_Load("private/grisBis.png");
	this->imagenGusanoGrisIzq = IMG_Load("private/gris.png");

	this->imagenGusanoMuerto = IMG_Load("private/rip2.png");
	this->textureDelGusanoMuerto = NULL;
	vivo = true;
	
	switch(equipo){
	case 0:
		this->imagenGusanoIzq = IMG_Load("private/1.png");
		this->imagenGusanoDer = IMG_Load("private/1bis.png");
		this->r = 0;
		this->g = 0;
		this->b = 0;
		break;
	case 1:
		this->imagenGusanoIzq = IMG_Load("private/2.png");
		this->imagenGusanoDer = IMG_Load("private/2bis.png");
		this->r = 0;
		this->g = 0;
		this->b = 255;
		break;
	case 2:
		this->imagenGusanoIzq = IMG_Load("private/3.png");
		this->imagenGusanoDer = IMG_Load("private/3bis.png");
		this->r = 0;
		this->g = 255;
		this->b = 0;
		break;
	case 3:
		this->imagenGusanoIzq = IMG_Load("private/4.png");
		this->imagenGusanoDer = IMG_Load("private/4bis.png");
		this->r = 255;
		this->g = 0;
		this->b = 0;
		break;
	default:
		break;
	}

	this->letraGusano = TTF_OpenFont("FreeSansBold.ttf", 36);
	if (this->letraGusano == NULL){
		std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}

	//COLOR PARA LA LETRA
	int r = this->r;
	int g = this->g;
	int b = this->b;
	SDL_Color bg_color = {r, g, b};
	SDL_Color negro = {0,0,0};
	this->surfaceNombre = TTF_RenderText_Blended(this->letraGusano, this->getNombre().c_str() , bg_color);

	
}

void Gusano::estaMuerto(float nivelAgua) {
	if ((int)vida == 0 || (this->y < nivelAgua)) {
		if (this->elegido) elegido = false;
		vivo = false;
	}
	else{
		vivo = true;
	}
}

Gusano::~Gusano(){
	if (this->cuerpoGusano != NULL) delete this->cuerpoGusano;
	if (this->imagenGusanoIzq != NULL)delete this->imagenGusanoIzq;
	if (this->imagenGusanoDer != NULL)delete this->imagenGusanoDer;
	if (this->textureDelGusanoIzq != NULL)delete this->textureDelGusanoIzq;
	if (this->textureDelGusanoDer != NULL)delete this->textureDelGusanoDer;
	if (this->textureNombre != NULL)delete this->textureNombre;
	if (this->surfaceNombre != NULL)delete this->surfaceNombre;
	if (this->letraGusano != NULL)delete this->letraGusano;
	if (this->imagenGusanoGrisDer != NULL)delete this->imagenGusanoGrisDer;
	if (this->imagenGusanoGrisIzq != NULL)delete this->imagenGusanoGrisIzq;
	if (this->textureGusanoGrisDer != NULL)delete this->textureGusanoGrisDer;
	if (this->textureGusanoGrisIzq != NULL)delete this->textureGusanoGrisIzq;
	if (this->textureArmaDer != NULL)delete this->textureArmaDer;
	if (this->textureArmaIzq != NULL)delete this->textureArmaIzq;
}

void Gusano::actualizar(){
	this->enMundo = true;
	this->rot = 1;
	this->masa = 100;
	this->estatico = "no";
	
	switch(equipo){
	case 0:
		this->imagenGusanoIzq = IMG_Load("private/1.png");
		this->imagenGusanoDer = IMG_Load("private/1bis.png");
		this->r = 255;
		this->g = 255;
		this->b = 255;
		break;
	case 1:
		this->imagenGusanoIzq = IMG_Load("private/2.png");
		this->imagenGusanoDer = IMG_Load("private/2bis.png");
		this->r = 0;
		this->g = 0;
		this->b = 255;
		break;
	case 2:
		this->imagenGusanoIzq = IMG_Load("private/3.png");
		this->imagenGusanoDer = IMG_Load("private/3bis.png");
		this->r = 0;
		this->g = 255;
		this->b = 0;
		break;
	case 3:
		this->imagenGusanoIzq = IMG_Load("private/4.png");
		this->imagenGusanoDer = IMG_Load("private/4bis.png");
		this->r = 255;
		this->g = 0;
		this->b = 0;
		break;
	default:
		break;
	}
}

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

void Gusano::saltar(){

	if( this->estaApoyado() ){
		int salto;
		if(this->miraADerecha) {
			salto = 3;
		} else {
			salto = -3;
		}
		for(int i= 1; i<2; i++){
			this->cuerpoGusano->getParte(i)->SetLinearVelocity(b2Vec2(salto, 10));
		}
	}
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
	SDL_Texture* aDibujar = NULL;

	if(this->vivo){
		if (this->pintarEnColor) {
			if(this->miraADerecha == true){
				if(this->textureDelGusanoDer == NULL){
					this->textureDelGusanoDer = SDL_CreateTextureFromSurface(renderer, this->imagenGusanoDer);
				}
				aDibujar = this->textureDelGusanoDer;
			}
			else{
				if(this->textureDelGusanoIzq == NULL){
					this->textureDelGusanoIzq = SDL_CreateTextureFromSurface(renderer, this->imagenGusanoIzq);
				}
				aDibujar = this->textureDelGusanoIzq;
			}
		} else {
			if(this->miraADerecha == true){
				if(this->textureGusanoGrisDer == NULL){
					this->textureGusanoGrisDer = SDL_CreateTextureFromSurface(renderer, this->imagenGusanoGrisDer);
				}
				aDibujar = this->textureGusanoGrisDer;
			}else{
				if(this->textureGusanoGrisIzq == NULL){
					this->textureGusanoGrisIzq = SDL_CreateTextureFromSurface(renderer, this->imagenGusanoGrisIzq);
				}
				aDibujar = this->textureGusanoGrisIzq;
			}
		}

		//DIBUJO DE LA VIDA
		if(this->surfaceVida != NULL){
			SDL_FreeSurface(this->surfaceVida);
		}
		int r = this->r;
		int g = this->g;
		int b = this->b;

		SDL_Rect rectanguloVida;

		rectanguloVida.h = 10 * escalaY * factorDeZoom;
		rectanguloVida.w = 20 * escalaX * factorDeZoom;
		rectanguloVida.x = this->x * escalaX * factorDeZoom - offsetX - rectanguloVida.w / 2;
		rectanguloVida.y = (altoVentana - this->y * escalaY) * factorDeZoom - offsetY - rectanguloVida.h / 2 - 20 * factorDeZoom;

		SDL_Color bg_color = {r, g, b};
		SDL_Color negro = {0,0,0};
		char vida[4] = { '0'};

		_itoa(this->vida, vida, 10);
		//std::cout << vida << std::endl;
		this->surfaceVida = TTF_RenderText_Blended(this->letraGusano, vida, bg_color); //TTF_RenderText_Blended(this->letraGusano, vida, bg_color);
		
		if(this->textureVida != NULL){
			SDL_DestroyTexture(this->textureVida);
		}
		this->textureVida = SDL_CreateTextureFromSurface(renderer, this->surfaceVida);

		rectanguloVida.y = (altoVentana - this->y * escalaY) * factorDeZoom - offsetY - rectanguloVida.h / 2 - 30 * factorDeZoom;
		SDL_RenderCopy(renderer, this->textureVida, NULL, &rectanguloVida);

		if(this->elegido){

		SDL_Rect rectanguloNombre;
		rectanguloNombre.h = 10 * escalaY * factorDeZoom;
		rectanguloNombre.w = 20 * escalaX * factorDeZoom;
		rectanguloNombre.x = this->x * escalaX * factorDeZoom - offsetX - rectanguloNombre.w / 2;
		rectanguloNombre.y = (altoVentana - this->y * escalaY) * factorDeZoom - offsetY - rectanguloNombre.h / 2 - 20 * factorDeZoom;
		
		SDL_Rect rectanguloArma;
		rectanguloArma.h = ALTO_IMAGEN_GUSANO * escalaY * factorDeZoom;
		rectanguloArma.w = ANCHO_IMAGEN_GUSANO * escalaX * factorDeZoom;
		rectanguloArma.x = this->x * escalaX * factorDeZoom - offsetX - rectanguloArma.w / 2;
		rectanguloArma.y = (altoVentana - this->y * escalaY) * factorDeZoom - offsetY - rectanguloArma.h / 2;
		if(this->textureNombre == NULL){
			this->textureNombre = SDL_CreateTextureFromSurface(renderer, this->surfaceNombre);
		}
		SDL_RenderCopy(renderer, this->textureNombre, NULL, &rectanguloNombre);

		if (this->textureArmaDer == NULL){
			SDL_Surface* surfaceArma = IMG_Load("private/armaBazooka.png");
			this->textureArmaDer = SDL_CreateTextureFromSurface(renderer,surfaceArma);
		}

		if (this->textureArmaIzq == NULL){
			SDL_Surface* surfaceArma = IMG_Load("private/armaBazookaBis.png");
			this->textureArmaIzq = SDL_CreateTextureFromSurface(renderer,surfaceArma);		
		}
		if (this->miraADerecha){
			SDL_RenderCopy(renderer,this->textureArmaDer, NULL, &rectanguloArma);
		}else{
			SDL_RenderCopy(renderer,this->textureArmaIzq, NULL, &rectanguloArma);
		}
		
	
	}

	} else{
		if(this->textureDelGusanoMuerto == NULL){
				this->textureDelGusanoMuerto = SDL_CreateTextureFromSurface(renderer, this->imagenGusanoMuerto);
			}
			aDibujar = this->textureDelGusanoMuerto;
		}
	
	SDL_Rect rectangulo;
	rectangulo.h = ALTO_IMAGEN_GUSANO * escalaY * factorDeZoom;
	rectangulo.w = ANCHO_IMAGEN_GUSANO * escalaX * factorDeZoom;
	rectangulo.x = this->x * escalaX * factorDeZoom - offsetX - rectangulo.w / 2;
	rectangulo.y = (altoVentana - this->y * escalaY) * factorDeZoom - offsetY - rectangulo.h / 2;
	SDL_RenderCopy(renderer, aDibujar, NULL, &rectangulo);

	if(this->elegido){

		SDL_Rect rectanguloNombre;
		rectanguloNombre.h = 10 * escalaY * factorDeZoom;
		rectanguloNombre.w = 20 * escalaX * factorDeZoom;
		rectanguloNombre.x = this->x * escalaX * factorDeZoom - offsetX - rectanguloNombre.w / 2;
		rectanguloNombre.y = (altoVentana - this->y * escalaY) * factorDeZoom - offsetY - rectanguloNombre.h / 2 - 20 * factorDeZoom;
		
		if(this->textureNombre == NULL){
			this->textureNombre = SDL_CreateTextureFromSurface(renderer, this->surfaceNombre);
		}
		SDL_RenderCopy(renderer, this->textureNombre, NULL, &rectanguloNombre);

		if (this->textureArmaDer == NULL){
			SDL_Surface* surfaceArma = IMG_Load("private/armaBazooka.png");
			this->textureArmaDer = SDL_CreateTextureFromSurface(renderer,surfaceArma);
		}

		if (this->textureArmaIzq == NULL){
			SDL_Surface* surfaceArma = IMG_Load("private/armaBazookaBis.png");
			this->textureArmaIzq = SDL_CreateTextureFromSurface(renderer,surfaceArma);		
		}
		if (this->miraADerecha){
			SDL_RenderCopy(renderer,this->textureArmaDer, NULL, &rectangulo);
		}else{
			SDL_RenderCopy(renderer,this->textureArmaIzq, NULL, &rectangulo);
		}
		
	}
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
	return ((rd() % max) + min);
}

bool nivelAguaMenorATierraEnPos(Tierra* unaTierra, float nivelAgua, int xPos, float escalaX){
	b2ChainShape* cadenaForma = (b2ChainShape*)(unaTierra->getContorno()->GetFixtureList()->GetShape()); //obtengo forma de la tierra
	b2EdgeShape linea;
	int indiceInicial = (xPos-1) * ((int)(escalaX)); 
	if ((indiceInicial < 0) || (indiceInicial >= cadenaForma->GetChildCount())){
		indiceInicial = 0;
	}
	cadenaForma->GetChildEdge(&linea, indiceInicial);
	
	int i = 0;
	cadenaForma->GetChildEdge(&linea, i);
	while( linea.m_vertex2.x < xPos ){
		indiceInicial++;
		i++;
		cadenaForma->GetChildEdge(&linea, i);
	}
	float pendiente = (linea.m_vertex2.y - linea.m_vertex1.y) / (linea.m_vertex2.x - linea.m_vertex1.x);
	float alturaRecta = linea.m_vertex1.y + pendiente * (xPos - linea.m_vertex1.x);

	if(alturaRecta < nivelAgua) return false;

	return true;
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
	this->y = yMin;
	this->x = numRandom(xMin, xMax);
	this->incluirEnMundo(unMundo);
	b2Vec2 pos;

	while( !nivelAguaMenorATierraEnPos(unaTierra, altoAgua, this->x,(anchoPx/xMax)) 
		|| !this->solapaConTierra(unaTierra->getContorno(), altoPx, anchoPx, yMax, xMax) ){
			this->x = numRandom(xMin, xMax);
			pos.Set(this->x, this->y);
			this->getCuerpo()->SetTransform(pos, 0);
	}

	while( this->solapaConTierra(unaTierra->getContorno(), altoPx, anchoPx, yMax, xMax)  || this->solapaConOtroCuerpo(unMundo) ){
		this->y += 1;
		pos.Set(this->x, this->y);
		this->getCuerpo()->SetTransform(pos, 0);
	}
	this->enMundo = true;
	
}

bool Gusano::estaEnMundo(){
	return this->enMundo;
}