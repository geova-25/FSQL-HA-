#ifndef INTERPRETESERVER_H
#define INTERPRETESERVER_H

#include "fsql_manager.h"
#include "stdio.h"
#include <cstring>

class InterpreteServer
{
public:
    InterpreteServer();
    void escuchar(string data_recibida );

private:

    FSQL_Manager  fsql_manager2;




    bool entro_create_table = false;
    int contador = 0;
    bool entro_nombre_tabla = false;
    string nombre_tabla;

    bool entro_insert_into=false;

    bool entro_update=false;

    bool entro_create_user=false;

    bool entro_drop_user=false;

    bool entro_grant=false;

};

#endif // INTERPRETESERVER_H
