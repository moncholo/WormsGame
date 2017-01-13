#include "Cliente.h"

#define PUERTO_SERVER 9000
#define IP_SERVER "127.0.0.1"

Cliente::Cliente (int puertoEnServidor, char* ipServer) {
	Log log(PATH_LOG);
	socket = new SocketCliente(puertoEnServidor, ipServer);
	trabajando = true;
	accionCliente = NULL;
	buffer_receptor = new char[TAM_DE_LO_Q_MANDA_SERVIDOR];
	for (int i = 0; i < strlen(buffer_receptor); i++) buffer_receptor[i] = ' ';
	recibiendo = 1;
}

int Cliente::esperaCierre(void* ptr) {
	char buffer[10] = "";
	while (buffer[0] != 'q' && trabajando) { std::cin >> buffer;}
	if (buffer[0] == 'q') {std::cout << "bufferq: " <<buffer<<std::endl; trabajando = false;}
	return 0;
}

void Cliente::hayQueTerminar() {
	trabajando = false;
	socket->terminarConexion();
}

//int aux(void* ptr) {
//	cliente1->esperaCierre(ptr);
//	return 0;
//}

int recibeYDibuja (void* client){
	int serverON;
	Cliente* cliente = (Cliente*) client;
	while(cliente->trabajando) {
		while(cliente->trabajando && cliente->recibiendo) {
				
				serverON = cliente->socket->recibirInfo(cliente->buffer_receptor);	//el server le envia el juego actualizado
				if (serverON == -1) {
					cliente->trabajando = false;
					std::cout << "Se desconecto el servidor."<<std::endl;
				} else {
					std::cout << "EL SERVER ME MANDA EL JUEGO ACTUAL: " << cliente->buffer_receptor <<std::endl;
					//juegoActual = desserializar(buffer_receptor);
				}
		}
	}
	return 0;
}

int enviaAccion (void* client){
	// desde el juego lo qe hace el cliente se pone en cliente->accionCliente
	Cliente* cliente = (Cliente*) client;
	while(cliente->trabajando) {
		if (cliente->accionCliente) {
			SDL_Delay(1);
			cliente->socket->enviarInfo(cliente->accionCliente);	//le manda la accion al server
			std::cout <<std::endl<< "MANDO ACCION AL SERVER: " << cliente->accionCliente <<std::endl<<std::endl;
			cliente->accionCliente = NULL;
			cliente->recibiendo = true;
		}
	}
	return 0;
}

int Worms(void* client) {
	Cliente* cliente = (Cliente*) client;
	//cargar escenario, abrir ventana y dibujar. Inicializar juegoActual.
	/*while (cliente->trabajando) {
		dibujar(juegoActual);
		if (eventoDelCliente) {			//deberia haber un hilo aparte que espere la accion del cliente?
			A = serializarEvento();
			cliente->accionCliente = A;
		}
	}*/
	return 0;
}

// CLIENTE 1 !!

int main(int argc, char* argv[]) {

	//PREGUNTAR NOMBRE, IP_SERVER y PUERTO_SERVER.
	
	Cliente* client = new Cliente(PUERTO_SERVER, IP_SERVER);
	client->trabajando = true;

	// HILO DEL JUEGO. DONDE SE ABRE LA VENTANA, SE CARGA EL ESCENARIO INICIAL y se espera por las acciones del cliente?
	// SDL_Thread* juego = SDL_CreateThread(Worms, "recibeInfoYDibuja", (void*)client);

	SDL_Thread* recibeInfoYDibuja = SDL_CreateThread(recibeYDibuja, "recibeInfoYDibuja", (void*)client);
	SDL_Thread* enviaAccionAlServer = SDL_CreateThread(enviaAccion, "enviaAccionAlServer", (void*)client);
	//SDL_Thread* esperoCierreCliente = SDL_CreateThread(aux, "esperaCierre", (void*)NULL);
	SDL_Delay(15000);
	client->recibiendo = false;
	client->accionCliente = "estado del juego 2";
	SDL_Delay(6000);
	client->recibiendo = false;
	client->accionCliente = "estado del juego 4";
	SDL_Delay(6000);
	client->recibiendo = false;
	client->accionCliente = "estado del juego 6";

	int* result = 0;
	SDL_WaitThread(recibeInfoYDibuja, result);
	SDL_WaitThread(enviaAccionAlServer, result);
	client->hayQueTerminar();
	
	std::cout << "El cliente termino correctamente." <<std::endl;
	system("PAUSE");

	//SDL_WaitThread(esperoCierreCliente, result);

	return 0;
}