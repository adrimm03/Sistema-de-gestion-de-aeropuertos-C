//
// Created by usuario on 12/12/2023.
//

#ifndef PR1_MALLAREGULAR_H
#define PR1_MALLAREGULAR_H

#include "vector"
#include "Celda.h"
#include "stdexcept"
#include "cmath"
#include "iostream"

template<typename T>
class MallaRegular {
private:
    float _axMax, _ayMax, _axmin, _aymin, _tamCasillasX, _tamCasillasY;
    int _nDiv, _totalelementos=0;
    std::vector<std::vector<Celda<T>>> _malla;
    Celda<T> *calcular_casilla(float x, float y);
    std::vector<int> calcular_pos(float x, float y);
public:
    MallaRegular();
    MallaRegular(MallaRegular<T> &orig);
    MallaRegular(float axMax, float ayMax, float axmin, float aymin,int nDiv);
    MallaRegular<T> operator =(MallaRegular<T> &orig);
    virtual ~MallaRegular();

    void inserta(float x, float y, T& dato);
    T* busca(float x,float y,T&dato);
    void borra( float  x, float y, T&dato);

    unsigned int maxElementosporCelda();
    float promedioElementosxCelda();
    std::vector<T> buscarRadio(float xcentro, float ycentro, float radio);
    float calcular_distancia(float lat1, float los1, float lat2, float long2 );
    const std::vector<std::vector<Celda<T>>> &getMalla() const ;

    int getTotalelementos() const {
        return _totalelementos;
    }

    int getNDiv() const {
        return _nDiv;
    }
    T masCercano(float xcentro, float ycentro);
};

/**
 * @brief Constructor por defecto de una malla
 * @tparam T
 * @post Nos crea una malla con los min=0 y los max=1 y una única división
 */
template<typename T>
MallaRegular<T>::MallaRegular():_axMax(1), _ayMax(1),
                                _axmin(0), _aymin(0), _nDiv(1) {
    _tamCasillasX=_axMax-_axmin/_nDiv;
    _tamCasillasY=_ayMax-_aymin/_nDiv;

    _malla.resize(_nDiv);
    for (int i = 0; i < _nDiv; ++i) {
        _malla[i].resize(_nDiv);
    }
}

/**
 * @brief Constructor copia
 * @tparam T
 * @param orig malla que deseamos copiar
 */
template<typename T>
MallaRegular<T>::MallaRegular(MallaRegular<T> &orig):_axMax(orig._axMax), _ayMax(orig._ayMax),
                                            _axmin(orig._axmin), _aymin(orig._aymin), _nDiv(orig._nDiv), _tamCasillasY(orig._tamCasillasY),
                                            _tamCasillasX(orig._tamCasillasX) {

    _malla.resize(_nDiv);
    for (int i = 0; i < _nDiv; ++i) {
        _malla[i].resize(_nDiv);
    }

    for (int i = 0; i < _tamCasillasX; ++i) {
        for (int j = 0; j < _tamCasillasY; ++j) {
            _malla[i][j].celda=orig._malla[i][j].celda;
        }
    }
}

/**
 * @brief Constructor parametrizado
 *
 * @tparam T
 * @param axMax
 * @param ayMax
 * @param axmin
 * @param aymin
 * @param nDiv
 */
template<typename T>
MallaRegular<T>::MallaRegular(float axMax, float ayMax, float axmin, float aymin, int nDiv):_axMax(axMax), _ayMax(ayMax),
                                                                _axmin(axmin), _aymin(aymin), _nDiv(nDiv){
    _tamCasillasX=_axMax-_axmin/_nDiv;
    _tamCasillasY=_ayMax-_aymin/_nDiv;

    _malla.resize(_nDiv);
    for (int i = 0; i < _nDiv; ++i) {
        _malla[i].resize(_nDiv);
    }

}

/**
 * @brief Destrcutor
 * @tparam T
 */
template<typename T>
MallaRegular<T>::~MallaRegular() {

}

/**
 * @brief Operador asignación
 *
 * @tparam T
 * @param orig
 * @return
 */
template<typename T>
MallaRegular<T> MallaRegular<T>::operator=(MallaRegular<T> &orig) {
    if(this!=orig){
        this->_axMax=orig._axMax;
        _ayMax=orig._ayMax;
        _axmin=orig._axmin;
        _aymin=orig._aymin;
        _nDiv=orig._nDiv;
        _tamCasillasX=orig._numCasillasX;
        _tamCasillasY=orig._numCasillasy;
        _malla=orig._malla;
    }
    return *this;
}

/**
 * @brief Calcula la casilla de un valor
 * @code dado una posición devuelve la casilla en la que se encuentra.
 * @tparam T
 * @param x
 * @param y
 * @return Celda
 */
template<typename T>
Celda<T> *MallaRegular<T>::calcular_casilla(float x, float y) {
    int i= (x-_axmin)/ _tamCasillasX;
    int j= (y-_aymin)/ _tamCasillasY;
    return &_malla[i][j];
}

/**
 * @brief Calcula las coordenadas i j de las posiciones en la matriz
 * @tparam T
 * @param x
 * @param y
 * @return
 */
template<typename T>
std::vector<int> MallaRegular<T>::calcular_pos(float x, float y) {
    int i= (x-_axmin)/ _tamCasillasX;
    int j= (y-_aymin)/ _tamCasillasY;
    std::vector<int> sol;
    sol.push_back(i); sol.push_back(j);
    return sol;
}

