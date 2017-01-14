#include "Parseador.h"
#include "Cliente.h"
#include "MenuDeArmas.h"

Cliente::Cliente (int puertoEnServidor, char* ipServer) {
	Log log(PATH_LOG);
	socket = new SocketCliente(puertoEnServidor, ipServer);
	trabajando = true;
	accionCliente = NULL;
	buffer_receptor = new char[TAM_DE_LO_Q_RECIBE_CLIENTE];
	this->juegoActual = new ManejoSerializacionServidor();
	for (int i = 0; i < strlen(buffer_receptor); i++) buffer_receptor[i] = ' ';
	this->semHuboAccion = SDL_CreateSemaphore(1);
	this->semTocoJuegoActual = SDL_CreateSemaphore(1);
	this->semInicializador = SDL_CreateSemaphore(1);
	this->loop = true;
	jugando = false;
}

int Cliente::esperaCierre(void* ptr) {
	char buffer[10] = "";
	while (buffer[0] != 'q' && trabajando) { std::cin >> buffer;}
	if (buffer[0] == 'q') {//std::cout << "bufferq: " <<buffer<<std::endl;
	trabajando = false;}
	return 0;
}

void Cliente::hayQueTerminar() {
	trabajando = false;
	socket->terminarConexion();
}

//int aux(void* ptr) {
//	cliente1->esperaCierre(ptr);
//	return 0;
//}

int recibeYDibuja (void* client){
	
	int serverON;
	Cliente* cliente = (Cliente*) client;

	SDL_SemWait(cliente->semInicializador);
	SDL_SemPost(cliente->semInicializador);
	
	while(cliente->trabajando) {
		
		serverON = cliente->socket->recibirInfo(cliente->buffer_receptor,TAM_DE_LO_Q_RECIBE_CLIENTE);	//el server le envia el juego actualizado
		if (serverON == -1) {
			cliente->trabajando = false;
			std::cout << "Se desconecto el servidor."<<std::endl;
		} else {
			SDL_SemWait(cliente->semTocoJuegoActual);
			//std::cout << "EL SERVER ME MANDA EL JUEGO ACTUAL: " << ((SerializacionServidor*) cliente->buffer_receptor)->vectorObjetosEnviables[0].y <<std::endl;
			cliente->jugando = ((SerializacionServidor*) (cliente->buffer_receptor))->jugando;
			cliente->juegoActual->setMensajeSerializado( (SerializacionServidor*) (cliente->buffer_receptor) );
			cliente->juegoActual->deSerializar(cliente->miEscenario->gusanos, cliente->miEscenario->objetos);
			cliente->juegoActual->deSerializarExplosion(cliente->miEscenario);
			cliente->juegoActual->deSerializarMuniciones(cliente->unMenu->getVectorDeMuniciones());
			cliente->miEscenario->turnoDe = cliente->juegoActual->getMensajeSerializado()->turnoDeEquipo;
			cliente->miEscenario->tiempoTurnoRestante = cliente->juegoActual->getMensajeSerializado()->tiempoTurnoRestante;
			cliente->miEscenario->playSonido( ((SerializacionServidor*) (cliente->buffer_receptor))->numeroDeSonido);
			SDL_SemPost(cliente->semTocoJuegoActual);
		}
		
	}
	return 0;
}

int enviaAccion (void* client){
	// desde el juego lo qe hace el cliente se pone en cliente->accionCliente
	Cliente* cliente = (Cliente*) client;
	
	SDL_SemWait(cliente->semInicializador);
	SDL_SemPost(cliente->semInicializador);

	while(cliente->trabajando) {
		if (cliente->accionCliente) {
			//semaforo
			SDL_SemWait(cliente->semHuboAccion);
			cliente->socket->enviarInfo((char*)(cliente->accionCliente),TAM_DE_LO_Q_MANDA_CLIENTE);	//le manda la accion al server
			//std::cout <<std::endl<< "MANDO ACCION AL SERVER: " << (int) cliente->accionCliente->keyLectura <<std::endl<<std::endl;
			cliente->accionCliente = NULL;
			SDL_SemPost(cliente->semHuboAccion);
			//semaforo accion
		}
	}
	return 0;
}


