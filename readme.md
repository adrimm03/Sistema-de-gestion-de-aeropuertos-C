# Sistema de Gestión de Aeropuertos, Aerolíneas y Vuelos

Aplicación desarrollada en **C++** para gestionar información relacionada con aeropuertos, aerolíneas, vuelos y rutas.

El proyecto fue desarrollado como parte de la formación en **Ingeniería Informática**, aplicando programación orientada a objetos, estructuras de datos, algoritmos y gestión de memoria dinámica.

## 🛠️ Tecnologías

- C++
- Programación Orientada a Objetos (POO)
- CMake
- Ficheros CSV
- Estructuras de datos
- Gestión de memoria dinámica

## 📋 Funcionalidades

El sistema permite trabajar con información de:

- Aeropuertos
- Aerolíneas
- Vuelos
- Rutas
- Información geográfica de los aeropuertos

Entre las operaciones desarrolladas se incluyen:

- Inserción y gestión de información.
- Búsqueda de elementos.
- Eliminación de elementos.
- Recorrido de estructuras de datos.
- Procesamiento de información procedente de ficheros CSV.
- Búsqueda de aeropuertos por proximidad geográfica.

## 🧩 Estructuras de datos

Durante el desarrollo se utilizaron diferentes estructuras de datos dinámicas, entre ellas:

- Vectores dinámicos.
- Listas enlazadas.
- Árboles AVL.
- Tablas hash.
- Grafos.
- Mallas regulares.

El proyecto también incluye trabajo con **punteros, nodos y memoria dinámica**.

## 🏗️ Organización del proyecto

El código está organizado mediante clases y módulos separados en archivos `.h` y `.cpp`, facilitando la organización y mantenimiento del proyecto.

Entre las principales clases y componentes se encuentran:

- `Aeropuerto`
- `Aerolinea`
- `Vuelo`
- `Ruta`
- `AVL`
- `MallaRegular`
- `ThashAeropuerto`
- `VectorDinamico`
- `ListaEnlazada`
- `Nodo`
- `NodoAvl`

## ⚙️ Compilación

El proyecto utiliza **CMake** para su configuración y compilación.

```bash
mkdir build
cd build
cmake ..
cmake --build .
