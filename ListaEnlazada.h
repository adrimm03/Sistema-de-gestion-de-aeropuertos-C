//
// Created by usuario on 06/10/2023.
//

#ifndef PR1_LISTAENLAZADA_H
#define PR1_LISTAENLAZADA_H
#include "Iterador.h"
#include "Nodo.h"
#include "stdexcept"


template<typename T>
class ListaEnlazada {
private:
    Nodo<T> *_cabecera = nullptr;               ///< Puntero apuntando al primer elemento
    Nodo<T> *_cola = nullptr;                   ///< Puntero apuntando al ultimo elemento
    unsigned int _tam=0;
public:
    ListaEnlazada()=default;
    ListaEnlazada(const ListaEnlazada<T> &orig);
    ListaEnlazada& operator=(const ListaEnlazada<T> &orig);
    virtual ~ListaEnlazada() ;

    T& inicio() const;
    T& fin() const;
    Iterador<T> iterador() const;
    void Inserta_inicio(T& dato);
    void Inserta_final(T& dato);
    void Inserta(Iterador<T> &i,T &dato);
    void Inserta_Detras(Iterador<T> &i, T& dato);
    void borraInicio();
    void borraFinal();
    void borra(Iterador<T> &i);
    unsigned int tam() const;
    void concatena(const ListaEnlazada<T> &l);
    ListaEnlazada<T> operator+(ListaEnlazada<T> &lista);
};


/**
 * @brief Constructor copia
 *
 * @throw invalid_argument Si la lista pasada no contiene nada
 * @tparam T
 * @param orig
 */
template<typename T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &orig): _tam(orig.tam()) {
    if(orig._cabecera==0){
        throw std::invalid_argument ("ListaEnlazada<T>::ListaEnlazada: Fallo Concstructor copia, la lista que queremos copiar está vacía ");
    }
    Nodo<T> *aux;
    aux=orig._cabecera;

    _cabecera = new Nodo<T>(orig._cabecera->_dato,0);
    _cola=_cabecera;

    while (aux->sig_!=0){
        aux = aux->sig_;
        Nodo<T> *nuevo = new Nodo<T>(aux->_dato,0);
        _cola->sig_=nuevo;
        _cola=nuevo;
    }
}


/**
 * @brief Operador =
 *
 * @tparam T
 * @param orig
 * @return
 */
template<typename T>
ListaEnlazada<T> &ListaEnlazada<T>::operator=(const ListaEnlazada<T> &orig) {
    if (orig._cabecera == this->_cabecera && this->_cola == orig._cola){
        return *this;
    }

    Nodo<T> *eliminar;
    /// 1º Limpiamos nuestra lista
    while (_cabecera!=0){
        eliminar=_cabecera;
        _cabecera=_cabecera->sig_;
        delete eliminar;
    }
    _tam=orig._tam;

    Nodo<T> *aux;
    aux = orig._cabecera;
    _cabecera=new Nodo<T>(aux->_dato,0);
    _cola=_cabecera;
    while (aux->sig_!=0){
        aux=aux->sig_;
        Nodo<T> *n_nodo=new Nodo<T>(aux->_dato,0);
        _cola->sig_ = n_nodo;
        _cola=n_nodo;
    }
    return *this;
}


/**
 * @brief Destuctor
 *
 * @tparam T
 */
template<typename T>
ListaEnlazada<T>::~ListaEnlazada() {
    while (_cabecera!=_cola){
        this->borraInicio();
    }
}

/**
 *
 * @throw out_of_range si la lista esta vacia
 * @tparam T
 * @return Devuelve el dato del primer nodo
 */
template<typename T>
T &ListaEnlazada<T>::inicio() const {
    if(_cabecera==0){
        throw std::out_of_range("ListaEnlazada<T>::inicio(): La lista esta vacia ") ;
    }
    return _cabecera->_dato;
}

/**
 *
 * @throw out_of_range si la lista esta vacia
 * @tparam T
 * @return Devuelve el dato del ultimo nodo
 */
template<typename T>
T &ListaEnlazada<T>::fin() const{
    if(_cola==0){
        throw std::out_of_range("ListaEnlazada<T>::fin(): La lista esta vacia ") ;
    }
    return _cola->_dato;
}

/**
 * @brief Iterador apuntando al primer elemento
 *
 * @tparam T
 * @return
 */
template<typename T>
Iterador<T> ListaEnlazada<T>::iterador() const {
    return Iterador<T>(_cabecera);
}

/**
 * @brief Inserta un nodo por el principio
 * @code Se genera el nuevo nodo ynla cabecera apunta a él
 *
 * @tparam T
 * @param dato
 */
template<typename T>
void ListaEnlazada<T>::Inserta_inicio(T &dato) {
    Nodo<T> *n=new Nodo<T>(dato,0);
    if(_cabecera == 0){
        _cola=n;
    }else{
        n->sig_=_cabecera;
    }
    _cabecera = n;
    _tam++;
}

/**
 * @brief Inserta por el final
 *
 * @tparam T
 * @param dato
 */
