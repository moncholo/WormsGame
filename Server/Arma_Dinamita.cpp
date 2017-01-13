#include "Arma_Dinamita.h"

int cronometrador3(void* unArma){
	Arma_Dinamita* granada = (Arma_Dinamita*) unArma;
	while(!granada->destruida){
		if (granada->tiempoDeVida){
			granada->tiempoDeVida--;
		}
		SDL_Delay(1000);
	}
	return 0;
}


Arma_Dinamita::Arma_Dinamita(b2World* unMundo, Escenario* unEscenario ) {
	this->miEscenario = unEscenario;
	this->mundo = unMundo;
	sonidoEjecucion = "";
	std::string tipoDeMunicion("Municion_Granada");
	this->radioExplosion = 3.0f;
	this->tiempoDeVida = 5;
	this->destruida = false;
	this->fuerzaExplosion = 60;
	SDL_Thread* cronometrar = SDL_CreateThread(cronometrador3, "cronometrar", (void*)this);
}

Arma_Dinamita::~Arma_Dinamita(){
	this->destruida = true;
}

void Arma_Dinamita::agregarMuniciones(int cant){
	Municion_Dinamita* municion;
	/*for (int i = 0; i < cant; i++) {
		municion = new Municion_Granada;
		municiones->push_back(municion);
	}*/
}


bool Arma_Dinamita::verificarMunicionActual(Escenario* unEscenario){

	
	bool explosion = false;

	if (unEscenario->municionActual != NULL){
		
		if (this->tiempoDeVida == 0){

			explosion = true;

			this->explotar(unEscenario);

		}
	}
	return explosion;

}


void Arma_Dinamita::ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual){

		this->crearMunision(posX, posY, angulo, potencia, municionActual);
		municionActual->SetLinearVelocity(b2Vec2(0,0));
		if(this->miEscenario->miTierra->tienePuntoAdentroDeLaTierra(municionActual->GetPosition().x,municionActual->GetPosition().y)){

			municionActual->SetGravityScale(0);
		}
		municiones--;
		tiempoDeVida= 5;

}