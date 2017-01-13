#include <queue>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class ProcesadorDeTierra{
	
public:
		/* ATRIBUTOS */
		std::queue<float> *colaDeAlturas;

		int cantidadDePixelsVerticales;
		int cantidadDePixelsHorizontales;

		int altoPx; //Valores que representan alto y ancho de ventana del juego, para validar máscara de tierra
		int anchoPx;
		int nivelAgua;

		SDL_Surface *superficie;

		Uint8 parteRojaDelMarronDeTierra;
		Uint8 parteVerdeDelMarronDeTierra;
		Uint8 parteAzulDelMarronDeTierra;
		Uint8 parteAlphaDelMarronDeTierra;
		Uint8 parteRojaDelCielo;
		Uint8 parteVerdeDelCielo;
		Uint8 parteAzulDelCielo;
		Uint8 parteAlphaDelCielo;



		/* FIN DE LOS ATRIBUTOS */
		

		Uint32*	getPixelEnLaPosicion( int fila, int columna);
		
		
		Uint8	getParteRojo(Uint32* elPixel, SDL_PixelFormat *formato);
		void	setParteRojo(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 rojo);

		Uint8	getParteVerde(Uint32* elPixel, SDL_PixelFormat *formato);
		void	setParteVerde(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 verde);

		Uint8	getParteAzul(Uint32* elPixel, SDL_PixelFormat *formato);
		void	setParteAzul(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 azul);

		Uint8	getParteAlpha(Uint32* elPixel, SDL_PixelFormat *formato);
		void	setParteAlpha(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 alpha);

		void	setColorRGBAenPixel(Uint32* elPixel, SDL_PixelFormat *formato, Uint8 rojo, Uint8 verde, Uint8 azul, Uint8 alpha);

		
		bool pixelEsAire(Uint32* elPixel, SDL_PixelFormat *formato);
		
		bool pixelEsTierra(Uint32* elPixel, SDL_PixelFormat *formato);
				
		
		bool elRestoDeLaColumnaEsBlanca(int fila, int columna, int cantidadDeFilas);
		
		//si no se cumplió el formato en la imagen se escribe esto en el archivo log
		void chequearSiSeCumpleElFormato(std::string *rutaDelArchivoLog, bool seCumpleFormato);
	

		void parsearSurface(std::string *rutaDelArchivoLog);

	public:
        // Constructor
        ProcesadorDeTierra(std::string *rutaDelArchivoImagen, std::string *rutaDelArchivoLog, int altoPix, int anchoPix, int nivelAguaPix);

		// Destructor
        ~ProcesadorDeTierra();

		SDL_Surface* getSurfaceDeLaTierra();
        
		int getCantidadDePuntosHorizontales();

		int getCantidadDePuntosVerticales();

		std::queue<float>* getColaDeAlturas();

};