/**
 * @brief Inserta un dao en la matriz
 * @tparam T
 * @param x
 * @param y
 * @param dato
 * @code usa el calcular casilla para averiguar en que casilla insertar
 */
template<typename T>
void MallaRegular<T>::inserta(float x, float y, T &dato) {
    this->calcular_casilla(x,y)->inserta_dato(dato);
    _totalelementos++;
}

/**
 * @brief Busca un dato en la matriz
 * @tparam T
 * @param x
 * @param y
 * @param dato
 * @code usa el calcular casilla para averiguar en que casilla se encuentra
 * @returno nullptr si el dato no es encontrado.
 */
template<typename T>
T *MallaRegular<T>::busca(float x, float y, T &dato) {
    return this->calcular_casilla(x,y)->busca(dato);
}

/**
 * @brief Borra un dato , buscandolo primero
 * @tparam T
 * @param x
 * @param y
 * @param dato
 */
template<typename T>
void MallaRegular<T>::borra(float x, float y, T &dato) {
    this->calcular_casilla(x,y)->Borrar(dato);
    _totalelementos--;
}

/**
 * @brief Calcula la celda con mayor número de elementos
 * @tparam T
 * @return
 */
template<typename T>
unsigned int MallaRegular<T>::maxElementosporCelda() {
    unsigned maxElementoCelda = 0;
    for (int i = 0; i < _nDiv; i++) {
        for (int j = 0; j < _nDiv; j++) {
            if (_malla[i][j].numElementos() > maxElementoCelda) {
                maxElementoCelda = _malla[i][j].numElementos();
            }
        }
    }
    return maxElementoCelda;
}
/**
 * @brief Promedio de elementos por celda
 * @tparam T
 * @return
 */
template<typename T>
float MallaRegular<T>::promedioElementosxCelda() {
    float t=_totalelementos+0.0, div=_nDiv+0.0;
    return t/div;

}
/**
 * @brief Buscar los elementos en un radio comprendido
 * @tparam T
 * @param xcentro
 * @param ycentro
 * @param radio
 * @return
 */
template<typename T>
std::vector<T> MallaRegular<T>::buscarRadio(float xcentro, float ycentro, float radio) {
    radio=radio/111.1;
    std::vector<T> vector_sol;
    int v1,v2,v3,v4;
    v1=ycentro+radio;v2=xcentro+radio;
    v3=xcentro-radio;v4=ycentro-radio;
    int v1i= calcular_pos(v3,v1)[0], v1j=calcular_pos(v2,v1)[1];
    int v2i= calcular_pos(v2,v4)[0], v2j= calcular_pos(v2,v4)[1];

    for (int i = v1i; i <= v2i ; ++i) {
        for (int j = v1j; j <= v2j; ++j) {
            Celda<T> casilla = _malla[i][j];
            auto iterator = casilla.celda.begin();
            while (iterator != casilla.celda.end()) {
                float d=calcular_distancia(xcentro,ycentro,iterator.operator*()->getX(),iterator.operator*()->getY());
                if (d <= radio*111.1) {
                    vector_sol.push_back(iterator.operator*());
                }
                iterator++;
            }
        }
    }
    return vector_sol;
}

/**
 * @brief Obtenemos la malla
 * @tparam T
 * @return
 */
template<typename T>
const std::vector<std::vector<Celda<T>>> &MallaRegular<T>::getMalla() const {
        return _malla;
}

/**
 * @brief Calcula la distencia entre dos puntos.
 * @tparam T
 * @param lat1
 * @param long1
 * @param lat2
 * @param long2
 * @return
 */
template<typename T>
float MallaRegular<T>::calcular_distancia(float lat1, float long1, float lat2, float long2) {
    const float R = 6378.0; // Radio medio de la Tierra en kilómetros
    const float PI = 3.14159265358979323846;   // Número PI

    float incrLat = (lat2 - lat1) * (PI / 180);
    float incrLon = (long2 - long1) * (PI / 180);
    float a = sin(incrLat / 2) * sin(incrLat / 2) +
               cos(lat1 * (PI / 180)) * cos(lat2 * (PI / 180)) *
               sin(incrLon / 2) * sin(incrLon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float d = R * c;
    return d;
}

/**
 * @brief Calcula el elemento más cercano a un punto
 * @tparam T
 * @param xcentro
 * @param ycentro
 * @return
 */
template<typename T>
T MallaRegular<T>::masCercano(float xcentro, float ycentro) {
    int i= calcular_pos(xcentro,ycentro)[0], j=calcular_pos(xcentro,ycentro)[1];
    float distancia=10000.00;
    T cercano;
    if(i>0){
        i--;
    }else if(j>0){
        j--;
    }
    for (int k = i; k < i+3; ++k) {
        for (int l = j; l < j+3; ++l) {
            Celda<T> casilla = _malla[k][l];
            auto iterator = casilla.celda.begin();
            while (iterator!=casilla.celda.end()){
                float d=calcular_distancia(xcentro,ycentro,iterator.operator*()->getX(),iterator.operator*()->getY());
                if(d<distancia){
                    distancia=d;
                    cercano=iterator.operator*();
                }
                iterator++;
            }
        }

    }
    return cercano;
}
#endif //PR1_MALLAREGULAR_H
