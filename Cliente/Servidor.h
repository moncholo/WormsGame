#ifndef server_
#define server_

#include <iostream>
#include "Log.h"

class Servidor;
#include "ManejoSerializacionCliente.h"
#include "ManejoSerializacionServidor.h"
#include "Servidor_Atendedor.h"
#include "SDL_thread.h"
#include "SDL.h"
#define PUERTO_SERVER 9000


#include "Socket.h"
#include "SDL_thread.h"
#include <string>

#define TAM_DE_LO_Q_RECIBE_CLIENTE 812
#define TAM_DE_LO_Q_MANDA_CLIENTE 12
#define INTERVALO_PARA_MANDAR_JUEGO 2000	// hay que regular este param segun lo que tarde en actualizar el juego

class Servidor_Atendedor {
public:
	Socket* socket;
	bool trabajando;
	Servidor* serverDondePertenece;
	bool activo;
	bool enviando;
	std::string nombreUsuario;
	SDL_Thread* hiloSend;
	SDL_Thread* hiloRecv;
	char* buffer_receptor;

	Servidor_Atendedor();
	Servidor_Atendedor(int portS, int socketC);

	void terminarConexion();
	void run();
	void hayQueTerminar ();

};


class Servidor {
public:
	int puerto_donde_atiende;
	SOCKADDR_IN servidor_addr;
	Socket* socket;
	SOCKET socketS;
	char buffer_receptor[100];
	std::vector<Servidor_Atendedor*> Servidor::clientes;
	SDL_Thread* hilo;
	bool trabajando;
	char* accionDeCliente;
	SerializacionServidor* juegoActual;

	Servidor();
	Servidor(int puertoDondeAtiende);
	void escucharClientes();
	void aceptarClientes();
	void repartirInfo(char* msj);
	void terminarConexion();
	int esperaCierre();
	void run();
	void start();
	void hayQueTerminar();
	void Servidor::eliminarCliente(Servidor_Atendedor* cliente);
};

#endif