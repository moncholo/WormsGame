
////////////////////////// FUNCIONES DE CLASE JUEGO ??? //////////////////////////////////
#include "Parseador.h"

#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 10
#define POSITION_ITERATIONS 10
#define PATH_LOG "log.txt"
#define PATH_ESCENARIO "escenario.yaml"

class QueryCallback : public b2QueryCallback {
	public:
        QueryCallback(const b2Vec2& point) {
			m_point = point;
			m_fixture = NULL;
        }
        bool ReportFixture(b2Fixture* fixture) {
			b2Body* body = fixture->GetBody();
			if (body->GetType() == b2_dynamicBody) {
				bool inside = fixture->TestPoint(m_point);
				if (inside) {
					m_fixture = fixture;

					// We are done, terminate the query.
					return false;
				}
			}
			// Continue the query.
			return true;
        }
        b2Vec2 m_point;
        b2Fixture* m_fixture;
};

void seleccionarCuerpo(Escenario* unEscenario, b2World* unMundo, Gusano** gusano, int xPx, int yPx) {
        /*if((*cuerpo) != NULL){
                Objeto* objeto = (Objeto*) ((*cuerpo)->GetUserData());
                objeto->setElegido(false);
        }*/
        if( (*gusano) != NULL) (*gusano)->setElegido(false);

        float xUn, yUn;

        float escalaX = unEscenario->ancho_px / unEscenario->ancho_un;
        float escalaY = unEscenario->alto_px / unEscenario->alto_un;

        xUn= ((float)xPx + unEscenario->getOffsetX() )  / escalaX / unEscenario->recorredorDeImagenes->getZoom();
        yUn= ( unEscenario->alto_px - (((float)yPx + unEscenario->getOffsetY() ) / unEscenario->recorredorDeImagenes->getZoom() ) ) / escalaY;

        b2Vec2 p;
        p.Set(xUn, yUn);

        b2AABB aabb;
        b2Vec2 d;
        d.Set(0.01f, 0.01f);
        aabb.lowerBound = p - d;
        aabb.upperBound = p + d;

        QueryCallback callback(p);
        unMundo->QueryAABB(&callback, aabb);

        if (callback.m_fixture){
			//std::cout << "seleccionado un cuerpo" << std::endl;
			b2Body *seleccionado = callback.m_fixture->GetBody();
			//*cuerpo = callback.m_fixture->GetBody();
			Objeto* objeto = (Objeto*)((seleccionado)->GetUserData());
			if ( objeto->esGusano() ){
				(*gusano) = (Gusano*)objeto;
				objeto->setElegido(true);
				std::cout << "Gusano seleccionado del " << (*gusano)->getNombre() << std::endl;
			}
        }
}

SDL_Window* crearVentana(Escenario* escenario, Log log) {

        SDL_Window* window = NULL;

        //Creo la ventana del juego, centrada en la pantalla, con los valores que provee el escenario
        window = SDL_CreateWindow("WORMS ARMAGEDDON", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, escenario->ancho_px, escenario->alto_px, 
                SDL_WINDOW_SHOWN);

        //Chequeo si la ventana se creó correctamente
        if(window==NULL){               
			log.escribirLog("Fatal error: No se pudo crear la ventana de la aplicación");
			log.escribirLog("############################ FIN DE LA EJECUCIÓN ###################################");
			SDL_Quit(); 
			exit(1);
        }

        //seteo el renderer que se encargará de dibujar el juego
        escenario->renderer = SDL_CreateRenderer(window, -1, 0);
        
        return window;
}

////////////////////////// FUNCIONES DE CLASE JUEGO ??? //////////////////////////////////

#include "Servidor.h"

Servidor::Servidor(int puerto) {
	puerto_donde_atiende = puerto;
	socket = new Socket(puerto_donde_atiende);
	socketS = socket->socket_;
	accionDeCliente = new char[TAM_DE_LO_Q_MANDA_CLIENTE];
	accionDeCliente = NULL;
	juegoActual = new SerializacionServidor;

}

void Servidor::escucharClientes () {
	Log log(PATH_LOG);
	int t = listen(socketS, 5);
    if (t == -1) {
		log.escribirLog("Error cuando se intento comenzar a escuchar en socket servidor.");
		return;						
	}
}

