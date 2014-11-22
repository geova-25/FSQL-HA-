#ifndef REGISTER_H
#define REGISTER_H

#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "filemanager.h"

using namespace std;


class Register
{
public:
    Register(FileManager* file_manager , const char * Directory );

    /**
     * @brief initRegister Almacena el nombre de la tabla a la que se quiere añadir el nuevo registro.
     *  Reserva el espacio en el heap de memoria con un puntero void* del tamaño especificado en el
     *  metadata del header. Guarda un puntero nulo en disco al registro anterior, pues no se ha añadido
     *  al archivo en este punto.
     * @param file_name
     */
    void initRegister(const char * file_name );
    bool fill_Register(VectorRelacional<const char* ,  const char *>* campos);

    /**
     * @brief isDirty Devuelve un bool que significa que el registro debe guardarse en disco en el futuro.
     * @return
     */
    bool isDirty();
    /**
     * @brief setDirty Enciende una bandera luego de crearse un registro, y la apaga
     * después de haberse almacenado en el disco. Esta bandera funciona para no escribir
     * todos los mismos registros varias veces, pues estos van a existir en memoria y en
     * determinado momento se van a escribir los registros con la bandera encendida.
     */
    void setDirty(bool);
    void setID(int);
    int getID();
    /**
     * @brief getPtr_al_anterior Obtiene el puntero de disco cuando el registro esté cargado en memoria.
     */
    int getPtr_al_anterior();

    /**
     * @brief setPtr_al_anterior Cuando el registro este en memoria le asigna un puntero en
     * disco a otro registro al formar una tabla.
     * @return
     */

    void setPtr_al_anterior(int);
    int getSizeOfRegister();
    /**
     * @brief getBuffer Devuelve el puntero buffer reservado el en heap donde están los datos del registro.
     * @return
     */
    void* getBuffer();

private :

    void saveString(const char* string , const char* nombre_columna,int desplazamiento);
    void saveInt(int Int , const char* nombre_columna,int desplazamiento);
    void saveFloat(float Float , const char* nombre_columna,int desplazamiento);

    int regID;

    const char* directory;

    const char* fileName;

    int size_of_register;

    bool dirty = false;

    void* Buffer = NULL;

    int* ptr_al_anterior = NULL;
    int* ptr_al_siguiente = NULL;

    FileManager* fileManager;

    const int NULL_POINTER = -1;







};

#endif // REGISTER_H
