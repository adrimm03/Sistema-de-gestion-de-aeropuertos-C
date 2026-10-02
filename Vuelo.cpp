//
// Created by usuario on 07/11/2023.
//

#include "Vuelo.h"

/**
 * @brief Constructor parametrizado
 *
 * @param flightnumb
 * @param plane
 * @param datometeo
 * @param fecha
 * @param orig
 * @param dest
 */
Vuelo::Vuelo(const std::string flightnumb,const std::string plane,const std::string datometeo,const Fecha& fecha, Aeropuerto *&orig,
              Aeropuerto *&dest): _flightnumb(flightnumb), _plane(plane), _datometeo(datometeo),_fecha(fecha), airOrigen(orig),airDestino(dest) {

}

/**
 * @brief Constructor copia
 * @param orig
 */
Vuelo::Vuelo(const Vuelo &orig): _flightnumb(orig._flightnumb), _plane(orig._plane), _datometeo(orig._datometeo),_fecha(orig._fecha),
                            airOrigen(orig.airOrigen),airDestino(orig.airDestino), aerolinea(orig.aerolinea) {

}

/**
 * @brief Destructor
 */
Vuelo::~Vuelo() {
    airDestino = nullptr;
    airOrigen = nullptr;
    aerolinea = nullptr;
}

/**
 * @brief Getter identificador de Vuelo
 * @return _flightnumb
 */
const std::string &Vuelo::getFlightnumb() const {
    return _flightnumb;
}

/**
 * @brief Setter flightnumb
 * @param flightnumb
 */
void Vuelo::setFlightnumb(const std::string &flightnumb) {
    _flightnumb = flightnumb;
}

/**
 * @brief Getter Plane
 * @return _plane
 */
const std::string &Vuelo::getPlane() const {
    return _plane;
}

/**
 * @brief Setter Plane
 * @param plane
 */
void Vuelo::setPlane(const std::string &plane) {
    _plane = plane;
}

/**
 * @brief Getter DatoMeteo
 * @return _datometeo
 */
const std::string &Vuelo::getDatometeo() const {
    return _datometeo;
}

/**
 * @brief Setter DatoMeteo
 * @param datometeo
 */
void Vuelo::setDatometeo(const std::string &datometeo) {
    _datometeo = datometeo;
}

/**
 * @brief Getter Fecha
 * @return _fecha
 */
const Fecha &Vuelo::getFecha() const {
    return _fecha;
}

/**
 * @brief Setter Fecha
 * @param fecha
 */
void Vuelo::setFecha(const Fecha &fecha) {
    _fecha = fecha;
}
/**
 * @brief Getter Aeropuerto Origen
 * @return airOrigen
 */
Aeropuerto *Vuelo::getAirOrigen() const {
    return airOrigen;
}

/**
 * @brief Setter Aeropuerto Origen
 * @param airOrigen
 */
void Vuelo::setAirOrigen(Aeropuerto *airOrigen) {
    Vuelo::airOrigen = airOrigen;
}

/**
 * @brief Getter Aeropueto Destino
 * @return airDestino
 */
Aeropuerto *Vuelo::getAirDestino() const {
    return airDestino;
}

/**
 * @brief Setter Aeropuerto Destino
 * @param airDestino
 */
void Vuelo::setAirDestino(Aeropuerto *airDestino) {
    Vuelo::airDestino = airDestino;
}

/**
 * @brief Getter Aerolinea
 * @return aerolinea
 */
Aerolinea *Vuelo::getAerolinea() const {
    return aerolinea;
}

/**
 * @brief Setter Aerolinea
 * @param aerolinea
 */
void Vuelo::setAerolinea(Aerolinea *aerolinea) {
    Vuelo::aerolinea = aerolinea;
}