void Servidor::aceptarClientes () {
	Log log(PATH_LOG);
	SOCKADDR_IN cliente_addr;
	int cliente_len = sizeof(SOCKADDR_IN);

	std::cout << "aceptando..."<<std::endl;
	int socketC = accept(socketS, (struct sockaddr*) &cliente_addr, &cliente_len);

	void* ptr = NULL;
	if (socketC == -1) {
		log.escribirLog("No se pudo aceptar el cliente.");
		return;
	} else {
		Servidor_Atendedor* cliente = new Servidor_Atendedor(puerto_donde_atiende, socketC);
		std::cout << "creo hilo servidor: " << puerto_donde_atiende << std::endl;
		cliente->serverDondePertenece = this;
		clientes.push_back(cliente);
		std::cout << "clientes.size(): " << clientes.size() << std::endl;
		cliente->run();

		std::stringstream s;	s << "PUERTO " <<puerto_donde_atiende << ". Conexión aceptada.";
		log.escribirLog(s.str().data());
	}
}

int Servidor::esperaCierre() {
	char buffer[10] = "";
	while (buffer[0] != 'q' && trabajando) { std::cin >> buffer;}
	if (buffer[0] == 'q') {std::cout << "bufferq: " <<buffer<<std::endl; trabajando = false;}
	return 0;
}

void Servidor::run(){
	while (trabajando) {
		escucharClientes();
		if (clientes.size() == 4) {SDL_Delay(1000);std::cout << "Server completo. No se aceptan mas conexiones."<<std::endl;}
		while (trabajando && (clientes.size() < 4)) {
			aceptarClientes();
		}
	}
}

int aux3(void* server) {
	((Servidor*)server)->run();
	return 0;
}
void Servidor::start() {
	trabajando = true;
	hilo = SDL_CreateThread(aux3, "run", (void*)this);
}

void Servidor::hayQueTerminar() {
	trabajando = false;
	std::cout << "terminando hilos" <<std::endl;
	std::cout << "clientes.size(): " << clientes.size() <<std::endl;
	for (std::vector<Servidor_Atendedor*>::iterator it = clientes.begin(); it != clientes.end(); ++it) {
		(*it)->hayQueTerminar();	// (*it)->join((*it)->getHilo(), NULL);
		//clientes.erase(clientes.begin());
		//delete (*it);
		//std::cout << "clientes.size(): " << clientes.size() <<std::endl;
	}
	shutdown(socketS, 2);		// aca o abajo desp de terminar todos los Servidor_Atendedor??
	closesocket(socketS);
	WSACleanup();
}

int aux(void* server) {
	((Servidor*)server)->esperaCierre();
	return 0;
}