int Worms(void* client) {
	
	Cliente* cliente = (Cliente*) client;
	SDL_SemWait(cliente->semInicializador);

	Log log(PATH_LOG);
	
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	Escenario* unEscenario = new Escenario(); //Donde ocurre la magia
	
	char ok = 0;

	//RECIBO YAML DEL SERVER
	char buffer[TAM_MAX_YAML] = {'0'};
	while(buffer[0] == '0'){
		cliente->socket->recibirInfo(buffer,TAM_MAX_YAML);
	}
	ok = 1;
	cliente->socket->enviarInfo(&ok, 1);
	FILE* pArchivo=	fopen( PATH_ESCENARIO,"wb");
	if(pArchivo != NULL){

		int tamanioArchivo = ((yamlEnviable*)buffer)->tamanio;
		char* contenidoArchivo = ((yamlEnviable*)buffer)->contenido;
		std::cout << ((yamlEnviable*)buffer)->tamanio << std::endl << ((yamlEnviable*)buffer)->contenido << "termine" << std::endl;
		if (tamanioArchivo) {
			fwrite( ((yamlEnviable*)buffer)->contenido, 1, tamanioArchivo, pArchivo);
		}
		fclose(pArchivo);
	}
	

	//REcIBO IMAGEN CORTADA DEL SERVER
	char bufferImagen[TAM_MAX_IMAGEN+TAM_MAX_NOMBRE_IMAGEN+2*sizeof(int)] = {'0'};
	
	while(bufferImagen[0] == '0'){
		cliente->socket->recibirInfo(bufferImagen,TAM_MAX_IMAGEN+TAM_MAX_NOMBRE_IMAGEN+2*sizeof(int));
	}
	ok = 2;
	cliente->socket->enviarInfo(&ok, 1);

	std::cout << "largo nombre imagen: " <<((imagenEnviable*)bufferImagen)->largoNombreImagen << " y nombre :" <<((imagenEnviable*)bufferImagen)->nombre << std::endl;
	int largo = ((imagenEnviable*)bufferImagen)->largoNombreImagen;
	std::cout << "LARGO: " << largo << std::endl;
	char *cstr = new char[((imagenEnviable*)bufferImagen)->largoNombreImagen];
	strcpy(cstr, (char*)(((imagenEnviable*)bufferImagen)->nombre));
	std::cout << cstr << std::endl;
	FILE* pArchivoImagen=fopen(cstr,"wb"); 
	if(pArchivoImagen != NULL){

		int tamanioArchivoImagen = ((imagenEnviable*)bufferImagen)->tamanio;
		char* contenidoArchivoImagen = ((imagenEnviable*)bufferImagen)->contenido;
		if (tamanioArchivoImagen) {
			fwrite( ((imagenEnviable*)bufferImagen)->contenido, 1, tamanioArchivoImagen, pArchivoImagen);
		}
		fclose(pArchivoImagen);
	}//acordarse de hacer el free[];

	//REcIBO IMAGEN DEL SERVER

	bufferImagen[0] = '0';
	
	while(bufferImagen[0] == '0'){
		cliente->socket->recibirInfo(bufferImagen,TAM_MAX_IMAGEN+TAM_MAX_NOMBRE_IMAGEN+2*sizeof(int));
	}
	ok = 4;
	cliente->socket->enviarInfo(&ok, 1);

	std::cout << "largo nombre imagen: " <<((imagenEnviable*)bufferImagen)->largoNombreImagen << " y nombre :" <<((imagenEnviable*)bufferImagen)->nombre << std::endl;
	char *cstr2 = new char[((imagenEnviable*)bufferImagen)->largoNombreImagen];
	strcpy(cstr2, (char*)(((imagenEnviable*)bufferImagen)->nombre));
	std::cout << cstr2 << std::endl;
	FILE* pArchivoImagen2=fopen(cstr2,"wb"); 
	if(pArchivoImagen2 != NULL){

		int tamanioArchivoImagen = ((imagenEnviable*)bufferImagen)->tamanio;
		char* contenidoArchivoImagen = ((imagenEnviable*)bufferImagen)->contenido;
		if (tamanioArchivoImagen) {
			fwrite( ((imagenEnviable*)bufferImagen)->contenido, 1, tamanioArchivoImagen, pArchivoImagen2);
		}
		fclose(pArchivoImagen2);
	}

	delete[] cstr2;
	
	//RECIBO IMAGEN DEL CIELO DEL SERVER
	//char bufferImagenCielo[TAM_MAX_IMAGEN+TAM_MAX_NOMBRE_IMAGEN+2*sizeof(int)] = {'0'};
	bufferImagen[0] = '0';

	while(bufferImagen[0] == '0'){
		cliente->socket->recibirInfo(bufferImagen,TAM_MAX_IMAGEN+TAM_MAX_NOMBRE_IMAGEN+2*sizeof(int));
	}
	ok = 3;
	cliente->socket->enviarInfo(&ok, 1);

	std::cout << "largo nombre imagen: " <<((imagenEnviable*)bufferImagen)->largoNombreImagen << " y nombre :" <<((imagenEnviable*)bufferImagen)->nombre << std::endl;
	int largoNom = ((imagenEnviable*)bufferImagen)->largoNombreImagen;
	std::cout << "LARGO: " << largoNom << std::endl;
	char *cstrCielo = new char[((imagenEnviable*)bufferImagen)->largoNombreImagen];
	strcpy(cstrCielo, (char*)(((imagenEnviable*)bufferImagen)->nombre));
	std::cout << cstrCielo << std::endl;
	FILE* pArchivoCielo=fopen(cstrCielo,"wb"); 
	if(pArchivoCielo != NULL){

		int tamanioArchivoImagenCielo = ((imagenEnviable*)bufferImagen)->tamanio;
		char* contenidoArchivoImagenCielo = ((imagenEnviable*)bufferImagen)->contenido;
		if (tamanioArchivoImagenCielo) {
			fwrite( ((imagenEnviable*)bufferImagen)->contenido, 1, tamanioArchivoImagenCielo, pArchivoCielo);
		}
		fclose(pArchivoCielo);
	}//acordarse de hacer el free[];

	delete[] cstrCielo;




	//PARSEO EL YAML
	Parseador* unParser = new Parseador(); //para cargar el escenario desde archivo
	unParser->parsearEscenario(unEscenario, PATH_ESCENARIO, log); //cargo datos desde archivo "escenario.yaml"
	delete unParser;

	unEscenario->imagen_tierra = cstr;

	delete[] cstr;

	cliente->miEscenario = unEscenario;

	//SDL_Thread* entrada = SDL_CreateThread(entradaDeDatos, "entrada", (void*)client);

	//cargar escenario, abrir ventana y dibujar. Inicializar juegoActual.
	SDL_Window* window = SDL_CreateWindow("WORMS ARMAGEDDON", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, cliente->miEscenario->ancho_px, cliente->miEscenario->alto_px, 
		SDL_WINDOW_SHOWN);

	//Chequeo si la ventana se creó correctamente
	if(window==NULL){		
		SDL_Quit();
		TTF_Quit();
		exit(1);
	}

	cliente->miEscenario->renderer = SDL_CreateRenderer(window, -1, 0);
	//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	
	//SDL_Surface* surfaceDelCielo = IMG_Load("cielo.png");
	//SDL_Texture* textureDelCielo = SDL_CreateTextureFromSurface(renderer,surfaceDelCielo);
	////seteo el renderer que se encargará de dibujar el juego
	//SDL_RenderCopy(renderer,textureDelCielo,NULL,NULL);

	//SDL_Delay(150);

	unEscenario->inicializarRecursosImagenes();
	//cliente->miEscenario->dibujarEscenario();
	log.escribirLog("############################ COMIENZO DE LA EJECUCIÓN ###################################");

			//cliente->miEscenario->dibujarEscenario();
			//SDL_RenderPresent(cliente->miEscenario->renderer); //AFUERA DE DIBUJARESCENARIO PARA PRUEBAS
	//SDL_Delay(5000);

	SDL_Event evento;
	char mensaje=0;
	int x=0;
	int armaAnterior = 2;
	int y=0;
	char click = 0;
	int potencia = 0;

	MenuDeArmas* unMenu = new MenuDeArmas(500,100,cliente->miEscenario->renderer);


	cliente->unMenu = unMenu;
	
	ManejoSerializacionCliente* unSerialClient = new ManejoSerializacionCliente;

	SDL_SemPost(cliente->semInicializador);

	SDL_Surface* imagenInicio = IMG_Load("private/bill.jpg");
	SDL_Texture* textureimagenInicio = SDL_CreateTextureFromSurface(cliente->miEscenario->renderer,imagenInicio);

	cliente->miEscenario->dibujarEscenario();

	while (cliente->trabajando && cliente->loop) {
	
		if (SDL_PollEvent(&evento)){
			potencia = 0;
			mensaje= 0;
			click=0;
			if (evento.type == SDL_MOUSEWHEEL){
				if (evento.wheel.y > 0){
					cliente->miEscenario->incrementarZoom();
				}else if (evento.wheel.y < 0){
					cliente->miEscenario->decrementarZoom();
				}
			}
			SDL_GetMouseState(&x,&y);
			//solo se puede scrollear cuando el menu esta deshabilitado
			if (!cliente->unMenu->isActive()){
			if ((cliente->miEscenario->ancho_px - x) < 30)
				cliente->miEscenario->desplazarHacia(DERECHA);
			else if ((x>0)&&(x<30))
				cliente->miEscenario->desplazarHacia(IZQUIERDA);
			if ((cliente->miEscenario->alto_px - y) < 30)
				cliente->miEscenario->desplazarHacia(ABAJO);
			else if ((y>0)&&(y<30))
				cliente->miEscenario->desplazarHacia(ARRIBA);
			
			}
			if(evento.type == SDL_MOUSEBUTTONDOWN){
				mensaje = mascaraClick;

				if(cliente->unMenu->seleccionarArma(x,y) != -1){
					unSerialClient->unMensajeFinal->arma = cliente->unMenu->seleccionarArma(x,y);
					if(unSerialClient->unMensajeFinal->arma != -1){
						cliente->miEscenario->playSonido(NUMERO_SERIAL_CARGAPISTOLA);
					}
					
				}else{
					mensaje = mascaraClick;
				click = 1;
				}
				//seleccionarCuerpo(miEscenario, mundo, &gusanoSeleccionado);
			}


			if(evento.type == SDL_KEYDOWN){
				switch( evento.key.keysym.sym ){
				case SDLK_p: //tecla "p" para pausar el juego

					mensaje = mascaraPause;
					
					break;
				case SDLK_ESCAPE: //tecla "escape" para salir

					mensaje = mascaraEsc;
					cliente->loop = false;
					break;
				case SDLK_LEFT:

					mensaje = mascaraLeft;
					//if(gusanoSeleccionado != NULL) gusanoSeleccionado->moverIzq();
					break;
				case SDLK_SPACE:
					
					mensaje= 0;

					mensaje = mascaraDisparo;

					//if(gusanoSeleccionado != NULL) gusanoSeleccionado->moverIzq();
					break;
				case SDLK_RIGHT: 

					mensaje = mascaraRight;
					//if(gusanoSeleccionado != NULL) gusanoSeleccionado->moverDer();
					break;
				case SDLK_RETURN:

					mensaje = mascaraUp;
					//if(gusanoSeleccionado != NULL) gusanoSeleccionado->saltar();
					break;
				case SDLK_1:
					cliente->miEscenario->playSonido(NUMERO_SERIAL_CARGAPISTOLA);
					unSerialClient->unMensajeFinal->arma = 1;
					cliente->unMenu -> seleccionarArma(0);
					break;
				case SDLK_2:
					cliente->miEscenario->playSonido(NUMERO_SERIAL_CARGAPISTOLA);
					unSerialClient->unMensajeFinal->arma = 2;
					cliente->unMenu -> seleccionarArma(1);
					break;
				case SDLK_3:
					cliente->miEscenario->playSonido(NUMERO_SERIAL_CARGAPISTOLA);
					unSerialClient->unMensajeFinal->arma = 3;
					cliente->unMenu -> seleccionarArma(2);
					break;
				case SDLK_4:
					cliente->miEscenario->playSonido(NUMERO_SERIAL_CARGAPISTOLA);
					unSerialClient->unMensajeFinal->arma = 4;
					cliente->unMenu -> seleccionarArma(3);
					break;
				case SDLK_m:
					if(cliente->unMenu->isActive()){
						cliente->miEscenario->manejadorSonido->dalePlayAlTema(NUMERO_SERIAL_CERRARMENU);
					}
					else{
						cliente->miEscenario->manejadorSonido->dalePlayAlTema(NUMERO_SERIAL_ABRIRMENU);
					}
					cliente->unMenu->setActivo(!(cliente->unMenu->isActive()));				
					break;
				case SDLK_UP:
					mensaje = mascaraAnguloUp;
					break;
				case SDLK_DOWN:
					mensaje = mascaraAnguloDown;
					break;

				case SDLK_n:
					if (cliente->jugando = false) {
						mensaje = mascaraEsc;
						cliente->loop = false;
					}
					break;

				case SDLK_s:
					if (cliente->jugando = false) {
						mensaje = mascaraQuieroSeguirJugando;
						//cliente->loop = false;
					}
					break;

				default:
					break;
				}
			} else if(evento.type == SDL_KEYUP){
				switch( evento.key.keysym.sym){
				case SDLK_LEFT:

					mensaje = mascaraKeyUp;
					break;
				case SDLK_RIGHT:
					mensaje = mascaraKeyUp;
					break;
				case SDLK_SPACE:
					mensaje = mascaraKeyUp;
					
					std::cout<< "Se envia el disparo" << std::endl;
					break;

				}
			}
		}
		if(click){
			//SDL_Delay(1000);
			float escalaX = cliente->miEscenario->ancho_px / cliente->miEscenario->ancho_un;
			float escalaY = cliente->miEscenario->alto_px / cliente->miEscenario->alto_un;
			int xUn= ((float)x + cliente->miEscenario->getOffsetX() )  / escalaX / cliente->miEscenario->recorredorDeImagenes->getZoom();
			int yUn= ( cliente->miEscenario->alto_px - (((float)y + cliente->miEscenario->getOffsetY() ) / cliente->miEscenario->recorredorDeImagenes->getZoom() ) ) / escalaY;
			
			unSerialClient->serializarMensajeFinalConClick(mensaje, &xUn,&yUn);
			//std::cout<< "mando con click x: " << x << " y : " << y << std::endl;
			//std::cout<< "mando con click xUn: " << xUn << " yUn : " << yUn << std::endl;
		}
		else{ 
			unSerialClient->serializarMensajeFinalSinClick(mensaje);
		}
		if (mensaje || (armaAnterior != unSerialClient->unMensajeFinal->arma) && (cliente->jugando)){
			armaAnterior = unSerialClient->unMensajeFinal->arma;
			SDL_SemWait(cliente->semHuboAccion);
			cliente->accionCliente = unSerialClient->unMensajeFinal;
			SDL_SemPost(cliente->semHuboAccion);
			//SDL_Delay(20);
		}
		//SDL_Delay(10);

		if(cliente->juegoActual->getMensajeSerializado()->reinicio){

			SDL_Surface* unSurface = IMG_Load("private/inicial.png");
			SDL_Surface* surfaceAux = cliente->miEscenario->miProcesador->superficie;
			cliente->miEscenario->miProcesador->superficie = unSurface;
			SDL_FreeSurface(surfaceAux);
			SDL_Texture* unTexture = SDL_CreateTextureFromSurface(cliente->miEscenario->renderer, unSurface);
			SDL_Texture* textureAux = cliente->miEscenario->unaTextura;
			cliente->miEscenario->unaTextura = unTexture;
			if (textureAux != NULL) SDL_DestroyTexture(textureAux);
		}
		
		SDL_SemWait(cliente->semTocoJuegoActual);			
		cliente->miEscenario->dibujarEscenario();		
		cliente->miEscenario->equipoGanador = cliente->juegoActual->getMensajeSerializado()->ganador;
		SDL_SemPost(cliente->semTocoJuegoActual);
		cliente->unMenu->mostrarMenu();
		
		if(!(cliente->jugando)) {
			if(!(cliente->jugando)){
				SDL_RenderCopy(cliente->miEscenario->renderer,textureimagenInicio,NULL,NULL);
			}
		}
		

		//SDL_semaphore* sem = SDL_CreateSemaphore(1);
		//SDL_SemWait(cliente->miEscenario->semaforoRenderer);
		SDL_RenderPresent(cliente->miEscenario->renderer);
		//SDL_SemPost(cliente->miEscenario->semaforoRenderer);

		SDL_Delay(7);


		for (int i = 0; i < (cliente->miEscenario->gusanos->size()); i++) {
			if (cliente->miEscenario->gusanos->at(i)->enMundo)
				cliente->miEscenario->gusanos->at(i)->estaMuerto(cliente->miEscenario->nivel_agua);
		}


		//cliente->miEscenario->dibujarEscenario();
		//SDL_RenderPresent(cliente->miEscenario->renderer); //AFUERA DE DIBUJARESCENARIO PARA PRUEBAS
		//dibujar(cliente->juegoActual);
	
	}
	//SDL_WaitThread(entrada, 0);
	//finaliza el SDL
	SDL_FreeSurface(imagenInicio);
	SDL_DestroyTexture(textureimagenInicio);
	SDL_Quit();
	TTF_Quit();
	return 0;
}

