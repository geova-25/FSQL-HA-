#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include "vector3d.h"


class ListaDeServersCircular
{
public:
    ListaDeServersCircular();
    void agregarServer(const char* ip ,int puerto);
    const char* get_IP_server_actual();
    int get_puerto_server_actual();
    int get_id_server_actual();
    void getServerSiguiente();





private:
    Vector3d<const char*,int , int > lista_de_servers;
    int id_server = 0;
    Nodo3d<const char*,int,int>* Nodo_del_server_actual ;

    Nodo3d<const char*,int,int>* getPrimerNodo_server();
    Nodo3d<const char*,int,int>* getUltimoNodo_server();
};

#endif // LISTACIRCULAR_H