// esta funcion cumple la funcion del juego.
int Worms(void* server) {
	Servidor* servidor = (Servidor*)server;

	//Inicializo SDL
	ManejoSerializacionServidor* unSerialServer = new ManejoSerializacionServidor();
    
    SDL_Init(SDL_INIT_VIDEO);
	Log log(PATH_LOG);
	log.escribirLog("############################ COMIENZO DE LA EJECUCIÓN ###################################");

	Escenario* miEscenario = new Escenario(); //Donde ocurre la magia

	Parseador* unParser = new Parseador(); //para cargar el escenario desde archivo

	unParser->parsearEscenario(miEscenario, PATH_ESCENARIO, log); //cargo datos desde archivo "escenario.yaml"

	//creo la ventana del juego
    SDL_Window* window = crearVentana(miEscenario, log);
        
    // Vector de la gravedad
	b2Vec2 gravity(0.0f, -10.0f);
	// Mundo que vamos a utilizar 
	b2World* mundo = new b2World(gravity);;

	//cargo objetos en el mundo: tierra, figuras geométricas, etc. Verifica solapamientos en esta etapa.
	miEscenario->incluirObjetosEnElMundo(mundo);
	//configura imagenes de fondo, agua, etc
	miEscenario->inicializarRecursosImagenes();

    //LOOP DEL JUEGO
	bool loop = true; //variable que controla el loop
	bool pausa = true; //variable que controla cuándo el juego está en pausa
	SDL_Event evento; //variable para manejar eventos desde teclado

	int teclaS = 0; //variable para manejar arranque y reinicio del juego
	int x=0;
	int y=0;
	Gusano* gusanoSeleccionado = NULL;
	
	//PRUEBAS GUSANOS
	//Gusano* unGusanito = new Gusano("Rock", 1);
		   
	//unGusanito->incluirEnMundo(mundo);		
	//PRUEBAS GUSANOS
	//Gusano* unGusanito = new Gusano();

	//unGusanito->incluirEnMundo(mundo);
	miEscenario->agregarNuevoEquipo("Equipo 1", mundo);

	while (loop && servidor->trabajando){

		//Si el juego no está en pausa, hago avanzar el tiempo
		if (!pausa) mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		
		//chequeo si los cuerpos está en el agua, para modificar su comportamiento
		miEscenario->comprobarSiCuerposEnAgua(mundo->GetBodyList());

		//pinto el escenario: pinta el fondo, la tierra, el agua y los objetos
		miEscenario->dibujarEscenario();
		
		//unGusanito->dibujarConColor(miEscenario->renderer, miEscenario->alto_px, miEscenario->ancho_px, miEscenario->alto_un, miEscenario->ancho_un, miEscenario->recorredorDeImagenes->getZoom());

		SDL_RenderPresent(miEscenario->renderer); //AFUERA DE DIBUJARESCENARIO PARA PRUEBAS

		while(SDL_PollEvent(&evento)) {	

			if(evento.type == SDL_KEYDOWN){
				switch( evento.key.keysym.sym ){
				case SDLK_p: //tecla "p" para pausar el juego
					if (teclaS != 0) pausa = !pausa;
					break;
				case SDLK_s: //tecla "s" para iniciar/reiniciar el juego
					if (teclaS == 0) {
						pausa = false;
						teclaS = 1;
					}else{
						log.escribirLog("---------------------------- SIMULACIÓN REINICIADA ----------------------------");
						if(gusanoSeleccionado != NULL){
							(gusanoSeleccionado)->setElegido(false);
							gusanoSeleccionado = NULL;
						}						
						delete mundo;
						mundo = new b2World(gravity);
						miEscenario->incluirObjetosEnElMundo(mundo);
						miEscenario->resetEquipos();
						pausa = false;
					}
					break;
				}
			}
		
			if (servidor->accionDeCliente) {
				mensajeFinal* accionParseada = (mensajeFinal*)(servidor->accionDeCliente);
				for (std::vector<Servidor_Atendedor*>::iterator it = servidor->clientes.begin(); it != servidor->clientes.end(); ++it) {
					if ((*it)->activo) {
						switch (accionParseada->keyLectura){
							case mascaraClick:

								std::cout << "El loco hizo click x: "<< accionParseada->xMouse << " y: " << accionParseada->yMouse << std::endl;
								seleccionarCuerpo(miEscenario, mundo, &gusanoSeleccionado, accionParseada->xMouse,accionParseada->yMouse);
								if(gusanoSeleccionado)
									std::cout << "SELECCIONADO!"<< std::endl;
								break;

							case mascaraEsc:

								std::cout << "El loco hizo ESC, SALIR!"<< std::endl;
								break;

							case mascaraLeft:

								std::cout << "El loco toco IZQUIERDA, mover gusano >>>"<< std::endl;
								if(gusanoSeleccionado != NULL) gusanoSeleccionado->moverIzq();
								break;

							case mascaraPause:

								std::cout << "El loco puso PAUSE, cagon!" << std::endl;
								pausa = !pausa;

								break;
							case mascaraRight:

								std::cout << "El loco toco DERECHA, mover gusano <<<" << std::endl;
								if(gusanoSeleccionado != NULL) gusanoSeleccionado->moverDer();
								break;

							case mascaraUp:

								std::cout << "El loco toco ARRIBA, gusano SALTAR!" << std::endl;
								if(gusanoSeleccionado != NULL) gusanoSeleccionado->saltar();

								break;

						}
						
						unSerialServer->serializar(miEscenario->objetos);
						servidor->juegoActual = unSerialServer->getMensajeSerializado();
						(*it)->enviando = true;
						
					}
				}
				servidor->accionDeCliente = NULL;
			}
		}
		
	}

	//if(window){
	//	SDL_DestroyWindow(window); 
	//}

	////finalizo SDL
	SDL_Quit(); 

	//Destruyo cosas que usé

	delete miEscenario;
	delete mundo;
	delete unParser;
	delete unSerialServer;

	log.escribirLog("############################ FIN DE LA EJECUCIÓN ###################################");

	return 0;
		
}

int main (int argc, char* argv[]) {

	//Correr Juego: en un hilo no? el juego deberia tener un MOV que pueda ser seteado desd afuera por 
	//la funcion repartir juego. a su vez el juego  en cada uno de sus ciclos realiza este for:

	/*
	for (std::vector<Servidor_Atendedor*>::iterator it = clientes.begin(); it != clientes.end(); ++it) {
		(*it)->juegoActual = juegoActualizado;
		std::cout << "(*it)->juegoActual: " << (*it)->juegoActual <<std::endl;
	}
	*/

	// que actualiza el char* juegoActual que se envia constantemente a los clientes

	Servidor* server = new Servidor(PUERTO_SERVER);
	server->start();

	SDL_Thread* juego = SDL_CreateThread(Worms, "juego", (void*)server); // este es el thread que corre el juego
	SDL_Thread* esperoCierreServidor = SDL_CreateThread(aux, "esperaCierre", (void*)server);
	
	int* result = 0;
	SDL_WaitThread(esperoCierreServidor, result);
	server->hayQueTerminar();
	SDL_WaitThread(juego, result);
	SDL_WaitThread(server->hilo, result);
	
	std::cout << "Servidor cerro correctamente." << std::endl;
	system("PAUSE");

	return 0;
}
