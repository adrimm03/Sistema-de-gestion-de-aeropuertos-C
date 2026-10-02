//
// Created by usuario on 25/09/2023.
//

#include "UTM.h"

/**
 * @brief Constructor parametrizado
 *
 * @post Genera un objeto de tipo UTM ya inicializado segun los datos que le pasemos
 * @param latitud
 * @param longitud
 */
UTM::UTM(const float latitud,const float longitud): _latitud(latitud),_longitud(longitud) {

}

/**
 * @brief Constructor copia
 *
 * @param orig objeto UTM que copiaremos
 */
UTM::UTM(const UTM &orig):_latitud(orig._latitud),
                    _longitud(orig._longitud) {

}

/**
 * @brief Destructor
 *
 */
UTM::~UTM() {

}

/**
 * @brief Getter Latitud
 *
 * @return latitud de nuestro objeto
 */
float UTM::getLatitud() const {
    return _latitud;
}

/**
 * @brief Setter Latitud
 *
 * @param latitud
 */
void UTM::setLatitud(float latitud) {
    _latitud = latitud;
}

/**
 * @brief Getter Longitud
 *
 * @return longitud del objeto UTM
 */
float UTM::getLongitud() const {
    return _longitud;
}

/**
 * @brief Setter Longitud
 *
 * @param longitud
 */
void UTM::setLongitud(float longitud) {
    _longitud = longitud;
}
