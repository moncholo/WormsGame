#include "Arma_Granada.h"

int cronometrador1(void* unArma){
	Arma_Granada* granada = (Arma_Granada*) unArma;
	while(!granada->destruida){
		if (granada->tiempoDeVida){
			granada->tiempoDeVida--;
		}
		SDL_Delay(1000);
	}
	return 0;
}

Arma_Granada::Arma_Granada(b2World* unMundo, Escenario* unEscenario ) {
	this->miEscenario = unEscenario;
	this->mundo = unMundo;
	sonidoEjecucion = "";
	std::string tipoDeMunicion("Municion_Granada");
	this->radioExplosion = 2.0f;
	this->tiempoDeVida = 3;
	this->fuerzaExplosion = 55;
	this->destruida = false;
	SDL_Thread* cronometrar = SDL_CreateThread(cronometrador1, "cronometrar", (void*)this);
}

Arma_Granada::~Arma_Granada(){
	this->destruida = true;
}

void Arma_Granada::agregarMuniciones(int cant){
	Municion_Granada* municion;
	/*for (int i = 0; i < cant; i++) {
		municion = new Municion_Granada;
		municiones->push_back(municion);
	}*/
}


bool Arma_Granada::verificarMunicionActual(Escenario* unEscenario){

	
	bool explosion = false;

	if (unEscenario->municionActual != NULL){
		
		if (this->tiempoDeVida == 0){

			explosion = true;

			this->explotar(unEscenario);

		}
	}
	return explosion;

}


void Arma_Granada::ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual){

		this->crearMunision(posX, posY, angulo, potencia, municionActual);
		if(this->miEscenario->miTierra->tienePuntoAdentroDeLaTierra(municionActual->GetPosition().x,municionActual->GetPosition().y)){

			municionActual->SetGravityScale(0);
			municionActual->SetLinearVelocity(b2Vec2(0,0));
		}
		municiones--;
		tiempoDeVida= 3;

}