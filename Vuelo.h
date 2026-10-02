//
// Created by usuario on 07/11/2023.
//

#ifndef PR1_VUELO_H
#define PR1_VUELO_H


#include "string"
#include "fecha.h"
#include "Aeropuerto.h"

class Aerolinea;
class Vuelo {
private:
    std::string _flightnumb="";                  /// Identificador del Vuelo
    std::string _plane="";
    std::string _datometeo="";                    /// Tiempo Atmosférico del Vuelo
    Fecha _fecha;                                 /// Fecha del Vuelo 'dd-mm-aa'
    Aeropuerto *airOrigen= nullptr;               /// Puntero al Aeropuerto Origen
    Aeropuerto *airDestino= nullptr;              /// Puntero al Aeropuerto Destino
    Aerolinea *aerolinea = nullptr;               /// Puntero a la Aerolinea asociada al vuelo
public:
    Vuelo()=default;
    Vuelo(const std::string flightnumb,const std::string plane,
          const std::string  datometeo,const Fecha& fecha,Aeropuerto *&orig,Aeropuerto *&dest);
    Vuelo(const Vuelo &orig);
    virtual ~Vuelo();


    const std::string &getFlightnumb() const;
    void setFlightnumb(const std::string &flightnumb);

    const std::string &getPlane() const;
    void setPlane(const std::string &plane);

    const std::string &getDatometeo() const;
    void setDatometeo(const std::string &datometeo);

    const Fecha &getFecha() const;
    void setFecha(const Fecha &fecha);

    Aeropuerto *getAirOrigen() const;
    void setAirOrigen(Aeropuerto *airOrigen);

    Aeropuerto *getAirDestino() const;
    void setAirDestino(Aeropuerto *airDestino);

    Aerolinea *getAerolinea() const;
    void setAerolinea(Aerolinea *aerolinea);

};


#endif //PR1_VUELO_H
