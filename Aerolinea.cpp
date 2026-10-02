//
// Created by usuario on 27/10/2023.
//

#include "Aerolinea.h"

/**
 *
 * @param id[in]
 * @param icao[in]
 * @param nombre[in]
 * @param pais[in]
 * @param activo[in]
 * @param aerorouter[in] deque de punteros a Ruta
 * @param numaerorutas[in]
 */
Aerolinea::Aerolinea(const unsigned int id, const std::string& icao, const std::string& nombre, const std::string& pais,
                     bool activo,std::deque<Ruta*> &aerorouter, const unsigned int numaerorutas) :_id(id),_icao(icao),_nombre(nombre),_pais(pais),
                     _activo(activo){
    this->_aerorouter=aerorouter;
}

/**
 * @brief Constructor copia
 * @param orig
 */
Aerolinea::Aerolinea(const Aerolinea &orig): _id(orig._id),_icao(orig._icao),_nombre(orig._nombre),_pais(orig._pais),
                                            _activo(orig._activo),_aerorouter(orig._aerorouter), flights(orig.flights){

}
/**
 * @brief Constructor Parametrizado
 * @param id
 * @param icao
 * @param nombre
 * @param pais
 * @param activo
 */
Aerolinea::Aerolinea(const unsigned int id, const std::string icao, const std::string nombre, const std::string pais,
                     bool activo): _id(id),_icao(icao),_nombre(nombre),_pais(pais),_activo(activo) {

}
/**
 * @brief Constructor parametrizado
 * @code implementado para la busqueda de una aerolinea en el AVL
 * @param icao
 *
 */
Aerolinea::Aerolinea(const std::string& icao):_icao(icao) {

}
/**
 * @brief destructor
 */
Aerolinea::~Aerolinea() {
    for (int i = _aerorouter.size()-1; i > 0; --i) {
        _aerorouter[i]= nullptr;
        delete _aerorouter[i];
        _aerorouter.pop_front();
    }
}
/**
 * @brief getter Aerolinea
 * @return Vector dinamico de ruta
 */
std::deque<Ruta*> Aerolinea::getAerorouter() const {
    return _aerorouter;
}

/**
 * @brief getter id
 * @return
 */
unsigned int Aerolinea::getId() const {
    return _id;
}
 /**
  * @brief setter id
  * @param id
  */
void Aerolinea::setId(unsigned int id) {
    _id = id;
}
/**
 * @brief getter codigo de la aerolinea
 * @return
 */
const std::string &Aerolinea::getIcao() const {
    return _icao;
}
/**
 * @brief setter codigo de la aerolinea
 * @param icao
 */
void Aerolinea::setIcao(const std::string &icao) {
    _icao = icao;
}
/**
 * @brief getter nombre de la aerolinea
 * @return
 */
const std::string &Aerolinea::getNombre() const {
    return _nombre;
}
/**
 * @brief setter nombre de la aerolinea
 * @param nombre
 */
void Aerolinea::setNombre(const std::string &nombre) {
    _nombre = nombre;
}
/**
 * @brief getter pais
 * @return
 */
const std::string &Aerolinea::getPais() const {
    return _pais;
}
/**
 * @brief setter pais
 * @param pais
 */
void Aerolinea::setPais(const std::string &pais) {
    _pais = pais;
}

/**
 * @brief indica si la aerolinea esta activa
 * @return
 */
bool Aerolinea::isActivo() const {
    return _activo;
}
/**
 * @brief setter estado de activacion de la aerolinea
 * @param activo
 */
void Aerolinea::setActivo(bool activo) {
    _activo = activo;
}

/**
 * /**
 * @brief getter numero de rutas
 * @return
 */
unsigned int Aerolinea::getNumaerorutas() const {
    return _aerorouter.size();
}


/**
 * @brief selecciona el aeropuerto de origen
 * @throw invalid_argument Si el vector de Aerolineas esta vacio
 * @return vector dinamico del aeropuerto de origen
 */

