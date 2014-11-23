#include "interprete_client.h"
#include <stdio.h>
#include <string.h>
#include <cstring>

#include "serversocket.h"
#include "SocketException.h"
#include "clientsocket.h"
#include "SocketException.h"
#include <string>

Interprete_Cliente :: Interprete_Cliente()
{


}


/**
 * @brief Interprete_Comandos::run metodo
 * Este metodo se encarga de recibir todo lo que se encuentre en la consola para ser procesado a asi generar
 * los comando que sean necasarios para el manejo de archivos
 */
void Interprete_Cliente::run(){
    cout<<"********************************************************************************"<<endl;
    cout<<"*********************************  FSQL-HA  ************************************"<<endl;
    cout<<"************************** Controlador de archivos *****************************"<<endl;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<"Inicio ¬ ¬"<<endl;


    for (int j=0; j<48; j++){
        lista[j]="0";             //Inicia lasta principal con ceros string
    }

    //deletefrom
    for (int j=0; j<20; j++){
        lista_sentencias[j]="0";  //Inicia la lista de sentencia la cual es de AND y OR con ceros string
    }
    for (int j=0; j<20; j++){
        lista_valor[j]=999;       //Inicia la lista de valores con el valor por defecto de 999 este indica que es nulo el valor
    }

    //update
    for (int j=0; j<48; j++){
        lista_cambios[j]="0";     //Inicia la lista de cambios en el update con ceros string
    }


    while(!exit){


        string text;  // todo el comando en consola
        cin >>text;   // captura el comando




        conection(text);
        //metodos que realizan lan funciones del manejador de archivos

        crear_Create_Table(text);
        crear_Delete(text);
        crear_Insert_Into(text);
        crear_Select_Asterisco(text);
        crear_Select_From(text);
        crear_Update(text);

        crear_usuario(text);
        crear_drop(text);
        crear_grant(text);
        crear_revoke(text);

        if (strcmp(text.c_str(),"exit")==0){  // Este if se encarga de salir del programa si encuentra un exit como sentencia
            exit = true;                      // Bandera para salir del while y salir del programa
        }
    } // Final del while
}  //Final de run


void Interprete_Cliente::crear_usuario(string text){

     //general para el text
    std::string result = std::string(text);
    const char* token = result.c_str();

    if(bol_usuarios && iniciar){
        enviar(token);
        iniciar=false;

    }
    if(strcmp(text.c_str(),"create_user")==0){
        enviar(token);
        bol_usuarios=true;
        iniciar=true;
    }

    if(password && bol_usuarios){
        enviar(token);
        password=false;
        bol_usuarios=false;
    }
    if(strcmp(text.c_str(),"with_password")==0){
        password=true;
    }
}


void Interprete_Cliente::crear_drop(string text){
    std::string result = std::string(text);
    const char* token = result.c_str();

    if(bol_drop){
        enviar(token);
        bol_drop=false;
    }
    if(strcmp(text.c_str(),"drop_user")==0){
        bol_drop=true;
        enviar(token);
    }
}


void Interprete_Cliente::crear_grant(string text){
    std::string result = std::string(text);
    const char* token = result.c_str();

    if (bol_grant && iniciar){
        enviar(token);
        iniciar=false;
    }
    if(strcmp(text.c_str(),"grant")==0){
        enviar(token);
        bol_grant=true;
        iniciar=true;
    }


    if(bol_on && bol_grant){
        enviar(token);
        bol_on=false;
    }
    if(strcmp(text.c_str(),"on")==0 && bol_grant){
        bol_on=true;
    }


    if(bol_to && bol_grant){
        enviar(token);
        bol_to=false;
        bol_grant=false;
    }
    if(strcmp(text.c_str(),"to")==0 && bol_grant){
        bol_to=true;
    }
}

void Interprete_Cliente::crear_revoke(string text){
    std::string result = std::string(text);
    const char* token = result.c_str();

    if (bol_revoke && iniciar){
        enviar(token);
        iniciar=false;
    }
    if(strcmp(text.c_str(),"revoke")==0){
        enviar(token);
        bol_revoke=true;
        iniciar=true;

    }


    if(bol_on && bol_revoke){
        enviar(token);
        bol_on=false;
    }
    if(strcmp(text.c_str(),"on")==0 && bol_revoke){
        bol_on=true;
    }


    if(bol_to && bol_revoke){
        enviar(token);
        bol_to=false;
        bol_revoke=false;
    }
    if(strcmp(text.c_str(),"to")==0 && bol_revoke){
        bol_to=true;
    }
}

