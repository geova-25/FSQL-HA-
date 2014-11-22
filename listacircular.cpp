#include "listacircular.h"

ListaDeServersCircular::ListaDeServersCircular()
{
    //cuando se incicializa se enlaza el primer nodo con el ultimo
   // lista.get_ultimoNodo()->set_siguiente(lista.get_primerNodo());
}

void ListaDeServersCircular :: agregarServer(const char* ip , int puerto){
    lista_de_servers.agregarAlFinal(ip,puerto,id_server);
    //se aumenta el id
    id_server++;
    //Si acaba de agregar elprimer server se asigna el server acutual al primer nodo
    //una unica vez
    if(id_server == 1){
        Nodo_del_server_actual = lista_de_servers.get_primerNodo();
    }

}

Nodo3d<const char*,int,int>* ListaDeServersCircular :: getPrimerNodo_server(){
    return lista_de_servers.get_primerNodo();
}
Nodo3d<const char*,int,int>* ListaDeServersCircular :: getUltimoNodo_server(){
    return lista_de_servers.get_ultimoNodo();
}

const char* ListaDeServersCircular :: get_IP_server_actual(){
    return Nodo_del_server_actual->get_elemento1();
}
int ListaDeServersCircular :: get_puerto_server_actual(){
    return Nodo_del_server_actual->get_elemento2();
}
int ListaDeServersCircular :: get_id_server_actual(){
    return Nodo_del_server_actual->get_elemento3();
}
void ListaDeServersCircular :: getServerSiguiente(){
     Nodo_del_server_actual = Nodo_del_server_actual->get_siguiente();
     if(Nodo_del_server_actual == lista_de_servers.get_ultimoNodo()){
         Nodo_del_server_actual = lista_de_servers.get_primerNodo();
     }
}

