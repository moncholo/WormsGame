#include "Parseador.h"

Parseador::Parseador(){
		
}
Parseador::~Parseador(){
}

bool Parseador::chequearMap(const YAML::Node& nodo, char* key, int tipoDeDato, Log log) {
	try {
		if (nodo[key]. Type() != 1) {

			YAML::Mark mark = nodo[key].GetMark();
			std::stringstream s; s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<".";
			s << "Error de formato de entrada del atributo " << key << ".";
			log.escribirLog(s.str());
			return false;
		}
	} catch (const YAML::KeyNotFound& e) {
			std::stringstream s; s<<"Line: "<<e.mark.line+1<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
			log.escribirLog(s.str());
			return false;
		}
	if (tipoDeDato == 1) {
		try {
			nodo[key].to<float>();
		}	
		catch(const YAML::InvalidScalar& e) {
			if (IsNull(nodo[key])) {
				YAML::Mark mark = nodo[key].GetMark();
				std::stringstream s; s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<". Msg: Empty map.";
				log.escribirLog(s.str());
			} else {
				std::stringstream s; s<<"Line: "<<e.mark.line+1<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
				log.escribirLog(s.str());
			}
			return false;
		} /*catch (const YAML::KeyNotFound& e) {
			std::stringstream s; s<<"Line: "<<e.mark.line<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
			log.escribirLog(s.str());
			return false;
		}*/
	} else if (tipoDeDato == 2) {
		try {
			nodo[key].to<std::string>();
		}
		catch(const YAML::InvalidScalar& e) {
			if (IsNull(nodo[key])) {
				YAML::Mark mark = nodo[key].GetMark();
				std::stringstream s; s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<". Msg: Empty map.";
				log.escribirLog(s.str());
			} else {
				std::stringstream s; s<<"Line: "<<e.mark.line+1<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
				log.escribirLog(s.str());
			}
			return false;
		} /*catch (const YAML::KeyNotFound& e) {
			std::stringstream s; s<<"Line: "<<e.mark.line<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
			log.escribirLog(s.str());
			return false;
		} catch(const YAML::TypedKeyNotFound<std::basic_string<char,std::char_traits<char>,std::allocator<char>>>& e) {
			std::stringstream s; s<<"Line: "<<e.mark.line<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
			log.escribirLog(s.str());
			return false;
		}*/
	}
	return true;
}

bool validarColor(const YAML::Node& node) {
	// se supone que es un string, no null.
	std::string aux = node["color"].to<std::string>();
	if (aux.size() != 7) return false;
	else if (aux[0] != '#') return false;
	else {
		for (int i = 1; i < 7; i++) {
			if (!((aux[i] >= '0' && aux[i] <= '9') || (aux[i] >= 'a' && aux[i] <= 'f') || (aux[i] >= 'A' && aux[i] <= 'F'))) 
			return false;
		}
	}
	return true;
}

bool validarAtributo(char* atributo, const YAML::Node& node, int tipoDeDato, int min, int max) {
	
	if (tipoDeDato == 1) {
		if (node[atributo].to<float>() < min || node[atributo].to<float>() > max) return false;
	} else if (tipoDeDato == 2) {
		if (!strcmp(atributo, "color")) return validarColor(node);
		else if (!strcmp(atributo, "estatico")) {
			if (strcmp("si", node["estatico"].to<std::string>().c_str()) && 
				strcmp("no",node["estatico"].to<std::string>().c_str())) return false;
		}
	}
	return true;
}

int random(int min, int max) {
	std::random_device rd;
	return ((rd() % max) + min);
}

void informarErrorEnAtributo(char* atributo, const YAML::Node& node, Log log, int nuevoValor, const char* nuevoValor_c) {
	YAML::Mark mark = node[atributo].GetMark();
	std::stringstream s; s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
	if (nuevoValor)	
		s<<"El valor ingresado para el atributo "<<atributo<<" del objeto es invalido. Fue reemplazado por " << nuevoValor <<".";
	else 
		s<<"El valor ingresado para el atributo "<<atributo<<" del objeto es invalido. Fue reemplazado por " << nuevoValor_c <<".";
	log.escribirLog(s.str());
}

