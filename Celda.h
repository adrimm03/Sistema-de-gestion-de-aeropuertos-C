//
// Created by usuario on 12/12/2023.
//

#ifndef PR1_CELDA_H
#define PR1_CELDA_H

template<typename T>
class  MallaRegular;
#include "list"

template<typename T>
class Celda {
    friend class MallaRegular<T>;
private:
    std::list<T> celda;
public:
    Celda();
    Celda(const Celda &orig);
    Celda<T> operator =(const Celda<T> &orig);
    T *busca(const T &dato);
    virtual ~Celda();
    bool Borrar(T &dato);
    void inserta_dato(const T& dato);
    unsigned int numElementos() const;

    const std::list<T> &getCelda() const;
};

template<typename T>
Celda<T>::~Celda() {

}

template<typename T>
Celda<T>::Celda():celda() {

}

template<typename T>
Celda<T>::Celda(const Celda<T> &orig):celda(orig.celda) {

}

template<typename T>
Celda<T> Celda<T>::operator=(const Celda<T> &orig) {
    if(this!=orig){
        this->celda=orig.celda;
    }
    return *this;
}

template<typename T>
void Celda<T>::inserta_dato(const T &dato) {
    celda.push_back(dato);
}


template<typename T>
bool Celda<T>::Borrar(T &dato) {
    auto it= celda.begin();
    while(it!=celda.end()){
        if(*it=dato){
            celda.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

template<typename T>
T *Celda<T>::busca(const T &dato) {
    auto it= celda.begin();
    while(it!=celda.end()){
        if(*it==dato){
            return &(*it);
        }
        it++;
    }
    return nullptr;
}

template<typename T>
unsigned int Celda<T>::numElementos() const {
    return celda.size();
}

template<typename T>
const std::list<T> &Celda<T>::getCelda() const {
    return celda;
}
#endif //PR1_CELDA_H
