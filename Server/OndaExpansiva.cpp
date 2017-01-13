#include "Arma.h"

OndaExpansiva::OndaExpansiva(std::vector<Gusano*>* unVectorDeGusanos, std::vector<Objeto*>* unVectorDeObjetos){
	this->vectorDeGusanos = unVectorDeGusanos;
	this->vectorDeObjetos = unVectorDeObjetos;
	this->calculoDanio = 0;

}

void OndaExpansiva::expandirConRadio(float posX, float posY, float radio, Arma* unArma){

	//linear velocity
	
	for (unsigned int i = 0; i < this->vectorDeObjetos->size(); i++){
		b2Vec2 vectorDeDiferencia(this->vectorDeObjetos->at(i)->getCuerpo()->GetPosition().x-posX,
			this->vectorDeObjetos->at(i)->getCuerpo()->GetPosition().y-posY);
		if (vectorDeDiferencia.Length() < ((float32)radio*RADIO_BASE*RADIO_ONDA)){
			vectorDeDiferencia*= unArma->fuerzaExplosion*(1.0f / vectorDeDiferencia.Length());
			
			this->vectorDeObjetos->at(i)->getCuerpo()->SetLinearVelocity(vectorDeDiferencia);
		}
	
	}

	for (unsigned int i = 0; i < this->vectorDeGusanos->size(); i++){
		if (this->vectorDeGusanos->at(i)->estaEnMundo()){
		
			b2Vec2 vectorDeDiferencia(this->vectorDeGusanos->at(i)->getCuerpo()->GetPosition().x-posX,
			this->vectorDeGusanos->at(i)->getCuerpo()->GetPosition().y-posY);

			if (vectorDeDiferencia.Length() < ((float32)radio*RADIO_BASE*RADIO_ONDA)){
				float32 distancia = vectorDeDiferencia.Length();
				vectorDeDiferencia*= unArma->fuerzaExplosion*(1.0f / distancia);			
				this->vectorDeGusanos->at(i)->getCuerpo()->SetLinearVelocity(vectorDeDiferencia);
				calculoDanio = unArma->fuerzaExplosion;
				calculoDanio -= (distancia*unArma->fuerzaExplosion)/(radio*RADIO_BASE*RADIO_ONDA);
				this->vectorDeGusanos->at(i)->vida-= calculoDanio;
				if(this->vectorDeGusanos->at(i)->vida < 0){
					this->vectorDeGusanos->at(i)->vida = 0;
				}

			}
		}
	}

}