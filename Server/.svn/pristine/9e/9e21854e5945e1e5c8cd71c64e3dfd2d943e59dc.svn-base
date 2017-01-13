#include "Arma_Bazooka.h"
#include <math.h>

Arma_Bazooka::Arma_Bazooka(b2World* unMundo, Escenario* unEscenario) {
	this->miEscenario = unEscenario;
	this->mundo = unMundo;
	sonidoEjecucion = "";
	std::string tipoDeMunicion("Municion_Bazooka");
	radioExplosion = 3.0f;
	this->fuerzaExplosion = 50;
}

void Arma_Bazooka::agregarMuniciones(int cant){
	Municion_Bazooka* municion;
	/*for (int i = 0; i < cant; i++) {
		municion = new Municion_Bazooka;
		municiones->push_back(municion);
	}	*/
}
bool Arma_Bazooka::verificarMunicionActual(Escenario* unEscenario){

	
	bool explosion = false;

	if (unEscenario->municionActual != NULL){
		
		if( (unEscenario->municionActual->GetPosition().x < -10) || (unEscenario->municionActual->GetPosition().x > unEscenario->ancho_un +10)
			|| (unEscenario->municionActual->GetPosition().y < -10)){

			explosion = true;
			this->explotar(unEscenario);
		}

		else if ((unEscenario->municionActual->GetContactList()!=NULL)&&(unEscenario->municionActual->GetPosition().x < unEscenario->ancho_un)&&
			(unEscenario->municionActual->GetPosition().x >0)&&(unEscenario->municionActual->GetPosition().y > 0)){

			explosion = true;

			this->explotar(unEscenario);
		}
	}
	return explosion;

}

void Arma_Bazooka::ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual){

	this->crearMunision(posX, posY, angulo, potencia, municionActual);
	if(this->miEscenario->miTierra->tienePuntoAdentroDeLaTierra(municionActual->GetPosition().x,municionActual->GetPosition().y)){
		
		this->explotar(this->miEscenario);
	
	}
	municiones--;
}
