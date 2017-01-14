#include "ManejoSerializacionServidor.h"


		SerializacionServidor* ManejoSerializacionServidor::getMensajeSerializado(){
			return this->unaSerializacion;
		}
		void ManejoSerializacionServidor::setMensajeSerializado(SerializacionServidor* serializacion){
			this->unaSerializacion = serializacion;
		}
		
		ManejoSerializacionServidor::ManejoSerializacionServidor(){

			this->unaSerializacion = new SerializacionServidor;

			this->unaSerializacion->cantidadDeGusanosPorJugador = CantidadMaximaGusanosPorJugador;

			this->unaSerializacion->cantidadDeJugadores = CantidadMaximaJugadores;

			this->unaSerializacion->cantidadDeObjetos = CantidadMaximaObjetos;

			this->unaSerializacion->armaActual.disparoActivo = false;
			
			this->unaSerializacion->armaActual.yExplosion = 0.0f;

			this->unaSerializacion->armaActual.xExplosion = 0.0f;

			this->unaSerializacion->armaActual.x = 0.0f;

			this->unaSerializacion->armaActual.y = 0.0f;

			this->unaSerializacion->armaActual.radio = -1;

			this->unaSerializacion->armaActual.idArma = 0;

			this->unaSerializacion->armaActual.tiempoDeVida = -1;

			this->unaSerializacion->numeroDeSonido = 0;

			this->unaSerializacion->turnoDeEquipo = 0;
						
			this->unaSerializacion->ganador = -1;

			this->unaSerializacion->reinicio = false;

			for (int i = 0; i < NUMERO_DE_ARMAS; i++){
				this->unaSerializacion->vectorMuniciones[i] = 0;
			}
		}

		ManejoSerializacionServidor::~ManejoSerializacionServidor(){
			delete this->unaSerializacion;
		}


		int ManejoSerializacionServidor::serializarYAML(char* fileYAML, char serialYAML[]){	
			FILE* pArchivo = fopen(fileYAML,"rb");
			if(pArchivo != NULL){ /*el archivo existe*/
				int tamanioArchivo = 0; 
				/*fseek (pArchivo , 0 , SEEK_END);
				tamanioArchivo = ftell (pArchivo);
				rewind (pArchivo); 

				if (tamanioArchivo) {
					char* variable;
					variable = (char*) calloc (tamanioArchivo, sizeof(char)*tamanioArchivo);
					fread (variable,1,tamanioArchivo,pArchivo);

					for(int i = 0; i < tamanioArchivo; i++){
						serialYAML[i] = variable[i];
					}
				}*/
				int lectura = 1;
				while(lectura == 1){
					lectura = fread(&serialYAML[tamanioArchivo],1,1, pArchivo);
					tamanioArchivo++;
				}
				fclose(pArchivo);

				return tamanioArchivo-1;
			}//acordarse de hacer el free[];
			return -1;
		}
		
		void ManejoSerializacionServidor::serializar(std::vector<Gusano*>* losGusanos, std::vector<Objeto*>* losObjetos, bool* estadoOnline){
			int i;
			for(i=0; i<losGusanos->size(); i++){
				if(losGusanos->at(i)->getCuerpo()){
					this->unaSerializacion->vectorObjetosEnviables[i].x=losGusanos->at(i)->getCuerpo()->GetPosition().x; //donde la magia sucede
					this->unaSerializacion->vectorObjetosEnviables[i].y=losGusanos->at(i)->getCuerpo()->GetPosition().y;
					this->unaSerializacion->vectorObjetosEnviables[i].rot=losGusanos->at(i)->getCuerpo()->GetAngle();
					this->unaSerializacion->vectorObjetosEnviables[i].estaEnMundo=losGusanos->at(i)->enMundo;
					this->unaSerializacion->vectorObjetosEnviables[i].estaOnline= losGusanos->at(i)->pintarEnColor;
					this->unaSerializacion->vectorObjetosEnviables[i].miraADerecha= losGusanos->at(i)->miraADerecha;
					this->unaSerializacion->vectorObjetosEnviables[i].vida = losGusanos->at(i)->vida;

					//if(losGusanos->at(i)->pintarEnColor) std::cout << "True" << std::endl;
					//else std::cout << "false" << std::endl;
				}
				
				
			}
			for(int j=0; j<losObjetos->size(); j++){
				this->unaSerializacion->vectorObjetosEnviables[j+i].x=losObjetos->at(j)->getCuerpo()->GetPosition().x; //donde la magia sucede
				this->unaSerializacion->vectorObjetosEnviables[j+i].y=losObjetos->at(j)->getCuerpo()->GetPosition().y;
				this->unaSerializacion->vectorObjetosEnviables[j+i].rot=losObjetos->at(j)->getCuerpo()->GetAngle();
				this->unaSerializacion->vectorObjetosEnviables[j+i].estaEnMundo=losObjetos->at(j)->getCuerpo()->IsActive();

			}
		}
		
		void ManejoSerializacionServidor::deSerializarExplosion(Escenario* unEscenario){
			unEscenario->radioDeExplosion = this->unaSerializacion->armaActual.radio;
			unEscenario->posXExplosion = this->unaSerializacion->armaActual.xExplosion;
			unEscenario->posYExplosion = this->unaSerializacion->armaActual.yExplosion;
			unEscenario->dibujarBomba = this->unaSerializacion->armaActual.disparoActivo;
			unEscenario->xDisparo = this->unaSerializacion->armaActual.x;
			unEscenario->yDisparo = this->unaSerializacion->armaActual.y;
			unEscenario->idArma = this->unaSerializacion->armaActual.idArma;
			unEscenario->xMira = this->unaSerializacion->armaActual.xMira;
			unEscenario->yMira = this->unaSerializacion->armaActual.yMira;
			unEscenario->tiempoDeVidaArma = this->unaSerializacion->armaActual.tiempoDeVida;
			unEscenario->idCliente = this->unaSerializacion->idCliente;
		}

		
		void ManejoSerializacionServidor::deSerializarMuniciones(std::vector<int>* unVector){
			for (int i=0; i<unVector->size(); i++){
				unVector->at(i) = this->unaSerializacion->vectorMuniciones[i];
			}
		}

		void ManejoSerializacionServidor::deSerializar(std::vector<Gusano*>* losGusanos, std::vector<Objeto*>* losObjetos){
			int i;
			for(i=0; i<losGusanos->size(); i++){
				losGusanos->at(i)->x= this->unaSerializacion->vectorObjetosEnviables[i].x; //donde la magia sucede
				losGusanos->at(i)->y= this->unaSerializacion->vectorObjetosEnviables[i].y;
				losGusanos->at(i)->rot = this->unaSerializacion->vectorObjetosEnviables[i].rot;
				losGusanos->at(i)->enMundo = this->unaSerializacion->vectorObjetosEnviables[i].estaEnMundo;
				losGusanos->at(i)->pintarEnColor = this->unaSerializacion->vectorObjetosEnviables[i].estaOnline;
				losGusanos->at(i)->miraADerecha = this->unaSerializacion->vectorObjetosEnviables[i].miraADerecha;
				losGusanos->at(i)->vida = this->unaSerializacion->vectorObjetosEnviables[i].vida;
				if(this->unaSerializacion->gusanoSeleccionado == i){
					losGusanos->at(i)->setElegido(true);
				}
				else {
					losGusanos->at(i)->setElegido(false);
				}
				//if(this->unaSerializacion->vectorObjetosEnviables[i].estaOnline) std::cout << i << "True" << std::endl;
					//else std::cout << i << "false" << std::endl;
				
			}
			for(int j=0; j<losObjetos->size(); j++){
				losObjetos->at(j)->x= this->unaSerializacion->vectorObjetosEnviables[i+j].x; //donde la magia sucede
				losObjetos->at(j)->y= this->unaSerializacion->vectorObjetosEnviables[i+j].y;
				losObjetos->at(j)->rot = this->unaSerializacion->vectorObjetosEnviables[i+j].rot;
				losObjetos->at(j)->enMundo = this->unaSerializacion->vectorObjetosEnviables[i+j].estaEnMundo;
			}
			
			//std::cout<< "El numero de municiones es de: "<< this->unaSerializacion->vectorMuniciones[1] << std::endl;

		}