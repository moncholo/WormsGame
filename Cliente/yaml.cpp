#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include "yaml-cpp/yaml.h"
#include "Escenario.h"
#include "Poligono.h"
#include "Circulo.h"

void operator >> (const YAML::Node& node, Objeto& objeto) {
	//std::fstream fs("test.txt", std::fstream::app);
	node["x"] >> objeto.x;			//fs << "objeto.x " << objeto.x << std::endl;
	node["y"] >> objeto.y;			//fs << "objeto.y " << objeto.y << std::endl;
	node["ancho"] >> objeto.ancho;			//fs << "objeto.ancho " << objeto.ancho << std::endl;
	node["alto"] >> objeto.alto;			//fs << "objeto.alto " << objeto.alto << std::endl;
	node["color"] >> objeto.color;			//fs << "objeto.color " << objeto.color << std::endl;
	node["rot"] >> objeto.rot;			//fs << "objeto.rot " << objeto.rot << std::endl;
	node["masa"] >> objeto.masa;			//fs << "objeto.masa " << objeto.masa << std::endl;
	node["estatico"] >> objeto.estatico;			//fs << "objeto.estatico " << objeto.estatico << std::endl;
	//fs.close();
}

void operator >> (const YAML::Node& node, Escenario& escenario) {
	//std::fstream fs("test.txt", std::fstream::out);
	node["alto_px"] >> escenario.alto_px;			//fs << "escenario.alto_px " << escenario.alto_px << std::endl;
	node["alto_un"] >> escenario.alto_un;			//fs << "escenario.alto_un " << escenario.alto_un << std::endl;
	node["ancho_px"] >> escenario.ancho_px;			//fs << "escenario.ancho_px " << escenario.ancho_px << std::endl;
	node["ancho_un"] >> escenario.ancho_un;			//fs << "escenario.ancho_un " << escenario.ancho_un << std::endl;
	node["nivel_agua"] >> escenario.nivel_agua;			//fs << "escenario.nivel_agua " << escenario.nivel_agua << std::endl;
	node["imagen_tierra"] >> escenario.imagen_tierra;			//fs << "escenario.imagen_tierra " << escenario.imagen_tierra << std::endl;
	node["imagen_cielo"] >> escenario.imagen_cielo;			//fs << "escenario.imagen_cielo " << escenario.imagen_cielo << std::endl;
	//fs.close();

	std::string tipo;
	const YAML::Node& nodoObjetos = node["objetos"];
	for(unsigned i=0; i < nodoObjetos.size(); i++) {
		Objeto objeto;
		nodoObjetos[i]["tipo"] >> tipo;
														//fs << "tipo.c_str() " << tipo.c_str() << std::endl;
		if (!strcmp(tipo.c_str(),"circulo")) Circulo objeto;
		else Poligono objeto;

		nodoObjetos[i] >> objeto;
		escenario.objetos.push_back(objeto);
	}
	//fs.open ("test.txt", std::fstream::app);
	//fs << "escenario.objetos.size():" <<escenario.objetos.size()<< std::endl;
	//fs.close();
}
/*
int main() {
	try {
		std::ifstream fin("escenario.yaml");
		YAML::Parser parser(fin);
		YAML::Node doc;
		parser.GetNextDocument(doc);
		for(unsigned i=0;i<doc.size();i++) {
			Escenario escenario;
			doc[i] >> escenario;
		}
	} catch(YAML::ParserException& e) {
		std::cout << "NO IMPRIME UNA CHOTA" << std::endl;
		std::cout << e.what() << "\n";
	}
	//system("PAUSE");   
	return 0;
}
*/