/**
 * @brief Interprete_Comandos::crear_Create_Table
 * @param text
 * Este metodo se encarga basicamente de resibir toda la sentencia pero si en el primer token
 * recibe un create table entonces empieza a funcionar y crea la tabla
 */
void Interprete_Cliente::crear_Create_Table(string text){

    Vector3d<const char*, const char*,const char*>  args;

           //create table
           string caracteristica;// tomar la primer varable de columnas
           string tipo;   // tipo de varable (string, int)
           string caracteres;  // cantidad de caracteres que le va a entrar a la caracteristica

           //general para el text
           std::string result = std::string(text);
           const char* token = result.c_str();

           if(iniciar && bol_create_table){
               enviar(token);
               nombre=token;  // captura el nombre de la tabla
               iniciar=false;
           }
           if(strcmp(text.c_str(),"create_table")==0){
               iniciar =true;  // inicia el comando para la captura
               enviar(token);
               bol_create_table=true;
           }

           if(bool_Caracteristica && bol_create_table){
               //enviar(token);
               caracteristica=token;                      //recibe la caracteristica en este caso es la columna
               enviar(caracteristica.c_str());
               lista[i]=caracteristica;                   // lo agrega a la lista principal
               i++;
               bool_Caracteristica=false;
           }
           if(strcmp(text.c_str(),"(")==0 || strcmp(text.c_str(),",")==0 && bol_create_table){
               bool_Caracteristica=true;                 // bandera para recir la caracteristica
           }

           if(bool_tipo && bol_create_table){
               tipo=token;                              //recibe el tipo de dato que es
               enviar(token);
               lista[i]=tipo;                           //lo agrega a la lista princpal
               i++;
               bool_tipo=false;
           }
           if(strcmp(text.c_str(),":")==0 && bol_create_table){
               bool_tipo=true;                          //bandera para recibir el tipo
           }

           if(bool_Caracteres && bol_create_table){
               caracteres=token;                        //recibe la cantida de caracteres para escribirlos en la tabla
               enviar(token);
               lista[i]=caracteres;                     // los agrega a la lista principal
               i++;
               bool_Caracteres=false;
           }
           if(strcmp(text.c_str(),"-")==0 && bol_create_table){
               bool_Caracteres=true;                    //bandera para recibir los caracteres
           }

           if (bol_raid && bol_create_table){
               raid = token;  // captura del raid
               for(int i=0; i<48;i=i+3){
                   if(lista[i]!="0"){
                       string variable_1= lista[i];     // saca la columna
                       string variable_2= lista [i+1];  // saca el tipo de la columna
                       string variable_3= lista[i+2];   // saca los caracteres que va a tener

                       args.agregarAlFinal(variable_1.c_str(), variable_2.c_str(),variable_3.c_str());  //Agraga a un vector para luego mandar
                                                                                                        // a crear el archivo

                   }
               }
              // fsql_manager->createTable(nombre.c_str(),&args);   // manda los datos necesarios para crear la tabla

               // vuelve a reestablecer a la manera original todos los valores utilizados en create table
               for (int j=0; j<48; j++){
                   lista[j]="0";
               }
               i=0;
               nombre="";
               raid = "";
               bol_raid= false;
               bol_create_table=false;
               cout<<"\n"<<endl;
           }
           if(strcmp(text.c_str(),"using_raid")==0 && bol_create_table){
               bol_raid=true;     //bandera para captura el raid
           }
} // Fin de create table


/**
 * @brief Interprete_Comandos::crear_Delete
 * @param text
 * Este metodo se encarga basicamente de resibir toda la sentencia pero si en el primer token
 * recibe un delete_from entonces manda todos los datos necesarios para eliminar ese registro
 * del archivo
 */
