#include "MenuDeArmas.h"

MenuDeArmas::MenuDeArmas(int tamanioX, int tamanioY, SDL_Renderer* unRenderer){
	
	this->rendererDelJuego = unRenderer;
	this->estaActivo = false;
	this->porcentajeDedicadoAArmas = 0.65;
	this->porcentajeDedicadoAUsuario = 0.35;
	this->armaSeleccionada = -1;
	this->surfaceDelMarco = NULL;
	//Creo el surface del menu
    Uint32 rmask, gmask, bmask, amask;

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;

    this->surfaceDelMenu = SDL_CreateRGBSurface(0, tamanioX, tamanioY, 32,
                                   rmask, gmask, bmask, amask);
	this->vectorDeImagenes = new std::vector<SDL_Surface*>();
	this->vectorDeMuniciones = new std::vector<int>(NUMERO_DE_ARMAS);

	
	vectorDeImagenes->push_back(IMG_Load("private/granada.png"));
	vectorDeImagenes->push_back(IMG_Load("private/bazooka.png"));
	vectorDeImagenes->push_back(IMG_Load("private/granadaHoly.png"));
	vectorDeImagenes->push_back(IMG_Load("private/dinamita.png"));

	//el tamanio me da la cantidad de armas
	float cantidadDeArmas = vectorDeImagenes->size();

		//hago un resize de cada imagen
	for (int i = 0; i < cantidadDeArmas; i++){
		float factorX = this->porcentajeDedicadoAArmas*(float)(this->surfaceDelMenu->w) / cantidadDeArmas;
		float factorY = (float)(this->surfaceDelMenu->h);
		factorX = factorX / (float)(vectorDeImagenes->at(i)->w);
		factorY = factorY / (float)(vectorDeImagenes->at(i)->h);
		//agrego las imagenes resizeadas al final de la cola
		//y afuera del for elimino las primeras surface que no sirven mas
		//para esouso la cantidad de armas declarada arriba
		vectorDeImagenes->push_back(zoomSurface(vectorDeImagenes->at(i),factorX,factorY,SMOOTHING_ON));
		SDL_FreeSurface(vectorDeImagenes->at(i));
		
	}

	//elimino los surfaces que no voy a usar mas
	for (int i = 0; i < cantidadDeArmas; i++){
		vectorDeImagenes->erase(vectorDeImagenes->begin());		
	}
	
	
	//hago los blit Surface para cada una de las imagenes

	SDL_Rect rectanguloDestino;
	rectanguloDestino.x = 0;
	rectanguloDestino.y = 0;
	rectanguloDestino.h = 0;
	rectanguloDestino.w = 0;

	for (int i = 0; i < vectorDeImagenes->size(); i++){
		rectanguloDestino.x += rectanguloDestino.w;		
		rectanguloDestino.h = vectorDeImagenes->at(i)->h;
		rectanguloDestino.w = vectorDeImagenes->at(i)->w;
		SDL_BlitSurface(vectorDeImagenes->at(i),NULL,this->surfaceDelMenu,&rectanguloDestino);
				
	}

	this->texturaDelMenu = SDL_CreateTextureFromSurface(this->rendererDelJuego,this->surfaceDelMenu);

	    SDL_Surface* surfaceAuxiliar = IMG_Load("private/marco.png");
		//agrego las imagenes resizeadas al final de la cola
		//y afuera del for elimino las primeras surface que no sirven mas
		//para esouso la cantidad de armas declarada arriba
		float factorX = (float)(this->vectorDeImagenes->at(0)->w) / (float)(surfaceAuxiliar->w);
		float factorY = (float)(this->vectorDeImagenes->at(0)->h) / (float)(surfaceAuxiliar->h);
		this->surfaceDelMarco = zoomSurface(surfaceAuxiliar,factorX,factorY,SMOOTHING_ON);
		
		surfaceAuxiliar = IMG_Load("private/marcoGris.png");
		factorX = (float)(this->vectorDeImagenes->at(0)->w) / (float)(surfaceAuxiliar->w);
		factorY = (float)(this->vectorDeImagenes->at(0)->h) / (float)(surfaceAuxiliar->h);	
		this->surfaceDelMarcoGris = zoomSurface(surfaceAuxiliar,factorX,factorY,SMOOTHING_ON);

	this->textureDelMarco = SDL_CreateTextureFromSurface(this->rendererDelJuego,this->surfaceDelMarco);
	this->textureDelMarcoGris = SDL_CreateTextureFromSurface(this->rendererDelJuego,this->surfaceDelMarcoGris);

}


MenuDeArmas::~MenuDeArmas(){
	delete this->vectorDeMuniciones;
	SDL_DestroyTexture(texturaDelMenu);
	SDL_DestroyTexture(textureDelMarco);
	for (int i = 0; i < this->vectorDeImagenes->size(); i++){
		SDL_FreeSurface(this->vectorDeImagenes->at(i));
	}
	delete this->vectorDeImagenes;
}

void MenuDeArmas::seleccionarArma(int numeroDeArma){
	
	this->armaSeleccionada = numeroDeArma;

}


void MenuDeArmas::mostrarArmaSeleccionada(){
		
		SDL_Rect unRect;
		unRect.x = (this->armaSeleccionada)*this->surfaceDelMarco->w;
		unRect.y = 0;
		unRect.h = this->surfaceDelMarco->h;
		unRect.w = this->surfaceDelMarco->w ;
		
		SDL_RenderCopy(this->rendererDelJuego,this->texturaDelMenu,NULL,&(this->surfaceDelMenu->clip_rect));
	
		if (this->vectorDeMuniciones->at(this->armaSeleccionada) > 0 ){
			SDL_SetClipRect(this->surfaceDelMarco,&unRect); 
			SDL_RenderCopy(this->rendererDelJuego, this->textureDelMarco, NULL, &unRect);
		}else{
			SDL_SetClipRect(this->surfaceDelMarcoGris,&unRect); 
			SDL_RenderCopy(this->rendererDelJuego, this->textureDelMarcoGris, NULL, &unRect);
		}

}

void MenuDeArmas::mostrarMenu(){
		
	if (this->estaActivo){
		if ( (this->armaSeleccionada>=0) && (this->armaSeleccionada < this->vectorDeImagenes->size()) ){
			
			this->mostrarArmaSeleccionada();
			
		}else{
			SDL_RenderCopy(this->rendererDelJuego,this->texturaDelMenu,NULL,&(this->surfaceDelMenu->clip_rect));
	
		}
		
	}

}

int MenuDeArmas::seleccionarArma(float posXMouse, float posYMouse){
	
	if ((this->estaActivo)&&(posYMouse > 0) &&(posYMouse < this->surfaceDelMarco->h)){
		
		int divisionEntera = ((int)(posXMouse)) / (this->surfaceDelMarco->w) + 1;
		
		if ((divisionEntera > 0)&&(divisionEntera <= this->vectorDeImagenes->size())){
			this->armaSeleccionada = divisionEntera - 1;		
		}
		return divisionEntera;
	}
	return -1;

}

bool MenuDeArmas::isActive(){
	return this->estaActivo;
}

std::vector<int>* MenuDeArmas::getVectorDeMuniciones(){
	return this->vectorDeMuniciones;
}

void MenuDeArmas::setActivo(bool activo){
	this->estaActivo = activo;
}