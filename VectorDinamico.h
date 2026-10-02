//
// Created by usuario on 18/09/2023.
//

#ifndef PR_1_VECTORDINAMICO_H
#define PR_1_VECTORDINAMICO_H

#include "iostream"
#include "cmath"
#include "algorithm"
#include "functional"
#include "stdexcept"

template<typename T>

class VectorDinamico {
private:
    T *vector;
    unsigned int tamf=1 ;      /// Tamanio fisico (espacio reservado)
    unsigned int taml=0;      /// Tamanio lógico (datos ocupados)
public:
    VectorDinamico();
    VectorDinamico(const VectorDinamico<T> &orig);
    VectorDinamico(const VectorDinamico<T> &orig, unsigned int posinicial, unsigned int posfinal);
    VectorDinamico(unsigned int _taml);
    virtual ~VectorDinamico() {
        delete []vector;
    }
    VectorDinamico<T> &operator= (VectorDinamico<T> v);
    T& operator[] (unsigned int pos);
    void insertar(const T &dato,unsigned int posicion= UINT_MAX);
    T& eliminar(unsigned int posicion = UINT_MAX);
    void ordena() const;
    void OrdenaRev();
    int busquedabinaria(T& elem) const;
    ///< Metodo Inline del getter del tam logico
    unsigned int getTaml() const {
        return taml;
    }
private:
    int aumemta(unsigned int _taml);
};

/**
 * @brief Constructor por defecto
 *
 * @tparam T
 */
template<typename T>
VectorDinamico<T>::VectorDinamico(): tamf(1),taml(0) {
    vector= new T[tamf];
}

/**
 * @brief Constructor copia
 *
 * @tparam T
 * @param orig vector Dinámico que copiaremos
 */
template<typename T>
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T> &orig): tamf(orig.tamf), taml(orig.taml) {
    vector=new T[tamf];
    for(int i=0;i<taml;i++){
        vector[i]=orig.vector[i];
    }
}

/**
 * @brief Constructor parametrizado
 *
 * @tparam T
 * @param _taml
 */
template<typename T>
VectorDinamico<T>::VectorDinamico(unsigned int _taml):taml(_taml) {
    tamf= aumemta(_taml);
    vector= new T[tamf];
}

/**
 * @brief Realiza la potencia de dos para aumentar el tam fisico del vector
 *
 * @tparam T
 * @param _taml
 * @return
 */
template<typename T>
int VectorDinamico<T>::aumemta(unsigned int _taml) {
    int valor=pow(2,ceil(log2(_taml)));
    return valor;
}
/**
 * @brief Constructor copia parcial
 *
 * @throw invalid_argument posinicial es superior a la final, no copia nada
 * @throw invalid_argument posfinal mayor tamlogico no se puede copiar valores que no están aun almacenados
 *
 * @tparam T
 * @param orig vector que copiamos
 * @param posinicial indica desde donde copiamos
 * @param posfinal indica hasta que posición copiamos
 */
template<typename T>
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T> &orig, unsigned int posinicial, unsigned int posfinal) {
    if(posinicial>posfinal){
        throw std::invalid_argument("VectorDinamico<T>::VectorDinamico: La posicion inicial no puede ser mayor a la final");
    }
    if (posfinal < orig.taml){
        throw std::invalid_argument("VectorDinamico<T>::VectorDinamico: La posicion final no puede ser mayor que el tamaño logico");
    }
    taml=posfinal-posinicial;
    tamf= aumemta(taml);
    vector = new T[tamf];
    for(int i=posinicial;i<posfinal;i++){
        int contador=0;
        vector[contador]=orig.vector[i];
        contador++;
    }
}


/**
 * @brief operador asignación
 *
 * @tparam T
 * @param v
 * @return vector que asignamos, hacemos que haga return para poder hacer llamadas recursivas
 */
template<typename T>
VectorDinamico<T> &VectorDinamico<T>::operator=(VectorDinamico<T> v) {
    if(v.tamf == this->tamf && v.taml == this->taml){
        bool soniguales=true;
        for(int i=0;i< taml || soniguales != false; i++){
            if(v.vector[i]!=vector[i]){
                soniguales = false;
            }
        }
        if(soniguales){
            return *this;
        }
    }
    this->tamf=v.tamf;
    this->taml=v.taml;
    T* n_vector= new T[tamf];
    delete []vector;

    for(int i=0;i<tamf;i++){
        n_vector[i]=v.vector[i];
    }
    vector=n_vector;
    return *this;

}

