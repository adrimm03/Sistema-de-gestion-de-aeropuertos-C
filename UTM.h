//
// Created by usuario on 25/09/2023.
//

#ifndef PR1_UTM_H
#define PR1_UTM_H


class UTM {
private:
    float _latitud=0.0;
    float _longitud=0.0;
public:
    UTM() = default;
    UTM(const float latitud, const float longitud);
    UTM(const UTM &orig);
    virtual ~UTM();

    float getLatitud() const;
    void setLatitud(float latitud);

    float getLongitud() const;
    void setLongitud(float longitud);
};


#endif //PR1_UTM_H