void Interprete_Cliente::crear_Delete(string text){
    Vector3d<const char*, const char*,const char*>  args;   // vector para la lista principal
    VectorRelacional<const char*,int> operadores_logic3;    // vector para la lisat de sentencias

           string columna; //se utiliza en delete
           string dato;   // se utiliza en delete

           string condicion; // es = , < , > ...
           string sentencia; // and | or


           std::string result = std::string(text);
           const char* token = result.c_str();

           if(iniciar && bol_delete_from){
               nombre=token;                 // captura el nombnre de la tabla a la que se le va a insertar
               enviar(token);
               iniciar=false;
           }
           if(strcmp(text.c_str(),"delete_from")==0){
               iniciar=true;
               bol_delete_from=true;
           }

           if(bol_dato && bol_delete_from){
               dato=token;                    // dato a buscar para comparar
               enviar(token);
               lista[i]=dato;                 // agraga a lista principal
               i++;
               bol_dato=false;
           }
           if(bol_Condicion && bol_delete_from){
               condicion=token;               // condicion es para capturar cual comparador esta utilizando
               enviar(token);
               lista[i]=condicion;            // lo agraga a la lista principal la condicion
               i++;
               bol_Condicion=false;
               bol_dato=true;
           }
           if(bol_columna && bol_delete_from){
               columna = token;               // columna en la que se ubica el dato
               enviar(token);
               lista[i]=columna;              // agraga a la lista principal la columna
               i++;
               bol_columna=false;
               bol_Condicion=true;
           }
           if(strcmp(text.c_str(),"where_delete")==0 || strcmp(text.c_str(),">")==0 && bol_delete_from){
               bol_columna=true;             //bandera para las condiciones
           }

           if(bol_Valor && bol_delete_from){
               sentencia=token;                             // captura la sentencia
               enviar(token);
               lista_sentencias[valor]=sentencia;           // agrega a la lista de sentencias la sentencia entrante
               lista_valor[valor]=valor;                    // agrega el valor a la lisat decalor
               valor++;
               bol_Valor=false;
           }
           if(strcmp(text.c_str(),"<")==0 && bol_delete_from){
               bol_Valor=true;             // bandera por si se encuentra una sentencia en la linea de codigo
           }

           if(strcmp(text.c_str(),".")==0 && bol_delete_from){
               for (int i = 0; i < 48; i=i+3) {
                   if(lista[i]!="0"){
                       string variable_1= lista[i];     //saca la columna
                       string variable_2= lista [i+1];  //saca la condicion
                       string variable_3= lista[i+2];   //saca el dato a buscar

                       args.agregarAlFinal(variable_1.c_str(), variable_2.c_str(),variable_3.c_str()); //los agraga para ser mandados a borrar
                                                                                                       // el registro con ese dato

                   }
               }
               for (int i = 0; i < 20; ++i) {
                   if(lista_sentencias[i]!="0" && lista_valor[i]!= 999){
                       string variable_1= lista_sentencias[i];   // saca la la sentencia
                       int val = lista_valor[i];                 // saca el valor
                       operadores_logic3.agregarAlFinal(variable_1.c_str(),val);     //lista de operadores para ser enviados a cumplir las
                                                                                     //condicones
                   }
               }

              // fsql_manager->DeleteFrom(nombre.c_str(),&args,&operadores_logic3);    // manda a borrar el registro del archivo seleccionado


               // vuelve a reestablecer a la manera original todos los valores utilizados en delete
               for (int j=0; j<48; j++){
                   lista[j]="0";
               }
               for (int j=0; j<20; j++){
                   lista_sentencias[j]="0";
               }
               for (int j=0; j<20; j++){
                   lista_valor[j]=999;
               }
               nombre="";
               i=0;
               valor=0;
               bol_delete_from=false;
               cout<<"\n"<<endl;

           }
} // Fin de delete

/**
 * @brief Interprete_Comandos::crear_Index
 * @param text
 * Este metodo se encarga basicamente de resibir toda la sentencia pero si en el primer token
 * recibe un create index entonces empieza a funcionar para mandar los parametros y asi crear
 * el index con el arbol
 */
void Interprete_Cliente::crear_Index(string text){

} //Fin de index

