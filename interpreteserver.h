#ifndef INTERPRETESERVER_H
#define INTERPRETESERVER_H

#include "fsql_manager.h"
#include "stdio.h"
#include <cstring>

class InterpreteServer
{
public:
    InterpreteServer(FSQL_Manager*);
    void escuchar(string data_recibida );

private:
    FSQL_Manager* fsql_manager;

    bool entro_create_table = false;
    int contador = 0;
    bool entro_nombre_tabla = false;
    string nombre_tabla;

};

#endif // INTERPRETESERVER_H
