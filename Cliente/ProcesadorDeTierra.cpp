#include "ProcesadorDeTierra.h"
#include <iostream>
#include "Log.h"

Uint32* ProcesadorDeTierra::getPixelEnLaPosicion(int fila, int columna){
	Uint32 *primerPixel, *pixelFinal;
	//SDL_LockSurface(this->superficie);
	primerPixel = (Uint32*)this->superficie->pixels;
	//SDL_UnlockSurface(this->superficie);
		
	//TODO chequear+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	pixelFinal = primerPixel + (fila * superficie->w + columna);
		
	return pixelFinal;
}


Uint8 ProcesadorDeTierra::getParteRojo(Uint32* elPixel, SDL_PixelFormat *formato){
	Uint32 pixelAuxiliar = *elPixel;
	Uint8 parteRojo;
	pixelAuxiliar = (*elPixel) & (formato->Rmask);  
	pixelAuxiliar = pixelAuxiliar >> formato->Rshift; 
	pixelAuxiliar = pixelAuxiliar << formato->Rloss;  
	parteRojo = (Uint8)pixelAuxiliar;
	return parteRojo;
}
	

Uint8 ProcesadorDeTierra::getParteVerde(Uint32* elPixel, SDL_PixelFormat *formato){
	Uint32 pixelAuxiliar = *elPixel;
	Uint8 parteVerde;
	pixelAuxiliar = (*elPixel) & (formato->Gmask);  
	pixelAuxiliar = pixelAuxiliar >> formato->Gshift; 
	pixelAuxiliar = pixelAuxiliar << formato->Gloss;  
	parteVerde = (Uint8)pixelAuxiliar;
	return parteVerde;
}


Uint8 ProcesadorDeTierra::getParteAzul(Uint32* elPixel, SDL_PixelFormat *formato){
	Uint32 pixelAuxiliar = *elPixel;
	Uint8 parteAzul;
	pixelAuxiliar = (*elPixel) & (formato->Bmask);  
	pixelAuxiliar = pixelAuxiliar >> formato->Bshift; 
	pixelAuxiliar = pixelAuxiliar << formato->Bloss;  
	parteAzul = (Uint8)pixelAuxiliar;
	return parteAzul;
}


Uint8 ProcesadorDeTierra::getParteAlpha(Uint32* elPixel, SDL_PixelFormat *formato){
	Uint32 pixelAuxiliar = *elPixel;
	Uint8 parteAlpha;
	pixelAuxiliar = (*elPixel) & (formato->Amask);  
	pixelAuxiliar = pixelAuxiliar >> formato->Ashift; 
	pixelAuxiliar = pixelAuxiliar << formato->Aloss;  
	parteAlpha = (Uint8)pixelAuxiliar;
	return parteAlpha;
}


void ProcesadorDeTierra::setParteRojo(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 rojo){
	Uint8 parteVerde = this->getParteVerde(elPixel,formato);
	Uint8 parteAzul = this->getParteAzul(elPixel,formato);
	Uint8 parteAlpha = this->getParteAlpha(elPixel,formato);
	*elPixel = SDL_MapRGBA(formato, rojo, parteVerde, parteAzul, parteAlpha);
}


void ProcesadorDeTierra::setParteVerde(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 verde){
	Uint8 parteRojo = this->getParteRojo(elPixel,formato);
	Uint8 parteAzul = this->getParteAzul(elPixel,formato);
	Uint8 parteAlpha = this->getParteAlpha(elPixel,formato);
	*elPixel = SDL_MapRGBA(formato, parteRojo, verde, parteAzul, parteAlpha);
}


void ProcesadorDeTierra::setParteAzul(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 azul){
	Uint8 parteRojo = this->getParteRojo(elPixel,formato);
	Uint8 parteVerde = this->getParteVerde(elPixel,formato);
	Uint8 parteAlpha = this->getParteAlpha(elPixel,formato);
	*elPixel = SDL_MapRGBA(formato, parteRojo, parteVerde, azul, parteAlpha);
}


