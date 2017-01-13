#ifndef _CLIENTE_

#include <windows.h>
#include <iostream>
#include "Log.h"
#include "SDL_thread.h"
#include "SDL.h"
#include "SocketCliente.h"
#include "ManejoSerializacionCliente.h"
#include "ManejoSerializacionServidor.h"

class Cliente {
public:
	SocketCliente* socket;
	SOCKADDR_IN servidor_addr;
	int puerto_en_servidor;
	bool trabajando;
	bool recibiendo;
	mensajeFinal* accionCliente;

	void recibirMsj(int largo);

	Cliente(int puertoEnServidor, char* ipServidor);
	Cliente();
	void enviarInfo();
	void recibirInfo();
	int esperaCierre(void* ptr);
	void hayQueTerminar();
	void terminarConexion();
};
#endif // !_CLIENTE_