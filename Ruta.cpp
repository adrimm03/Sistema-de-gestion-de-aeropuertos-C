//
// Created by admin on 10/10/2023.
//

#include "Ruta.h"

/**
 * @brief Constructor por Defecto
 *
 */
Ruta::Ruta() {

}

/**
 * @brief Constructor copia
 *
 * @param orig objeto a partir del cual copiamos los atributos
 */
Ruta::Ruta(const Ruta &orig):aerolinea(orig.aerolinea),  _origin(orig._origin), _destination(orig._destination), flightrou(orig.flightrou){

}

/**
 * @brief Constructor parametrizado
 *
 * @param *aerolinea1
 * @param orig
 * @param destino
 */
Ruta::Ruta(Aerolinea *aerolinea1, Aeropuerto* orig,Aeropuerto* destino): aerolinea(aerolinea1) {
    this->_origin = orig;
    this->_destination = destino;
}

/**
 * @brief Destructor
 */
Ruta::~Ruta() {
    _origin= nullptr;
    _destination= nullptr;
    auto it=flightrou.begin();
    it ++;
    Vuelo *aux;
    while (it!=flightrou.end()){
        aux=it.operator*();
        delete aux;
        it++;
    }
}


/**
 * @brief Getter Aeropuerto Origen
 *
 * @return puntero al Aeropuerto
 */
Aeropuerto& Ruta::getOrigin() const {
    return *_origin;
}

/**
 * @brief Setter Aeropuerto Origen
 *
 * @param origin
 */
void Ruta::setOrigin(Aeropuerto& origin) {
    this->_origin = &origin;
}

/**
 * @brief Getter Aeropuerto Destino
 *
 * @return
 */
Aeropuerto& Ruta::getDestination() const {
    return *_destination;
}

/**
 * @brief Setter Aeropuerto Destino
 *
 * @param destination
 */
void Ruta::setDestination(Aeropuerto& destination) {
    this->_destination = &destination;
}

/**
 * @brief Operador de asignacion
 *
 * @param orig
 * @return el objeto asignado
 */
Ruta &Ruta::operator=(const Ruta &orig) {
    if(*this->_origin==*orig._origin && *this->_destination==*orig._destination){
        return *this;
    }else {
        *_origin = *orig._origin;
        *_destination = *orig._destination;
        return *this;
    }
}

/**
 * @brief Setter Aerolinea
 *
 * @param aerolinea1
 */
void Ruta::setAerolinea(Aerolinea *aerolinea1) {
    aerolinea=aerolinea1;
}

/**
 * @brief Añade un vuelo a la lista de vuelos
 * @param v
 * @throw invalid_argument si el uelo pasado esta vacio
 * @return true si el dato es correcto
 */
bool Ruta::addVuelo(Vuelo v) {
    if(&v== nullptr){
        throw std::invalid_argument("Ruta::addVuelo: El dato que se desea insertar no contiene nada " );
    }
    if(*v.getAirDestino()==*_destination && *v.getAirOrigen()==*_origin && v.getAerolinea() == aerolinea) {            ////Añadir comprobación Aerolinea
        Vuelo *n_vuelo = new Vuelo(v);
        flightrou.push_back(n_vuelo);
        return true;
    }
    return false;
}

/**
 * @brief Getter de Num de Vuelos
 *
 * @return Obtiene el numero de Vuelos asociados a una Ruta
 */
unsigned int Ruta::getNumVuelos() {
    return flightrou.size();

}


/***
 * @brief Dos rutas son iguales si los aeropuertos origen y destino son iguales y si comparten también la Aerolinea
 * @param rhs
 * @return true si son iguales y false si son diferentes
 */
bool Ruta::operator==(const Ruta &rhs) const {
    return this->_destination==rhs._destination && this->_origin==rhs._origin && this->aerolinea == rhs.aerolinea ;

}

/**
 * @brief Getter lista de Vuelos
 * @return lista de puntero a vuelos
 */
std::list<Vuelo *> *Ruta::getFlightrou()   {
    return &flightrou;
}

