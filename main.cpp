#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VuelaFlight.h"
#include "MallaRegular.h"

/**
 * @author Adrian Murillo Moreno amm00419@red.ujaen.es
 * @author Sonia Marín Ferré smf00033@red.ujaen.es
 *
 * @date 25/09/2023
 * @file pr5.cpp
 *
 */


/**
 * @brief Función para almacenar los Aeropuertos en un mapa
 *
 * @param mapa_vuelos
 */
void Leer_Aeropuertos(MallaRegular<Aeropuerto> &mapa_vuelos){
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string id = "";
    std::string iata = "";
    std::string tipo = "";
    std::string nombre = "";
    std::string latitud_str = "";
    std::string longitud_str = "";
    std::string continente = "";
    std::string iso_pais = "";
    int fallos=0;
    bool activo=false;
    float latitud, longitud;

    is.open("../aeropuertos_v3.csv"); //carpeta de proyecto
    if (is.good()) {

        clock_t t_ini = clock();
        while (getline(is, fila)) {

            if (fila != "") {

                columnas.str(fila);


                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, iata, ';');
                getline(columnas, tipo, ';');
                getline(columnas, nombre, ';');
                getline(columnas, latitud_str, ';');
                getline(columnas, longitud_str, ';');
                getline(columnas, continente, ';');
                getline(columnas, iso_pais, ';');

                //  Transformamos la latitud y longitud a float
                if(activo) {
                    latitud = std::stof(latitud_str);
                    longitud = std::stof(longitud_str);
                    UTM pos(latitud, longitud);

                    Aeropuerto a1(id, iata, tipo, nombre, pos, continente, iso_pais);
                    mapa_vuelos.inserta(latitud,longitud,a1);

                }else{
                    activo=true;
                }
                fila = "";
                columnas.clear();
            }

        }
        is.close();

        std::cout << "Tiempo lectura con Mapa: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
}




int main() {
    try {
        ///COMPARAMOS LA TABLA HASH DE VUELAFLIGHT CON UN MAPA DE AERPUERTOS.
        VuelaFlight vuelos;
        UTM pos_Jaen(37.769220,-3.79028); UTM pos_Londres(51.473463,-0.303690);
        UTM pos_Madrid(40.438063,-3.688413);UTM pos_Venecia(45.500980,12.227178);
        Aeropuerto a_jaen("2581JN","JEN","","Jaen Airport", pos_Jaen,"EU","ES");
        Aeropuerto a_madrid(*vuelos.buscaAeropuerto("MAD"));
        Aeropuerto a_barcelona(*vuelos.buscaAeropuerto("BCN"));
        Aerolinea iberia(vuelos.busca_Aerolinea("IBE"));
        Ruta r_Jaen_Madrid(&iberia,&a_jaen,&a_madrid);
        Ruta r_Jaen_Barcelona(&iberia,&a_jaen,&a_barcelona);
        Ruta r_Barcelona_Jaen(&iberia,&a_barcelona,&a_jaen);
        Ruta r_Madrid_Jaen(&iberia,&a_madrid,&a_jaen);
        std::vector<Aeropuerto*> v_aeropuertos(vuelos.buscarAeropuertosRadio(pos_Jaen,300.0));
        std::vector<Aeropuerto*> vector(vuelos.aeropuertoMassalidas(pos_Madrid,800));
        std::vector<Aeropuerto*> v_Londres(vuelos.buscarAeropuertosRadio(pos_Londres,400));
        std::vector<Aeropuerto*> v_Venecia(vuelos.buscarAeropuertosRadio(pos_Venecia,400));
        Aeropuerto *cercano_jaen(vuelos.aeropuertomasCercano(pos_Jaen));
        int menu=0;
        do{
            std::cout << "----------------------MENU----------------------" << std::endl;
            std::cout << "1. Aeropuertos a 300km de Jaén. " << std::endl;
            std::cout << "2. Aeropuerto más cercano a Jaén. " << std::endl;
            std::cout << "3. 5 Aeropuertos con más vuelos en un radio de 800 km " << std::endl;
            std::cout << "4. ¿Qué ciudad ,Londres o Venecia, concentra más aeropuertos en un radio de 400Kms?" << std::endl;
            std::cout << "5. Ejercicio por parejas " << std::endl;
            std::cout << "6. SALIR "<< std::endl;
            std::cin >> menu;
            switch (menu) {
                case 1:
                    for (int i = 0; i < v_aeropuertos.size(); ++i) {
                        std::cout << i << ". Iata: " << v_aeropuertos[i]->getIata() << ", nombre: " << v_aeropuertos[i]->getNombre() <<
                        ", longitud: " << v_aeropuertos[i]->getX() << "- latitud: " << v_aeropuertos[i]->getY() << std::endl;
                    }
                break;
                case 2:
                    std::cout << "El aeropuerto mas cercano a Jaen es: Iata: " << cercano_jaen->getIata() <<
                    ", Nombre: " << cercano_jaen->getNombre() << ", pais: " << cercano_jaen->getIsoPais() << ", Continente: " <<
                    cercano_jaen->getContinente() << ", coordenadas X: " << cercano_jaen->getX() << ", Y:" << cercano_jaen->getY()<< std::endl;
                break;
                case 3:
                    for (int i = 0; i < vector.size(); ++i) {
                        std::cout << "Iata: " << vector[i]->getIata()  << "X: " << vector[i]->getX() <<
                        "- Y:" << vector[i]->getY() << ", Nombre: " << vector[i]->getNombre() << "Continente: " << vector[i]->getContinente()
                        << "Pais: " << vector[i]->getIsoPais()<< std::endl;
                    }
                break;
                case 4:
                    if(v_Venecia.size()>v_Londres.size()){
                        std::cout << "Hay mas aeropuertos  en un radio de 400 km cerca de Venecia " << std::endl;
                    } else if(v_Venecia.size()<v_Londres.size()){
                        std::cout << "Hay mas aeropuertos  en un radio de 400 km cerca de Londres " << std::endl;
                    }else{
                        std::cout << "Ambos Aeropuertos contienen el mismo numero de aeropuertos cercanos" << std::endl;
                    }
                break;
                case 5:
                vuelos.Anadir_Vector(a_jaen);
                vuelos.Anadir_Ruta(r_Jaen_Madrid);
                vuelos.Anadir_Ruta(r_Barcelona_Jaen);
                vuelos.Anadir_Ruta(r_Jaen_Barcelona);
                vuelos.Anadir_Ruta(r_Madrid_Jaen);
                UTM antequera(37.0193800, -4.5612300);
                std::vector<Aeropuerto*> v_300km_Antequera(vuelos.buscarAeropuertosRadio(antequera,300));
                    for (int i = 0; i < v_300km_Antequera.size(); ++i) {
                        std::cout << "Iata: " << v_300km_Antequera[i]->getIata() << ", id: " << v_300km_Antequera[i]->getId() <<
                        ", tipo: " << v_300km_Antequera[i]->getTipo() << ", Nombre: " << v_300km_Antequera[i]->getNombre() << " Posición: " <<
                        v_300km_Antequera[i]->ObtenerPosicion() << ", pais: " << v_300km_Antequera[i]->getIsoPais() << " , continente: " <<
                        v_300km_Antequera[i]->getContinente() << std::endl;
                    }
                break;
            }

        }while(menu!=6);
    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }


    return 0;
}

