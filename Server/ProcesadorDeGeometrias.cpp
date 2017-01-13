#include "ProcesadorDeGeometrias.h"

//las declaro afuera por un tema de boost
b2Vec2 puntosDelChain[MAX_PIXELES_IMAGEN_TIERRA];

int indiceRecorredorDelChain = 0;

ProcesadorDeGeometrias::ProcesadorDeGeometrias(float unaEscalaParaElCirculo, b2World* unMundo, vectorChains* unVectorDeChains,
											   vectorPoligonos* vectorInicialDePoligonos){

	this->listaPuntosCentradosEnOrigen = new vectorPuntos();

	this->escalaDelCirculo = unaEscalaParaElCirculo;

	this->mundo = unMundo;

	this->vectorDeChains = unVectorDeChains;

	this->vectorDePoligonos = vectorInicialDePoligonos;

	this->crearCirculoCentradoEnElOrigen();

	
}

bool ProcesadorDeGeometrias::puntoAdentroDeLaTierra(double x, double y){

	BOOST_FOREACH(polygon const& poligonoActual, (*this->vectorDePoligonos)){
		if (boost::geometry::within(point(x,y), poligonoActual)){
			return true;
		}
	}

	return false;

}
void ProcesadorDeGeometrias::crearCirculoCentradoEnElOrigen(){

	
	float incrementador = (float)M_PI*2.0f / (float)CANTIDAD_LADOS_POLIGONOS;
	float angulo = M_PI/4.0f;
	
	/*Geometria Pura*/
	float x = cos(angulo)*this->escalaDelCirculo; 
	float y = sin(angulo)*this->escalaDelCirculo;

	for (unsigned int j=0; j < CANTIDAD_LADOS_POLIGONOS; j++){
		x = cos(angulo)*this->escalaDelCirculo; 
		y = sin(angulo)*this->escalaDelCirculo;			
		angulo = angulo - incrementador;

		this->listaPuntosCentradosEnOrigen->push_back(point(x,y));

		/*push_back(exterior_ring(this->poligonoCircular))
            (point(x+200, y+140));*/
	}

	//a la lista le agrego como ultimo punto el primero
	//para poder cerrar la geometria

		this->listaPuntosCentradosEnOrigen->push_back(
				this->listaPuntosCentradosEnOrigen->at(0));
	

}

void ProcesadorDeGeometrias::explotarTierraEnPosicion(float posicionX, float posicionY, int radioArma){
	
	//creo el poligono Circular para luego hacer la diferencia
	
	//el clear elimina todos los chiches que tenia el poligono	
	this->poligonoCircular.clear(); 

	for (unsigned int i = 0; i < this->listaPuntosCentradosEnOrigen->size(); i++){
		double x = (get<0>(this->listaPuntosCentradosEnOrigen->at(i)) * radioArma)+ posicionX;
		double y = (get<1>(this->listaPuntosCentradosEnOrigen->at(i))* radioArma) + posicionY; 
		
		push_back(exterior_ring(this->poligonoCircular)) (point(x,y));	
		
	}
	//ya tengo el poligono centrado en la diferencia

	
	vectorPoligonos vector;
	BOOST_FOREACH(polygon const& poligonoActual, (*this->vectorDePoligonos)){
		boost::geometry::difference(poligonoActual,this->poligonoCircular, vector);
	}

	//adentro no habia new's asi que no pierdo memoria
	this->vectorDePoligonos->clear();

	for (unsigned int i = 0; i < vector.size(); i++){
		polygon poligonoASimplificar;
		simplify(vector.at(i), poligonoASimplificar, 1.0);
		this->vectorDePoligonos->push_back(poligonoASimplificar);
	}

	//chau vector
	vector.clear();

	/*
	vectorPoligonos* nuevoVector = vectorDePoligonos;
	vectorDePoligonos = new vectorPoligonos();
	//hago la diferencia para cada poligono, y la guardo en un vector

	BOOST_FOREACH(polygon const& poligonoActual, *nuevoVector){
			boost::geometry::difference(poligonoActual, this->poligonoCircular, (*vectorDePoligonos));
	}

*/

//	delete nuevoVector;
	//tiro a la basura los poligonos que tenia y le pongo los nuevos
//	delete[] this->vectorDePoligonos;
//	this->vectorDePoligonos = nuevoVector;
	this->convertirGeometriasAChain();


}

template <typename Point>
void list_coordinates(Point const& puntoActual)
{
	//obtengo los puntos de la funcion
	//luego los cargo en el chain
	using boost::geometry::get;

	puntosDelChain[indiceRecorredorDelChain].Set(get<0>(puntoActual),get<1>(puntoActual));

	indiceRecorredorDelChain++;

}

void ProcesadorDeGeometrias::convertirGeometriasAChain(){

	int cantidadDeChainsADesactivar = this->vectorDeChains->size();

	
	//desactivo los chains que estaban antes
	
	BOOST_FOREACH(polygon const& poligonoActual, (*this->vectorDePoligonos)){
		
		indiceRecorredorDelChain = 0;

		b2BodyDef contornoDef;
		
		contornoDef.type = b2_staticBody;	

		boost::geometry::for_each_point(poligonoActual, list_coordinates<point>);
		
		b2Body* contornoTierra;
		contornoTierra = mundo->CreateBody(&contornoDef);
		
		b2ChainShape cadenaForma;
		//indice-1 porque no quiero el ultimo punto
		cadenaForma.CreateLoop(puntosDelChain, indiceRecorredorDelChain - 1);

		contornoTierra->CreateFixture(&cadenaForma, 0.0f);

		//agrego el nuevo Chain
		this->vectorDeChains->push_back(contornoTierra);

	}

	for (unsigned int i = 0; i < cantidadDeChainsADesactivar; i++){
		//this->vectorDeChains->at(i)->SetActive(false);

		mundo->DestroyBody(this->vectorDeChains->at(0));
		this->vectorDeChains->erase(this->vectorDeChains->begin());
	}
	
	

}

ProcesadorDeGeometrias::~ProcesadorDeGeometrias(){

}