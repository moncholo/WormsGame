#ifndef ServidorAtendedor
#define ServidorAtendedor

#include "Socket.h"
#include "SDL_thread.h"
#include <string>


#endif

//#ifndef server__
//#define server__
//#include "Servidor.h"
//#endif
//
//#ifndef ServidorAtendedor
//#define ServidorAtendedor
//
//#include "Socket.h"
//#include "SDL_thread.h"
//#include <string>
//
//#define INTERVALO_PARA_MANDAR_JUEGO 2000	// hay que regular este param segun lo que tarde en actualizar el juego
//
//class Servidor_Atendedor {
//public:
//	Socket* socket;
//	bool trabajando;
//	Servidor* serverDondePertenece;
//	bool activo;
//	bool enviando;
//	std::string nombreUsuario;
//	SDL_Thread* hiloSend;
//	SDL_Thread* hiloRecv;
//	char* buffer_receptor;
//
//	Servidor_Atendedor();
//	Servidor_Atendedor(int portS, int socketC);
//
//	void terminarConexion();
//	void run();
//	void hayQueTerminar ();
//
//};
//
//#endif