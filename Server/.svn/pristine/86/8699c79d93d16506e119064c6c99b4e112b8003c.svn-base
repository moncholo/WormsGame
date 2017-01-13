#ifndef __PROCESADOR_DE_GEOMETRIAS__
#define  __PROCESADOR_DE_GEOMETRIAS__

#include <iostream>
#include <queue>
#include <Box2D/Box2D.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include "SDL2_gfx-1.0.0\SDL2_gfxPrimitives.h"
#include <vector>
#include <boost/geometry/algorithms/within.hpp>


#include <boost/assign.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/foreach.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/adapted/boost_range/filtered.hpp>
#include <boost/geometry/algorithms/buffer.hpp>
BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)
//#include "Constantes.h"


using namespace boost::geometry;
using namespace boost::assign;

typedef boost::geometry::model::d2::point_xy<double> point;
typedef boost::geometry::model::box<point> box;
typedef boost::geometry::model::polygon<point> polygon;
typedef std::vector<b2Body*> vectorChains;
typedef std::deque<polygon> vectorPoligonos;
typedef std::vector<point> vectorPuntos;

#define CANTIDAD_LADOS_POLIGONOS 50
#define MAX_PIXELES_IMAGEN_TIERRA 3000


class ProcesadorDeGeometrias{

	private:

		vectorPoligonos* vectorDePoligonos;

		vectorPuntos* listaPuntosCentradosEnOrigen;
		
		vectorChains* vectorDeChains;

		void crearCirculoCentradoEnElOrigen();
	
		float escalaDelCirculo;

		polygon poligonoCircular;

		b2World* mundo;

	public:

		//al igual que poligonos, tiene un factorDeEscala
		ProcesadorDeGeometrias(float unaEscalaParaLaGeometria, b2World* unMundo, vectorChains* unVectorDeChains,
								vectorPoligonos* vectorInicialDePoligonos);

		~ProcesadorDeGeometrias();

		bool puntoAdentroDeLaTierra(double posX, double posY);

		void convertirGeometriasAChain();

		//recibe las coordenadas del centro de masa para recalcular geometrias
		void explotarTierraEnPosicion(float posicionX, float posicionY,int radioArma);

};




#endif