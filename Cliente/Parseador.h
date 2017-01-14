#ifndef PARSEADOR
#define PARSEADOR

#define _SCL_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <Windows.h>
#include <string.h>
#include "yaml-cpp/yaml.h"
#include "Escenario.h"
#include "PoligonoRegular.h"
#include "Circulo.h"
#include "Rectangulo.h"
#include "Gusano.h"
#include "Log.h"
class Parseador{
	
	private:
		
		Escenario* parsearEscenarioDefault(Escenario* miEscenario, Log log);
	
	public:
		Parseador();
		~Parseador();
		Escenario* parsearEscenario(Escenario* unEscenario, char* pathEscenario, Log log);
		//void comenzarJuego(b2World* mundo);
		bool chequearMap(const YAML::Node& nodo, char* key, int tipoDeDato, Log log);
		void pasarParametros(Escenario* escenario, const YAML::Node& node, Objeto* objeto, Log log);
		void pasarParametros(Escenario* escenario, const YAML::Node& node, PoligonoRegular* objeto, Log log);
		void pasarParametros(Escenario* escenario, const YAML::Node& node, Circulo* objeto, Log log);
		void pasarParametros(Escenario* escenario, const YAML::Node& node, Rectangulo* objeto, Log log);
		void pasarParametros(Escenario* escenario, const YAML::Node& node, Gusano* objeto, Log log);

		bool pasarParametros(const YAML::Node& node, Escenario* escenario, Log log);
};

#endif