/**
 * @brief Interprete_Comandos::crear_Insert_Into
 * @param text
 * Este metodo se encarga basicamente de resibir toda la sentencia pero si en el primer token
 * recibe un insert into recibe todos los datos necesarios para realizar un nuevo registro
 */
void Interprete_Cliente::crear_Insert_Into(string text){

    VectorRelacional<const char* , const char*> args1;   // vector para ingresar los datos nuevos al archivo

           string columna; //se utiliza en delete
           string dato;   // se utiliza en delete

           std::string result = std::string(text);
           const char* token = result.c_str();


           if(iniciar && bol_inser_into){
               nombre=token;              //recibe el nombre del archivo
               enviar(token);
               iniciar=false;
           }
           if(strcmp(text.c_str(),"insert_into")==0){
                enviar(token);
               iniciar=true;
               bol_inser_into=true;
           }

           if(bol_columna && bol_inser_into){
               columna=token;             // columna a la cual le desea agregar el dato
                enviar(token);
               lista[i]=columna;          // lo agraga a la lista principal
               i++;
               bol_columna=false;
           }
           if(strcmp(text.c_str(),"(")==0 || strcmp(text.c_str(),",")==0 && bol_inser_into){
               bol_columna=true;          // bandera para capturar la columna
           }

           if(bol_dato && bol_inser_into){
               dato=token;               // captura el nuevo dato de la columna correspondiente
                enviar(token);
               lista[i]=dato;            // lo agrega a la lisat principal
               i++;
               bol_dato=false;
           }
           if(strcmp(text.c_str(),"-")==0 && bol_inser_into){
               bol_dato=true;            // bandera para capturar el dato
           }

           if(strcmp(text.c_str(),")")==0 && bol_inser_into){
               for (int i = 0; i < 48; i=i+2) {
                   if(lista[i]!="0"){
                       string variable_1=lista[i];   //saca la columna
                       string variable_2=lista[i+1]; //saca el nuevo dato

                       args1.agregarAlFinal(variable_1.c_str(), variable_2.c_str());  // agrega a una lista para ser enviados al archivo
                   }
               }

               //fsql_manager->insertInto(nombre.c_str(), &args1);   // se envian al archivo y se crea el nuevo registro

               // vuelve a reestablecer a la manera original todos los valores utilizados en cinsert into
               for (int j=0; j<48; j++){
                   lista[j]="0";
               }
               nombre="";
               terminar=false;
               i=0;
               bol_inser_into=false;
               cout<<"\n"<<endl;
           }


}// Fin de insert into

/**
 * @brief Interprete_Comandos::crear_Select_Asterisco
 * @param text
 * Este metodo se encarga basicamente de resibir toda la sentencia pero si en el primer token
 * recibe un select_* reciva el nombre del archivo y imprima todo lo que contenga
 */
void Interprete_Cliente::crear_Select_Asterisco(string text){

           std::string result = std::string(text);
           const char* token = result.c_str();

           if(bol_Select_ALL){
               nombre=token;     // resive el nombre de la tabla
               enviar(token);
              // fsql_manager->Select_asterisco(nombre.c_str());   // envia el nombre del archivo para imprimir todo lo del archivo

               // vuelve a reestablecer a la manera original todos los valores utilizados en select asterisco
               bol_Select_ALL=false;
               nombre="";
               cout<<"\n"<<endl;
           }
           if(strcmp(text.c_str(),"select_*")==0){
                enviar(token);
               bol_Select_ALL=true;    // bandera para el select asterisco
           }

}//Fin de select asterisco

/**
 * @brief Interprete_Comandos::crear_Select_From
 * @param text
 * Este metodo se encarga basicamente de resibir toda la sentencia pero si en el primer token
 * recibe un select from recibe los datos necesarios para imprimir lo que uno quiere en este caso
 * el dato que se encuentre en la columna selecionada
 */
