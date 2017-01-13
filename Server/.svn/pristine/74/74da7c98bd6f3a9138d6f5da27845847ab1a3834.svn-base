#include <WinSock2.h>
#include <iostream>
#include "Log.h"
#include "SDL_thread.h"
#include "SDL.h"
#include "SocketCliente.h"

#define TAM_DE_LO_Q_MANDA_SERVIDOR 18

class Cliente {
public:
	SocketCliente* socket;
	SOCKADDR_IN servidor_addr;
	int puerto_en_servidor;
	bool trabajando;
	bool recibiendo;
	char* accionCliente;
	char* buffer_receptor;
	char* juegoActual;

	//void recibirMsj(int largo);

	Cliente(int puertoEnServidor, char* ipServidor);
	//void enviarInfo();
	//void recibirInfo();
	int esperaCierre(void* ptr);
	void hayQueTerminar();
	//void terminarConexion();
};