void ProcesadorDeTierra::setParteAlpha(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 alpha){
/*	Uint8 parteRojo = this->getParteRojo(elPixel,formato);
	Uint8 parteVerde = this->getParteVerde(elPixel,formato);
	Uint8 parteAzul = this->getParteAzul(elPixel,formato);
	*elPixel = SDL_MapRGBA(formato, parteRojo, parteVerde, parteAzul, alpha);
	*/
	this->setColorRGBAenPixel(elPixel,this->superficie->format, this->parteRojaDelCielo,this->parteVerdeDelCielo,
		this->parteAzulDelCielo,alpha);

}


void ProcesadorDeTierra::setColorRGBAenPixel(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 rojo, Uint8 verde, Uint8 azul, Uint8 alpha){
	*elPixel = SDL_MapRGBA(formato, rojo, verde, azul, alpha);
}


bool ProcesadorDeTierra::pixelEsAire(Uint32* elPixel, SDL_PixelFormat *formato){
	//SDL_PixelFormat *formato = superficie->format;
	return ( getParteAlpha(elPixel,formato)==0);
	//return (getParteAzul(elPixel, formato) == 255 && getParteRojo(elPixel, formato) == 255 && getParteVerde(elPixel, formato) == 255);
}


bool ProcesadorDeTierra::pixelEsTierra(Uint32* elPixel, SDL_PixelFormat *formato){	
	return ( getParteAlpha(elPixel,formato)!=0 );
	//return(getParteAzul(elPixel, formato) != 255 || getParteRojo(elPixel, formato) != 255 || getParteVerde(elPixel, formato) != 255);
}


bool ProcesadorDeTierra::elRestoDeLaColumnaEsBlanca(int fila, int columna, int cantidadDeFilas){
	bool cumple = true;
	int nivelDeAguaRelativoALaSuperficie = this->nivelAgua*this->superficie->h/this->altoPx;
	while( (fila>0) && (cumple) ){
		Uint32* unPixel = this->getPixelEnLaPosicion(fila,columna);
		cumple = pixelEsAire(unPixel, superficie->format);
		this->setColorRGBAenPixel(unPixel,superficie->format,this->parteRojaDelCielo,this->parteVerdeDelCielo, this->parteAzulDelCielo,this->parteAlphaDelCielo);				
		if (fila> nivelDeAguaRelativoALaSuperficie)
			this->setColorRGBAenPixel(unPixel, superficie->format, 67,180,215,120);
		fila--;
	}
	return cumple;
}


void ProcesadorDeTierra::chequearSiSeCumpleElFormato(std::string *rutaDelArchivoLog, bool seCumpleFormato){
	//si no se cumplió el formato en la imagen de entrada, cargo la default
	Log log(*rutaDelArchivoLog);
	if(!seCumpleFormato){
		this->superficie = IMG_Load("private/imagen_tierra_default.png"); 
		log.escribirLog("La imagen de mascara de la tierra es invalida. Se pone por default: private/imagen_tierra_default.png.");
		//si no existe el archivo default, cierra el programa
		if ( this->superficie == nullptr ){
			log.escribirLog( "Usted ha tocado los archivos de la carpeta Private. Explota todo!");
			exit(2);
		}
			
		//parseo la nueva imagen
		SDL_LockSurface(this->superficie);			
		parsearSurface(rutaDelArchivoLog);
		SDL_UnlockSurface(this->superficie);
	}
}

// Constructor
ProcesadorDeTierra::ProcesadorDeTierra(std::string *rutaDelArchivoImagen, std::string *rutaDelArchivoLog, int altoPix, int anchoPix, int nivelAgua_px){
		
	this->colaDeAlturas = NULL;
		
	// en wikipedia decia estos numeros para el marron
	this->parteRojaDelMarronDeTierra = 108; // M
	this->parteVerdeDelMarronDeTierra = 54;
	this->parteAzulDelMarronDeTierra = 0;
	this->parteAlphaDelMarronDeTierra = 255;
	this->parteRojaDelCielo = 186;
	this->parteVerdeDelCielo = 241;
	this->parteAzulDelCielo = 245;
	this->parteAlphaDelCielo = 0;
	this->altoPx = altoPix;
	this->anchoPx = anchoPix;
	this->nivelAgua = nivelAgua_px;

	this->superficie = IMG_Load((*rutaDelArchivoImagen).c_str());
		
	SDL_LockSurface(this->superficie);
	//this->parsearSurface(rutaDelArchivoLog);
	SDL_UnlockSurface(this->superficie);
		
}


