#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "vector3d.h"
#include "vectorrelacional.h"

using namespace std;


class FileManager
{
private:

    void * header_buffer = NULL;
    char * fileBuffer =NULL;


    char* nameOfFile = NULL;
    int* sizeOfFile = NULL;
    int* numberOfRegisters = NULL;
    int* numberOfFreeRegisters = NULL;
    int* ptrOfFirstRegister = NULL;
    int* ptrToLastRegister = NULL;
    int* ptrToFirstRegisterFree = NULL;
    int* sizeOfRegister = NULL;
    int* numberOfColumns = NULL;


    const char* directory;

    Vector3d<const char *, int, int > schema;

public:
    const int INT_ID = 999;
    const int FLOAT_ID = 888;
    const int STRING_ID = 777;
    const int BYTES_4 = 4;
    const int TABLESIZE = 30;
    const int INICIO_DE_REGISTRO_EN_BYTES =  12 ;
    const int OFFSET_PTRSIG = 4 ;
    const int OFFSET_NUM_RAID=8;

    const int sizeOfHeader = 62;
    const int nullPosition = -1;

    FileManager();
    /**
     * @brief initHeader Inicializa el header del manejador de archivos,
     * con un tamaño de archivo y header ambos igual a 62. Con punteros a
     * disco inicializados en nulo y contadores inicializados en cero.
     */
    void initHeader();

    /**
     * @brief loadHeader Carga el Header a memoria del archivo especificado
     * en el parámetro name_of_file . Utiliza la biblioteca fstream, lee la
     * información de los bytes almacenados la extrae como puntero char* y
     * se guardan en memoria en los punteros que contienen la metadata del
     *  archivo.
     * @param name_of_file
     */
    void loadHeader(const char * name_of_file);
    /**
     * @brief saveHeader Salva el header el disco en caso de que se termine de modificar o se quiera hacer persistente.
     * Crea un archivo binario con el nombre de la tabla en donde usa la biblioteca fstream.
     */
    void saveHeader();
    /**
     * @brief printHeader Imprime los valores de la metadata que contiene el header, para una revisión visual.
     */
    void printHeader();

    void openFile();
    /**
     * @brief addNewRegister Añade un registro al archivo que tenga el Header cargado en el FileManager.
     * Lo escribirá al final del archivo.
     */
    void addNewRegister(void*);
    int* where(Vector3d<const char*,const char*,const char*>* , VectorRelacional<const char*,int>*);
    bool cumpleCondicion(const char* ,const char* operador, const char*,void* temp_register);
    void printFile();
    void closeFile();
    void saveFile();
    void setCampo(const char* columna , const char* campo,int num_row);
    void printValorDeCampo(const char* columna ,int num_row);
    void delete_row(int);

    /**
     * @brief initSchema Vacía el schema que está en memoria.
     * Básicamente vacía una lista enlazada que es como un arreglo relacional.
     */
    void initSchema();
    /**
     * @brief loadSchema Carga el schema del Archivo que tenga el header en memoria. Que por dentro
     * llena una estructura enlazada de un arreglo relacional. Lee los datos del arreglo relacional
     *  en el mismo orden en que se guardaron y va llenando la estructura en forma secuencial.
     */
    void loadSchema();
    /**
     * @brief saveSchema Salva el schema en disco  del Archivo que tenga el header en memoria. Este se
     *  guarda como un archivo de texto plano con el mismo nombre del archivo pero con extensión txt.
     * Escribe los datos del arreglo relacional en el mismo orden en que se guardaron en memoria.
     */
    void saveSchema();
    void generate_binaryFile();
    Vector3d<const char *, int, int > getSchema();
    void addStringToSchema(const char*, int);
    void addIntToSchema(const char*,int);
    void addFloatToSchema(const char*,int);


    char* getNameOfFile();
    int getSizeOfFile();
    int getNumberOfRegisters();
    int getNumberOfFreeRegisters();
    int getPtrOfFirstRegister();
    int getPtrToLastRegister();
    int getPtrToFirstRegisterFree();
    int getSizeOfRegister();
    int getNumberOfColumns();

    void setNameOfFile(const char*);
    void setSizeOfFile( int);
    void setNumberOfRegisters(int);
    void setNumberOfFreeRegisters(int);
    void setPtrOfFirstRegister(int);
    void setPtrToLastRegister(int);
    void setPtrToFirstRegisterFree(int);
    void setSizeOfRegister(int);
    void setNumberOfColumns(int);

    bool compare_strings(const char* str1 , const char* str2);

    void set_directory(const char* dir);


};

#endif // FILEMANAGER_H
