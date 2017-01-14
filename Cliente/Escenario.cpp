
#include "Escenario.h"
std::string imagen = "imagenTierra.png";
std::string pathLog = "log.txt";


void Escenario::inicializarGusanos(){
	Gusano* nuevoGusano;
	std::string nombres[20] = {"El Maestruli","Chewaca","Pikachu","Susano","Hola","Coraje","Goku","Yo","El Gusanito","Iujuuuu",
								"Frodo Bolson","Riquelme","Corneja","Byte","Johnny Bravo","Pepito","Gollum","Semaforo","Ash Ketchup","Gabo"};
	int equipo;
	char e;
	std::string eq = "Equipo ";
	std::string nombre;
	//Creo los gusanos con sus respectivos equipos
	for(int i = 0; i < GUSANOS_POR_EQUIPO * MAX_EQUIPOS_EN_ESCENARIO; i++){
		equipo =((i / GUSANOS_POR_EQUIPO));
		e = (i / GUSANOS_POR_EQUIPO)+ 48;
		//nombre = eq + e; //POR AHORA
		nombre = nombres[i];
		nuevoGusano = new Gusano(nombre, equipo, i);
		nuevoGusano->equipo = equipo;
		nuevoGusano->x = 0;
		nuevoGusano->y = 0;
		this->gusanos->push_back(nuevoGusano);
	}
}


Escenario::Escenario() {
	this->miExplosion = NULL;

	this->manejadorSonido = new Sonido();
	this->alto_px = 0;
	this->ancho_px = 0;
	this->alto_un = 0;
	this->ancho_un = 0;
	this->nivel_agua = 0;
	this->imagen_tierra="";
	this->imagen_cielo="";
	this->objetos = new std::vector<Objeto*>();
	this->gusanos = new std::vector<Gusano*>();
	this->renderer = NULL;
	this->textureDelCielo = NULL;
	this->texturaDeFondo = NULL;
	this->miTierra = NULL;
	this->unaTextura = NULL;
	this->zoom = 1.0f;
	this->idArma = 2;
	this->xMira = -1;
	this->yMira = -1;
	this->equiposPermitidos = MAX_EQUIPOS_EN_ESCENARIO;
	this->equiposEnEscenario = 0;
	this->inicializarGusanos();
	this->radioDeExplosion = 0;
	this->radioDeExplosionAnt = 0;
	this->xDisparo = 0;
	this-> yDisparo = 0;
	this->dibujarBomba = false;
	this->posXExplosionAnt = 0;
	this->posYExplosion = 0;
	this->posXExplosion = 0;
	this->posYExplosionAnt = 0;
	this->turnoDe = 0;
	this->tiempoTurnoRestante = 0;
	this->surfaceTiempo = NULL;
	this->textureTiempo = NULL;
	semaforoRenderer = SDL_CreateSemaphore(1);
}

Escenario::~Escenario() {
	
	for (int i= 0; i < this->objetos->size(); i++){
		delete this->objetos->at(i);
	}
	for (int i= 0; i < this->gusanos->size(); i++){
		delete this->gusanos->at(i);
	}
	delete this->objetos;
	delete this->gusanos;
	delete this->miTierra;
	delete this->miProcesador;
	delete this->manejadorSonido;
	delete this->letra;
	delete this->textoTurnoDe;
	delete this->textureTurnoDe;
}

void Escenario::dibujarObjetos(){
	//para cada objeto, si está activo, lo dibujo
	this->offsetX = recorredorDeImagenes->getRectangulo()->x * ancho_px / recorredorDeImagenes->getAnchoImagen() * recorredorDeImagenes->getZoom();
	this->offsetY = recorredorDeImagenes-> getRectangulo()->y * alto_px / recorredorDeImagenes->getAltoImagen() * recorredorDeImagenes->getZoom();
	float dif = (recorredorDeImagenes->getAltoImagen() - recorredorDeImagenes->getRectangulo()->h);
	for (int i=0; i<this->objetos->size(); i++){
			if(this->objetos->at(i)->enMundo){
				this->objetos->at(i)->dibujarConColor(this->renderer,this->alto_px,this->ancho_px,this->alto_un,this->ancho_un, 
				this->recorredorDeImagenes->getZoom(), offsetX , offsetY);
			}
	}

	for (int i=0; i< this->gusanos->size(); i++){
		if(this->gusanos->at(i)->estaEnMundo()){

			this->gusanos->at(i)->dibujarConColor(this->renderer, this->alto_px, this->ancho_px, this->alto_un, this->ancho_un,
				this->recorredorDeImagenes->getZoom(), offsetX, offsetY);
		}
	}
}	

