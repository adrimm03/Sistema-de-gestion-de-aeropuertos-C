//
// Created by usuario on 27/10/2023.
//

#ifndef PR1_AEROLINEA_H
#define PR1_AEROLINEA_H

#include "string"
#include "sstream"
#include "Ruta.h"
#include "deque"
#include "map"
#include "vector"

class Aerolinea {
    private:
        unsigned int _id=0;											// unsigned int ,
        std::string _icao="";                                       // CDC Icao den a Aerolinea Type:std::string
        std::string _nombre="";                                     /// Nombre de la Aerolinea
        std::string _pais="";                                       /// Pais de la Aerolinea
        bool _activo= false;                                        /// Indica si la Aerolinea esta activa
        std::deque<Ruta*> _aerorouter;                              /// Vector de punteros a rutas
        std::multimap<std::string ,Vuelo> flights;                  /// Multimapa con clave el identificador de un vuelo
    public:
        Aerolinea()=default;
        Aerolinea(const unsigned int id,const std::string& icao, const std::string& nombre, const std::string&  pais, bool activo,
                  std::deque<Ruta*> &aerorouter, const unsigned int numaerorutas);
        Aerolinea(const unsigned int id,const std::string icao, const std::string nombre, const std::string  pais, bool activo);
        Aerolinea(const std::string& icao);
        Aerolinea(const Aerolinea& orig);
        virtual ~Aerolinea();
        std::string ToCSV();
        std::string informacion_Aeroroute() ;

        ///Metodos Getter y Setter
        std::deque<Ruta*> getAerorouter() const;
        unsigned int getId() const;
        void setId(unsigned int id);
        const std::string &getIcao() const;
        void setIcao(const std::string &icao);
        const std::string &getNombre() const;
        void setNombre(const std::string &nombre);
        const std::string &getPais() const;
        void setPais(const std::string &pais);
        bool isActivo() const;
        void setActivo(bool activo);
        unsigned int getNumaerorutas() const;
        void setNumaerorutas(unsigned int numaerorutas);
        const std::multimap<std::string, Vuelo> *getFlights() const;

    ///Métodos a Implementar
        std::vector<Aeropuerto> getAeropuertoOrig();
        std::vector<Ruta>& getRutasAeropuerto(const std::string iataAeropuerto);
        void linkaerolinea(Ruta &r);
        Vuelo *addvuelo(Vuelo &v);
        std::vector<Vuelo> getVuelos( std::string fnumber);
        std::vector<Vuelo> getVuelos( Fecha &f_ini, Fecha &f_fin);
        void bajaAeropuerto(std::string IATA);

        ///Operadores <, > y == usamos el parametro _icao
        Aerolinea& operator=(Aerolinea &rhs);
        bool operator==(const Aerolinea &rhs) const;
        bool operator< (const Aerolinea &rhs) const;
        bool operator> (const Aerolinea &rhs) const;
        bool operator!=(const Aerolinea &rhs) const;
        bool operator<=(const Aerolinea &rhs) const;
        bool operator>=(const Aerolinea &rhs) const;
    };



#endif //PR1_AEROLINEA_H
