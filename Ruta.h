//
// Created by admin on 10/10/2023.
//

#ifndef PR1_RUTA_H
#define PR1_RUTA_H

#include "list"
#include "Vuelo.h"

class Aerolinea;
class Ruta {

private:
    Aerolinea *aerolinea = nullptr;
    Aeropuerto *_origin= nullptr;
    Aeropuerto *_destination = nullptr;
    std::list<Vuelo*> flightrou;                /// Lista de punteros a Vuelos

public:
    Ruta();
    Ruta(const Ruta &orig);
    Ruta(Aerolinea *a, Aeropuerto* origin, Aeropuerto* destin);
    virtual ~Ruta();

    /// Getter y Setter de la clase
    Aeropuerto &getOrigin() const;
    void setOrigin(Aeropuerto& origin);
    Aeropuerto &getDestination() const;
    void setDestination(Aeropuerto& destination);
    void setAerolinea(Aerolinea *aerolinea1);
    /// Operadores = y ==
    Ruta& operator=(const Ruta &orig);
    bool operator==(const Ruta &rhs) const;
    ///Métodos que nos piden
    bool addVuelo( Vuelo v);
    unsigned int getNumVuelos();
    std::list<Vuelo *> *getFlightrou();

};


#endif //PR1_RUTA_H
