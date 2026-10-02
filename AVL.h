//
// Created by usuario on 24/10/2023.
//

#ifndef PR1_AVL_H
#define PR1_AVL_H

#include "NodoAvl.h"
#include <string>
#include "iostream"
#include "VectorDinamico.h"

template<typename T>
class AVL {
    NodoAvl<T> *_raiz;
    unsigned int _cuentanodos=0;        /// Parametro utilizado para contar los objetos que hay en el árbol
private:
    void rotIzq(NodoAvl<T>* &origen);
    void rotDer(NodoAvl<T>* &origen);
    int inserta(NodoAvl<T>* &c, T &dato);
    void inorden(NodoAvl<T> *p, VectorDinamico<T*>& v_nodos);
    NodoAvl<T>* busReq(T &dato, NodoAvl<T> *pos);
    void copianodo(const NodoAvl<T> *n, NodoAvl<T>* &copia);
    void destruyenodo(NodoAvl<T>* &q);
    void calculoaltura(NodoAvl<T>* &nodo, int  alt, int& alt_max);
public:
    AVL();
    AVL(const AVL<T>& orig);
    virtual ~AVL();

    AVL&  operator =(const AVL<T> &orig);
    unsigned int numElementos();
    bool inserta( T& dato);
    T* buscaRec(T& dato);
    T* buscaIt(T& dato);
    unsigned int altura();
    VectorDinamico<T*> recorreInorden();
};

/**
 * @brief numero de elementos del AVL
 * @tparam T
 * @return _cuentanodos
 */
template<typename T>
unsigned int AVL<T>::numElementos() {
    return _cuentanodos;
}

/**
 * @brief Rota a izquierdas dado un nodo
 * @tparam T
 * @param origen nodo origen
 */
template<typename T>
void AVL<T>::rotIzq(NodoAvl<T>* &origen) {
    NodoAvl<T> *q= origen, *r;
    origen = r = q->der ;
    q->der = r->izq;
    r->izq = q;
    q->bal ++;
    if(r->bal < 0){
        q->bal+= -r->bal;
        r->bal++;
    }
    if(q->bal > 0){
        r->bal += q->bal;
    }
}

/**
 * @brief Rotación a derechas dado un nodo
 * @tparam T
 * @param origen nodo origen
 */
template<typename T>
void AVL<T>::rotDer(NodoAvl<T> *&origen) {
    NodoAvl<T> *q = origen, *r;
    origen = r = q->izq;
    q->izq = r->der;
    r->der = q;
    q->bal--;
    if(r->bal > 0){
        q->bal -= r->bal;
        r->bal--;
    }
    if(q->bal < 0){
        r->bal -= -q->bal;
    }
}

/**
 * @brief inserta en la lista AVL un elemento con un dato
 * @tparam T
 * @param c  nuevo nodo
 * @param dato dato que insertar
 * @return 1 si el dato ha sido insertado
 */
template<typename T>
int AVL<T>::inserta(NodoAvl<T> *&c, T &dato) {
    NodoAvl<T> *p = c;
    int deltaH = 0;
    if(!p){
        p = new NodoAvl<T>(dato);
        c = p;
        deltaH=1;
        _cuentanodos++;
    }else if( dato > p->dato){
        if(inserta(p->der,dato)){
            p->bal --;
            if(p->bal == -1){
                deltaH=1;
            }else if(p->bal == -2) {
                if (p->der->bal == 1) {
                    rotDer(p->der);
                }
                rotIzq(c);
             }
        }
    } else if (dato<p->dato){
        if (inserta(p->izq,dato)){
            p->bal++;
            if( p->bal==1){
                deltaH=1;
            }else if(p->bal==2){
                if(p->izq->bal == -1){
                    rotIzq(p->izq);
                }
                rotDer(c);
            }
        }
    }
    return deltaH;
}
/**
 * @brief Recorre los elementos del mas pequeño al mas grande
 * @tparam T
 * @param p
 * @param nivel
 * @param v_nodos
 */
template<typename T>
void AVL<T>::inorden(NodoAvl<T> *p, VectorDinamico<T*> &v_nodos) {
    if(p){
        inorden(p->izq,v_nodos);
        v_nodos.insertar(&p->dato);
        inorden(p->der,v_nodos);
    }
}
/**
 * @brief inserta un dato
 * @tparam T
 * @param dato
 * @return
 */
template<typename T>
bool AVL<T>::inserta(T &dato) {
    return inserta(_raiz,dato);
}
/**
 * @brief Constructor por defecto
 * @tparam T
 */
template<typename T>
AVL<T>::AVL() {
    _raiz = 0;
}
/**
 * @brief Constructor copia
 * @tparam T
 * @param orig
 * @throw invalid_argument si el arbol esta vacio
 */
