#include "Sonido.h"
#include <iostream>
#include "stdlib.h"

	Sonido::Sonido(){
		/*Inicializo el mixer, los samples y otras yerbas mas*/
		Mix_Init(SDL_INIT_AUDIO);
		Mix_AllocateChannels(NUMERO_DE_CHANNELS);
		Mix_OpenAudio(FRECUENCIA_DE_LOS_SONIDOS, MIX_DEFAULT_FORMAT, CANAL_PARA_ACTIVAR_COMO_STEREO, CHUNK_SIZE_USADO);
		
		this->numeroSerialTemaAnterior = -1;
		
		this->sample_AGUA = Mix_LoadWAV(PATH_AGUA);
		this->sample_SELFDESTRUCT = Mix_LoadWAV(PATH_SELFDESTRUCT);
		this->sample_DISPARO1 = Mix_LoadWAV(PATH_DISPARO1);
		this->sample_DISPAROBAZOOKA = Mix_LoadWAV(PATH_DISPAROBAZOOKA);
		this->sample_LANZOGRANADA = Mix_LoadWAV(PATH_LANZO_GRANADA);
		this->sample_LANZOGRANADASANTA = Mix_LoadWAV(PATH_LANZO_GRANADASANTA);
		this->sample_EXPLOSION1 = Mix_LoadWAV(PATH_EXPLOSION1);
		this->sample_EXPLOSION2 = Mix_LoadWAV(PATH_EXPLOSION2);
		this->sample_EXPLOSION3 = Mix_LoadWAV(PATH_EXPLOSION3);
		this->sample_CARGAPOTENCIA = Mix_LoadWAV(PATH_CARGO_POTENCIA);
		this->sample_FONDO1 = Mix_LoadWAV(PATH_FONDO);
		this->sample_FONDO2 = Mix_LoadWAV(PATH_FONDO2);
		this->sample_CAMBIOARMA = Mix_LoadWAV(PATH_CARGAPISTOLA);
		this->sample_HURRY = Mix_LoadWAV(PATH_HURRY);
		this->sample_HURRY2 = Mix_LoadWAV(PATH_HURRY2);
		this->sample_HURRY3 = Mix_LoadWAV(PATH_HURRY3);
		this->sample_SALTO1 = Mix_LoadWAV(PATH_SALTO1);
		this->sample_SALTO2 = Mix_LoadWAV(PATH_SALTO2);
		this->sample_ABRIRMENU = Mix_LoadWAV(PATH_ABRIRMENU);
		this->sample_CERRARMENU = Mix_LoadWAV(PATH_CERRARMENU);
		this->sample_ITSALIVE = Mix_LoadWAV(PATH_ITSALIVE);
		this->sample_USETHEFORCE = Mix_LoadWAV(PATH_USETHEFORCELUKE);
		this->sample_GOODDAYTODIE = Mix_LoadWAV(PATH_GOODDAYTODAY);
		this->sample_ITCOULDWORK = Mix_LoadWAV(PATH_ITCOULDWORK);
		this->sample_INCOMING = Mix_LoadWAV(PATH_INCOMING);
		this->sample_WHATTHE = Mix_LoadWAV(PATH_WHATTHE);
		this->sample_TRAITOR = Mix_LoadWAV(PATH_TRAITOR);
		this->sample_GALLINA = Mix_LoadWAV(PATH_GALLINA);
		this->sample_ESPERAYVERAS = Mix_LoadWAV(PATH_ESPERAYVERAS);
		this->sample_YESSIR = Mix_LoadWAV(PATH_YESSIR);
		this->sample_LEAVEMEALONE = Mix_LoadWAV(PATH_LEAVEMEALONE);
		this->sample_HOLA = Mix_LoadWAV(PATH_HOLA);
		this->sample_RISA = Mix_LoadWAV(PATH_RISA);
		this->sample_FIREINTHEHOLE = Mix_LoadWAV(PATH_FIREINTHEHOLE);
		this->sample_HASTALAVISTA2 = Mix_LoadWAV(PATH_HASTALAVISTA2);
		this->sample_HASTALAVISTA = Mix_LoadWAV(PATH_HASTALAVISTA);

	}

	Sonido::~Sonido(){
		// deleteo todos los samples
		Mix_FreeChunk(this->sample_AGUA );
		Mix_FreeChunk(this->sample_SELFDESTRUCT );
		Mix_FreeChunk(this->sample_DISPARO1 );
		Mix_FreeChunk(this->sample_DISPAROBAZOOKA );
		Mix_FreeChunk(this->sample_LANZOGRANADA );
		Mix_FreeChunk(this->sample_LANZOGRANADASANTA );
		Mix_FreeChunk(this->sample_EXPLOSION1 );
		Mix_FreeChunk(this->sample_EXPLOSION2 );
		Mix_FreeChunk(this->sample_EXPLOSION3 );
		Mix_FreeChunk(this->sample_CARGAPOTENCIA );
		Mix_FreeChunk(this->sample_FONDO1 );
		Mix_FreeChunk(this->sample_FONDO2 );
		Mix_FreeChunk(this->sample_CAMBIOARMA );
		Mix_FreeChunk(this->sample_HURRY );
		Mix_FreeChunk(this->sample_HURRY2 );
		Mix_FreeChunk(this->sample_HURRY3 );
		Mix_FreeChunk(this->sample_SALTO1 );
		Mix_FreeChunk(this->sample_SALTO2 );
		Mix_FreeChunk(this->sample_ABRIRMENU );
		Mix_FreeChunk(this->sample_CERRARMENU );
		Mix_FreeChunk(this->sample_ITSALIVE );
		Mix_FreeChunk(this->sample_USETHEFORCE );
		Mix_FreeChunk(this->sample_GOODDAYTODIE );
		Mix_FreeChunk(this->sample_ITCOULDWORK );
		Mix_FreeChunk(this->sample_INCOMING );
		Mix_FreeChunk(this->sample_WHATTHE );
		Mix_FreeChunk(this->sample_TRAITOR );
		Mix_FreeChunk(this->sample_GALLINA );
		Mix_FreeChunk(this->sample_ESPERAYVERAS );
		Mix_FreeChunk(this->sample_YESSIR );
		Mix_FreeChunk(this->sample_LEAVEMEALONE );
		Mix_FreeChunk(this->sample_HOLA );
		Mix_FreeChunk(this->sample_RISA );
		Mix_FreeChunk(this->sample_FIREINTHEHOLE );
		Mix_FreeChunk(this->sample_HASTALAVISTA2 );
		Mix_FreeChunk(this->sample_HASTALAVISTA );
					

		//deleteo el mixer
		Mix_Quit();
	}
					
	//solo pone el tema si es un numero de tema valido y ademas no es igua al anterior				
	void Sonido::dalePlayAlTema(int numeroSerialTema){
		if( (numeroSerialTema!=numeroSerialTemaAnterior) && (1 <= numeroSerialTema) && (numeroSerialTema <= NUMERO_DE_SONIDOS) ){
			switch(numeroSerialTema){
				case NUMERO_SERIAL_AGUA2:
				case NUMERO_SERIAL_AGUA:
					Mix_PlayChannel(NUMERO_CHANNEL_EFECTOS, this->sample_AGUA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_SELFDESTRUCT:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSOTROS, this->sample_SELFDESTRUCT, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_DISPARO1:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_DISPARO1, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_DISPAROBAZOOKA:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_DISPAROBAZOOKA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_LANZO_GRANADA:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_LANZOGRANADA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_LANZO_GRANADASANTA:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_LANZOGRANADASANTA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_EXPLOSION1:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_EXPLOSION1, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_EXPLOSION2:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_EXPLOSION2, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_EXPLOSION3:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_EXPLOSION3, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_CARGA_POTENCIA:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_CARGAPOTENCIA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_FONDO:
					Mix_PlayChannel(NUMERO_CHANNEL_MUSICADEFONDO , this->sample_FONDO1, -1);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_FONDO2:
					Mix_PlayChannel(NUMERO_CHANNEL_MUSICADEFONDO , this->sample_FONDO2, -1);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_CARGAPISTOLA:
					Mix_PlayChannel(NUMERO_CHANNEL_EFECTOS , this->sample_CAMBIOARMA, 0);
					break;
				case NUMERO_SERIAL_HURRY:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_HURRY, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_HURRY2:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_HURRY2, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_HURRY3:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_HURRY3, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_SALTO1:
					Mix_PlayChannel(NUMERO_CHANNEL_EFECTOS , this->sample_SALTO1, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_SALTO2:
					Mix_PlayChannel(NUMERO_CHANNEL_EFECTOS , this->sample_SALTO2, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_ABRIRMENU:
					Mix_PlayChannel(NUMERO_CHANNEL_EFECTOS , this->sample_ABRIRMENU, 0);
					break;
				case NUMERO_SERIAL_CERRARMENU:
					Mix_PlayChannel(NUMERO_CHANNEL_EFECTOS , this->sample_CERRARMENU, 0);
					break;
				case NUMERO_SERIAL_ITSALIVE:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_ITSALIVE, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_USETHEFORCELUKE:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_USETHEFORCE, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_GOODDAYTODAY:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_GOODDAYTODIE, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_ITCOULDWORK:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_ITCOULDWORK, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_INCOMING:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_INCOMING, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_WHATTHE:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_WHATTHE, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_TRAITOR:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_TRAITOR, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_GALLINA:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_GALLINA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_ESPERAYVERAS:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_ESPERAYVERAS, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_YESSIR:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_YESSIR, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_LEAVEMEALONE:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_LEAVEMEALONE, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_HOLA:
					Mix_PlayChannel(NUMERO_CHANNEL_COMENTARIOSDEGUSANOS , this->sample_HOLA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_RISA:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_RISA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_FIREINTHEHOLE:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_FIREINTHEHOLE, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_HASTALAVISTA2:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_HASTALAVISTA2, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;
				case NUMERO_SERIAL_HASTALAVISTA:
					Mix_PlayChannel(NUMERO_CHANNEL_ARMASYBOMBAS , this->sample_HASTALAVISTA, 0);
					numeroSerialTemaAnterior = numeroSerialTema;
					break;

			}
		}
	}
