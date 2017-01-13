#ifndef __ARMA_BAZOOKA__

#include "Arma.h"
#include "Municion_Bazooka.h"
#include "Constantes.h"

class Arma_Bazooka: public Arma {
	public:
	
		b2Body* cuerpoDelaMunicion; 

		Arma_Bazooka(b2World* unMundo, Escenario* unEscenario);

		void agregarMuniciones(int cant);

		bool verificarMunicionActual(Escenario* unEscenario);

		void ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual);
};

#endif // !__ARMA_BAZOOKA__
