#ifndef __ARMA_DINAMITA__

#include "Arma.h"
#include "Municion_Dinamita.h"


class Arma_Dinamita: public Arma {
	public:

		bool destruida;

		int tiempoDeVida;

		Arma_Dinamita(b2World* mundo, Escenario* unEscenario);
		~Arma_Dinamita();
		void agregarMuniciones(int cant);

		bool verificarMunicionActual(Escenario* unEscenario);
		
		void ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual);
};
#endif // !__ARMA_DINAMITA__