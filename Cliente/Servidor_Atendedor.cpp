#include "Servidor.h"

Servidor_Atendedor::Servidor_Atendedor() {}

Servidor_Atendedor::Servidor_Atendedor(int portS, int socketC) {
	socket = new Socket();
	socket->socketC = socketC;
	buffer_receptor = new char[TAM_DE_LO_Q_RECIBE_CLIENTE];
	for (int i = 0; i < strlen(buffer_receptor); i++) buffer_receptor[i] = ' ';
	enviando = true;
}

void Servidor_Atendedor::hayQueTerminar () { 
	trabajando = false;
	// enviar AL CLIENTE QUE SE CERRO EL SERVER.
	shutdown(socket->socketC, 2);	// es necesario para socketC?
	closesocket(socket->socketC);
	int* result = 0;
	SDL_WaitThread(hiloSend, result);
	SDL_WaitThread(hiloRecv, result);
}

int aux1 (void* servAtend){
	Servidor_Atendedor* atend = (Servidor_Atendedor*)servAtend;
	while (atend->trabajando && atend->activo) {
		while (atend->trabajando && atend->activo && atend->enviando) {
			SDL_Delay(INTERVALO_PARA_MANDAR_JUEGO);
			atend->socket->enviarInfo((char*)(atend->serverDondePertenece->juegoActual), TAM_DE_LO_Q_RECIBE_CLIENTE);
			std::cout << "SERVER ENVIA JUEGO ACTUAL: (muestro la y del primero)" << atend->serverDondePertenece->juegoActual->vectorObjetosEnviables[0].y << std::endl;
		}
	}
	return 0;
}

int aux2 (void* servAtend){
	Servidor_Atendedor* atend = (Servidor_Atendedor*)servAtend;
	int clienteOn;
	while (atend->trabajando && atend->activo) {
		clienteOn = atend->socket->recibirInfo(atend->buffer_receptor, TAM_DE_LO_Q_MANDA_CLIENTE);
		if (clienteOn == -1) {
			atend->activo = false;
			std::cout << "Se desconecto el cliente." << std::endl;
		} else {
			atend->enviando = false;
			std::cout << "SERVER RECIBE UNA ACCION DEL CLIENTE: " <<(int)((mensajeFinal*) atend->buffer_receptor)->keyLectura << std::endl;
			atend->serverDondePertenece->accionDeCliente = atend->buffer_receptor; //le paso la accion del cliente al server. accion es una
																	// variable del servidor. la seteamos desde aca.
								// en el ciclo del juego se comprueba si tiene algo y en caso de tener se ejecuta en el juego.													
			//if (buffer_receptor == Me voy || -1) {      // si se desconesta a sale
			//	activo = false;
			//}
		}
	}
	return 0;
}

void Servidor_Atendedor::run() {
	trabajando = true;
	activo = true;

	// INTERACCION CON CLIENTE PARA NOMBRE DE USUARIO
	
	//este hilo manda todo el tiempo el juego actual al cliente
	hiloSend = SDL_CreateThread(aux1, "hiloSend", (void*)this);
	
	//este hilo espera una accion del cliente
	hiloRecv = SDL_CreateThread(aux2, "hiloRead", (void*)this);
	
}