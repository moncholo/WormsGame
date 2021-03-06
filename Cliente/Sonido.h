#include <SDL.h>
#include "SDL2_mixer-2.0.0\include\SDL_mixer.h"
#include "Constantes.h"

//se define la funcion como estaba en internet recomendada y la ayuda del sdl
#define Mix_PlayChannel(channel,chunk,loops) Mix_PlayChannelTimed(channel,chunk,loops,-1)

//defino NumeroDeChannels igual al numero de samples que voy a tener (1 sample por cada WAV)
#define NUMERO_DE_SONIDOS 222
#define FRECUENCIA_DE_LOS_SONIDOS 88200
#define CANAL_PARA_ACTIVAR_COMO_STEREO 2
#define CHUNK_SIZE_USADO 4096

#define NUMERO_DE_CHANNELS 5
#define NUMERO_CHANNEL_MUSICADEFONDO 1
#define NUMERO_CHANNEL_COMENTARIOSDEGUSANOS 2
#define NUMERO_CHANNEL_COMENTARIOSOTROS 3
#define NUMERO_CHANNEL_ARMASYBOMBAS 4
#define NUMERO_CHANNEL_EFECTOS 5

#define MIN_EXTRAS 23
#define MAX_EXTRAS 33

#define MIN_DISP_BAZOOKA 4
#define MAX_DISP_BAZOOKA 5

#define MIN_EXPLOSION 8
#define MAX_EXPLOSION 10

#define MIN_APURO 15
#define MAX_APURO 17

#define MIN_SALTAR 18
#define MAX_SALTAR 19

#define MIN_DINAMITA 34
#define MAX_DINAMITA 37


//CAIDA AGUA
#define NUMERO_SERIAL_AGUA 1
#define PATH_AGUA "private/sonidos/changewatertype.wav"

#define NUMERO_SERIAL_AGUA2 2

//SUICIDA
#define NUMERO_SERIAL_SELFDESTRUCT 3
#define PATH_SELFDESTRUCT "private/sonidos/selfdestruct.wav"

//DISPAROS BAZOOKA
#define NUMERO_SERIAL_DISPARO1 4
#define PATH_DISPARO1 "private/sonidos/ShotGunFire.wav"

#define NUMERO_SERIAL_DISPAROBAZOOKA 5
#define PATH_DISPAROBAZOOKA "private/sonidos/10 Guage Shotgun-SoundBible.com-74120584.wav"

//LANZA GRANADA
#define NUMERO_SERIAL_LANZO_GRANADA 6
#define PATH_LANZO_GRANADA "private/sonidos/GRENADE.wav"

//LANZA GRANADA SANTA
#define NUMERO_SERIAL_LANZO_GRANADASANTA 7
#define PATH_LANZO_GRANADASANTA "private/sonidos/HOLYGRENADE.wav"

//SONIDOS EXPLOSION
#define NUMERO_SERIAL_EXPLOSION3 8
#define PATH_EXPLOSION3 "private/sonidos/Explosion3.wav"

#define NUMERO_SERIAL_EXPLOSION2 9
#define PATH_EXPLOSION2 "private/sonidos/Explosion2.wav"

#define NUMERO_SERIAL_EXPLOSION1 10
#define PATH_EXPLOSION1 "private/sonidos/Explosion1.wav"

//CARGA GRANADA Y SANTA
#define NUMERO_SERIAL_CARGA_POTENCIA 11
#define PATH_CARGO_POTENCIA "private/sonidos/THROWPOWERUP.wav"

//MUSICA DE FONDO
#define NUMERO_SERIAL_FONDO 12
#define PATH_FONDO "private/sonidos/fondo.wav"

#define NUMERO_SERIAL_FONDO2 13
#define PATH_FONDO2 "private/sonidos/strangersNight.wav"

//CAMBIO ARMA
#define NUMERO_SERIAL_CARGAPISTOLA 14
#define PATH_CARGAPISTOLA "private/sonidos/Shotgun-SoundBible.com-862990674.wav"

//apurarlo
#define NUMERO_SERIAL_HURRY 15
#define PATH_HURRY "private/sonidos/HURRY.wav"

#define NUMERO_SERIAL_HURRY2 16
#define PATH_HURRY2 "private/sonidos/hurry2.wav"

#define NUMERO_SERIAL_HURRY3 17
#define PATH_HURRY3 "private/sonidos/hurry3.wav"

//saltar

#define NUMERO_SERIAL_SALTO1 18
#define PATH_SALTO1 "private/sonidos/JUMP1.wav"

#define NUMERO_SERIAL_SALTO2 19
#define PATH_SALTO2 "private/sonidos/JUMP2.wav"

//abrir/cerrar menu
#define NUMERO_SERIAL_ABRIRMENU 20
#define PATH_ABRIRMENU "private/sonidos/menu1.wav"

