//
// Created by usuario on 21/11/2023.
//

#include "ThashAeropuerto.h"

/**
 * @brief Función de dispersión
 * @param clave valor númerico
 * @param intento
 * @return posición que encontramos
 */
unsigned int ThashAeropuerto::funcion_dispersion(unsigned long clave, int intento) {
    int pos ;
    unsigned long valor=(clave*clave);
    unsigned long n_valor= valor;
    int modulo=1;
    while(n_valor>0){
        modulo=modulo+(n_valor%10);
        n_valor=n_valor/10;
    }
    modulo=modulo*valor*clave;
    pos = ( (valor%tam) + intento*(19763 - (modulo% 19763)) ) % tam;
    return pos;
}

/**
 * @brief Dice si un número es primo o no
 * @return true si es primo o false si no
 */
bool ThashAeropuerto::esprimo(unsigned int _tam) {
    for (int i = 2; i < _tam ; ++i) {
        if (_tam%i==0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief crea una tabla hash con un número maximo de elementos y un factor de carga
 * @param maxElementos
 * @param lambda , por defecto es 0.70
 */
ThashAeropuerto::ThashAeropuerto(int maxElementos, float _lambda) {
    tam = maxElementos*100 / (_lambda*100);
    lambda=_lambda;
    while(!esprimo(tam)){
        tam++;
    }
    for (int i = 0; i < tam; ++i) {
        tabla.push_back(nullptr);
    }
}

/**
 * @brief Constructor copia
 * @param orig
 */
ThashAeropuerto::ThashAeropuerto(ThashAeropuerto &orig): tam(orig.tam), tabla(orig.tabla), numElementos(orig.numElementos),
                                  MAXCOLISIONES(orig.MAXCOLISIONES), num_redispersiones(orig.num_redispersiones) {

}

/**
 * @brief Operador =
 * @param orig
 * @return TablaHash
 */
ThashAeropuerto ThashAeropuerto::operator=(ThashAeropuerto &orig){
    if(numElementos!=0){
        for (int i = 0; i < tam; ++i) {
            if(tabla[i] != nullptr){
                 delete tabla[i];
                 tabla[i]= nullptr;
            }
        }
    }
    tam=orig.tam;
    numElementos=orig.numElementos;
    MAXCOLISIONES=orig.MAXCOLISIONES;
    num_redispersiones=orig.num_redispersiones;
    tabla=orig.tabla;
    return *this;
}

/**
 * @brief Destructor
 */
ThashAeropuerto::~ThashAeropuerto() {

    for (int i = 0; i < tam; ++i) {
        if(tabla[i]!= nullptr){
            delete tabla[i];
            tabla[i]= nullptr;
        }
    }
}

/**
 * @brief Inserta un dato
 * @code Tiene treinta intentos para insertar un dato
 * @param clave
 * @param dato
 * @param codigo
 * @return true si el dato ha sido insertado
 */
bool ThashAeropuerto::inserta(unsigned long clave, Aeropuerto &dato,std::string codigo) {
    for (int i = 0; i < 30; ++i) {
        int pos_inserta = funcion_dispersion(clave, i);
        if (tabla[pos_inserta] != nullptr) {
            if(tabla[pos_inserta]->getIata()==codigo){
                MAXCOLISIONES=MAXCOLISIONES-i;
                if(i>10){
                    max10=max10-(i-10);
                }
                return false;
            }
            if(tabla[pos_inserta]->getIata()=="VACIO"){
                Aeropuerto *n_aeropuerto = new Aeropuerto(dato);
                tabla[pos_inserta] = n_aeropuerto;
                numElementos++;
                float factor_carga= this->factor_carga() /100;
                if(factor_carga > lambda){
                    int n_tam=tam+(tam*0.3);
                    while (!esprimo(n_tam)){
                        n_tam++;
                    }
                    this->redispersar(n_tam);
                }
                return true;
            }
            if(i==0) {
                MAXCOLISIONES++;
            }
            if(i>10){
                max10++;
            }
        } else {
            Aeropuerto *n_aeropuerto = new Aeropuerto(dato);
            tabla[pos_inserta] = n_aeropuerto;
            numElementos++;
            float factor_carga= this->factor_carga() /100;
            if(factor_carga > lambda){
                int n_tam=tam+(tam*0.3);
                while (!esprimo(n_tam)){
                    n_tam++;
                }
                this->redispersar(n_tam);
            }
            return true;
        }
    }
    return false;
}

/**
 * @brief Busca un dato en la tabla hash con una clave
 * @param clave
 * @param cicao
 * @return puntero al Aeropuerto buscado
 */
Aeropuerto *ThashAeropuerto::buscar(unsigned long clave, std::string cicao) {
    for (int i = 0; i < 30; ++i) {
        int pos_dato = funcion_dispersion(clave, i);
        if (tabla[pos_dato] != nullptr) {
            if(tabla[pos_dato]->getIata()==cicao){
                return tabla[pos_dato];
            }
        } else {
            return nullptr;
        }
    }
    return nullptr;
}

/**
 * @brief Borra el dato que deseamos
 * @param clave
 * @param frase
 * @code Marcamos la casilla borrada creando un nuevo Aeropuerto vacio que dice eliminado
 * @return true si el dato esta la tabla y se puede borrar
 */
bool ThashAeropuerto::Borrar(unsigned long clave, std::string frase) {
    for (int i = 0; i < 30; ++i) {
        int pos = funcion_dispersion(clave, i);
        if (tabla[pos] != nullptr) {
            if (tabla[pos]->getIata() == frase) {
                delete tabla[pos];
                tabla[pos] = nullptr;
                numElementos--;
                Aeropuerto *a=new Aeropuerto("VACIO");          ///Generamos un nuevo Aeropuerto con codigo ICAO que pone vacio esto indicará que antes habia un aeropuerto pero que ya ha sido borrado para las busqueda
                tabla[pos] = a;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Getter NumElementos
 * @return NumElementos
 */
unsigned int ThashAeropuerto::getnumelementos() {
    return numElementos;
}

/**
 * @brief Getter Tamanio
 * @return tam
 */
unsigned int ThashAeropuerto::tamTabla() {
    return tam;
}

/**
 * @brief Calculo factor de carga
 * @return numelementos*100/tam
 */
float ThashAeropuerto::factor_carga() {
    return (numElementos*100/tam);
}

/**
 * @brief Getter MaxColisiones
 * @return MAXCOLISIONES
 */
unsigned int ThashAeropuerto::numMAXCOLISIONES() {
    return MAXCOLISIONES;
}

/**
 * @brief Getter Colisiones en mas de 10
 * @return max10
 */
unsigned int ThashAeropuerto::nummax10() {
    return max10;
}

/**
 * @brief Calcula la media de colisiones
 * @return MAXCOLISIONES/NUMELEMENTOS
 */
float ThashAeropuerto::promedio_colisiones() {
    float m=MAXCOLISIONES+0.0 , n=numElementos+0.0;
    return m/n ;
}

/**
 * @brief Operador[] que devuelve el dato de una posición en concreto del dato
 * @param pos
 * @throw out_of_range posición menor a 0 o mayor al tamaño
 * @return
 */
Aeropuerto* ThashAeropuerto::operator[](unsigned int pos) {
    if(pos>tam || pos<0){
        throw std::out_of_range("ThashAeropuerto::operator[]: La posición no se encuentra en el vector");
    }
    return tabla[pos];
}

/**
 * @brief Función de redispersión de la tabla con un nuevo tamanio
 * @param _tam
 */
void ThashAeropuerto::redispersar(unsigned int _tam) {
    max10=0;
    MAXCOLISIONES=0;
    numElementos=0;
    std::vector<Aeropuerto*> copia;
    for (int i = 0; i < tam; ++i) {
        copia.push_back(nullptr);
        if(tabla[i]!= nullptr){
            Aeropuerto* a= new Aeropuerto(*tabla[i]);
            copia[i]=a;
            delete tabla[i];
            tabla[i]= nullptr;
        }
    }
    int total_datos(tam);
    tam=_tam;
    for (int i = 0; i < _tam; ++i) {
      tabla.push_back(nullptr);
    }

    for (int i = 0; i < total_datos; ++i) {
        if(copia[i]!= nullptr){
            if(copia[i]->getIata()!="VACIO"){
                //// CALCULO CLAVE
                unsigned long hash = 5381;
                int c;

                for (int j = 0; j < copia[i]->getIata().size(); ++j) {
                    c = copia[i]->getIata()[j];
                    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
                    hash = hash * 33 + c;
                }
                this->inserta(hash,*copia[i],copia[i]->getIata());
            }
        }
    }

    for (int i = 0; i < copia.size(); ++i) {
        if(copia[i]!= nullptr){
            delete copia[i];
            copia[i]= nullptr;
        }
    }
    num_redispersiones++;
}

/**
 * @brief Getter Num Redispersiones
 * @return
 */
unsigned int ThashAeropuerto::getNumRedispersiones() const {
    return num_redispersiones;
}