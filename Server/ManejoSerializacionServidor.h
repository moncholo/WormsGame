#ifndef __MANEJOSERIALIZACIONSERVIDOR__

#define _CRT_SECURE_NO_WARNINGS 0
#include <vector>
#include "Escenario.h"

struct yamlEnviable{
	int tamanio;
	char contenido[TAM_MAX_YAML];
};

struct imagenEnviable{
	int tamanio;
	char contenido[TAM_MAX_IMAGEN];

	int largoNombreImagen;
	char nombre[TAM_MAX_NOMBRE_IMAGEN];
};

struct ObjetoEnviable
{
	float rot;
	float x;
	float y;
	bool estaOnline;
	bool estaEnMundo;
	bool miraADerecha;
	char vida;
};

struct ArmaEnviable
{
	int idArma;
	float x;
	float y;
	int radio;
	float xExplosion;
	float yExplosion;
	bool disparoActivo;
	float xMira;
	float yMira;
	int tiempoDeVida;	
};


struct SerializacionServidor{
	int vectorMuniciones[NUMERO_DE_ARMAS];
	ObjetoEnviable vectorObjetosEnviables[CantidadMaximaGusanosPorJugador * CantidadMaximaJugadores + CantidadMaximaObjetos];
	ArmaEnviable armaActual;
	int cantidadDeJugadoresActual;
	int cantidadDeJugadores;
	int cantidadDeGusanosPorJugador;
	int cantidadDeObjetos;
	int gusanoSeleccionado;
	char numeroDeSonido;
	bool jugando;
	int turnoDeEquipo;
	int tiempoRestanteTurno;
	int ganador;
	bool reinicio;
	int idCliente;
	int tiempoParaReinicio;
};

class ManejoSerializacionServidor{
	private:
		SerializacionServidor* unaSerializacion;

	public:

		SerializacionServidor* getMensajeSerializado();

		void setMensajeSerializado(SerializacionServidor* serializacion);
		
		void setCantJugadoresPermitidos(int jugadoresPermitidos);

		void setCantJugadoresActual(int cantJugadoresAcutal);

		void setComienzoDelJuego(bool jugando_);
		
		void serializar(std::vector<Gusano*>* losGusanos, std::vector<Objeto*>* losObjetos, bool* estadoOnline);

		void deSerializarExplosion(Escenario* miEscenario);

		void deSerializar(std::vector<Gusano*>* losGusanos, std::vector<Objeto*>* losObjetos);

		int serializarYAML(char* fileYAML, char* serialYAML);

		void setSonido(int num);
		
		ManejoSerializacionServidor();
		~ManejoSerializacionServidor();
};

#endif