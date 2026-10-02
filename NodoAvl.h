//
// Created by usuario on 24/10/2023.
//

#ifndef PR1_NODOAVL_H
#define PR1_NODOAVL_H

template<typename T>
class NodoAvl {
public:
    T dato;
    NodoAvl<T> *izq, *der;
    char bal=0;
    /**
     * @brief Constructor parametrizado, aquellos que solo se cree un nodo con dato
     * @param elem
     */
    NodoAvl(T &elem): izq(0),der(0),dato(elem),bal(0){};
    /**
     * @brief Constructor parametrizado pasandole el dato y el balance
     * @param _elem
     * @param _bal
     */
    NodoAvl(T& _elem, char& _bal): izq(0),der(0),bal(_bal),dato(_elem){};
};


#endif //PR1_NODOAVL_H
