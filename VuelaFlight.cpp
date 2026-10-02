//
// Created by usuario on 11/10/2023.
//

#include "VuelaFlight.h"
#include "algorithm"

/**
 * @brief Constructor por Defecto
 * @code Constructor de tablahash
 */
VuelaFlight::VuelaFlight():airportsUTM(500,500,-200,-200,5100) {
    this->Leer_Aeropuertos();
    this->Leer_Aerolineas();
    this->Leer_Rutas();
    this->Cargar_Vuelos("../infovuelos_v1.csv");
    this->rellenaMalla();
}

/**
 * @brief Destructor
 *
 */
VuelaFlight::~VuelaFlight() {
        auto it=routedest.begin();

        while(it!=routedest.end()){
            auto aux=it;
            it++;
            delete aux->second;
            aux->second= nullptr;
            routedest.erase(aux);
        }

    auto malla=airportsUTM.getMalla();
    for (int i = 0; i < airportsUTM.getNDiv(); ++i) {
        for (int j = 0; j < airportsUTM.getNDiv(); ++j) {
            std::list<Aeropuerto*> lista = malla[i][j].getCelda();
            auto it_lista=lista.begin();
            while (it_lista!=lista.end()){
                auto aux=it_lista;
                it_lista++;
                delete aux.operator*();
                aux.operator*()= nullptr;
            }
        }
    }
}

/**
 * @brief Busca una ruta en nuestra lista enlazada
 *
 * @param id_orig
 * @param id_dest
 * @return
 */
Ruta &VuelaFlight::buscarrutasOrigDest(const std::string &id_orig, const std::string &id_dest) {
    Aeropuerto a1(id_orig);
    Aeropuerto a2(id_dest);
    Ruta *r= nullptr;
    std::list<Ruta>::iterator it_r(this->l_rutas.begin());
    while(it_r!= l_rutas.end()){
        if(it_r->getOrigin()==a1 && it_r->getDestination()==a2){
            return *it_r;
        }
        it_r++;
    }
    return *r;
}

/**
 * @brief Crea una Lista Enlazada con todas las rutas que tienen un aeropuerto de origen en común
 *
 * @param id_orig
 * @return
 */
std::list<Ruta> VuelaFlight::BuscarRutasOrigen(const std::string &id_orig) {

    Aeropuerto a_orig(id_orig);
    std::list<Ruta> r_orig;                         ///< Parametros
    auto it_r(this->l_rutas.begin());

    while(it_r!= l_rutas.end()){
        if(it_r->getOrigin()==a_orig){
            r_orig.push_back(*it_r);
        }
        it_r++;
    }

    return r_orig;
}

/**
 * @brief Añadir una ruta a nuestra lista
 *
 *
 * @param aerolinea
 * @param iata_orig
 * @param iata_dest
 */
void VuelaFlight::addRuta(const std::string &aerolinea,const std::string &iata_orig, const std::string &iata_dest) {
    Aeropuerto a_orig(iata_orig), a_dest(iata_dest);
    Aerolinea a_busqueda(aerolinea);
    Ruta ruta1;

    Aeropuerto *aorig=&v_aeropuertos.find(iata_orig)->second;           /////HACER CAMBIOS
    Aeropuerto *adest=&v_aeropuertos.find(iata_dest)->second;
    Aerolinea *a = &work.find(aerolinea)->second;
    if(aorig!= nullptr && adest != nullptr) {
        ruta1.setOrigin(*aorig);
        ruta1.setDestination(*adest);
        ruta1.setAerolinea(a);
        this->Anadir_Ruta(ruta1);
        a->linkaerolinea(ruta1);
        routeorig.insert(std::pair(iata_orig,ruta1));
        Ruta* ruta=new Ruta(ruta1);
        routedest.insert(std::pair(iata_dest,ruta));

    }
}

/**
 * @brief Buscais un aeropuerto por Pais
 *
 * @param pais
 * @return
 */
std::vector<Aeropuerto*> VuelaFlight::buscar_Aeropuerto_Pais(const std::string &pais) {
    std::vector<Aeropuerto*> vector_Pais;

    /*for(int i=0;i< this->v_aeropuertos.size();i++){
        if(v_aeropuertos[i].getIsoPais() == pais){
            vector_Pais.push_back(&v_aeropuertos[i]);
        }
    }*/
    return vector_Pais;
}


/**
 * @brief Obtenemos la lista
 *
 * @return
 */
