#include "Arma_SantaGranada.h"

int cronometrador(void* unArma){
	Arma_SantaGranada* granada = (Arma_SantaGranada*) unArma;
	while(!granada->destruida){
		if (granada->tiempoDeVida){
			granada->tiempoDeVida--;
		}
		SDL_Delay(1000);
	}
	return 0;
}


Arma_SantaGranada::Arma_SantaGranada(b2World* unMundo, Escenario* unEscenario ) {
	this->miEscenario = unEscenario;
	this->mundo = unMundo;
	sonidoEjecucion = "";
	std::string tipoDeMunicion("Municion_Granada");
	this->radioExplosion = 3.0f;
	this->tiempoDeVida = 4;
	this->destruida = false;
	this->fuerzaExplosion = 95;
	SDL_Thread* cronometrar = SDL_CreateThread(cronometrador, "cronometrar", (void*)this);
}

Arma_SantaGranada::~Arma_SantaGranada(){
	this->destruida = true;
}

void Arma_SantaGranada::agregarMuniciones(int cant){
	Municion_SantaGranada* municion;
	/*for (int i = 0; i < cant; i++) {
		municion = new Municion_Granada;
		municiones->push_back(municion);
	}*/
}


bool Arma_SantaGranada::verificarMunicionActual(Escenario* unEscenario){

	
	bool explosion = false;

	if (unEscenario->municionActual != NULL){
		
		if (this->tiempoDeVida == 0){

			explosion = true;

			this->explotar(unEscenario);

		}
	}
	return explosion;

}


void Arma_SantaGranada::ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual){

		this->crearMunision(posX, posY, angulo, potencia, municionActual);
		if(this->miEscenario->miTierra->tienePuntoAdentroDeLaTierra(municionActual->GetPosition().x,municionActual->GetPosition().y)){

			municionActual->SetGravityScale(0);
			municionActual->SetLinearVelocity(b2Vec2(0,0));
		}
		municiones--;
		tiempoDeVida= 4;

}