float Escenario::getZoom(){
	return this->recorredorDeImagenes->getZoom();
}


void Escenario::inicializarRecursosImagenes(){
    
	 if (this->miProcesador != NULL){
        delete this->miProcesador; //posiblemente se haya creado uno antes
     }
   
	 this->miProcesador = new ProcesadorDeTierra(&(this->imagen_tierra), &pathLog, this->alto_px, this->ancho_px, this->alto_px-this->nivel_agua*this->alto_px/this->alto_un);

	 this->recorredorDeImagenes = new RecorredorDeImagenes(miProcesador->getSurfaceDeLaTierra()->w,
	miProcesador->getSurfaceDeLaTierra()->h, this->alto_px, this->ancho_px, this->alto_un, this->ancho_un);
    
	//para dibujar el agua

	this->rectanguloAgua = new SDL_Rect();
	this->rectanguloAgua->h = (2*this->alto_px);
    this->rectanguloAgua->w = this->ancho_px;
    this->rectanguloAgua->x = 0;
    this->rectanguloAgua->y = this->alto_px- this->nivel_agua * (this->alto_px/ this->alto_un);

	this->surfaceDeFondo = IMG_Load("private/agua.png");

	this->surfaceDelCirculo = IMG_Load("private/circulo.png");
	
	SDL_SetSurfaceAlphaMod(surfaceDeFondo,150);
	this->texturaDeFondo = SDL_CreateTextureFromSurface(renderer,surfaceDeFondo);
	
	//para dibujar la tierra
//	SDL_Surface* unSurface = miProcesador->getSurfaceDeLaTierra();	
	this->unaTextura = SDL_CreateTextureFromSurface(renderer, miProcesador->getSurfaceDeLaTierra());
	
	//para dibujar el cielo
	SDL_Surface* surfaceDelCielo = IMG_Load((this->imagen_cielo).c_str());
	
	this->textureDelCielo = SDL_CreateTextureFromSurface(renderer,surfaceDelCielo);
	
	//para dibujar armas

	SDL_Surface* surfMira = IMG_Load("private/mira.png");
	this->texturasDeArmas[0] = SDL_CreateTextureFromSurface(renderer, surfMira);
	SDL_Surface* surfAux1 = IMG_Load("private/granada.png");
	this->texturasDeArmas[1] = SDL_CreateTextureFromSurface(renderer, surfAux1);
	SDL_Surface* surfAux2 = IMG_Load("private/bazooka.png");
	this->texturasDeArmas[2] = SDL_CreateTextureFromSurface(renderer, surfAux2);
	SDL_Surface* surfAux3 = IMG_Load("private/granadaHoly.png");
	this->texturasDeArmas[3] = SDL_CreateTextureFromSurface(renderer, surfAux3);
	SDL_Surface*surfDinamita = IMG_Load("private/dinamita.png");
	this->texturasDeArmas[4] = SDL_CreateTextureFromSurface(renderer, surfDinamita);

	//surface Del Turno
	this->rectanguloTurno.x = this->ancho_px - 200;
	this->rectanguloTurno.y = 10;
	this->rectanguloTurno.h = 50;
	this->rectanguloTurno.w = 50;

	this->letra = TTF_OpenFont("FreeSansBold.ttf", 36);
	SDL_Color color = {0,0,0};
	this->textoTurnoDe = TTF_RenderText_Blended(letra, "Turno del equipo:" , color);
	this->textureTurnoDe = SDL_CreateTextureFromSurface(this->renderer, this->textoTurnoDe);

	this->rectanguloTextoTurnoDe.x = this->ancho_px - 325;
	this->rectanguloTextoTurnoDe.y = 25;
	this->rectanguloTextoTurnoDe.h = 20;
	this->rectanguloTextoTurnoDe.w = 100;

	//Para dibujar el tiempo restante
	this->rectanguloTiempoTurno.x = this->ancho_px - 100;
	this->rectanguloTiempoTurno.y = 10;
	this->rectanguloTiempoTurno.h = 50;
	this->rectanguloTiempoTurno.w = 50;

	for(int i = 0; i < 10; i++){
		this->incrementarZoom();
	}
}

void Escenario::incrementarZoom(){
	this->recorredorDeImagenes->incrementarZoom();
}

void Escenario::decrementarZoom(){
	this->recorredorDeImagenes->decrementarZoom();	
}

void Escenario::desplazarHacia(Direccion unaDireccion){
	this->recorredorDeImagenes->desplazarHacia(unaDireccion);
}

