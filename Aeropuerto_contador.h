//
// Created by usuario on 14/12/2023.
//

#ifndef PR1_AEROPUERTO_CONTADOR_H
#define PR1_AEROPUERTO_CONTADOR_H

#include "Aeropuerto.h"
/**
 * @brief Esta clase es utilizada para ordenar en el  pririty_queue.
 */
class Aeropuerto_contador {
private:
    Aeropuerto *a= nullptr;     /// Aeropuerto
    int repeticiones=0;         /// Contador del número de vuelos que tiene este Aeropuerto
public:
    Aeropuerto_contador() = default;
    Aeropuerto_contador(Aeropuerto *a, int nrep);
    Aeropuerto_contador(const Aeropuerto_contador& orig);
    virtual ~Aeropuerto_contador();
    /**
     * @brief Operadores , comparan el contador
     * @param rhs
     * @return
     */
    bool operator <(const Aeropuerto_contador &rhs) const;
    bool operator >(const Aeropuerto_contador &rhs) const;
    bool operator==(const Aeropuerto_contador &rhs) const;
    bool operator<=(const Aeropuerto_contador &rhs) const;
    bool operator>=(const Aeropuerto_contador &rhs) const;
    Aeropuerto *getA() const;
};


#endif //PR1_AEROPUERTO_CONTADOR_H
