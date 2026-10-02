//
// Created by usuario on 25/09/2023.
//

#ifndef PR1_AEROPUERTO_H
#define PR1_AEROPUERTO_H

#include "iostream"
#include "string"
#include "sstream"
#include "UTM.h"

class Aeropuerto {
private:
    std::string _id="";
    std::string _iata="";
    std::string _tipo="";
    std::string _nombre="";
    UTM _posicion;
    std::string _continente="";
    std::string _iso_pais="";
public:
    Aeropuerto()=default;
    Aeropuerto(const std::string& id, const std::string& iata,const std::string&  tipo, const std::string& nombre,
               const UTM& posicion, const  std::string& continente, const std::string& iso_pais);
    Aeropuerto(const Aeropuerto &orig);
    Aeropuerto(const std::string& iata);
    virtual ~Aeropuerto();

    const std::string &getId() const;
    const std::string &getContinente() const;
    const std::string &getIata() const;
    const std::string &getTipo() const;
    const std::string &getNombre() const;
    const std::string &getIsoPais() const; 
    std::string ObtenerPosicion() const;

    Aeropuerto &operator =(const Aeropuerto &rhs);
    bool operator <(const Aeropuerto &rhs) const;
    bool operator >(const Aeropuerto &rhs) const;
    bool operator<=(const Aeropuerto &rhs) const;
    bool operator>=(const Aeropuerto &rhs) const;
    bool operator==(const Aeropuerto &rhs) const;
    bool operator!=(const Aeropuerto &rhs) const;

    float getX();
    float getY();
};


#endif //PR1_AEROPUERTO_H