#define NUMERO_SERIAL_CERRARMENU 21
#define PATH_CERRARMENU "private/sonidos/menu2.wav"


//EXTRAS
#define NUMERO_SERIAL_ITSALIVE 22
#define PATH_ITSALIVE "private/sonidos/itsalive.wav"

#define NUMERO_SERIAL_USETHEFORCELUKE 23
#define PATH_USETHEFORCELUKE "private/sonidos/useforceluke.wav"

#define NUMERO_SERIAL_GOODDAYTODAY 24
#define PATH_GOODDAYTODAY "private/sonidos/gooddaytodie.wav"

#define NUMERO_SERIAL_ITCOULDWORK 25
#define PATH_ITCOULDWORK "private/sonidos/itcouldwork.wav"

#define NUMERO_SERIAL_INCOMING 26
#define PATH_INCOMING "private/sonidos/INCOMING.wav"

#define NUMERO_SERIAL_WHATTHE 27
#define PATH_WHATTHE "private/sonidos/whatthe.wav"

#define NUMERO_SERIAL_TRAITOR 28
#define PATH_TRAITOR "private/sonidos/TRAITOR.wav"

#define NUMERO_SERIAL_GALLINA 29
#define PATH_GALLINA "private/sonidos/COWARD.wav"

#define NUMERO_SERIAL_ESPERAYVERAS 30
#define PATH_ESPERAYVERAS "private/sonidos/YOULLREGRETTHAT.wav"

#define NUMERO_SERIAL_YESSIR 31
#define PATH_YESSIR "private/sonidos/YESSIR.wav"

#define NUMERO_SERIAL_LEAVEMEALONE 32
#define PATH_LEAVEMEALONE "private/sonidos/LEAVEMEALONE.wav"

#define NUMERO_SERIAL_HOLA 33
#define PATH_HOLA "private/sonidos/HELLO.wav"

//deja dinamita
#define NUMERO_SERIAL_RISA 34
#define PATH_RISA "private/sonidos/LAUGH.wav"

#define NUMERO_SERIAL_FIREINTHEHOLE 35
#define PATH_FIREINTHEHOLE "private/sonidos/fire.wav"

#define NUMERO_SERIAL_HASTALAVISTA2 36
#define PATH_HASTALAVISTA2 "private/sonidos/fatality.wav"

#define NUMERO_SERIAL_HASTALAVISTA 37
#define PATH_HASTALAVISTA "private/sonidos/HASTA.wav"

class Sonido{
	private:
		int numeroSerialTemaAnterior;

		Mix_Chunk *sample_AGUA;
		
		Mix_Chunk *sample_SELFDESTRUCT;
		
		Mix_Chunk *sample_DISPARO1;
		Mix_Chunk *sample_DISPAROBAZOOKA;

		Mix_Chunk *sample_LANZOGRANADA;
		Mix_Chunk *sample_LANZOGRANADASANTA;

		Mix_Chunk *sample_EXPLOSION1;
		Mix_Chunk *sample_EXPLOSION2;
		Mix_Chunk *sample_EXPLOSION3;

		Mix_Chunk *sample_CARGAPOTENCIA;

		Mix_Chunk *sample_FONDO1;
		Mix_Chunk *sample_FONDO2;

		Mix_Chunk *sample_CAMBIOARMA; //se llama cargo pistola

		Mix_Chunk *sample_HURRY;
		Mix_Chunk *sample_HURRY2;
		Mix_Chunk *sample_HURRY3;

		Mix_Chunk *sample_SALTO1;
		Mix_Chunk *sample_SALTO2;

		Mix_Chunk *sample_ABRIRMENU;
		Mix_Chunk *sample_CERRARMENU;

		Mix_Chunk *sample_ITSALIVE;
		Mix_Chunk *sample_USETHEFORCE;
		Mix_Chunk *sample_GOODDAYTODIE;
		Mix_Chunk *sample_ITCOULDWORK;
		Mix_Chunk *sample_INCOMING;
		Mix_Chunk *sample_WHATTHE;
		Mix_Chunk *sample_TRAITOR;
		Mix_Chunk *sample_GALLINA;
		Mix_Chunk *sample_ESPERAYVERAS;
		Mix_Chunk *sample_YESSIR;
		Mix_Chunk *sample_LEAVEMEALONE;
		Mix_Chunk *sample_HOLA;
		
		Mix_Chunk *sample_RISA;
		Mix_Chunk *sample_FIREINTHEHOLE;
		Mix_Chunk *sample_HASTALAVISTA2;
		Mix_Chunk *sample_HASTALAVISTA;


	public:
		Sonido();
		~Sonido();
		void dalePlayAlTema(int numeroSerialTema);
};

