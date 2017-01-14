#ifndef __MANEJOSERIALIZACIONCLIENTE__

#include <iostream>
#include "Constantes.h"

struct mensajeFinal
{
	unsigned char keyLectura;

	int xMouse;

	int yMouse;

	int idCliente;

	int arma;

};

class ManejoSerializacionCliente{

public:

	mensajeFinal* unMensajeFinal;

	void serializarMensajeFinalConClick(unsigned char mensaje, int* x, int* y);

	void serializarMensajeFinalSinClick(unsigned char mensaje);

	ManejoSerializacionCliente();

	ManejoSerializacionCliente::~ManejoSerializacionCliente();
};


#endif