void Escenario::dibujarEscenario(){
	
	//borro pantalla anterior
	SDL_RenderClear(this->renderer);

		
	//dibujo el cielo
	SDL_RenderCopy(this->renderer,this->textureDelCielo,this->recorredorDeImagenes->getRectangulo(),NULL);

	//dibujo la tierra
	SDL_RenderCopy(this->renderer,this->unaTextura,this->recorredorDeImagenes->getRectangulo(),NULL);
	
	if(dibujarBomba){
		
		rectanguloBomba.h = 10.0f * alto_px/alto_un * recorredorDeImagenes->getZoom();
		rectanguloBomba.w = 10.0f * ancho_px/ancho_un *  recorredorDeImagenes->getZoom();
		rectanguloBomba.x = xDisparo *  ancho_px/ancho_un *  recorredorDeImagenes->getZoom() - offsetX - rectanguloBomba.w / 2;
		rectanguloBomba.y = (alto_px - yDisparo * alto_px/alto_un ) *  recorredorDeImagenes->getZoom() - offsetY - rectanguloBomba.h / 2;
		SDL_RenderCopy(renderer, texturasDeArmas[this->idArma],NULL, &rectanguloBomba);

	}

	if( (posXExplosionAnt != posXExplosion) || (posYExplosionAnt != posYExplosion)){
		
		std::cout<< "Pos X Explosion: "<< posXExplosion << std::endl;
		std::cout<< "Pos Y Explosion: "<< posYExplosion << std::endl;
		std::cout<< "Radio Explosion: "<< radioDeExplosion << std::endl;
		
		if(this->miExplosion != NULL) delete this->miExplosion;
		this->miExplosion = new Explosion(this->idArma, this->renderer, this->alto_px, this->ancho_px, this->alto_un, this->ancho_un,this->recorredorDeImagenes->getZoom(), offsetX, offsetY, posXExplosion, posYExplosion);
		
		
		this->recortarImagenEnPosicion(posXExplosion, posYExplosion, radioDeExplosion, semaforoRenderer);
		
		radioDeExplosionAnt = radioDeExplosion;

		posXExplosionAnt = posXExplosion;

		posYExplosionAnt = posYExplosion;

	}

	rectanguloMira.h =10.0f * alto_px/alto_un * recorredorDeImagenes->getZoom();
	rectanguloMira.w = 10.0f * ancho_px/ancho_un *  recorredorDeImagenes->getZoom();
	rectanguloMira.x = xMira *  ancho_px/ancho_un *  recorredorDeImagenes->getZoom() - offsetX - rectanguloMira.w / 2;
	rectanguloMira.y = (alto_px - yMira * alto_px/alto_un ) *  recorredorDeImagenes->getZoom() - offsetY - rectanguloMira.h / 2;
	SDL_SemWait(semaforoRenderer);
	SDL_RenderCopy(renderer, texturasDeArmas[0],NULL, &rectanguloMira);
	SDL_SemPost(semaforoRenderer);
	
	//dibujo los objetos
	SDL_SemWait(semaforoRenderer);
	this->dibujarObjetos();
	SDL_SemPost(semaforoRenderer);

	this->rectanguloAgua->y = (this->alto_px- this->nivel_agua * (this->alto_px/ this->alto_un))* this->recorredorDeImagenes->getZoom() - this->offsetY;
	//dibujo el agua
    SDL_RenderCopy(this->renderer,this->texturaDeFondo,NULL,(this->rectanguloAgua));
	
	//dibujo cuadrado de turno actual
	switch (this->turnoDe){
	case 0:
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
		break;
	case 1:
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 0);
		break;
	case 2:
		SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 0);
		break;
	case 3:
		SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 0);
		break;
	}
	
	SDL_RenderFillRect(this->renderer, &(this->rectanguloTurno));
	SDL_RenderCopy(this->renderer, this->textureTurnoDe, NULL, &(this->rectanguloTextoTurnoDe));

	//Dibujo cronometro de tiempo de turno
	if(this->surfaceTiempo != NULL){
		SDL_FreeSurface(this->surfaceTiempo);
	}

	char tiempo[4] = {'0'};
	_itoa(this->tiempoTurnoRestante, tiempo, 10);

	SDL_Color blanco = {255,255,255};
	SDL_Color negro = {0,0,0};
	this->surfaceTiempo =  TTF_RenderText_Shaded(this->letra, tiempo, blanco, negro);

	if(this->textureTiempo != NULL){
		SDL_DestroyTexture(this->textureTiempo);
	}
	this->textureTiempo = SDL_CreateTextureFromSurface(renderer, this->surfaceTiempo);
	SDL_RenderCopy(renderer, this->textureTiempo, NULL, &rectanguloTiempoTurno);

	if(((this->idArma == 1) || (this->idArma == 3) || (this->idArma == 4)) && (this->tiempoDeVidaArma > 0)){
		//Dibujo cronometro de tiempo de vida de granadas/dinamita
		if(this->surfaceTiempoArma != NULL){
			SDL_FreeSurface(this->surfaceTiempoArma);
		}

		char tiempoArma[4] = {'0'};
		_itoa(this->tiempoDeVidaArma, tiempoArma, 10);

		SDL_Color rojo = {255,0,0};
		this->surfaceTiempoArma =  TTF_RenderText_Blended(this->letra, tiempoArma, rojo);

		if(this->textureTiempoArma != NULL){
			SDL_DestroyTexture(this->textureTiempoArma);
		}
		this->textureTiempoArma = SDL_CreateTextureFromSurface(renderer, this->surfaceTiempoArma);
		
		this->rectanguloTiempoArma.w = 10 * this->ancho_px / this->ancho_un * this->getZoom();
		this->rectanguloTiempoArma.h = 10 * this->alto_px / this->alto_un * this->getZoom();

		this->rectanguloTiempoArma.x = this->xDisparo * this->ancho_px / this->ancho_un * this->getZoom() - this->offsetX - rectanguloTiempoArma.w / 2;
		this->rectanguloTiempoArma.y = (this->alto_px - (this->yDisparo + 10)* this->alto_px / this->alto_un) * this->getZoom() - this->offsetY - rectanguloTiempoArma.h / 2;

		SDL_RenderCopy(renderer, this->textureTiempoArma, NULL, &rectanguloTiempoArma);

	}


	if(this->miExplosion != NULL){
		this->miExplosion->dibujar();
		if(this->miExplosion->terminoAnimacion()){
			delete this->miExplosion;
			this->miExplosion = NULL;
		}
	}

	switch (this->idCliente){
	case 0:
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
		break;
	case 1:
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 0);
		break;
	case 2:
		SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 0);
		break;
	case 3:
		SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 0);
		break;
	}
	
	this->rectanguloIdCliente.w = 50 * this->ancho_px / this->ancho_un ;
	this->rectanguloIdCliente.h = 50 * this->alto_px / this->alto_un ;

	this->rectanguloIdCliente.x = ancho_px - 60;
	this->rectanguloIdCliente.y = alto_px - 60;


	SDL_RenderFillRect(this->renderer, &(this->rectanguloIdCliente));

	//Dibujo Mensaje de equipo ganador
		if(this->equipoGanador != -1){
			if(this->surfaceEquipoGanador != NULL){
				SDL_FreeSurface(this->surfaceEquipoGanador);
			}
			char elGanador[16] =  "¡¡¡¡Ganador!!!!";
			
			SDL_Color unColor;
			switch(this->equipoGanador){
			case 0:
				unColor.r= 0;
				unColor.g= 0;
				unColor.b= 0;
				break;
			case 1:
				unColor.r= 0;
				unColor.g= 0;
				unColor.b= 255;
				break;
			case 2:
				unColor.r= 0;
				unColor.g= 255;
				unColor.b= 0;
				break;
			case 3:
				unColor.r= 255;
				unColor.g= 0;
				unColor.b= 0;
				break;
			}
			this->surfaceEquipoGanador =  TTF_RenderText_Blended(this->letra, elGanador , unColor);

			if(this->textureEquipoGanador != NULL){
				SDL_DestroyTexture(this->textureEquipoGanador);
			}
			this->textureEquipoGanador = SDL_CreateTextureFromSurface(renderer, this->surfaceEquipoGanador);
			
			float escalaX = this->ancho_px / this->ancho_un;
			float escalaY = this->alto_px / this->alto_un;
				
			this->rectanguloEquipoGanador.w = 200 * escalaX * this->getZoom();
			this->rectanguloEquipoGanador.h = 20 * escalaY * this->getZoom();

			this->rectanguloEquipoGanador.x = (this->ancho_un / 2) * escalaX * this->getZoom() - this->offsetX - rectanguloEquipoGanador.w / 2;
			this->rectanguloEquipoGanador.y = (this->alto_px - (this->alto_un / 2 + 20)* escalaY) * this->getZoom() - this->offsetY - rectanguloEquipoGanador.h / 2;

			SDL_RenderCopy(renderer, this->textureEquipoGanador, NULL, &rectanguloEquipoGanador);


		}
}


