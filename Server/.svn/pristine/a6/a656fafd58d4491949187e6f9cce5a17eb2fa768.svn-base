#ifndef __ARMA_GRANADA__

#include "Arma.h"
#include "Municion_Granada.h"


class Arma_Granada: public Arma {
	public:

		bool destruida;

		int tiempoDeVida;

		Arma_Granada(b2World* mundo, Escenario* unEscenario);
		~Arma_Granada();
		void agregarMuniciones(int cant);

		bool verificarMunicionActual(Escenario* unEscenario);
		
		void ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual);
};
#endif // !__ARMA_GRANADA__