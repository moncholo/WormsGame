#include "Servidor.h"

Servidor_Atendedor::Servidor_Atendedor() {}

Servidor_Atendedor::Servidor_Atendedor(int portS, int socketC, int id) {
	socket = new Socket();
	socket->socketC = socketC;
	buffer_receptor = new char[TAM_DE_LO_Q_MANDA_CLIENTE];
	for (int i = 0; i < strlen(buffer_receptor); i++) buffer_receptor[i] = ' ';
	enviando = true;
	this->idCliente = id;
	jugando = false;
}

void Servidor_Atendedor::cargarArmas(b2World* mundo, Escenario* unEscenario) {
	armas = new std::vector<Arma*>;
	Arma_Patada* arma_p = new Arma_Patada;								armas->push_back(arma_p);
	Arma_Granada* arma_g = new Arma_Granada(mundo, unEscenario);		armas->push_back(arma_g);
	Arma_Bazooka* arma_b = new Arma_Bazooka(mundo, unEscenario);		armas->push_back(arma_b);
	Arma_SantaGranada* arma_sg = new Arma_SantaGranada(mundo,unEscenario);		armas->push_back(arma_sg);
	Arma_Dinamita* arma_d = new Arma_Dinamita(mundo,unEscenario);				armas->push_back(arma_d);
	Arma_AtaqueAereo* arma_a = new Arma_AtaqueAereo;					armas->push_back(arma_a);
	
}

void Servidor_Atendedor::hayQueTerminar () { 
	trabajando = false;
	// enviar AL CLIENTE QUE SE CERRO EL SERVER.
	shutdown(socket->socketC, 2);	// es necesario para socketC?
	closesocket(socket->socketC);
	int* result = 0;
	for(int i= 0; i < this->armas->size(); i++){
		delete armas->at(i);

	}
	SDL_WaitThread(hiloSend, result);
	SDL_WaitThread(hiloRecv, result);
}

int enviar (void* servAtend){
	Servidor_Atendedor* atend = (Servidor_Atendedor*)servAtend;
	while (atend->trabajando && atend->activo) {
			SDL_Delay(INTERVALO_PARA_MANDAR_JUEGO);//(atend->serverDondePertenece->gusanosSeleccionados->at(atend->idCliente))->idGusano();
			SDL_SemWait(atend->serverDondePertenece->unSemTocoJuegoActual);
			SDL_SemWait(atend->serverDondePertenece->semSeleccionados);

			for (int i = 0; i < NUMERO_DE_ARMAS; i++){
				atend->serverDondePertenece->juegoActual->vectorMuniciones[i] = atend->armas->at(i+1)->municiones;
			}
			Gusano* unGusano = (atend->serverDondePertenece->gusanosSeleccionados->at(atend->idCliente));
			if(unGusano != NULL){
				//std::cout << "seleccione " << unGusano->idGusano << std::endl;
				atend->serverDondePertenece->juegoActual->gusanoSeleccionado = unGusano->idGusano;
			}
			else{
				atend->serverDondePertenece->juegoActual->gusanoSeleccionado= -1;
			
			}
			SDL_SemPost(atend->serverDondePertenece->semSeleccionados);

			atend->serverDondePertenece->juegoActual->numeroDeSonido = (char)(atend->serverDondePertenece->miEscenario->sonidoActual);

			atend->serverDondePertenece->juegoActual->idCliente = atend->idCliente;

			atend->socket->enviarInfo((char*)(atend->serverDondePertenece->juegoActual), TAM_DE_LO_Q_RECIBE_CLIENTE);
			//std::cout<< "El radio enviado es: " << atend->serverDondePertenece->juegoActual->armaActual.x << std::endl;
			SDL_SemPost(atend->serverDondePertenece->unSemTocoJuegoActual);
			//std::cout << "SERVER ENVIA JUEGO ACTUAL: " << (atend->serverDondePertenece->juegoActual)->vectorObjetosEnviables[20].y << std::endl;
	}
	return 0;
}