template<typename T>
void ListaEnlazada<T>::Inserta_final(T &dato) {
    Nodo<T> *n = new Nodo<T>(dato,0);

    if (_cola == 0) {
        _cabecera = n;
    }else {
        _cola->sig_ = n;
    }
    _cola=n;
    _tam++;
}

/**
 * @brief Inserta en medio justo antes de la posición que se dice
 *
 * @tparam T
 * @param i
 * @param dato
 */
template<typename T>
void ListaEnlazada<T>::Inserta(Iterador<T> &i, T &dato) {
    if(_cabecera==0){
        throw std::invalid_argument("ListaEnlazada<T>::Inserta: No hay nada en la lista ") ;
    }

    Nodo<T> *ant=_cabecera;
    while(ant->sig_ != i.nodo){
        ant=ant->sig_;
    }
    Nodo<T> *nuevo = new Nodo<T>(dato,ant->sig_);
    ant->sig_ = nuevo;
    /// Como apuntar nuevo al siguiente

    if(_cabecera==i.nodo){
        _cabecera= nuevo;
    }
    _tam++;
}


/**
 * @brief Inserta en medio justo detras del nodo apuntado
 *
 * @tparam T
 * @param i
 * @param dato
 */
template<typename T>
void ListaEnlazada<T>::Inserta_Detras(Iterador<T> &i, T &dato) {
    Nodo<T> *n_nodo=new Nodo<T>(dato,i.nodo->sig_);
    i.nodo->sig_ = n_nodo;
    if(_cola==i.nodo){
        _cola=n_nodo;
    }
    _tam++;
}

/**
 * @brief Borra el primer nodo de la lista
 *
 * @tparam T
 */
template<typename T>
void ListaEnlazada<T>::borraInicio() {
    if(_cabecera==0){
        throw std::invalid_argument("ListaEnlazada<T>::borraInicio: La lista esta vacia no se puede eliminar nada ") ;
    }
    if(_cabecera==_cola){
        delete _cabecera;
        _cabecera= nullptr;
        _cola= nullptr;
    }else {
        Nodo<T> *aux(_cabecera);
        _cabecera = _cabecera->sig_;
        delete aux;
    }
    _tam--;
}

/**
 * @brief Borra el ultimo nodo de la lista
 *
 * @tparam T
 */
template<typename T>
void ListaEnlazada<T>::borraFinal() {
    if(_cola==0){
        throw std::invalid_argument("ListaEnlazada<T>::borraFinal: La lista esta vacia no se puede eliminar nada ") ;
    }
    if(_cabecera==_cola){
        delete _cola;
        _cabecera= nullptr;
        _cola= nullptr;
    }else {
        Nodo<T> *borra(_cabecera);
        while (borra->sig_ != _cola) {
            borra = borra->sig_;
        }
        borra->sig_ = 0;
        delete _cola;
        _cola = borra;
    }
    _tam--;
}

/**
 * @brief Borra un nodo pasando un iterador como posicion
 * @tparam T
 * @param i
 */
template<typename T>
void ListaEnlazada<T>::borra(Iterador<T> &i) {
    if(_cola==0){
        throw std::invalid_argument("ListaEnlazada<T>::borra: La lista esta vacia no se puede eliminar nada ") ;
    }
    if(_cabecera==_cola){
        delete _cola;
        _cabecera= nullptr;
        _cola= nullptr;
    }else {
        Nodo<T> *elimina(_cabecera);
        while (elimina->sig_ != i.nodo){
            elimina=elimina->sig_;
        }
        if(_cola==i.nodo){
            _cola=elimina;
        }
        elimina->sig_ = i.nodo->sig_;
        delete i.nodo;
    }
    _tam--;
}

/**
 * @brief Calcula el tamaño del vector
 *
 * @tparam T
 * @return
 */
template<typename T>
unsigned int ListaEnlazada<T>::tam() const{
    return _tam;
}

/**
 * @brief Une a nuestra lista la nueva lista
 * @tparam T
 * @param l
 */
template<typename T>
void ListaEnlazada<T>::concatena(const ListaEnlazada<T> &l) {
    if( this->_cabecera==0 ){
        throw std::invalid_argument("ListaEnlazada<T>::concatena: La lista primera esta vacia ");
    }
    Iterador<T> it=l.iterador();
    while(!it.esfin()){
        this->Inserta_final(it.dato());
        it.siguiente();
    }
}

/**
 *
 * @code Generamos una nueva Lista con el constructor copia, y llamamos a la funcion concatena para que a esta le una la lista a añadir
 *
 * @tparam T
 * @param lista lista que le añadimos
 * @param this lista inicial
 * @return nueva lista creada con la suma de las anteriores
 */
template<typename T>
ListaEnlazada<T> ListaEnlazada<T>::operator+(ListaEnlazada<T> &lista) {
    ListaEnlazada<T> listaEnlazada(*this);
    listaEnlazada.concatena(lista);
    return listaEnlazada;
}
#endif //PR1_LISTAENLAZADA_H
