#ifndef __ARMA_SANTAGRANADA__

#include "Arma.h"
#include "Municion_SantaGranada.h"


class Arma_SantaGranada: public Arma {
	public:

		bool destruida;

		int tiempoDeVida;

		Arma_SantaGranada(b2World* mundo, Escenario* unEscenario);
		~Arma_SantaGranada();
		void agregarMuniciones(int cant);

		bool verificarMunicionActual(Escenario* unEscenario);
		
		void ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual);
};
#endif // !__ARMA_SANTAGRANADA__