#include <windows.h>
#include "Log.h"

#ifndef SOCKET__
#define SOCKET__

class Socket {
	public:
		int puerto, socket_, socketC;
		SOCKADDR_IN addr;	// The address structure for a TCP socket

		Socket(int puerto);
		Socket();
		int recibirInfo(char* buffer_receptor, int CantBytes);
		int enviarInfo(char* info, int cantBytes);
		void terminarConexion();
};

#endif