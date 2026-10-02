cmake_minimum_required(VERSION 3.26)
project(PR1)

set(CMAKE_CXX_STANDARD 17)

add_executable(PR1 main.cpp
        VectorDinamico.cpp
        Aeropuerto.cpp
        Aeropuerto.h
        UTM.cpp
        UTM.h
        Nodo.cpp
        Nodo.h
        Iterador.cpp
        Iterador.h
        ListaEnlazada.cpp
        ListaEnlazada.h
        Ruta.h
        Ruta.cpp
        VuelaFlight.cpp
        VuelaFlight.h
        NodoAvl.cpp
        NodoAvl.h
        AVL.cpp
        AVL.h
        Aerolinea.cpp
        Aerolinea.h
        Aerolinea.cpp
        fecha.cpp
        Vuelo.cpp
        Vuelo.h
        ThashAeropuerto.cpp
        ThashAeropuerto.h
        MallaRegular.cpp
        MallaRegular.h
        Celda.cpp
        Celda.h
        Aeropuerto_contador.cpp
        Aeropuerto_contador.h)
