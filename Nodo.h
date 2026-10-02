//
// Created by usuario on 06/10/2023.
//

#ifndef PR1_NODO_H
#define PR1_NODO_H

template<typename T>
class Nodo {
public:
    T _dato;
    Nodo *sig_ = 0;
    Nodo(const T &dato, Nodo<T>* sig = 0):_dato(dato),sig_(sig){

    }
};



#endif //PR1_NODO_H
