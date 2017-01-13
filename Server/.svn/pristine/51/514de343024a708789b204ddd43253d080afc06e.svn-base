//#include "Parseador.h"
//#include "Box2D\Box2D.h"
//#include "Gusano.h"
//
//#define TIME_STEP 1.0f / 60.0f
//#define VELOCITY_ITERATIONS 10
//#define POSITION_ITERATIONS 10
//#define PATH_LOG "log.txt"
//#define PATH_ESCENARIO "escenario.yaml"
//
//
//class QueryCallback : public b2QueryCallback
//{
//public:
//	QueryCallback(const b2Vec2& point)
//	{
//		m_point = point;
//		m_fixture = NULL;
//	}
//
//	bool ReportFixture(b2Fixture* fixture)
//	{
//		b2Body* body = fixture->GetBody();
//		if (body->GetType() == b2_dynamicBody)
//		{
//			bool inside = fixture->TestPoint(m_point);
//			if (inside)
//			{
//				m_fixture = fixture;
//
//				// We are done, terminate the query.
//				return false;
//			}
//		}
//
//		// Continue the query.
//		return true;
//	}
//
//	b2Vec2 m_point;
//	b2Fixture* m_fixture;
//};
//
//
//
//void seleccionarCuerpo(Escenario* unEscenario, b2World* unMundo, Gusano** gusano){
//	/*if((*cuerpo) != NULL){
//		Objeto* objeto = (Objeto*) ((*cuerpo)->GetUserData());
//		objeto->setElegido(false);
//	}*/
//	if( (*gusano) != NULL) 
//		(*gusano)->setElegido(false);
//
//	int xPx, yPx;
//	float xUn, yUn;
//
//	SDL_GetMouseState( &xPx, &yPx);
//
//	float escalaX = unEscenario->ancho_px / unEscenario->ancho_un;
//	float escalaY = unEscenario->alto_px / unEscenario->alto_un;
//
//
//	xUn= ((float)xPx + unEscenario->getOffsetX() )  / escalaX / unEscenario->recorredorDeImagenes->getZoom();
//	yUn= ( unEscenario->alto_px - (((float)yPx + unEscenario->getOffsetY() ) / unEscenario->recorredorDeImagenes->getZoom() ) ) / escalaY;
//
//	b2Vec2 p;
//	p.Set(xUn, yUn);
//
//	b2AABB aabb;
//	b2Vec2 d;
//	d.Set(0.01f, 0.01f);
//	aabb.lowerBound = p - d;
//	aabb.upperBound = p + d;
//
//	QueryCallback callback(p);
//	unMundo->QueryAABB(&callback, aabb);
//
//	if (callback.m_fixture){
//		//std::cout << "seleccionado un cuerpo" << std::endl;
//		b2Body *seleccionado = callback.m_fixture->GetBody();
//		//*cuerpo = callback.m_fixture->GetBody();
//		Objeto* objeto = (Objeto*)((seleccionado)->GetUserData());
//		if ( objeto->esGusano() ){
//			(*gusano) = (Gusano*)objeto;
//			objeto->setElegido(true);
//			std::cout << "Gusano seleccionado del " << (*gusano)->getNombre() << std::endl;
//		}
//	}
//}
//
//SDL_Window* crearVentana(Escenario* escenario, Log log){
//
//	SDL_Window* window = NULL;
//
//	//Creo la ventana del juego, centrada en la pantalla, con los valores que provee el escenario
//	window = SDL_CreateWindow("ARMAGEDDON", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, escenario->ancho_px, escenario->alto_px, 
//		SDL_WINDOW_SHOWN);
//
//	//Chequeo si la ventana se creó correctamente
//	if(window==NULL){		
//		log.escribirLog("Fatal error: No se pudo crear la ventana de la aplicación");
//		log.escribirLog("############################ FIN DE LA EJECUCIÓN ###################################");
//		SDL_Quit(); 
//		exit(1);
//	}
//
//	//seteo el renderer que se encargará de dibujar el juego
//	escenario->renderer = SDL_CreateRenderer(window, -1, 0);
//	
//	return window;
//}
//
//int main(int argc, char* argv[]) {
//
//	//Inicializo SDL
//	SDL_Init(SDL_INIT_VIDEO);
//
//	Log log(PATH_LOG);
//
//	log.escribirLog("############################ COMIENZO DE LA EJECUCIÓN ###################################");
//
//	Escenario* miEscenario = new Escenario(); //Donde ocurre la magia
//
//	Parseador* unParser = new Parseador(); //para cargar el escenario desde archivo
//
//	unParser->parsearEscenario(miEscenario, PATH_ESCENARIO, log); //cargo datos desde archivo "escenario.yaml"
//
//	//creo la ventana del juego
//	SDL_Window* window = crearVentana(miEscenario, log);
//	
//	// Vector de la gravedad
//    b2Vec2 gravity(0.0f, -10.0f);
//	// Mundo que vamos a utilizar 
//	b2World* mundo = new b2World(gravity);;
//	
//	//cargo objetos en el mundo: tierra, figuras geométricas, etc. Verifica solapamientos en esta etapa.
//	miEscenario->incluirObjetosEnElMundo(mundo);
//	
//	//configura imagenes de fondo, agua, etc
//	miEscenario->inicializarRecursosImagenes();
//
//    //LOOP DEL JUEGO
//	bool loop = true; //variable que controla el loop
//  	bool pausa = true; //variable que controla cuándo el juego está en pausa
//	SDL_Event evento; //variable para manejar eventos desde teclado
//	SDL_MouseWheelEvent eventoMouse;
//	int teclaS = 0; //variable para manejar arranque y reinicio del juego
//	int x=0;
//	int y=0;
//	Gusano* gusanoSeleccionado = NULL;
//
//	//PRUEBAS GUSANOS
//	//Gusano* unGusanito = new Gusano();
//	
//	//unGusanito->incluirEnMundo(mundo);
//
//	while (loop){
//    
//		//Si el juego no está en pausa, hago avanzar el tiempo
//		if (!pausa) mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
//		
//		//chequeo si los cuerpos está en el agua, para modificar su comportamiento
//		miEscenario->comprobarSiCuerposEnAgua(mundo->GetBodyList());
//		
//		//pinto el escenario: pinta el fondo, la tierra, el agua y los objetos
//		miEscenario->dibujarEscenario();
//		
//		//unGusanito->dibujarConColor(miEscenario->renderer, miEscenario->alto_px, miEscenario->ancho_px, miEscenario->alto_un, miEscenario->ancho_un, miEscenario->recorredorDeImagenes->getZoom());
//    
//		SDL_RenderPresent(miEscenario->renderer); //AFUERA DE DIBUJARESCENARIO PARA PRUEBAS
//		
//		
//		//Manejo eventos del teclado
//		while(SDL_PollEvent(&evento)){	
//			SDL_GetMouseState(&x,&y);
//			if ((miEscenario->ancho_px - x) < 30)
//				miEscenario->desplazarHacia(DERECHA);
//			else if ((x>0)&&(x<30))
//				miEscenario->desplazarHacia(IZQUIERDA);
//			if ((miEscenario->alto_px - y) < 30)
//				miEscenario->desplazarHacia(ABAJO);
//			else if ((y>0)&&(y<30))
//				miEscenario->desplazarHacia(ARRIBA);
//
//			if(evento.type == SDL_QUIT) loop = false;
//			if (evento.type == SDL_MOUSEWHEEL){
//				if (evento.wheel.y > 0){
//				miEscenario->incrementarZoom();
//				}else if (evento.wheel.y < 0){
//				miEscenario->decrementarZoom();
//				}
//			}
//			
//			if(evento.type == SDL_MOUSEBUTTONDOWN){
//					seleccionarCuerpo(miEscenario, mundo, &gusanoSeleccionado);
//			}
//
//			if(evento.type == SDL_KEYDOWN){
//				switch( evento.key.keysym.sym ){
//				case SDLK_p: //tecla "p" para pausar el juego
//					if (teclaS != 0) pausa = !pausa;
//					break;
//				case SDLK_s: //tecla "s" para iniciar/reiniciar el juego
//					if (teclaS == 0) {
//						pausa = false;
//						teclaS = 1;
//					} else{
//						log.escribirLog("---------------------------- SIMULACIÓN REINICIADA ----------------------------");
//						if(gusanoSeleccionado != NULL){
//							(gusanoSeleccionado)->setElegido(false);
//							gusanoSeleccionado = NULL;
//						}						
//						delete mundo;
//						mundo = new b2World(gravity);
//						miEscenario->incluirObjetosEnElMundo(mundo);
//						miEscenario->resetEquipos();
//						pausa = false;
//					}
//					break;
//				case SDLK_q: //tecla "q" para salir
//					loop = false;
//					break;
//				case SDLK_ESCAPE: //tecla "escape" para salir
//					loop = false;
//					break;
//				case SDLK_LEFT:
//					if(gusanoSeleccionado != NULL) gusanoSeleccionado->moverIzq();
//					break;
//				case SDLK_RIGHT: 
//					if(gusanoSeleccionado != NULL) gusanoSeleccionado->moverDer();
//					break;
//				case SDLK_SPACE:
//					if(gusanoSeleccionado != NULL) gusanoSeleccionado->saltar();
//				case SDLK_UP:
//					if(gusanoSeleccionado != NULL) gusanoSeleccionado->saltar();
//					break;
//				case SDLK_1:
//					miEscenario->agregarNuevoEquipo("Equipo 1", mundo);
//					break;
//				default:
//					break;
//				}
//			} else if(evento.type == SDL_QUIT){
//				loop = false;
//			} else 	if(evento.type == SDL_KEYUP){
//				switch( evento.key.keysym.sym){
//				case SDLK_LEFT:
//					if(gusanoSeleccionado != NULL) gusanoSeleccionado->frenar();
//					break;
//				case SDLK_RIGHT:
//					if(gusanoSeleccionado != NULL) gusanoSeleccionado->frenar();
//					break;
//				}
//			}
//		}
//	}
//
//    if(window){
//		SDL_DestroyWindow(window); 
//	}
//	
//	//finalizo SDL
//	SDL_Quit(); 
//
//	//Destruyo cosas que usé
//	
//	delete miEscenario;
//	delete mundo;
//	delete unParser;
//
//	log.escribirLog("############################ FIN DE LA EJECUCIÓN ###################################");
//	
//	return 0;
//
//}