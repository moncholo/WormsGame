#include "ManejoSerializacionCliente.h"

	ManejoSerializacionCliente::ManejoSerializacionCliente(){
		this->unMensajeFinal = new mensajeFinal;
		this->unMensajeFinal->keyLectura = 32;
		
		this->unMensajeFinal->arma = 2;

	}

	ManejoSerializacionCliente::~ManejoSerializacionCliente(){
		delete this->unMensajeFinal;
	}

	void ManejoSerializacionCliente::serializarMensajeFinalConClick(unsigned char mensaje, int* x, int* y){
		
		this->unMensajeFinal->keyLectura = mensaje;
		this->unMensajeFinal->xMouse = *x;
		this->unMensajeFinal->yMouse = *y;
		this->unMensajeFinal->idCliente = -1;
		//this->unMensajeFinal->arma = 0;
		/*
		mensajeFinal[1] = (unsigned char) ( (*x)|(255) );
		mensajeFinal[2] = (unsigned char) ( ((*x)|(255 >> 8)) << 8);
		mensajeFinal[3] = (unsigned char) ( ((*x)|(255 >> 16)) << 16 );
		mensajeFinal[4] = (unsigned char) ( ((*x)|(255 >> 24)) << 24 );
		mensajeFinal[5] = (unsigned char) ( (*y)|(255) );
		mensajeFinal[6] = (unsigned char) ( ((*y)|(255 >> 8)) << 8 );
		mensajeFinal[7] = (unsigned char) ( ((*y)|(255 >> 16)) << 16 );
		mensajeFinal[8] = (unsigned char) ( ((*y)|(255 >> 24)) << 24 );
		*/
		
	}

	void ManejoSerializacionCliente::serializarMensajeFinalSinClick(unsigned char mensaje){

		this->unMensajeFinal->keyLectura = mensaje;
	}