void Escenario::recortarImagenEnPosicion(float posicionX, float posicionY, float radio, SDL_semaphore* semRenderer){

	//busco la posicion a partir de la cual tengo que recortar el surface del circulo
	//para ello le resto su radio horizontalmente como verticalmente

	posicionX = posicionX * this->miProcesador->getSurfaceDeLaTierra()->w / this->ancho_un;
	posicionY = miProcesador->getSurfaceDeLaTierra()->h - posicionY * this->miProcesador->getSurfaceDeLaTierra()->h / this->alto_un;
	
	if((posicionX > 0) && (posicionY >0)){
		
		int radioX = (int)(radio*this->miProcesador->getSurfaceDeLaTierra()->w / this->ancho_un);
		int radioY = (int)(radio*this->miProcesador->getSurfaceDeLaTierra()->h / this->alto_un);

		int posicionXInicialEnTierra = posicionX - radioX;
		int posicionYInicialEnTierra = posicionY - radioY;
	
		double factorX = radioX*2.0f/this->surfaceDelCirculo->w;
		double factorY = radioY*2.0f/this->surfaceDelCirculo->h;

		//me hace un resize del surface del circulo
		SDL_Surface* surfaceActualDelCirculo =  zoomSurface(surfaceDelCirculo, factorX, factorY,
			SMOOTHING_ON);


		Uint32* pixelActualDelCirculo, *pixelActualDeLaTierra;		

		int limiteSuperiorFilas = 0;
		int limiteSuperiorColumnas = 0;

		//la diferencia es la cantidadDePixeles a Comparar
		int diferencia = this->miProcesador->getSurfaceDeLaTierra()->w - posicionXInicialEnTierra;
	
		if (diferencia > surfaceActualDelCirculo->w){
			limiteSuperiorColumnas = surfaceActualDelCirculo->w;
		}else if (diferencia > 0 ){
			limiteSuperiorColumnas = diferencia;
		}

		diferencia = this->miProcesador->getSurfaceDeLaTierra()->h - posicionYInicialEnTierra;

		if (diferencia > surfaceActualDelCirculo->h){
			limiteSuperiorFilas = surfaceActualDelCirculo->h;
		}else if (diferencia > 0){
			limiteSuperiorFilas = diferencia;		
		}


		SDL_LockSurface(miProcesador->getSurfaceDeLaTierra());
		SDL_LockSurface(surfaceActualDelCirculo);

		//Ahora debo recorrer toods esos pixeles y sacarle toda la transparencia
			for (int i = 0; i < limiteSuperiorFilas ; i++){
		for (int j = 0; j < limiteSuperiorColumnas ; j++){
			pixelActualDelCirculo = (Uint32*)surfaceActualDelCirculo->pixels + i * surfaceActualDelCirculo->w + j;
			if ((miProcesador->getParteAlpha(pixelActualDelCirculo,surfaceActualDelCirculo->format) != 0)&&				
				(posicionXInicialEnTierra + j > 0)&&(posicionYInicialEnTierra + i > 0)){
				pixelActualDeLaTierra = this->miProcesador->getPixelEnLaPosicion(posicionYInicialEnTierra+i,posicionXInicialEnTierra+j);
				//que me importa el color que le pongo..
				miProcesador->setColorRGBAenPixel(pixelActualDeLaTierra,miProcesador->getSurfaceDeLaTierra()->format,
					0,0,0,0);
			}
		}
	}
	



		SDL_UnlockSurface(miProcesador->getSurfaceDeLaTierra());
		SDL_UnlockSurface(surfaceActualDelCirculo);
		if (unaTextura != NULL) SDL_DestroyTexture(unaTextura);
		SDL_SemWait(semRenderer);
		unaTextura = SDL_CreateTextureFromSurface(renderer,miProcesador->getSurfaceDeLaTierra());
		SDL_SemPost(semRenderer);
		//SDL_RenderPresent(renderer);
		SDL_FreeSurface(surfaceActualDelCirculo);
	}
}




void Escenario::resetEquipos(){
	for (int i= 0; i < this->gusanos->size(); i++){
		delete this->gusanos->at(i);
	}
	delete this->gusanos;
	this->equiposEnEscenario = 0;
	this->gusanos = new std::vector<Gusano*>();
	this->inicializarGusanos();
}

void Escenario::playSonido(char serialSonido){
	this->manejadorSonido->dalePlayAlTema((int) serialSonido);
}