void Interprete_Cliente::crear_Select_From(string text){

    Vector3d<const char*, const char*,const char*>  args;  // vector para capturar las comparaciones que se escriben despues del where
    VectorRelacional<const char*,int> operadores_logic3;   // vector para los operadores logicos de AND o OR
    VectorRelacional<const char*,int> columnas;            // vector para las columnas que se van a imprimir

           string columna; //se utiliza en delete
           string dato;   // se utiliza en delete

           string condicion; // es = , < , > ...
           string sentencia; // and | or

           std::string result = std::string(text);
           const char* token = result.c_str();

           if(bol_Select_from && iniciar){
               sentencia=token;                     //se captura el nombre de la columna a imprimir
               lista_sentencias[valor]=sentencia;   // en este caso se utiliza la lista de sentencias para tambien tener las columnas que se
                                                    // se desean imprimir con las comparaciones que se ingresaron
                enviar(token);
               lista_valor[valor]=valor;
               valor++;
               iniciar=false;
           }
           if(strcmp(text.c_str(),"select")==0 || strcmp(text.c_str(),"&")==0 ){
               bol_Select_from=true;
                enviar(token);
               iniciar=true;
           }

           if(bol_nombre && bol_Select_from){
               nombre=token;                  // recibe el nombre de la tabla
                enviar(token);
               bol_nombre=false;
           }
           if(strcmp(text.c_str(),"from")==0 && bol_Select_from){
               bol_nombre=true;               // bandera para resibir el nombre
           }

           if(bol_dato && bol_Select_from){
               dato=token;                      // dato a buscar para comparar
                enviar(token);
               lista[i]=dato;                   // agraga a lista principal
               i++;
               bol_dato=false;
           }
           if(bol_Condicion && bol_Select_from){
               condicion=token;                  // condicion es para capturar cual comparador esta utilizando
                enviar(token);
               lista[i]=condicion;               // lo agraga a la lista principal la condicion
               i++;
               bol_Condicion=false;
               bol_dato=true;
           }
           if(bol_columna && bol_Select_from){
               columna = token;                  // columna en la que se ubica el dato
                enviar(token);
               lista[i]=columna;                 // agraga a la lista principal la columna
               i++;
               bol_columna=false;
               bol_Condicion=true;
           }
           if(strcmp(text.c_str(),"where_select")==0 || strcmp(text.c_str(),">")==0 && bol_Select_from){
               bol_columna=true;                  //bandera para las condiciones

           }

           if(bol_Valor && bol_Select_from){
               sentencia=token;                           // captura la sentencia
                enviar(token);
               lista_sentencias[valor]=sentencia;         // agrega a la lista de sentencias la sentencia entrante
               lista_valor[valor]=valor;                  // agrega el valor a la lisat decalor
               valor++;
               bol_Valor=false;
           }
           if(strcmp(text.c_str(),"<")==0 && bol_Select_from){
               bol_Valor=true;                             // bandera por si se encuentra una sentencia en la linea de codigo
           }

           if(strcmp(text.c_str(),".")==0 && bol_Select_from){
               enviar(token);
               for (int i = 0; i < 48; i=i+3) {
                   if(lista[i]!="0"){
                       string variable_1= lista[i];     //saca la columna
                       string variable_2= lista [i+1];  //saca la condicion
                       string variable_3= lista[i+2];   //saca el dato

                       args.agregarAlFinal(variable_1.c_str(), variable_2.c_str(),variable_3.c_str());  // agraga a una lista

                   }
               }
               for (int i = 0; i < 20; ++i) {
                   if(lista_sentencias[i]=="AND" || lista_sentencias[i]=="OR" ){
                       string variable_1= lista_sentencias[i];  // saca la sentencia
                       int val_1 = lista_valor[i];              // saca el valor de la sentencia en ese momento
                       operadores_logic3.agregarAlFinal(variable_1.c_str(),val_1);   // los agrega a una lisat de sentencias

                   }
                   if(lista_sentencias[i]!="AND" && lista_sentencias[i]!="OR" && lista_sentencias[i]!="0"){
                       string variable_2 = lista_sentencias[i]; //casa las columnas que se van a imprimir
                       int val_2 = lista_valor[i];              //saca el valor que posee la columna
                       columnas.agregarAlFinal(variable_2.c_str(), val_2);  // agreaga a una lista
                   }
               }

              // fsql_manager->Select(nombre.c_str(),&args,&columnas, &operadores_logic3);  /* invia las lista necesarias para
                                                                                            //imprimir lo que se quiere busacar*/

               // vuelve a reestablecer a la manera original todos los valores utilizados en select from
               for (int j=0; j<48; j++){
                   lista[j]="0";
               }
               for (int j=0; j<20; j++){
                   lista_sentencias[j]="0";
               }
               for (int j=0; j<20; j++){
                   lista_valor[j]=999;
               }

               nombre="";
               i=0;
               valor=0;
               bol_Select_from=false;
               cout<<"\n"<<endl;

           }

}//Fin de select from

