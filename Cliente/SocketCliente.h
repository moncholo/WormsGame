
#ifndef SOCKET__
#define SOCKET__

#include <windows.h>
#include "Log.h"
#include "Constantes.h"
class SocketCliente {
public:

	int socketC;
	SOCKADDR_IN addr;	// The address structure for a TCP socket

	SocketCliente (int puertoEnServidor, char* ipServidor);
	SocketCliente();
	int recibirInfo(char* buffer_receptor, int CantBytes);
	int enviarInfo(char* info, int cantBytes);
	void terminarConexion();
};

#endif