//
// Created by usuario on 06/10/2023.
//

#ifndef PR1_ITERADOR_H
#define PR1_ITERADOR_H
#include "Nodo.h"

template<typename T>
class Iterador {
private:
    Nodo<T> *nodo;
    template<typename U>friend class ListaEnlazada;

public:
    /**
     * @brief Crea un iterador a partir de un nodo
     *
     * @param n_nodo
     */
    Iterador(Nodo<T> *n_nodo):nodo(n_nodo){

    }
    /**
     * @brief Comprueba si es el ultimo nodo de la lista
     *
     * @return
     */
    bool esfin(){
        if (nodo==0){
            return true;
        }
        return false;
    }
    /**
     * @brief Pasa al iguiente nodo de la lista
     *
     */
    void siguiente(){
        nodo = nodo->sig_;
    }
    /**
     * @brief Devuelve el dato del nodo que se dice
     *
     * @return
     */
    T &dato(){
        return nodo->_dato;
    }
};


#endif //PR1_ITERADOR_H
