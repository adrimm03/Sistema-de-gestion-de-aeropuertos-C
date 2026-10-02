//
// Created by usuario on 25/09/2023.
//

#include "Aeropuerto.h"
/**
 * @brief Constructor parametrizado
 *
 * @param id
 * @param idem
 * @param tipo
 * @param nombre
 * @param posicion
 * @param continente
 * @param iso_pais
 */
Aeropuerto::Aeropuerto(const std::string& id, const std::string& iata, const std::string& tipo, const std::string& nombre,
                       const UTM& posicion, const std::string& continente, const std::string& iso_pais): _id(id), _iata(iata),
                                        _tipo(tipo), _nombre(nombre), _posicion(posicion), _continente(continente),
                                        _iso_pais(iso_pais){

}

/**
 * @brief Constructor copia
 *
 * @param orig
 */
Aeropuerto::Aeropuerto(const Aeropuerto &orig): _id(orig._id), _iata(orig._iata), _tipo(orig._tipo),
                                        _nombre(orig._nombre), _posicion(orig._posicion),_continente(orig._continente),
                                        _iso_pais(orig._iso_pais){

}
/**
 * @brief Destructor
 */
Aeropuerto::~Aeropuerto() {

}
/**
 * @brief Operador ==
 * @post Dos aeropuertos seran iguales si tienen el mismo identificador
 *
 * @param rhs
 * @return true si son iguales y false si no lo son
 */
bool Aeropuerto::operator==(const Aeropuerto &rhs) const {
    return _iata == rhs._iata ;
}

/**
 * @brief Operador !=
 * @post Si dos objetos Aeropuerto no son iguales serán distintos
 *
 * @param rhs
 * @return true si no son iguales y false si son iguales
 */
bool Aeropuerto::operator!=(const Aeropuerto &rhs) const {
    return !(rhs == *this);
}

/**
 * @brief Operator <
 * @post Un aeropuerto sera menor que otro si su id es menor
 *
 * @param rhs
 * @return true si es menor y false si es mayor o igual
 */
bool Aeropuerto::operator<(const Aeropuerto &rhs) const {
    return this->_iata < rhs._iata;
}

/**
 * @brief operador >
 * @post un objeto Aeropuerto sera mayor a otro si su id es mayor
 *
 * @param rhs
 * @return true si es mayor y false si es menor o igual
 */
bool Aeropuerto::operator>(const Aeropuerto &rhs) const {
    return this->_iata > rhs._iata;
}

/**
 * @brief Operador <=
 *
 * @param rhs
 * @return true si el aeropuerto es menor e igual y false si es mayor
 */
bool Aeropuerto::operator<=(const Aeropuerto &rhs) const {
    return *this < rhs && *this==rhs;
}

/**
 * @brief Operador >=
 *
 * @param rhs
 * @return true si es mayor o igual y false si es menor
 */
bool Aeropuerto::operator>=(const Aeropuerto &rhs) const {
    return *this > rhs && *this==rhs;
}
/**
 * @brief Getter id
 *
 * @return id de nuestro aeropuerto
 */
const std::string &Aeropuerto::getId() const {
    return _id;
}

/**
 * @brief Getter Continente
 *
 * @return Continente
 */
const std::string &Aeropuerto::getContinente() const {
    return _continente;
}

/**
 * @brief Getter Idem
 *
 * @return Idem
 */
const std::string &Aeropuerto::getIata() const {
    return _iata;
}

/**
 * @brief Getter tipo
 *
 * @return Tipo
 */
const std::string &Aeropuerto::getTipo() const {
    return _tipo;
}

/**
 * @brief Getter Nombre
 *
 * @return nombre
 */
const std::string &Aeropuerto::getNombre() const {
    return _nombre;
}

/**
 * @brief Getter Iso Pais
 *
 * @return Iso Pais
 */
const std::string &Aeropuerto::getIsoPais() const {
    return _iso_pais;
}

/**
 * @brief Operador =
 * @post Dado dos objetos Aeropuerto le asignara los atributos de uno al otro. Antes debe comprobar que ambos objetos no sean iguales
 *
 * @param rhs
 * @return el objeto que asignaremos
 */
Aeropuerto &Aeropuerto::operator=(const Aeropuerto &rhs)  {
    if(rhs == *this){
        return *this;
    }else {
        this->_id= rhs._id;
        this->_posicion= rhs._posicion;
        this->_iso_pais = rhs._iso_pais;
        this->_continente= rhs._continente;
        this->_nombre = rhs._nombre;
        this->_tipo = rhs._tipo ;
        this->_iata = rhs._iata;
    }
    return *this;
}

/**
 * @brief Metodo toCSV para obtener la posicion segun sus dos parametros
 *
 * @return la posición como tipo string
 */
std::string Aeropuerto::ObtenerPosicion() const {
    std::stringstream aux;
    aux << _posicion.getLatitud() << "," << _posicion.getLongitud() << std::endl;
    return aux.str();
}

/**
 * @brief Constructor semi-parametrizado del atributo identificador
 *
 * @param id
 */
Aeropuerto::Aeropuerto(const std::string& iata): _iata(iata) {

}

float Aeropuerto::getX() {
    return _posicion.getLongitud();
}

float Aeropuerto::getY() {
    return _posicion.getLatitud();
}