template<typename T>
/**
 * @brief operator [], para devolver una posición del vector
 *
 * @throw out_of_range si la posición que deseamos devolver es mayor al tamaño logico
 * @tparam T
 * @param pos
 * @return el objeto que se encuentra en esa posición de nuestro vector
 */
T& VectorDinamico<T>::operator[](unsigned int pos) {
    if(pos >= this->tamf){
        throw std::out_of_range("VectorDinamico<T>::operator[]: La posición es mayor al tamaño de su vector");
    }
    return vector[pos];
}


/**
 * @brief operación para insertar un dato
 *
 * @throw invalid_argument si la posicion donde deseamos insertar es mayor al tamlogico
 * @tparam T
 * @param dato
 * @param posicion
 */
template<typename T>
void VectorDinamico<T>::insertar(const T &dato,unsigned int posicion) {
    if(posicion==UINT_MAX){
        posicion=taml;
    }else if(posicion > taml ){
        throw std::out_of_range ("VectorDinamico<T>::insertar: No puedes insertar un dato en una posición que no existe ");
    }

    if(tamf==taml){
        tamf= aumemta(taml+1);
        T* n_vector= new T[tamf];
        for(int i=0;i<taml;i++){
            n_vector[i]=vector[i];
        }
        delete []vector;
        vector=n_vector;
    }

    if(posicion==taml){
        taml++;
    }else{
        for(int i=taml;i>posicion;i--){
            vector[i]=vector[i-1];
        }
        taml++;
    }
    vector[posicion]=dato;
}

/**
 * @brief función para eliminar algún dato
 *
 * @throw invalid_argument si el objeto que deseamos eliminar no está en el vector
 * @tparam T
 * @param posicion
 * @return elemento que deseamos eliminar
 */
template<typename T>
T& VectorDinamico<T>::eliminar(unsigned int posicion) {
    if(posicion==UINT_MAX){
        posicion=taml-1;
    }
    if(posicion >= taml){
        throw std::invalid_argument("VectorDinamico<T>::eliminar: No se puede eliminar un dato inexistente");
    }
    if(tamf>=3*taml){
        tamf=tamf/2;
        T* n_vector = new T[tamf];
        for(int i=0;i<taml;i++){
            n_vector[i]=vector[i];
        }
        delete []vector;
        vector=n_vector;
    }

    T elemento;
    elemento= vector [posicion];
    for(int i=posicion;i<taml;i++){
        vector[i]=vector[i+1];
    }
    taml--;
    return elemento;

}


/**
 * @brief funcion para ordenar de menor a mayor
 *
 * @tparam T
 */
template<typename T>
void VectorDinamico<T>::ordena() const {
    std::sort(vector,vector+taml );
}

/**
 * @brief función para ordenar de mayor a menor
 *
 * @tparam T
 */
template<typename T>
void VectorDinamico<T>::OrdenaRev() {
    std::sort(vector,vector+taml,std::greater<T>());
}

/**
 * @brief Busqueda binaria de un elemento, primero ordenamos el vector y posteriormente vamos dividiendo el vector en la mitad hasta encontrar el elemento
 * @tparam T
 * @param elem
 * @return posicion donde se encuentra o -1 si no esta
 */
template<typename T>
int VectorDinamico<T>::busquedabinaria(T& elem) const {
    if(taml==0){
        std::invalid_argument("VectorDinamico<T>::buscquedabinaria: El vector esta vacio ");
    }
    //this->ordena();
    int inferior=0;
    int superior=taml;
    T dato_actual;
    do{
        int intermedio= (inferior + superior ) / 2;
        if(vector[intermedio]==elem){
            return intermedio;
        }else if(vector[intermedio] > elem){
            superior=intermedio-1;
        }else{
            inferior=intermedio+1;
        }
    }while(inferior<=superior);

    return -1;
}
#endif //PR_1_VECTORDINAMICO_H
