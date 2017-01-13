#include "RecorredorDeImagenes.h"



RecorredorDeImagenes::RecorredorDeImagenes(int anchoImagen, int altoImagen, int altoVentana, int anchoVentana, int altoMapa, int anchoMapa){
	this->altoVentana = altoVentana;
	this->anchoVentana = anchoVentana;
	this->rectanguloRecorredor = new SDL_Rect();
	this->zoom = 0.5;
	this->altoDeLaImagen = altoImagen;
	this->anchoDeLaImagen = anchoImagen;
	this->altoMapa = altoMapa;
	this->anchoMapa = anchoMapa;
	this->escalaX = (float)anchoVentana/(float)anchoMapa;
	this->escalaY = (float)altoVentana/(float)altoMapa;
	this->inicializarZoomYRectangulo();
}



void RecorredorDeImagenes::recalcularDimensionesDelRectangulo(){
	
	if (this->zoom == 1){
		this->rectanguloRecorredor->x = 0;
		this->rectanguloRecorredor->y = 0;
		this->rectanguloRecorredor->w = this->anchoDeLaImagen;
		this->rectanguloRecorredor->h = this->altoDeLaImagen;
	
	}else{
	
//	int x=0;
//	int y=0;
//	SDL_GetMouseState(&x,&y);
	

	float numero1 = 1.0f/this->zoom;
	float numero2 = 1.0f-numero1;
	int anchoInicial = this->rectanguloRecorredor->h;
	int posXInicialRectangulo = this->rectanguloRecorredor->x;
	int posYInicialRectangulo = this->rectanguloRecorredor->y;

	this->rectanguloRecorredor->h = (int)((float)this->altoDeLaImagen*(numero1));
	this->rectanguloRecorredor->w = (int)((float) this->anchoDeLaImagen*(numero1));
//	this->rectanguloRecorredor->x = x - this->rectanguloRecorredor->w / 2;
//	this->rectanguloRecorredor->y = y - this->rectanguloRecorredor->h / 2;
	
	if ((this->rectanguloRecorredor->y + this->rectanguloRecorredor->h) > this->altoDeLaImagen){
		this->rectanguloRecorredor->y -= this->rectanguloRecorredor->y +   this->rectanguloRecorredor->h - this->altoDeLaImagen;
	}
	if ((this->rectanguloRecorredor->x + this->rectanguloRecorredor->w) > this->anchoDeLaImagen){
 		this->rectanguloRecorredor-> x -= this->rectanguloRecorredor->x + this->rectanguloRecorredor->w - anchoDeLaImagen;
	}

	}
	
}


void RecorredorDeImagenes::inicializarZoomYRectangulo(){
	this->zoom = 1; //1 es el default, la imagen original
	this->rectanguloRecorredor = new SDL_Rect();
	this->rectanguloRecorredor->h = this->altoDeLaImagen;
	this->rectanguloRecorredor->w = this->anchoDeLaImagen;
	this->rectanguloRecorredor->x = 0;
	this->rectanguloRecorredor->y = 0;
}

RecorredorDeImagenes::~RecorredorDeImagenes(){
	delete this->rectanguloRecorredor;
}

SDL_Rect* RecorredorDeImagenes::getRectangulo(){
	return this->rectanguloRecorredor;
}

void RecorredorDeImagenes::incrementarZoom(){
	float diferencia = ZOOM_MAX - INCREMENTO_ZOOM;
	if (this->zoom < diferencia )
		this->zoom += INCREMENTO_ZOOM;
	if ((this->zoom >=diferencia)||(this->zoom>ZOOM_MAX))
		this->zoom = ZOOM_MAX; 

	this->recalcularDimensionesDelRectangulo();
}

void RecorredorDeImagenes::decrementarZoom(){
	float diferencia = ZOOM_MIN + INCREMENTO_ZOOM; 
	if (this->zoom >= diferencia)
		this->zoom -= INCREMENTO_ZOOM;
	if ((this->zoom <= diferencia)||(this->zoom < 1))   
		this->zoom = ZOOM_MIN;

	this->recalcularDimensionesDelRectangulo();	
}

void RecorredorDeImagenes::procesarMovimientoADerecha(){
	int posicionXFinalDelRectangulo = this->rectanguloRecorredor->x + this->rectanguloRecorredor->w;
	int posicionXInicialDelRectangulo = this->rectanguloRecorredor->x;
	if ((this->anchoDeLaImagen-posicionXFinalDelRectangulo) > DESPLAZAMIENTO_MAX){
			this->rectanguloRecorredor->x += DESPLAZAMIENTO_MAX;
			
	}

	if (((this->anchoDeLaImagen-posicionXFinalDelRectangulo) <= DESPLAZAMIENTO_MAX)||
								(posicionXFinalDelRectangulo>this->anchoDeLaImagen)){
		this->rectanguloRecorredor->x = this->anchoDeLaImagen-this->rectanguloRecorredor->w;
		
	}
}

void RecorredorDeImagenes::procesarMovimientoAIzquierda(){
	int posicionXInicialDelRectangulo = this->rectanguloRecorredor->x;
	if (this->rectanguloRecorredor->x >= DESPLAZAMIENTO_MAX)
		this->rectanguloRecorredor->x -= DESPLAZAMIENTO_MAX;
	if ((this->rectanguloRecorredor->x< DESPLAZAMIENTO_MAX)||(this->rectanguloRecorredor->x < 0)){
		this->rectanguloRecorredor->x = 0;
	}
}

void RecorredorDeImagenes::procesarMovimientoAbajo(){

	int posicionYFinalDelRectangulo = this->rectanguloRecorredor->y + this->rectanguloRecorredor->h;
	int posicionYInicialDelRectangulo = this->rectanguloRecorredor->y;
	if ((this->altoDeLaImagen - posicionYFinalDelRectangulo) > DESPLAZAMIENTO_MAX){
		this->rectanguloRecorredor->y += DESPLAZAMIENTO_MAX;
	}
	else if (((this->altoDeLaImagen-posicionYFinalDelRectangulo)<=DESPLAZAMIENTO_MAX) ||
								(posicionYFinalDelRectangulo>this->altoDeLaImagen)){
		this->rectanguloRecorredor->y = this->altoDeLaImagen - this->rectanguloRecorredor->h;
		}		


}
	
float RecorredorDeImagenes::getZoom(){
	return this->zoom;
}

void RecorredorDeImagenes::procesarMovimientoArriba(){
	
	int posicionYInicialDelRectangulo  = this->rectanguloRecorredor->y;

	if (this->rectanguloRecorredor->y > DESPLAZAMIENTO_MAX){
		this->rectanguloRecorredor->y -= DESPLAZAMIENTO_MAX;
		}	
	else if (this->rectanguloRecorredor->y <= DESPLAZAMIENTO_MAX)
		this->rectanguloRecorredor->y = 0;

}

void RecorredorDeImagenes::desplazarHacia(Direccion unaDireccion){
	
	switch (unaDireccion)
	{
		case ABAJO: {this->procesarMovimientoAbajo();}
			break;
		case ARRIBA: {this->procesarMovimientoArriba();}
			break;
		case DERECHA: {this->procesarMovimientoADerecha();}
			break;
		case IZQUIERDA: {this->procesarMovimientoAIzquierda();}
			break;
		default: {}
			break;
	}
	
}