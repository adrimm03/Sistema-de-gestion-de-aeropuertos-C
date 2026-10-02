//
// Created by usuario on 11/10/2023.
//

#ifndef PR1_VUELAFLIGHT_H
#define PR1_VUELAFLIGHT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Ruta.h"
#include "ThashAeropuerto.h"
#include "Aerolinea.h"
#include "Aeropuerto_contador.h"
#include "map"
#include "unordered_map"
#include "set"
#include "MallaRegular.h"
#include "queue"


class VuelaFlight {
private:
    std::unordered_map<std::string ,Aeropuerto> v_aeropuertos;
    std::list<Ruta> l_rutas;
    std::map<std::string, Aerolinea> work;
    std::multimap<std::string ,Ruta> routeorig;
    std::multimap<std::string ,Ruta*> routedest;
    MallaRegular<Aeropuerto*> airportsUTM;
    void Leer_Aeropuertos();
    void Leer_Aerolineas();
    void Leer_Rutas();
    void rellenaMalla();
public:
    VuelaFlight();
    virtual ~VuelaFlight();
    std::list<Ruta> &getLRutas();
    const std::unordered_map<std::string ,Aeropuerto> &ObtenerVector();
    std::map<std::string ,Aerolinea>& getAvlAerolinea();
    /// Funciones Necesarias a implementar
    void Anadir_Vector(Aeropuerto &a);
    void Anadir_Ruta(Ruta &r1);
    void Anadir_Aerolinea(Aerolinea &aer);

    /// Funciones Practica 2
    Ruta &buscarrutasOrigDest(const std::string &id_orig, const std::string &id_dest);
    std::list<Ruta> BuscarRutasOrigen(const std::string  &id_orig);
    void addRuta(const std::string &aerolinea, const std::string &id_orig, const std::string  &id_dest);
    std::vector<Aeropuerto*> buscar_Aeropuerto_Pais(const std::string &pais);
    /// Funciones Practica 3
    std::vector<Aerolinea*> buscar_Aerolinea_Activa();
    Aerolinea& busca_Aerolinea(const std::string &icao);
    std::vector<Aerolinea*> buscar_Aerolineas_Pais(const std::string &pais);
    ///Funciones Practica 4
    bool registrarVuelo( const std::string fnumber, const std::string iataAeroOrig, const std::string iataAerodest, const std::string plane,
                         const std::string datosmeteo, Fecha &f);
    void Cargar_Vuelos(std::string fichVuelos);
    std::vector<Vuelo> BuscaVuelos( std::string fnumber);
    std::vector<Vuelo> vuelosOperadospor(std::string icaoAerolinea, Fecha f);
    std::set<std::string> buscaVuelosDestAerop(const std::string paisOrig, const std::string iataAeroDest);
    std::map<std::string ,Aeropuerto> buscaAeropuertosAerolinea(std::string icaoAerolinea);                     /// Funcion en Parejas
    ///Funciones Practica 5
    Aeropuerto* buscaAeropuerto(std::string iata);
    unsigned int getNumAeropuertos();
    void eliminar_aeropuerto(std::string _Iata);
    void eliminar_aeropuertos_inactivos();
    ///Funciones Práctica 6
    std::vector<Aeropuerto*> buscarAeropuertosRadio(UTM& pos,float radio);
    std::vector<Aeropuerto*> aeropuertoMassalidas(UTM& pos,float radio);
    Aeropuerto* aeropuertomasCercano(UTM &pos);
};


#endif //PR1_VUELAFLIGHT_H