void pasarColorAObjeto(Objeto* objeto){
	char valores[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	for (int i = 1; i < 7; i++) {
		if (objeto->color[i] >= 97 && objeto->color[i] <= 102) objeto->color[i] -= 87;
		else if (objeto->color[i] >= 65 && objeto->color[i] <= 70) objeto->color[i] -= 55;
		else objeto->color[i] -= 48;
	}
	objeto->r = (objeto->color.c_str()[1]) * 16 + objeto->color.c_str()[2];
	objeto->g = (objeto->color.c_str()[3]) * 16 + objeto->color.c_str()[4];;
	objeto->b = (objeto->color.c_str()[5]) * 16 + objeto->color.c_str()[6];
}

void Parseador::pasarParametros(Escenario* escenario, const YAML::Node& node, Objeto* objeto, Log log) {
	std::fstream fs("test.txt", std::fstream::app);
	YAML::Mark mark;

	if (chequearMap(node, "x", 1, log) && validarAtributo("x", node, 1, 0, escenario->ancho_un)) node["x"] >> objeto->x;	
	else {
		if (!validarAtributo("x", node, 1, 0, escenario->ancho_un)) {
			mark = node["x"].GetMark();
			std::stringstream s; s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
			s << "La posicion x del objeto esta fuera del escenario y puede que no se vea dibujado en el inicio.";
			log.escribirLog(s.str());
			node["x"] >> objeto->x;
		} else {
			objeto->x = random(0, escenario->ancho_un);
			informarErrorEnAtributo("x", node, log, objeto->x, NULL);
		}
	}																						fs << "objeto.x " << objeto->x << std::endl;

	if (chequearMap(node, "y", 1, log) && validarAtributo("y", node, 1, 0, escenario->alto_un)) node["y"] >> objeto->y;
	else {
		if (!validarAtributo("y", node, 1, 0, escenario->alto_un)) {
			mark = node["y"].GetMark();
			std::stringstream s; s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
			s << "La posicion y del objeto esta fuera del escenario y puede que no se vea dibujado en el inicio.";
			log.escribirLog(s.str());
			node["y"] >> objeto->y;
		} else {
			objeto->y = random(0, escenario->alto_un);
			informarErrorEnAtributo("y", node, log, objeto->x, NULL);
		}
	}																						fs << "objeto.y " << objeto->y << std::endl;

	if (chequearMap(node, "color", 2, log) && validarAtributo("color", node, 2, 0, 0)) {
		objeto->color = node["color"].to<std::string>();
		pasarColorAObjeto(objeto);
	
	} else {
		char valores[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
		objeto->color.push_back('#');
		for (int i = 1; i < 7; i++) objeto->color.push_back(valores[random(0, 15)]);
		informarErrorEnAtributo("color", node, log, NULL , (objeto->color).c_str());
		pasarColorAObjeto(objeto);
	}																						fs << "objeto.r " << objeto->r << std::endl;
	
	if (chequearMap(node, "rot", 1, log) && validarAtributo("rot", node, 1, 0, 359)) node["rot"] >> objeto->rot;	
	else {
		objeto->rot = random(0, 359);
		informarErrorEnAtributo("rot", node, log, objeto->rot, NULL);
	}																						fs << "objeto.rot " << objeto->rot << std::endl;

	if (chequearMap(node, "masa", 1, log) && validarAtributo("masa", node, 1, 0, 100)) node["masa"] >> objeto->masa;	
	else {
		objeto->masa = random(1, 100);
		informarErrorEnAtributo("masa", node, log, objeto->masa, NULL);
	};																						fs << "objeto.masa " << objeto->masa << std::endl;
	//ver valor MAX de la masa!!!
	if (chequearMap(node, "estatico", 2, log) && validarAtributo("estatico", node, 2, 0, 0)) node["estatico"] >> objeto->estatico;	
	else {
		int bin = random (0,1);
		if (bin) objeto->estatico = "si";
		else objeto->estatico = "no";
		informarErrorEnAtributo("estatico", node, log, NULL , (objeto->estatico).c_str());
	}																						fs << "objeto.estatico " << objeto->estatico<< std::endl;
	fs.close();
}

void Parseador::pasarParametros(Escenario* escenario, const YAML::Node& node, Gusano* objeto, Log log){
	std::fstream fs("test.txt", std::fstream::app);
		

	if (chequearMap(node, "equipo", 1, log) && validarAtributo("equipo", node, 1, 1, 4)) node["equipo"] >> objeto->equipo;
	else {
		informarErrorEnAtributo("equipo", node, log, objeto->equipo, NULL);
	}

	fs.close();
	pasarParametros(escenario, node,(Objeto*) objeto, log);
}

void Parseador::pasarParametros (Escenario* escenario, const YAML::Node& node, PoligonoRegular* objeto, Log log) {
	std::fstream fs("test.txt", std::fstream::app);

	if (chequearMap(node, "escala", 1, log) && validarAtributo("escala", node, 1, 0, 15)) node["escala"] >> objeto->escala;							
	else {
		objeto->escala = random(1, 15);
		informarErrorEnAtributo("escala", node, log, objeto->escala, NULL);
	}																			fs << "objeto.escala " << objeto->escala<< std::endl;

	if (chequearMap(node, "numeroDeLados", 1, log) && validarAtributo("numeroDeLados", node, 1, 3, 8)) node["numeroDeLados"] >> objeto->numeroDeLados;		
	else {
		objeto->numeroDeLados = random(3, 8);
		informarErrorEnAtributo("numeroDeLados", node, log, objeto->numeroDeLados, NULL);
	}																			fs << "objeto.numeroDeLados " << objeto->numeroDeLados<< std::endl;
	
	fs.close();
	pasarParametros(escenario, node,(Objeto*) objeto, log);	
}

void Parseador::pasarParametros (Escenario* escenario, const YAML::Node& node, Circulo* objeto, Log log) {
	std::fstream fs("test.txt", std::fstream::app);

	if (chequearMap(node, "escala", 1, log) && validarAtributo("escala", node, 1, 1, 9)) node["escala"] >> objeto->escala;							
	else {
		objeto->escala = random(1, 9);
		informarErrorEnAtributo("escala", node, log, objeto->escala, NULL);
	}

	fs.close();
	pasarParametros(escenario, node, (Objeto*)objeto, log);
}

void Parseador::pasarParametros(Escenario* escenario, const YAML::Node& node, Rectangulo* objeto, Log log) {
	std::fstream fs("test.txt", std::fstream::app);

	if (chequearMap(node, "ancho", 1, log) && validarAtributo("ancho", node, 1, 1, 25)) 
		node["ancho"] >> objeto->ancho;	
	else {
		objeto->ancho = random(1, 25);
		informarErrorEnAtributo("ancho", node, log, objeto->ancho, NULL);
	}																				fs << "objeto.ancho " << objeto->ancho << std::endl;	
		
	if (chequearMap(node, "alto", 1, log) && validarAtributo("alto", node, 1, 1, 25)) 
		node["alto"] >> objeto->alto;	
	else {
		objeto->alto = random(1, 25);
		informarErrorEnAtributo("alto", node, log, objeto->alto, NULL);
	}																				fs << "objeto.alto " << objeto->alto<< std::endl;
	
	fs.close();
	pasarParametros(escenario, node, (Objeto*)objeto, log);
}


int validarEscenario(const YAML::Node& node, char* atributo, int min, int max){
	if (node[atributo].to<float>() > max) return 1;
	if (node[atributo].to<float>() < min) return 2;
	return 0;
}

void informarErrorEnEscenario(char* atributo, const YAML::Node& node, Log log, int nuevoValor1, std::string* nuevoValor2) {
	try {
		YAML::Mark mark = node[atributo].GetMark();
		std::stringstream s;	s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
		if (nuevoValor1) s << "El valor ingresado para el atributo "<<atributo<<" del escenario es invalido. Fue reemplazado por " << nuevoValor1 <<".";
		else s << "El valor ingresado para el atributo "<<atributo<<" del escenario es invalido. Fue reemplazado por " << *nuevoValor2 <<".";
		log.escribirLog(s.str());
	} catch (const YAML::KeyNotFound& e) {
			std::stringstream s; s<<"Line: "<<e.mark.line+1<<", Column: "<< e.mark.column <<".";
			if (nuevoValor1) s << "No se ingreso el atributo "<<atributo<<" del escenario-> Se pone por default: " << nuevoValor1 <<".";
			else s << "No se ingreso el atributo "<<atributo<<" del escenario-> Se pone por default: " << *nuevoValor2 <<".";
			log.escribirLog(s.str());
		}
}

bool validarArchivo(std::string path) {
	std::ifstream fin(path);
	if (!fin) return false;
	fin.close();
	return true;
}

bool Parseador::pasarParametros(const YAML::Node& node, Escenario* escenario, Log log) {
	std::fstream fs("test.txt", std::fstream::out);

	int val1 = 1;
	bool nodoOk = chequearMap(node, "alto_px", 1, log);
	if (nodoOk) 
		val1 = validarEscenario(node, "alto_px", 125, GetSystemMetrics(SM_CYSCREEN) - 50);
	if (nodoOk && !val1) {
		float aux; node["alto_px"] >> aux;
		escenario->alto_px = (int) aux;												
	} else {
		if (val1 == 1) escenario->alto_px = (GetSystemMetrics(SM_CYSCREEN) - 50);
		else escenario->alto_px = 125;
		informarErrorEnEscenario("alto_px", node, log, escenario->alto_px, 0);
	}																						fs << "escenario->alto_px " << escenario->alto_px << std::endl;
	
	if (chequearMap(node, "alto_un", 1, log)) node["alto_un"] >> escenario->alto_un;			
	else {
		escenario->alto_un = 100; //default;
		informarErrorEnEscenario("alto_un", node, log, escenario->alto_un, 0);
	}																						fs << "escenario->alto_un " << escenario->alto_un << std::endl;

	int val2 = 1;
	nodoOk = chequearMap(node, "ancho_px", 1, log);
	if (nodoOk) 
		val2 = validarEscenario(node, "ancho_px", 125, GetSystemMetrics(SM_CXSCREEN) - 50);
	if (nodoOk && !val2) {
		float aux2; node["ancho_px"] >> aux2;
		escenario->ancho_px = (int) aux2;												
	}												
	else {
		if (val2 == 1) escenario->ancho_px = (GetSystemMetrics(SM_CXSCREEN) - 50);
		else escenario->ancho_px = 125;
		informarErrorEnEscenario("ancho_px", node, log, escenario->ancho_px, 0);
	}  																						fs << "escenario->ancho_px " << escenario->ancho_px << std::endl; 
	
	if (chequearMap(node, "ancho_un", 1, log)) node["ancho_un"] >> escenario->ancho_un;		
	else {
		escenario->ancho_un = 100; //default;
		informarErrorEnEscenario("ancho_un", node, log, escenario->ancho_un, 0);
	}																						fs << "escenario->ancho_un " << escenario->ancho_un << std::endl;
	if (chequearMap(node, "nivel_agua", 1, log) &&
		!validarEscenario(node, "nivel_agua", 0, escenario->alto_un)) node["nivel_agua"] >> escenario->nivel_agua;			
	else {
		escenario->nivel_agua = (escenario->alto_un / 4);
		informarErrorEnEscenario("nivel_agua", node, log, escenario->nivel_agua, 0);				
	}																						fs << "escenario->nivel_agua " << escenario->nivel_agua << std::endl;
	if (chequearMap(node, "imagen_tierra", 2, log) 
		&& validarArchivo(node["imagen_tierra"].to<std::string>())) node["imagen_tierra"] >> escenario->imagen_tierra;	
	else {
		escenario->imagen_tierra = "private/imagen_tierra_default.png"; // poner el path de la imagen default.
		informarErrorEnEscenario("imagen_tierra", node, log, 0, &escenario->imagen_tierra);
	}																						fs << "escenario->imagen_tierra " << escenario->imagen_tierra << std::endl;
		
	if (chequearMap(node, "imagen_cielo", 2, log) 
		&& validarArchivo(node["imagen_cielo"].to<std::string>())) node["imagen_cielo"] >> escenario->imagen_cielo;		
	else {
		escenario->imagen_cielo = "private/imagen_cielo_default.jpg"; // poner el path de la imagen default.
		informarErrorEnEscenario("imagen_cielo", node, log, 0, &escenario->imagen_cielo);
	}																						fs << "escenario->imagen_cielo " << escenario->imagen_cielo << std::endl;

	if (chequearMap(node, "equiposPermitidos", 1, log)) node["equiposPermitidos"] >> escenario->equiposPermitidos;			
	else {
		escenario->equiposPermitidos = 4; //default;
		informarErrorEnEscenario("equiposPermitidos", node, log, escenario->equiposPermitidos, 0);
	}

	fs.close();

	std::string tipo;
	YAML::Node nodoObjetos;
	YAML::Mark mark;
	// chequear tipo del nodo objetos, que no este vacio(size), que este esa key(objetos)
	try {
		const YAML::Node& nodoObjetos = node["objetos"];
		if (nodoObjetos.Type() != 2) {
			mark = nodoObjetos.GetMark();
			std::stringstream s;	s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
			s << "Error de formato de entrada de los datos del escenario-> Se abre un escenario default.";
			log.escribirLog(s.str());
			return false;
		} else if (!nodoObjetos.size()) {
			mark = nodoObjetos.GetMark();
			std::stringstream s;	s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
			s << "No hay objetos en el escenario!. Se abre un escenario default.";
			log.escribirLog(s.str());
			return false;
		}
		for (unsigned i=0; i < nodoObjetos.size(); i++) {
			try {
				nodoObjetos[i]["tipo"].to<std::string>();
				if (chequearMap(nodoObjetos[i], "tipo", 2, log)) {
					nodoObjetos[i]["tipo"] >> tipo;
					if (!strcmp(tipo.c_str(),"circulo")) {
						Circulo* objeto = new Circulo();
						pasarParametros(escenario, nodoObjetos[i], objeto, log);
						objeto->actualizar();
						escenario->objetos->push_back(objeto);
					} else if (!strcmp(tipo.c_str(),"polireg")) {
						PoligonoRegular* objeto = new PoligonoRegular();
						pasarParametros(escenario, nodoObjetos[i], objeto, log);
						escenario->objetos->push_back(objeto);
					}else if (!strcmp(tipo.c_str(),"rectangulo")) {
						Rectangulo* objeto = new Rectangulo();
						pasarParametros(escenario, nodoObjetos[i], objeto, log);
						escenario->objetos->push_back(objeto);
					} 
					
					//Para pruebas, provisional
					else if (!strcmp(tipo.c_str(), "gusano")){
						Gusano* objeto = new Gusano("hola", 1,0); //HARDCODEADO para darle un nombre nomas
						pasarParametros(escenario, nodoObjetos[i], objeto, log);
						objeto->actualizar();
						escenario->objetos->push_back(objeto);
					} else {
						mark = nodoObjetos[i]["tipo"].GetMark();
						std::stringstream s; s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
						s << tipo <<": tipo de objeto ingresado incorrecto. Objeto eliminado";
						log.escribirLog(s.str());
					}
				}
			} catch (const YAML::KeyNotFound& e) {
				std::stringstream s; s<<"Line: "<<e.mark.line+1<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
				s << "Faltan atributos del objeto en el archivo. Se lo elimina del escenario.";
				log.escribirLog(s.str());
			} catch (const YAML::InvalidScalar& e) {
				std::stringstream s; s<<"Line: "<<e.mark.line+1<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
				s << "El formato de los atributos del objeto en el archivo es incorrecto. Se lo elimina del escenario.";
				log.escribirLog(s.str());
			}
		}
	} catch (const YAML::KeyNotFound& e) {
		std::stringstream s; s<<"Line: "<<e.mark.line+1<<", Column: "<< e.mark.column <<". Msg: "<< e.msg<<".";
		log.escribirLog(s.str());
	}
	
	fs.open ("test.txt", std::fstream::app);
	fs << "escenario->objetos.size():" <<escenario->objetos->size()<< std::endl;
	fs.close();
	return true;
}

Escenario* Parseador::parsearEscenarioDefault(Escenario* miEscenario, Log log) {
		YAML::Mark mark;
		std::ifstream fin("private/escenario.yaml");	
		YAML::Parser parser(fin);	
		YAML::Node doc;
		mark = doc.GetMark();
		parser.GetNextDocument(doc);
		pasarParametros(doc[0], miEscenario, log);
		return miEscenario;
}

Escenario* Parseador::parsearEscenario(Escenario* miEscenario, char* pathEscenario, Log log){
		
        YAML::Mark mark;
        try {
            std::ifstream fin(pathEscenario);  //chequear si no esta el archivo o no se puede abrir.cargar uno por defecto?
			if (fin == NULL){  //if (!fin)
				log.escribirLog("No se encontro el archivo que describe el escenario. Se crea un escenario default.");
				this->parsearEscenarioDefault(miEscenario, log);
			}else{
				YAML::Parser parser(fin);
				YAML::Node doc;
				mark = doc.GetMark();
				if (parser.GetNextDocument(doc)) {
					if (doc.Type() != 2 || doc.size() != 1 ) {
						std::stringstream s;	s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
						s << "Error de formato de entrada de los datos del escenario. Se abre un escenario default.";
						log.escribirLog(s.str());
						parsearEscenarioDefault(miEscenario, log);
					} else if (!pasarParametros(doc[0], miEscenario, log)) {
						std::stringstream s;	s<<"Line: "<<mark.line+1<<", Column: "<< mark.column <<"."<< std::endl;
						s << "Error de formato de entrada de los datos del escenario. Se abre un escenario default.";
						log.escribirLog(s.str());
						parsearEscenarioDefault(miEscenario, log);
					}
				}
			}	
        } catch (YAML::ParserException& e) {
                std::stringstream s; s << e.what() << " .Se crea un escenario default.";          
				log.escribirLog(s.str());
				parsearEscenarioDefault(miEscenario, log); // ver esto
        } catch (const YAML::TypedKeyNotFound<int>& e) {
                std::stringstream s; s << e.what() << " .Se crea un escenario default.";           
				log.escribirLog(s.str());
				parsearEscenarioDefault(miEscenario, log); // ver esto
        }
		return miEscenario;      
}