void ProcesadorDeTierra::parsearSurface(std::string *rutaDelArchivoLog){
	delete this->colaDeAlturas;
	this->colaDeAlturas = new std::queue<float>;
	this->cantidadDePixelsHorizontales = superficie->w;
	this->cantidadDePixelsVerticales = superficie->h;
	SDL_PixelFormat *formato = this->superficie->format;
	Uint32* pixel;
		
	bool empezoElCielo;
	bool seCumpleFormato = true;
	int indiceHorizontal = 0;
	int indiceVertical;
	int altura;

	if((int)formato->BitsPerPixel != 32){
		seCumpleFormato = false;
		Log log(*rutaDelArchivoLog);
		log.escribirLog("Imagen de mascara de tierra no tiene profundidad 32 bits.");
	}
	while( (indiceHorizontal < this->cantidadDePixelsHorizontales) && (seCumpleFormato) ){
		indiceVertical = cantidadDePixelsVerticales - 1;
		altura = 0;
		pixel = getPixelEnLaPosicion(indiceVertical,indiceHorizontal);
		if(this->pixelEsAire(pixel,formato)){
			seCumpleFormato = elRestoDeLaColumnaEsBlanca(indiceVertical,indiceHorizontal,cantidadDePixelsVerticales);	
				
		}else{
			if (pixelEsTierra(pixel,formato)){
				empezoElCielo = false;
				altura = 0;
				while((indiceVertical >= 0) && (seCumpleFormato) && (!empezoElCielo) ){
					pixel = getPixelEnLaPosicion(indiceVertical,indiceHorizontal);
					if(pixelEsTierra(pixel,formato)){
						//pinto el pixel del color que quieroque se vea la tierra
						//this->setColorRGBAenPixel(pixel,formato,this->parteRojaDelMarronDeTierra,this->parteVerdeDelMarronDeTierra,this->parteAzulDelMarronDeTierra,this->parteAlphaDelMarronDeTierra);
						altura++;
					}else{
						empezoElCielo = true;
					}
					indiceVertical--;
				}
				if (empezoElCielo){
					indiceVertical++; //porque cuando sale del ciclo anterior le resto una posicion de mas
					seCumpleFormato = elRestoDeLaColumnaEsBlanca(indiceVertical,indiceHorizontal,cantidadDePixelsVerticales);
				}
			}else{
				seCumpleFormato = false;	
				//TODO no se cumple el formato
					
			}
		}
		this->colaDeAlturas->push((float)altura);
		//std::cout << altura << std::endl;
		indiceHorizontal++;
	}

	int factor = this->anchoPx / this->cantidadDePixelsHorizontales;
	if( factor > 4 && factor <= 8){
		Log log(*rutaDelArchivoLog);
		log.escribirLog("WARNING: La imagen de la mascara de la tierra es muy chica en comparación con la ventana del juego. Pueden ocurrir interacciones extraás con la tierra durante la simulación");
	} else if(factor > 8){
		seCumpleFormato = false;
		Log log(*rutaDelArchivoLog);
		log.escribirLog("WARNING: Imagen de mascara de la tierra es muy chica en comparación con la ventana del juego.");
	}
	this->chequearSiSeCumpleElFormato(rutaDelArchivoLog , seCumpleFormato);
	//std::cout << std::endl  << seCumpleFormato << std::endl;
		
}

	
// Destructor
ProcesadorDeTierra::~ProcesadorDeTierra(){
	//TODO chequear el DESTRUIR SUPERFICIE++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SDL_FreeSurface ( this->superficie );
	delete this->colaDeAlturas;
}


SDL_Surface* ProcesadorDeTierra::getSurfaceDeLaTierra(){
	return this->superficie;
}

int ProcesadorDeTierra::getCantidadDePuntosHorizontales(){
	return this->cantidadDePixelsHorizontales;
}


int ProcesadorDeTierra::getCantidadDePuntosVerticales(){
	return this->cantidadDePixelsVerticales;
}


std::queue<float>* ProcesadorDeTierra::getColaDeAlturas(){
	return this->colaDeAlturas;
}