std::list<Ruta> &VuelaFlight::getLRutas() {
    return l_rutas;
}

/**
 * @brief Añade un Aeropuerto al vector
 *
 * @param a
 */
void VuelaFlight::Anadir_Vector(Aeropuerto &a) {
     v_aeropuertos.insert(std::pair<std::string ,Aeropuerto> (a.getIata(),a));
     Aeropuerto *n_aeropuerto=new Aeropuerto(a);
     airportsUTM.inserta(a.getX(),a.getY(),n_aeropuerto);
}

/**
 * @brief Añadir una nueva Ruta a la lista
 *
 * @param r1
 */
void VuelaFlight::Anadir_Ruta(Ruta &r1) {
    l_rutas.push_back(r1);
    routeorig.insert(std::pair(r1.getOrigin().getIata(),r1));
    routedest.insert(std::pair(r1.getDestination().getIata(),&r1));
}

/**
 * @brief Getter del Vector Dinámico
 *
 * @return
 */
const std::unordered_map<std::string ,Aeropuerto> &VuelaFlight::ObtenerVector() {
    return v_aeropuertos;
}

/**
 * @brief Metodo para añadir una Aerolinea al árbol
 *
 * @param aer
 */
void VuelaFlight::Anadir_Aerolinea(Aerolinea &aer) {
    work.insert(std::make_pair(aer.getIcao(),aer));
}

/**
 * @brief Busca las Aerolineas activas
 *
 * @return vector de aeropuertos activo
 */
std::vector<Aerolinea *> VuelaFlight::buscar_Aerolinea_Activa() {
    std::vector<Aerolinea *> v_aer_act;
    std::map<std::string, Aerolinea>::iterator it = work.begin();

    while (it != work.end()) {
        if (it->second.isActivo()) {
            v_aer_act.push_back(&it->second);
        }
        it++;
    }
    return v_aer_act;
}

/**
 * @brief Devuelve el Arbol de Aerolineas.
 * @return
 */
std::map<std::string ,Aerolinea> &VuelaFlight::getAvlAerolinea() {
    return this->work;
}

/**
 * @brief busca una Aerolinea pasandole un icao
 * @code usa el buscaRecursiva del árbol
 * @param icao
 * @return Aerolinea encontrada
 */
Aerolinea &VuelaFlight::busca_Aerolinea(const std::string &icao) {
    return work.find(icao)->second;
}

/**
 * @brief busca todas las aerolineas de un pais
 * @code recorre todo el árbol y los datos encontrados se van insertando en el vector
 * @param pais
 * @return vector_dinamico con todas las aerolineas de un pais
 */
std::vector<Aerolinea *> VuelaFlight::buscar_Aerolineas_Pais(const std::string &pais) {
    std::vector<Aerolinea *> solucion;
    std::map<std::string ,Aerolinea>::iterator it(work.begin());
    while(it != work.end()) {
        if(it->second.getPais()==pais){
            solucion.push_back(&it->second);
        }
        it++;
    }
    return solucion;
}

/**
 * @brief Registra un vuelo en la lista de Rutas y en el mapa de Aerolineas
 * @param fnumber
 * @param iataAeroOrig
 * @param iataAerodest
 * @param plane
 * @param datosmeteo
 * @param f
 * @return true si el dato ha sido añadido correctamente
 */
bool VuelaFlight::registrarVuelo(const std::string fnumber, const std::string iataAeroOrig, const std::string iataAerodest,
                                const std::string plane, const std::string datosmeteo, Fecha &f) {
    std::string aerolinea=fnumber.substr(0,3);

    Aeropuerto* aorig=&v_aeropuertos.find(iataAeroOrig)->second;            //// HACER CAMBIOS
    Aeropuerto* adest=&v_aeropuertos.find( iataAerodest)->second;
    if(aorig!= nullptr && adest!= nullptr) {
        Vuelo vuelo(fnumber, plane, datosmeteo, f, aorig, adest);
        auto it_a = work.find(aerolinea);

        if (it_a != work.end()) {
            vuelo.setAerolinea(&it_a->second);
            it_a->second.addvuelo(vuelo);
            auto it_r_orig = routeorig.find(aorig->getIata());
            while (it_r_orig->first==aorig->getIata()){
                if (it_r_orig->second.getDestination().getIata()==iataAerodest){
                    it_r_orig->second.addVuelo(vuelo);
                }
                it_r_orig++;
            }
            return true;
        } else {
            return false;
        }
    }
    return false;
}