void Cliente::preguntarNombre(int a){
	char nombreUsuario[30] = {'0'};
	char buffer[100] = {' '};
	std::cout << "Ingrese su nombre: ";
	std::cin >> nombreUsuario;
	socket->enviarInfo(nombreUsuario, 30);
	socket->recibirInfo(buffer, 58);
	if (a == 0) std::cout << buffer << std::endl;
}

int main(int argc, char** argv) {

	char Ip_server[30] = {' '};
	
	char puerto_en_server[5] ="9000";

	std::cout << "Ingrese IP del servidor al que desea conectarse: ";
	std::cin >> Ip_server;
	/*std::cout << "Ingrese el puerto del servidor al que desea conectarse: ";
	std::cin >> puerto_en_server;*/
	
	int puerto = 0;
	for (int i = 0; i < strlen(puerto_en_server); i++) puerto += (puerto_en_server[i] - '0') * pow(10,3-i);

	Cliente* client = new Cliente(puerto, (char*)Ip_server);
	char buffer[2] = "0";
	int a = 0;
	while (buffer[0] == '0') {
		if (a>0) std::cout << "El servidor ya tiene un usuario con ese nombre. Elija otro." << std::endl;
		client->preguntarNombre(a);
		client->socket->enviarInfo("2",1);
		client->socket->recibirInfo(buffer, 1);
		a++;
	}

	std::cout << "\n-----------------\n\nBienvenido a Worms\n\n-----------------\n";

	client->trabajando = true;

	// HILO DEL JUEGO. DONDE SE ABRE LA VENTANA, SE CARGA EL ESCENARIO INICIAL y se espera por las acciones del cliente?
	
	
	SDL_Thread* juego = SDL_CreateThread(Worms, "worms", (void*)client);
	SDL_Delay(60); 
	
	
	SDL_Thread* recibeInfoYDibuja = SDL_CreateThread(recibeYDibuja, "recibeInfoYDibuja", (void*)client);
	SDL_Thread* enviaAccionAlServer = SDL_CreateThread(enviaAccion, "enviaAccionAlServer", (void*)client);

	int* result = 0;
	
	SDL_WaitThread(recibeInfoYDibuja, result);
	SDL_WaitThread(enviaAccionAlServer, result);
	client->hayQueTerminar();

	std::cout << "El cliente termino correctamente." <<std::endl;
	system("PAUSE");

	//SDL_WaitThread(esperoCierreCliente, result);

	return 0;
}