int recv (void* servAtend){
	Servidor_Atendedor* atend = (Servidor_Atendedor*)servAtend;
	int clienteOn;
	
	while (atend->trabajando && atend->activo) {
		clienteOn = atend->socket->recibirInfo(atend->buffer_receptor, TAM_DE_LO_Q_MANDA_CLIENTE);
		if (clienteOn == -1) {
			atend->activo = false;
			std::cout << "Se desconecto el cliente." << std::endl;
			mensajeFinal* unMensajeAux = new mensajeFinal;
			unMensajeAux->keyLectura = mascaraEsc;
			unMensajeAux->idCliente = atend->idCliente;

			SDL_SemWait(atend->serverDondePertenece->semHuboAccion);
			atend->serverDondePertenece->accionDeCliente = unMensajeAux;
			SDL_SemPost(atend->serverDondePertenece->semHuboAccion);

		} else {

			SDL_SemWait(atend->serverDondePertenece->semHuboAccion);
			((mensajeFinal*)atend->buffer_receptor)->idCliente = atend->idCliente;
			//std::cout << "SERVER RECIBE UNA ACCION DEL CLIENTE: " << (int)((mensajeFinal*)(atend->buffer_receptor))->idCliente<< std::endl;
			atend->serverDondePertenece->accionDeCliente = (mensajeFinal*)(atend->buffer_receptor); //le paso la accion del cliente al server. accion es una
			//atend->serverDondePertenece->accionDeCliente->idCliente= atend->idCliente;
			SDL_SemPost(atend->serverDondePertenece->semHuboAccion);							
			// variable del servidor. la seteamos desde aca.
								// en el ciclo del juego se comprueba si tiene algo y en caso de tener se ejecuta en el juego.													
			//if (buffer_receptor == Me voy || -1) {      // si se desconesta a sale
			//	activo = false;
			//}
		}
	}
	return 0;
}

void Servidor_Atendedor::reasignarSocket(int socketC_) {
	socket->socketC = socketC_;
}