std::vector<Aeropuerto> Aerolinea::getAeropuertoOrig() {
    if(_aerorouter.size()==0){
        throw std::invalid_argument("Aerolinea::getAeropuertoOrig(): No hay Rutas insertadas en esta Aerolinea ");
    }
    std::vector<Aeropuerto> v;
    for (int i = 0; i < _aerorouter.size(); ++i) {
        v.push_back(_aerorouter[i]->getOrigin());
    }
    return v;
}

/**
 * @brief busca aeropuetos
 * @param iataAeropuerto
 * @return rutas cuyo aeropuerto origen o destino sea el indicado por parámetro
 */
std::vector<Ruta> &Aerolinea::getRutasAeropuerto(const std::string iataAeropuerto) {
    std::vector<Ruta> *v_rutas;
    for (int i = 0; i < _aerorouter.size(); ++i) {
        if(_aerorouter[i]->getOrigin().getIata() == iataAeropuerto || _aerorouter[i]->getDestination().getIata() == iataAeropuerto) {
            v_rutas->push_back(*_aerorouter[i]);
        }
    }
    return *v_rutas;
}

/**
 * @brief Añade una ruta al vector de rutas de la Aerolinea.
 * @param r
 */
void Aerolinea::linkaerolinea(Ruta& r) {
    Ruta* p = new Ruta(r);
    _aerorouter.push_back(p);
}


/**
 * @brief operador comparacion ( == )
 * @param rhs
 * @return si el codigo ICAO es el mismo
 */
bool Aerolinea::operator==(const Aerolinea &rhs) const {
    return _icao == rhs._icao;
}

/**
 * @brief operador ( < )
 * @param rhs
 * @return
 */
bool Aerolinea::operator<(const Aerolinea &rhs) const {
    return this->_icao < rhs._icao;
}

/**
 * @brief operador ( > )
 * @param rhs
 * @return
 */
bool Aerolinea::operator>(const Aerolinea &rhs) const {
    return this->_icao > rhs._icao;
}

/**
 * operador distinto ( != )
 * @param rhs
 * @return
 */
bool Aerolinea::operator!=(const Aerolinea &rhs) const {
    return !(rhs == *this);
}

/**
 * @brief operador menor o igual ( <= )
 * @param rhs
 * @return
 */
bool Aerolinea::operator<=(const Aerolinea &rhs) const {
    return (*this<rhs) || (*this==rhs);
}
/**
 * @brief operador mayor o igual ( >= )
 * @param rhs
 * @return
 */
bool Aerolinea::operator>=(const Aerolinea &rhs) const {
    return (*this>rhs) || (*this==rhs);
}
/**
 * @brief operador igual ( = )
 * @param rhs
 * @return
 */
Aerolinea &Aerolinea::operator=(Aerolinea &rhs) {
    if(*this==rhs){
        return *this;
    }else{
        this->_id=rhs._id;
        this->_icao=rhs._icao;
        this->_pais=rhs._pais;
        this->_nombre=rhs._nombre;
        this->_activo=rhs._activo;
        this->_aerorouter=rhs._aerorouter;
        return *this;
    }
}
/**
 * @brief Formato TO_CSV
 * @code usa la función 'Informacion_Aeroroute
 * @return una cadena con toda la información sobre la Aerolinea
 */
std::string Aerolinea::ToCSV() {
    std::stringstream frase;
    std::string sol;
    if(_activo) {
        frase << "Id: " << this->_id << ", nombre: " << this->_nombre << " , pais: " << this->_pais << ", codigo ICAO: "
              << this->_icao << ", esta activo y contiene: " << this->_aerorouter.size() << " rutas. Estos son: "
              << std::endl << this->informacion_Aeroroute();
    }else{
        frase << "Id: " << this->_id << ", nombre: " << this->_nombre << " , pais: " << this->_pais << ", codigo ICAO: "
              << this->_icao << ", no  esta activo y contiene: " << this->_aerorouter.size() << " rutas. Estos son: " << std::endl
              << this->informacion_Aeroroute();
    }
    sol = frase.str();
    return sol;

}

