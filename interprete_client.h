#ifndef INTERPRETE_COMANDOS_H
#define INTERPRETE_COMANDOS_H

#include "fsql_manager.h"
#include "vector3d.h"
#include "clientsocket.h"
#include "interpreteserver.h"

class Interprete_Cliente
{
public:

    Interprete_Cliente();
    void run();




private:


    InterpreteServer* interprete_server = new InterpreteServer();
    //  FSQL_Manager* fsql_manager;
        ClientSocket* client_socket;

        void crear_Create_Table(string text);
        void crear_Insert_Into(string text);
        void crear_Select_Asterisco(string text);
        void crear_Select_From(string text);
        void crear_Update(string text);
        void crear_Delete(string text);
        void crear_Index(string text);
        void crear_usuario(string text);
        void crear_drop(string text);
        void crear_grant(string text);
        void crear_revoke(string text);
        void conection(string text);
        void enviar(const char* token);


        // usuarios
        bool bol_usuarios=false;
        bool password=false;

        //drop
        bool bol_drop=false;

        //grant and revoke
        bool bol_grant=false;
        bool bol_revoke=false;
        bool bol_on=false;
        bool bol_to=false;

        //conction
        int serverPort = 40011;
        std::string ipDelServer = "192.168.0.104";
        std::string ipmia="172.26.104.25";

        //192.168.0.110     sebas
        //192.168.0.104     giova
        //192.168.0.101     mia

        bool flag=false;

        bool banderaCliente = true;

        //CREATE TABLE
        //banderas para capturar las variables que entra en create table
        bool bol_create_table=false;
        bool bool_Caracteristica=false;
        bool bool_tipo = false;
        bool bool_Caracteres= false;
        bool iniciar = false;
        bool bol_raid=false;

        string lista[48];    // lista principal
        int i=0;            // variable utilizada para agragar a cualquier lista en especial en lista principal
        string nombre; // nombre de la tabla
        string raid;   // captura el raid a utilizar

        //SELECT ASTERISCO
        bool bol_Select_ALL=false;  // bandera utilizada para salect asterisco



        //INSERT INTO
        //banderas para capturar las variables que entra en insert into
        bool bol_inser_into=false;
        bool bol_columna=false; // se usa en delete from
        bool bol_dato=false;


        //DELETE FROM
        //banderas para capturar las variables que entra en delete from
        bool bol_delete_from=false;
        bool bol_Condicion = false;
        bool bol_Valor=false;

        int valor=0;                 // numero que le tiene que entrar al delete para que se realice con exito el delete
        string lista_sentencias[20]; // tambien es utilizada en select_from, en esta guarda AND y OR
        int lista_valor[20];         // lista para guardar los valores


        //SELECT FROM
        //banderas para capturar las variables que entra en select from
        bool bol_Select_from=false;
        bool bol_nombre=false;



        //UPDATE
        //banderas para capturar las variables que entra en update
        bool bol_update=false;
        bool bol_pos = false;
        bool bol_cambio=false;

        int j=0;                  // variable utilizada para agregar a la lista de cambios que se van a realizar
        string lista_cambios[48]; // lista de cambios que se van a realizar en el archivo

        //VARIABLES GENERALES
        //banderas para capturar variables generales del programa
        bool terminar=false;
        bool exit= false;



};

#endif // INTERPRETE_COMANDOS_H
