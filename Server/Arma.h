

#ifndef __ARMA__
#define __ARMA__

#include "Objeto.h"
#include "Municion.h"
#include "Escenario.h"
#include "Sonido.h"

class Arma: public Objeto {
	public:
		int municiones;
		float32 fuerzaExplosion;

		float32 radioExplosion;
		//bool elegido; --> lo hereda de objeto

		char* sonidoEjecucion;

		std::string tipoDeMunicion;
		
		b2World* mundo;
		Escenario* miEscenario;

		Arma();

		//Recibe parametros en Box2D
		virtual void ejecutar(float posX, float posY, float angulo, int potencia, b2Body*& municionActual);

		virtual bool verificarMunicionActual(Escenario* unEscenario);

		void explotar(Escenario* unEscenario);

		void crearMunision(float posX, float posY, float angulo, int potencia, b2Body*& municionActual);

		~Arma();

};

#endif


#ifndef __ONDA_EXPANSIVA__
#define __ONDA_EXPANSIVA__

#include "Gusano.h"
#include "Objeto.h"
#include <vector>
#include "Box2D\Box2D.h"
#include "Constantes.h"

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