/**
 * @brief Formato To_CSV de Aeroroute
 * @return una cadena sobre todas las rutas
 */
std::string Aerolinea::informacion_Aeroroute()  {
    std::stringstream ss;
    std::string sol;
    for (int i = 0; i < _aerorouter.size() ; ++i) {
        ss <<"Pos: " << i <<", Origen id: " << _aerorouter[i]->getOrigin().getId()  << ", Nombre: " << _aerorouter[i]->getOrigin().getNombre() <<
        ", Continente: " << _aerorouter[i]->getOrigin().getContinente() << ", Iata: " << _aerorouter[i]->getOrigin().getIata() << ", Posición: " <<
        _aerorouter[i]->getOrigin().ObtenerPosicion() << std::endl;
    }
    return ss.str();
}


/**
 * @brief Añade un vuelo al multimapa de vuelos
 * @param v
 * @code compruba antes de añadir que la Aerolinea sea la correcta
 * @code Recorre la lista de rutas y comprueba si alguna coincide para añadirle a ella tambien el vuelo
 * @return puntero al dato insertado
 */
Vuelo *Aerolinea::addvuelo(Vuelo &v) {
    if(v.getAerolinea()!=this){
        return nullptr;
    }

    flights.insert(std::make_pair(v.getFlightnumb(),v));
    auto rango=flights.equal_range(v.getFlightnumb());
    auto iterUltimo = std::prev(rango.second);
    for (int i=0;i<_aerorouter.size();i++) {
        if(&_aerorouter[i]->getOrigin()==v.getAirOrigen() && &_aerorouter[i]->getDestination()==v.getAirDestino()){
            _aerorouter[i]->addVuelo(v);
            return &iterUltimo->second;
        }

    }

    return &iterUltimo->second;
}

/**
 * @brief Devuelve los vuelos registrados con el identificador indicado.
 * @param fnumber
 * @return vector con los vuelos que contengan este identificador de vuelo
 */
std::vector<Vuelo> Aerolinea::getVuelos(std::string fnumber) {
    std::vector<Vuelo> vuelos;
    for (auto it = flights.begin(); it != flights.end(); ++it) {
        const std::string& fnumber_vuelo = it->first;
        if(fnumber==fnumber_vuelo){
           const Vuelo v= it->second;
            vuelos.push_back(v);

        }
    }
    return vuelos;
}

/**
 * @brief Devuelve los vuelos registrados en un rango de fechas determinado.
 * @param f_ini
 * @param f_fin
 * @return vector de los vuelos comprendidos entre dos fechas
 */
std::vector<Vuelo> Aerolinea::getVuelos(Fecha &f_ini, Fecha &f_fin) {
    std::vector<Vuelo> vuelos;
    for (auto it = flights.begin(); it != flights.end(); ++it) {
        Fecha fecha= it->second.getFecha();
        if(fecha < f_fin &&  f_ini < fecha){
            const Vuelo v= it->second;
            vuelos.push_back(v);
        }
    }
    return vuelos;
}

/**
 * @brief Getter Vuelos
 * @return flights
 */
const std::multimap<std::string, Vuelo> *Aerolinea::getFlights() const {
    return &flights;
}

/**
 * @brief Da de baja un Aeropuerto
 * @code dado un iata elimina las rutas y vuelos que tenga ese aeropuerto en esta aerolinea
 * @param IATA
 */
void Aerolinea::bajaAeropuerto(std::string IATA) {

    for (auto i = flights.begin(); i != flights.end() ; ++i) {
        if(i->second.getAirOrigen()->getIata()==IATA || i->second.getAirDestino()->getIata()==IATA){
            flights.erase(i);
        }
    }

    for (auto i = _aerorouter.begin(); i != _aerorouter.end(); ++i) {
        if(i.operator*()->getOrigin().getIata()==IATA || i.operator*()->getDestination().getIata()==IATA){
        _aerorouter.erase(i);
        }
    }

}
