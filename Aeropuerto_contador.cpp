//
// Created by usuario on 14/12/2023.
//

#include "Aeropuerto_contador.h"

Aeropuerto_contador::Aeropuerto_contador(Aeropuerto *a, int nrep): a(a),repeticiones(nrep) {

}

Aeropuerto_contador::Aeropuerto_contador(const Aeropuerto_contador &orig):a(orig.a), repeticiones(orig.repeticiones) {

}

Aeropuerto_contador::~Aeropuerto_contador() {

}

bool Aeropuerto_contador::operator<(const Aeropuerto_contador &rhs) const {
    return repeticiones<rhs.repeticiones;
}

bool Aeropuerto_contador::operator>(const Aeropuerto_contador &rhs) const {
    return repeticiones>rhs.repeticiones;
}

bool Aeropuerto_contador::operator==(const Aeropuerto_contador &rhs) const {
    return repeticiones==rhs.repeticiones;
}


bool Aeropuerto_contador::operator<=(const Aeropuerto_contador &rhs) const {
    return *this<rhs && *this==rhs;
}

bool Aeropuerto_contador::operator>=(const Aeropuerto_contador &rhs) const {
    return *this>rhs && *this==rhs;
}

Aeropuerto *Aeropuerto_contador::getA() const {
    return a;
}