template<typename T>
AVL<T>::AVL(const AVL<T> &orig) {
    if(orig._raiz == 0){
        throw std::invalid_argument("AVL<T>::AVL(): El árbol que se desea copiar esta vacio ");
    }
    copianodo(orig._raiz, this->_raiz);
    this->_cuentanodos = orig._cuentanodos;

}

/**
 * @brief operador igual ( = )
 * @tparam T
 * @param orig
 * @throw invalid_argument si el arbol esta vacio
 * @return el nuevo arbol
 */
template<typename T>
AVL<T> &AVL<T>::operator=(const AVL<T> &orig) {
    if(orig._raiz == 0){
        throw std::invalid_argument("AVL<T>::AVL(): El árbol que se desea copiar esta vacio ");
    }
    if(*this!=orig){
        destruyenodo(this->_raiz);
        copianodo(orig._raiz, this->_raiz) ;
        this->_cuentanodos = orig._cuentanodos ;
    }
    return *this;
}
/**
 * @brief copia el nodo seleccionado
 * @tparam T
 * @param n
 * @param copia
 */
template<typename T>
void AVL<T>::copianodo(const NodoAvl<T> *n, NodoAvl<T>* &copia) {
    if(n){
        copia = new NodoAvl<T>(n->dato,n->bal);
        copianodo(n->izq,copia->izq);
        copianodo(n->der,copia->der);
    }
}

/**
 * @brief destruye el nodo seleccionado
 * @code destruimos los nodos en postorden
 * @tparam T
 * @param q
 */
template<typename T>
void AVL<T>::destruyenodo(NodoAvl<T> *&q) {
    if(q){
        destruyenodo(q->izq);
        destruyenodo(q->der);
        delete q;
        q = nullptr;
    }
}

/**
 * @brief busca un dato
 * @tparam T
 * @param dato
 * @param pos
 * @return un puntero al nodo que contiene el dato que buscamos
 */
template<typename T>
NodoAvl<T> *AVL<T>::busReq(T &dato, NodoAvl<T> *pos) {
    if(!pos){
        return 0;
    }else if(dato > pos->dato){
        return busReq(dato,pos->der);
    }else if(dato < pos->dato){
        return busReq(dato,pos->izq);
    }else{
        return pos;
    }
}

/**
 * @brief busca a partir de un dato
 * @tparam T
 * @code llama a la funcion busReq
 * @param dato
 * @return el dato encontrado
 */
template<typename T>
T* AVL<T>::buscaRec(T &dato) {
    NodoAvl<T> *n = busReq(dato, this->_raiz);
    if(n==0){
        throw std::invalid_argument("AVL<T>::buscaRec: El dato no se encuentra en el arbol");
    }
    return &n->dato;

}

/**
 * 
 * @tparam T
 * @return
 */
template<typename T>
VectorDinamico<T *> AVL<T>::recorreInorden() {
    VectorDinamico<T*> vector;
    inorden(this->_raiz,vector);
    return vector;
}

/**
 * @brief busqueda iterativa
 * @code se realiza la busqueda sin llamadas recursivas
 * @tparam T
 * @param dato
 * @return
 */
template<typename T>
T *AVL<T>::buscaIt(T &dato) {
    NodoAvl<T> *a= this->_raiz;

    while (a != 0) {
        if (dato == a->dato) {
            return a->dato;
        } else if (dato < a->dato) {
                a = a->izq;
        }else if (dato > a->dato) {
                a = a->der;
        } else{
            return nullptr;
        }

    }

}

/**
 * @brief Calcula la altura de un árbol
 * @code llama a la función calculaaltura
 * @tparam T
 * @return la altura del árbol
 */

template<typename T>
unsigned int AVL<T>::altura() {
    int altura=0;
    calculoaltura(this->_raiz,0,altura);
    return altura;
}

/**
 * @brief función privada Calcula Altura
 * @code es una función recursiva que calcula la altura máxima del árbol
 * @tparam T
 * @param nodo
 * @param alt
 * @param alt_max
 */
template<typename T>
void AVL<T>::calculoaltura(NodoAvl<T> *&nodo, int alt, int& alt_max) {
    if(nodo){
        calculoaltura(nodo->izq,alt+1,alt_max);
        calculoaltura(nodo->der,alt+1,alt_max);
        if(alt>alt_max){
            alt_max=alt;
        }
    }
}

/**
 * @brief Destructor correspondiente
 * @code llama a la función destruye nodo
 * @tparam T
 */
template<typename T>
AVL<T>::~AVL() {
    destruyenodo(this->_raiz);
    this->_cuentanodos = 0;
}

#endif //PR1_AVL_H