void Servidor_Atendedor::run() {
	trabajando = true;
	activo = true;

	ManejoSerializacionServidor *manejadorSerializacionDelServidor = new ManejoSerializacionServidor();
	cargarArmas(this->serverDondePertenece->mundo, this->serverDondePertenece->miEscenario);

	SDL_SemWait(this->serverDondePertenece->unSemTocoJuegoActual);
	SDL_SemWait(this->serverDondePertenece->semHuboAccion);
	SDL_SemWait(this->serverDondePertenece->semSeleccionados);

	char recibido = 0;
	//ENVIO EL YAML INICIAL
	yamlEnviable* unYamlEnviable = new yamlEnviable;
	int tamanio = manejadorSerializacionDelServidor->serializarYAML(PATH_ESCENARIO, (unYamlEnviable->contenido));
	unYamlEnviable->tamanio = tamanio;
	while(recibido != 1){
		this->socket->enviarInfo((char*)unYamlEnviable, TAM_MAX_YAML);
		this->socket->recibirInfo(&recibido,1);
	}
	
	delete unYamlEnviable;
	
	recibido = 0;

	
	std::cout << "recibido ok" << std::endl;

	//guardo la surface de la tierra en una imagen
	std::string pathImagenCortada = "private/imagenTierraCortada.png";
	char* cstr = new char[pathImagenCortada.length()+1];
	strcpy(cstr, pathImagenCortada.c_str());
	IMG_SavePNG(this->serverDondePertenece->miEscenario->miProcesador->getSurfaceDeLaTierra(), cstr);


	//ENVIO LA IMAGEN INICIAL
	//std::string pathImagenTierra = this->serverDondePertenece->miEscenario->imagen_tierra;
	imagenEnviable* unaImagenEscenario = new imagenEnviable;

	//char *cstr = new char[pathImagenTierra.length()+1];
	//strcpy(cstr, pathImagenTierra.c_str());
	
	int tamanioImagen = manejadorSerializacionDelServidor->serializarYAML(cstr, (unaImagenEscenario->contenido));
	//std::cout << cstr << "tam " << tamanioImagen << std::endl;
	
	unaImagenEscenario->tamanio = tamanioImagen;
	//largo del nombre de la imagen
	unaImagenEscenario->largoNombreImagen = (int)(pathImagenCortada.length()+1);

	//std::cout << "largo del nombre " << unaImagenEscenario->largoNombreImagen << std::endl;
	//seteo el nombre de la imagen
	for(int i = 0; i < unaImagenEscenario->largoNombreImagen; i++){
		unaImagenEscenario->nombre[i] = cstr[i];
	}
	std::cout << "Recibi: " << unaImagenEscenario->nombre << std::endl;
	while(recibido != 2){
		this->socket->enviarInfo((char*)unaImagenEscenario, TAM_MAX_IMAGEN+TAM_MAX_NOMBRE_IMAGEN+2*sizeof(int));
		this->socket->recibirInfo(&recibido,1);
	}
	/*for(int j = 0; j < tamanioImagen; j++){
		std::cout << unaImagenEscenario->contenido[j];
	}*/
	//std::cout << unaImagenEscenario->contenido << std::endl;

	delete[] cstr;

	// ENVIO IMAGEN ORIGINAL

	char* cstr2 = new char[this->serverDondePertenece->miEscenario->imagen_tierra.length()+1];
	strcpy(cstr2, this->serverDondePertenece->miEscenario->imagen_tierra.c_str());
		
	int tamanioImagenOriginal = manejadorSerializacionDelServidor->serializarYAML(cstr2, (unaImagenEscenario->contenido));
	//std::cout << cstr << "tam " << tamanioImagen << std::endl;
	
	unaImagenEscenario->tamanio = tamanioImagenOriginal;
	//largo del nombre de la imagen
	unaImagenEscenario->largoNombreImagen = 20;

	char auxNombre[20] = "private/inicial.png";
	for(int i = 0; i < 20; i++){
		unaImagenEscenario->nombre[i] = auxNombre[i];
	}

	while(recibido != 4){
		this->socket->enviarInfo((char*)unaImagenEscenario, TAM_MAX_IMAGEN+TAM_MAX_NOMBRE_IMAGEN+2*sizeof(int));
		this->socket->recibirInfo(&recibido,1);
	}

	delete[] cstr2;
	delete unaImagenEscenario;
	


	//ENVIO LA IMAGEN DEL CIELO
	std::string pathImagenCielo = this->serverDondePertenece->miEscenario->imagen_cielo;
	imagenEnviable* unaImagenCielo = new imagenEnviable;
	char *cstrCielo = new char[pathImagenCielo.length()+1];
	strcpy(cstrCielo, pathImagenCielo.c_str());
	int tamanioImagenCielo = manejadorSerializacionDelServidor->serializarYAML(cstrCielo, (unaImagenCielo->contenido));
	unaImagenCielo->tamanio = tamanioImagenCielo;
	unaImagenCielo->largoNombreImagen = (int)(pathImagenCielo.length()+1);
	for(int i = 0; i < unaImagenCielo->largoNombreImagen; i++){
		unaImagenCielo->nombre[i] = cstrCielo[i];
	}
	while(recibido != 3){
		this->socket->enviarInfo((char*)unaImagenCielo, TAM_MAX_IMAGEN+TAM_MAX_NOMBRE_IMAGEN+2*sizeof(int));
		this->socket->recibirInfo(&recibido,1);
	}
	delete unaImagenCielo;
	delete[] cstrCielo;


	delete manejadorSerializacionDelServidor;
	SDL_SemPost(this->serverDondePertenece->semSeleccionados);
	SDL_SemPost(this->serverDondePertenece->semHuboAccion);
	SDL_SemPost(this->serverDondePertenece->unSemTocoJuegoActual);


	//este hilo manda todo el tiempo el juego actual al cliente
	hiloSend = SDL_CreateThread(enviar, "hiloSend", (void*)this);
	
	//este hilo espera una accion del cliente
	hiloRecv = SDL_CreateThread(recv, "hiloRecv", (void*)this);
	
}