//
// Created by usuario on 21/11/2023.
//

#ifndef PR1_THASHAEROPUERTO_H
#define PR1_THASHAEROPUERTO_H

#include "vector"
#include "Aeropuerto.h"
class ThashAeropuerto {
private:
    int tam = 0;
    int numElementos=0;
    std::vector<Aeropuerto*> tabla;
    unsigned int MAXCOLISIONES=0;
    unsigned int max10=0;
    unsigned int num_redispersiones=0;
    float lambda=0.7;
    unsigned int funcion_dispersion(unsigned long clave, int intento );
public:
    ThashAeropuerto( int maxElementos, float lambda = 0.7);
    ThashAeropuerto( ThashAeropuerto &orig);
    ThashAeropuerto operator = (ThashAeropuerto &orig);
    virtual ~ThashAeropuerto();

    bool inserta(unsigned long clave, Aeropuerto &dato, std::string cadena);
    Aeropuerto* buscar(unsigned long clave, std::string frase);
    bool Borrar (unsigned long clave, std::string frase);
    Aeropuerto* operator[](unsigned int pos);
    ///FUNCIONES PRUEBA 1
    unsigned int getnumelementos();
    unsigned int tamTabla();
    float factor_carga();
    unsigned int numMAXCOLISIONES();
    unsigned int nummax10();
    float promedio_colisiones();
    bool esprimo(unsigned int tam);
    void redispersar(unsigned int tam);
    unsigned int getNumRedispersiones() const;

};


#endif //PR1_THASHAEROPUERTO_H