/**
 * @brief Interprete_Comandos::crear_Update
 * @param text
 * Este metodo se encarga basicamente de resibir toda la sentencia pero si en el primer token
 * recibe un update recibe todos los datos necesarios para actualizar los registros que se desean
 */
void Interprete_Cliente::crear_Update(string text){

    Vector3d<const char*, const char*,const char*>  args;  // vector para capturar los datos de comparacion
    VectorRelacional<const char* , const char*> args1;     // vector para capturar los datos a actualizar
    VectorRelacional<const char*,int> operadores_logic3;   // vector para capturar lo operadores logicos de AND o OR

           string columna; //se utiliza en delete
           string dato;   // se utiliza en delete

           string condicion; // es = , < , > ...
           string sentencia; // and | or

           string pos;  // es la columnas
           string cambio; // es el dato a actualizar

           std::string result = std::string(text);
           const char* token = result.c_str();

           if(iniciar && bol_update){
               nombre = token ;        //captura el nombre de la tabla
                enviar(token);
               iniciar=false;
           }
           if(strcmp(text.c_str(),"update")==0){
               iniciar=true;
                enviar(token);
               bol_update=true;
           }

           if(bol_pos && bol_update){
               pos=token;              //captura el nombre de la columna del dato que se desea actualizar
                enviar(token);
               lista_cambios[j]=pos;   //se agraga a la lista de cambios que se desean hacer
               j++;
               bol_pos=false;
           }
           if(strcmp(text.c_str(),"set")==0 || strcmp(text.c_str(),",")==0 && bol_update){
               bol_pos=true;          //bandera para capturar la columna a actualizar
           }

           if (bol_cambio && bol_update ){
               cambio=token;                //dato que se quiere actualizar en un registro en el archivo
                enviar(token);
               lista_cambios[j]=cambio;     //se agrega a la lisat de cambios para realizar
               j++;
               bol_cambio=false;
           }
           if(strcmp(text.c_str(),"-")==0 && bol_update){
               bol_cambio=true;             //bandera para capturar el dato
           }

           if(bol_dato && bol_update){
               dato=token;                        // dato a buscar para comparar
                enviar(token);
               lista[i]=dato;                     // agraga a lista principal
               i++;
               bol_dato=false;
           }
           if(bol_Condicion && bol_update){
               condicion=token;                   // condicion es para capturar cual comparador esta utilizando
                enviar(token);
               lista[i]=condicion;                // lo agraga a la lista principal la condicion
               i++;
               bol_Condicion=false;
               bol_dato=true;
           }
           if(bol_columna && bol_update){
               columna = token;                   // columna en la que se ubica el dato
                enviar(token);
               lista[i]=columna;                  // agraga a la lista principal la columna
               i++;
               bol_columna=false;
               bol_Condicion=true;
           }
           if(strcmp(text.c_str(),"where_update")==0 || strcmp(text.c_str(),">")==0 && bol_update){
               enviar(token);
               bol_columna=true;                  //bandera para las condiciones
           }

           if(bol_Valor && bol_update){
               sentencia=token;                      // captura la sentencia
                enviar(token);
               lista_sentencias[valor]=sentencia;    // agrega a la lista de sentencias la sentencia entrante
               lista_valor[valor]=valor;             // agrega el valor a la lisat decalor
               valor++;
               bol_Valor=false;
           }
           if(strcmp(text.c_str(),"<")==0 && bol_update){
               bol_Valor=true;                        if(strcmp(text.c_str(),"cliente")==0){
                   try
                     {
                       ClientSocket client_socket ( ipDelServer, serverPort );

                       std::string reply;
                       try
                     {
                       const char* envio = "bien conecto!";
                       std::string en = envio;
                       client_socket.sendMessage(en);
                       client_socket.reciveMessage(reply);



                     }
                       catch ( SocketException& ) {}
                       std::cout << "Recibimos esta respuesta del servidor:\n\"" << reply << "\"\n";;

                     }
                   catch ( SocketException& e )
                     {
                       std::cout << "Exception was caught:" << e.description() << "\n";
                     }
               }// bandera por si se encuentra una sentencia en la linea de codigo
           }

           if(strcmp(text.c_str(),".")==0 && bol_update){
               enviar(token);
               for (int i = 0; i < 48; i=i+3) {
                   if(lista[i]!="0"){
                       string variable_1= lista[i];     //saca la columna
                       string variable_2= lista [i+1];  //saca la condicon de comparación
                       string variable_3= lista[i+2];   //saca el dato a buscar o a comparar
                       args.agregarAlFinal(variable_1.c_str(), variable_2.c_str(),variable_3.c_str());   // se agrega a la lista a realizar

                   }
               }

               for (int i = 0; i < 48; i=i+2) {
                   if(lista_cambios[i]!="0"){
                       string variable_1=lista_cambios[i];      //saca la columna donde se encuentra el dato
                       string variable_2=lista_cambios[i+1];    // dato a actualizar
                       args1.agregarAlFinal(variable_1.c_str(), variable_2.c_str());    // lisat para ver que datos hay que actualizar
                   }
               }

               for (int i = 0; i < 20; ++i) {
                   if(lista_sentencias[i]=="AND" || lista_sentencias[i]=="OR" ){
                       string variable_1= lista_sentencias[i];    // saca la sentencia si es un OR o un AND
                       int val_1 = lista_valor[i];                // saca el valor en ese momento
                       operadores_logic3.agregarAlFinal(variable_1.c_str(),val_1);   // los agrega a una lisa

                   }

               }

              // fsql_manager->update(nombre.c_str(),&args,&operadores_logic3, &args1);   /* mando los datos necesarios para actualizar el
                                                                                          //el registro en el archivo selecionado*/

               // vuelve a reestablecer a la manera original todos los valores utilizados en update
               for (int j=0; j<48; j++){
                   lista[j]="0";
               }
               for (int j=0; j<20; j++){
                   lista_sentencias[j]="0";
               }
               for (int j=0; j<20; j++){
                   lista_valor[j]=999;
               }
               for (int j=0; j<48; j++){
                   lista_cambios[j]="0";
               }

               nombre="";
               i=0;
               j=0;
               valor=0;
               bol_update=false;
               cout<<"\n"<<endl;

           }
}//FIn de update