/**
 * @brief Funcion para leer el archivo donde se almacenan los vuelos
 * @param fichVuelos
 */
void VuelaFlight::Cargar_Vuelos(std::string fichVuelos ){
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;


    ///< Lectura del archivo de rutas y las añdimos a la lista enlazada
    std::string flightnomber="";
    std::string a_salida="";
    std::string a_llegada="";
    std::string plane= "";
    std::string dato_meteo="";
    std::string fecha="";
    bool activo=false;          /// Sirve para no leer la primera fila del archivo que no tiene nada que ver con la práctica
    int d,m,a;

    is.open(fichVuelos); //carpeta de proyecto
    if (is.good()) {
        clock_t t_ini = clock();

        while (getline(is, fila)) {

            if (fila != "") {
                columnas.str(fila);
                getline(columnas, flightnomber, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, a_salida, ';');
                getline(columnas, a_llegada, ';');
                getline(columnas, plane, ';');
                getline(columnas, dato_meteo, ';');
                getline(columnas, fecha, ';');
                if(activo) {
                    std::string dia=fecha.substr(0,2);
                    std::string mes=fecha.substr(3,2);
                    std::string anio=fecha.substr(6);
                    d=std::stoi(dia);
                    m=std::stoi(mes);
                    a=std::stoi(anio);
                    Fecha f(d,m,a);
                    this->registrarVuelo(flightnomber,a_salida,a_llegada,plane,dato_meteo,f);
                }else{
                    activo= true;
                }
                fila = "";
                columnas.clear();
            }

        }
        is.close();

        std::cout << "Tiempo lectura Vuelos: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
}

/**
 * @brief devuelve los datos de los vuelos con identificador especificado
 * @param fnumber
 * @code nos quedamos con los tres primeros valores del fnumber que corresponden al id de la Aerolinea
 * @code llamamos a la función getVuelos de la Aerolinea encontrada
 * @throw invalid_argument si el mapa de Aerolineas se encuentra vacio
 * @return vector con los Vuelos que contengan un ese identificador
 */
std::vector<Vuelo> VuelaFlight::BuscaVuelos(std::string fnumber) {
    if(work.size()==0){
        throw std::invalid_argument("VuelaFlight::BuscaVuelos: El mapa esta vacio " );
    }
    std::string aerolinea=fnumber.substr(0,3);
    auto it=work.find(aerolinea);
    std::vector<Vuelo> sol;
    if(it!=work.end()) {
       sol=it->second.getVuelos(fnumber);
    }
    return sol;
}

/**
 * @brief Busca una Aerolinea y de ella devuelve los vuelos realizados un dia
 * @param icaoAerolinea
 * @param f
 * @throw invalid_argument Si el mapa se encuentra vacio
 * @throw invalid_argument La Aerolinea buscada no esta almacenada
 * @return vector de vuelos de los vuelos realizados en una Aerolinea en una fecha concreta
 */
std::vector<Vuelo> VuelaFlight::vuelosOperadospor(std::string icaoAerolinea, Fecha f) {
    if (work.size()==0){
        throw std::invalid_argument("VuelaFlight::vuelosOperadospor: No hay ninguna Aerolinea insertada ");
    }
    auto it= work.find(icaoAerolinea);
    if(it==work.end()){
        throw std::invalid_argument("VuelaFlight::vuelosOperadospor: La Aerolinea insertada no existe ");
    }
    Fecha f_ini(f);
    f_ini.anadirDias(-1);
    f.anadirDias(1);
    return it->second.getVuelos(f_ini,f);
}

/**
 * @brief busca identificadores de vuelo (únicos), desde cualquier aeropuerto de un país al aeropuerto especificado
 * @param paisOrig
 * @param iataAeroDest
 * @throw invalid_argument la lista de rutas se encuentra vacia
 * @return conjunto de lo id de vuelo desde un pais a otro Aeropuerto indicado
 */
std::set<std::string> VuelaFlight::buscaVuelosDestAerop(const std::string paisOrig, const std::string iataAeroDest) {
    if(l_rutas.size()<=0){
        throw std::invalid_argument("VuelaFlight::buscaVuelosDestAerop: La lista de rutas se encuentra vacia ");
    }
    std::set<std::string > mapa;
    std::vector<Aeropuerto*> Aeropuertos_pais(this->buscar_Aeropuerto_Pais(paisOrig));
    std::sort(Aeropuertos_pais.begin(), Aeropuertos_pais.end());
    auto recorrer_rutas=l_rutas.begin();
    while (recorrer_rutas!=l_rutas.end()){
        if(recorrer_rutas->getFlightrou()->size()>0 &&
        std::binary_search(Aeropuertos_pais.begin(),Aeropuertos_pais.end(),&recorrer_rutas->getOrigin())){
            if (recorrer_rutas->getDestination().getIata()==iataAeroDest){
                auto Recorrer_Vuelos = recorrer_rutas->getFlightrou()->begin();
                while (Recorrer_Vuelos != recorrer_rutas->getFlightrou()->end()){
                    if(mapa.find(Recorrer_Vuelos.operator*()->getFlightnumb())==mapa.end()){
                        mapa.insert(Recorrer_Vuelos.operator*()->getFlightnumb());
                    }
                    Recorrer_Vuelos++;
                }

            }
        }
        recorrer_rutas++;
    }
    return mapa;
}

/**
 * @brief busca aeropuertosb(únicos) donde opera una aerolínea específica
 * @param icaoAerolinea
 * @throw invalid_argument La Aerolinea buscada no existe
 * @return mapa de Aeropuertos donde trabaja la Aerolinea indicada
 */
std::map<std::string, Aeropuerto> VuelaFlight::buscaAeropuertosAerolinea(std::string icaoAerolinea) {
    std::map<std::string ,Aeropuerto> mapaAeropuertoAerolinea;
    auto it_aerolinea_encontrada= work.find(icaoAerolinea);
    if(it_aerolinea_encontrada!=work.end()){
        std::multimap<std::string , Vuelo>rutas_aerolinea(*it_aerolinea_encontrada->second.getFlights());               ///Puede Reventar aqui
        auto recorrermultimapa= rutas_aerolinea.begin();
        while(recorrermultimapa != rutas_aerolinea.end()) {


            if(mapaAeropuertoAerolinea.find(recorrermultimapa->second.getAirOrigen()->getIata())== mapaAeropuertoAerolinea.end()){
                mapaAeropuertoAerolinea.insert(std::pair(recorrermultimapa->second.getAirOrigen()->getIata(),
                                                         *recorrermultimapa->second.getAirOrigen()));
            }
            if(mapaAeropuertoAerolinea.find(recorrermultimapa->second.getAirDestino()->getIata())== mapaAeropuertoAerolinea.end()){
                mapaAeropuertoAerolinea.insert(std::pair(recorrermultimapa->second.getAirDestino()->getIata(),
                                                         *recorrermultimapa->second.getAirDestino()));
            }

            recorrermultimapa++;
        }
    }else{
        throw std::invalid_argument ("VuelaFlight::buscaAeropuertosAerolinea: El codigo Icao no corresponde a ninguna Aerolinea Almacenada");
    }

    return mapaAeropuertoAerolinea;
}

/**
 * @brief Busca un Aeropuerto pasandole el iata
 * @code calcula la clave con djb2
 * @param iata
 * @return Puntero al Aeropuerto o null si no es encontrado
 */
Aeropuerto *VuelaFlight::buscaAeropuerto(std::string iata) {
    return &v_aeropuertos.find( iata)->second;
}

/**
 * @brief Devuelve el numero total de Aeropuertos en la tabla hash
 * @return numAeropuertos
 */
unsigned int VuelaFlight::getNumAeropuertos() {
    return v_aeropuertos.size();

}


/**
 * @brief Elimina un Aeropuerto y todas los vuelos y rutas que hay con este Aeropuerto
 * @param Iata
 */
void VuelaFlight::eliminar_aeropuerto(std::string Iata) {
    auto it=work.begin();
    while(it!=work.end()){
        it->second.bajaAeropuerto(Iata);
        it++;
    }
    unsigned long clave_orig = 5381;
    int c;

    for (int j = 0; j < Iata.size(); ++j) {
        c = Iata[j];
        clave_orig = ((clave_orig << 5) + clave_orig) + c; /* hash * 33 + c */
        clave_orig = clave_orig * 33 + c;
    }

    std::multimap<std::string ,Ruta>::iterator it1=routeorig.find(Iata);
    while(it1->first==Iata){
        auto buscar= routedest.find(it1->second.getDestination().getIata());
        while (buscar->first == it1->second.getDestination().getIata()){
            if(buscar->second->getOrigin().getIata()==Iata){
                Ruta *aux=buscar->second;
                routedest.erase(buscar);
                delete aux;
                aux= nullptr;
            }
            buscar++;
        }
        it1++;
    }
    routeorig.erase(Iata);
    std::multimap<std::string ,Ruta*>::iterator it3=routedest.find(Iata);
    while (it3->first==Iata){
        auto buscar=routeorig.find(it3->second->getOrigin().getIata());
        while (buscar->first==Iata){
            if(buscar->second.getOrigin().getIata()==Iata){
                routeorig.erase(buscar);
            }
            buscar++;
        }
        Ruta*aux=it3->second;
        delete aux;
        aux= nullptr;
        it3++;
    }
    auto it_l_rutas=l_rutas.begin();
    while(it_l_rutas!=l_rutas.end()){
        if(it_l_rutas->getOrigin().getIata()==Iata || it_l_rutas->getDestination().getIata()==Iata){
            auto borrado=it_l_rutas;
            it_l_rutas++;
            l_rutas.erase(borrado);
        }else {
            it_l_rutas++;
        }
    }
    v_aeropuertos.erase(v_aeropuertos.find(Iata));
}


/**
 * @brief Elimina los Aeropuertos que no se encuentran en ninguna ruta.
 */
void VuelaFlight::eliminar_aeropuertos_inactivos() {
    auto it=v_aeropuertos.begin();
    while(it!=v_aeropuertos.end()) {
        if(&it->second!= nullptr){
            /// Buscamos ese dato en rutasOrigen

            if(routeorig.find(it->second.getIata())==routeorig.end() &&       ///Si el Aeropuerto no es un aeropuerto de Origen buscamos por uno de destino
               routedest.find(it->second.getIata())==routedest.end()) {
               this->eliminar_aeropuerto(it->second.getIata());
            }
        }

    }
}


/**
 * @brief Relleba ka malla de Aeropuertos recorriendo el undered map de Aeropuertos que hemos rellenado anteriormenete
 *
 * @post Tiempo que tarda en leer estos datos
 */
void VuelaFlight::rellenaMalla() {
    if(v_aeropuertos.size()<0){
        throw std::invalid_argument("VuelaFlight::rellenaMalla: No hay aeropuertos registrados");
    }
    clock_t t_ini = clock();
    auto it_aeropuertos=v_aeropuertos.begin();
    while (it_aeropuertos!=v_aeropuertos.end()){
        float latitud=it_aeropuertos->second.getY();
        float longitud=it_aeropuertos->second.getX();
        Aeropuerto *a1=new Aeropuerto(it_aeropuertos->second);
        airportsUTM.inserta(longitud,latitud,a1);
        it_aeropuertos++;
    }
    std::cout << "Tiempo lectura Rellenar Malla: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
}

/**
 * @brief Función para leer los Aeropuertos y guardarlos en vuelos
 *
 * @post Tiempo que tarda en leer estos datos
 */
void VuelaFlight::Leer_Aeropuertos(){
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string id = "";
    std::string iata = "";
    std::string tipo = "";
    std::string nombre = "";
    std::string latitud_str = "";
    std::string longitud_str = "";
    std::string continente = "";
    std::string iso_pais = "";
    int fallos=0;
    bool activo=false;
    float latitud, longitud;

    is.open("../aeropuertos_v3.csv"); //carpeta de proyecto
    if (is.good()) {

        clock_t t_ini = clock();
        while (getline(is, fila)) {

            if (fila != "") {

                columnas.str(fila);


                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, iata, ';');
                getline(columnas, tipo, ';');
                getline(columnas, nombre, ';');
                getline(columnas, latitud_str, ';');
                getline(columnas, longitud_str, ';');
                getline(columnas, continente, ';');
                getline(columnas, iso_pais, ';');

                //  Transformamos la latitud y longitud a float
                if(activo) {
                    latitud = std::stof(latitud_str);
                    longitud = std::stof(longitud_str);
                    UTM pos(latitud, longitud);

                    Aeropuerto a1(id, iata, tipo, nombre, pos, continente, iso_pais);
                    v_aeropuertos.insert(std::pair<std::string ,Aeropuerto> (a1.getIata(),a1));


                }else{
                    activo=true;
                }
                fila = "";
                columnas.clear();
            }

        }
        is.close();

        std::cout << "Tiempo lectura Leer Aeropuertos: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

}

/**
 * @brief Función para leer Aerolineas
 *
 * @post Tiempo que tarda en leer estos datos
 */
void VuelaFlight::Leer_Aerolineas() {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;


    ///< Lectura del archivo de rutas y las añdimos a la lista enlazada
    std::string _id="";
    std::string _icao="";
    std::string _nombre="";
    std::string _pais="";
    std::string activo;

    Aeropuerto a1("");
    Ruta r1;
    bool p=false;          /// Sirve para no leer la primera fila del archivo que no tiene nada que ver con la práctica

    is.open("../aerolineas_v1.csv"); //carpeta de proyecto
    if (is.good()) {
        clock_t t_ini = clock();

        while (getline(is, fila)) {

            if (fila != "") {
                columnas.str(fila);
                getline(columnas, _id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, _icao, ';');
                getline(columnas, _nombre, ';');
                getline(columnas, _pais, ';');
                getline(columnas, activo, ';');
                if(p){
                    unsigned  int id;
                    bool _activo;
                    id= std::stoi(_id);
                    if(activo=="Y"){
                        _activo = true;
                    }else{
                        _activo = false;
                    }
                    Aerolinea aer(id,_icao,_nombre,_pais,_activo);
                    Anadir_Aerolinea(aer);
                }else{
                    p= true;
                }
                fila = "";
                columnas.clear();
            }

        }
        is.close();

        std::cout << "Tiempo lectura Leer Aerolineas: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
}

/**
 * @brief Función para leer las Rutas y guardarlos en vuelos
 *
 * @post Tiempo que tarda en leer estos datos
 */
void VuelaFlight::Leer_Rutas(){
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;


    ///< Lectura del archivo de rutas y las añdimos a la lista enlazada
    std::string aerolinea="";
    std::string a_salida="";
    std::string a_llegada="";
    Aeropuerto a1("");
    Ruta r1;
    bool activo=false;          /// Sirve para no leer la primera fila del archivo que no tiene nada que ver con la práctica

    is.open("../rutas_v1.csv"); //carpeta de proyecto
    if (is.good()) {
        clock_t t_ini = clock();

        while (getline(is, fila)) {

            if (fila != "") {
                columnas.str(fila);
                getline(columnas, aerolinea, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, a_salida, ';');
                getline(columnas, a_llegada, ';');
                if(activo) {
                    addRuta(aerolinea,a_salida,a_llegada);
                }else{
                    activo= true;
                }
                fila = "";
                columnas.clear();
            }

        }
        is.close();

        std::cout << "Tiempo lectura Leer Rutas: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
}

/**
 * @brief Busca Aeropuertos en un radio indicado sobre una posición
 * @param pos
 * @param radio
 * @return
 */
std::vector<Aeropuerto *> VuelaFlight::buscarAeropuertosRadio(UTM &pos, float radio) {
   return airportsUTM.buscarRadio(pos.getLongitud(),pos.getLatitud(),radio);
}

/**
 * @brief Aeropuerto con más salidas
 * @code busca todos los aeropuertos en un rango y los ordena según el numero de vuelos de salida que tenga cada uno
 * @param pos
 * @param radio
 * @return
 */
std::vector<Aeropuerto *> VuelaFlight::aeropuertoMassalidas(UTM &pos, float radio) {
    std::vector<Aeropuerto*> vector_aeropuertos_cercanos(this->buscarAeropuertosRadio(pos,radio));
    std::priority_queue<Aeropuerto_contador> cola_prioridad;
    std::vector<Aeropuerto*> sol;
    for (int i = 0; i < vector_aeropuertos_cercanos.size(); ++i) {
        int contador=0;
        auto it=routeorig.find(vector_aeropuertos_cercanos[i]->getIata());
        if(it!=routeorig.end()){
            while(it->first==vector_aeropuertos_cercanos[i]->getIata()){
                contador=contador+it->second.getNumVuelos();
                it++;
            }
        }
        Aeropuerto_contador cont(vector_aeropuertos_cercanos[i],contador);
        cola_prioridad.push(cont);
    }
    for (int i = 0; i < 5; ++i) {
        sol.push_back(cola_prioridad.top().getA());
        cola_prioridad.pop();
    }
    return sol;
}

/**
 * @brief Devuelve el Aeropuerto más cercano a un punto.
 * @code Llama a la función mascercano() de la clase Malla.
 * @param pos
 * @return
 */
Aeropuerto *VuelaFlight::aeropuertomasCercano(UTM &pos) {
    return airportsUTM.masCercano(pos.getLongitud(),pos.getLatitud());
}