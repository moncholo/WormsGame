#ifndef _CLIENTE_
#define _CRT_SECURE_NO_WARNINGS 

#include <windows.h>
#include <iostream>
#include "Log.h"
#include "SDL_thread.h"
#include "SDL.h"
#include "SocketCliente.h"
#include "ManejoSerializacionCliente.h"
#include "ManejoSerializacionServidor.h"
#include "Escenario.h"
#include "MenuDeArmas.h"

class Cliente {
public:
	MenuDeArmas* unMenu;

	SocketCliente* socket;
	SOCKADDR_IN servidor_addr;
	int puerto_en_servidor;
	bool trabajando;
	SDL_semaphore* semHuboAccion;
	SDL_semaphore* semTocoJuegoActual;
	SDL_semaphore* semInicializador;
	mensajeFinal* accionCliente;
	Escenario* miEscenario;
	char* buffer_receptor;
	ManejoSerializacionServidor* juegoActual;
	bool loop;
	void recibirMsj(int largo);
	bool jugando;

	Cliente(int puertoEnServidor, char* ipServidor);
	Cliente();
	void enviarInfo();
	void recibirInfo();
	int esperaCierre(void* ptr);
	void hayQueTerminar();
	void terminarConexion();
	void preguntarNombre(int a);
};
#endif // !_CLIENTE_