void Interprete_Cliente::conection(string text){

    std::string result = std::string(text);
    const char* token = result.c_str();

    if(strcmp(text.c_str(),"servidor")==0){
        try
          {
            // Create the socket
            ServerSocket server ( serverPort );
            //while (server.getConnectionStatus() && !flag)
            cout<<"entro servidor"<<endl;
            ServerSocket new_sock;
            server.accept (new_sock);
            try
              {
                while (server.getOutputMessageStatus()){
                std::string data;
                new_sock.reciveMessage(data);
                std::cout << data << std::endl;
                interprete_server->escuchar(data);
                //std::string data2;
                //data2 = ipmia;
                //new_sock.sendMessage(data2);
            }
            }
            catch ( SocketException& ) {}


        }
        catch ( SocketException& e )
        {
            std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
        }

    }
}


void Interprete_Cliente:: enviar(const char* token){
    std::string en = token;
    try
      {
        if(banderaCliente){
            client_socket = new ClientSocket( ipDelServer, serverPort );
            banderaCliente = false;
        }
        //ClientSocket* client_socket = new ClientSocket( ipDelServer, serverPort );

        std::string reply;
        try
      {

        //std::string en = envio;
        client_socket->sendMessage(en +".");
        //client_socket.reciveMessage(reply);


      }
        catch ( SocketException& ) {}
        //std::cout << "Recibimos esta respuesta del servidor:\n\"" << reply << "\"\n";;

      }
    catch ( SocketException& e )
      {
        std::cout << "Exception was caught:" << e.description() << "\n";
      }
}
