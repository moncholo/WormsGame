

#ifndef __ONDA_EXPANSIVA__
#define __ONDA_EXPANSIVA__

#include "Gusano.h"
#include "Objeto.h"
#include <vector>
#include "Box2D\Box2D.h"
#include "Constantes.h"
#include "Arma.h"

class OndaExpansiva{

	private:
		
		std::vector<Gusano*>* vectorDeGusanos;
		std::vector<Objeto*>* vectorDeObjetos;


	public: 

		float calculoDanio;

		OndaExpansiva(std::vector<Gusano*>* unVectorDeGusanos, std::vector<Objeto*>* unVectorDeObjetos);

		void expandirConRadio(float posX, float posY, float radio, Arma* unArma);


};



#endif