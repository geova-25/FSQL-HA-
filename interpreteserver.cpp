#include "interpreteserver.h"

InterpreteServer :: InterpreteServer()
{


}



void InterpreteServer :: escuchar(string data_recibida ){

   fsql_manager2.setDirectory("/home/sebastian/Escritorio/BaseDeDatos/");







   cout<<data_recibida<<endl;

   char palabra [300];
   string lista[49];
   string lista_cambio[49];
   int contador=0;
   int contador_cambio=0;
   int j=0;

   for (int j=0; j<49; j++){
       lista[j]="0";             //Inicia lasta principal con ceros string
   }

   Vector3d<const char*, const char*,const char*>  args;
   VectorRelacional<const char* , const char*> args1;   // vector para ingresar los datos nuevos al archivo

          //create table
          string caracteristica;// tomar la primer varable de columnas
          string tipo;   // tipo de varable (string, int)
          string caracteres;  // cantidad de caracteres que le va a entrar a la caracteristica


          if(entro_create_table){
              cout<<"entro bandera"<<endl;
              for  (int i = 0 ; i < data_recibida.length() ; i++){

                     if(data_recibida[i] != '.'){
                         palabra[j] = data_recibida[i];
                         j++;
                     }if(data_recibida[i] == '.'){
                         lista[contador]=palabra;
                         cout<<"palabra: "<<lista[contador]<<endl;
                         contador++;
                         j=0;
                         for(int i=0;i<300;i++){
                             palabra[i]=0;
                         }                        
                     }
                 }

              cout<<"segundo"<<endl;
              for(int i=1; i<49;i=i+3){
                  cout<<"entro segundo"<<endl;
                  if(lista[i]!="0"){
                      string variable_1= lista[i];     // saca la columna
                      string variable_2= lista [i+1];  // saca el tipo de la columna
                      string variable_3= lista[i+2];   // saca los caracteres que va a tener

                      cout<<"va 1: "<<variable_1<<endl;
                      cout<<"va 2: "<<variable_2<<endl;
                      cout<<"va 3: "<<variable_3<<endl;

                      args.agregarAlFinal(variable_1.c_str(), variable_2.c_str(),variable_3.c_str());  //Agraga a un vector para luego mandar                                                                                   // a crear el archivo

                  }
              }

              args.imprimir();
            string nombre =lista[0];
            cout<<nombre<<endl;
            fsql_manager2.createTable(nombre.c_str(),&args);   // manda los datos necesarios para crear la tabla

            for (int j=0; j<49; j++){
                lista[j]="0";             //Inicia lasta principal con ceros string
            }
            contador==0;
            entro_create_table=false;
          }

          if(data_recibida.compare("create_table.")==0){
              entro_create_table=true;
              cout<<"entro a create"<<endl;
          }


          //**************************************
          //insert_into
          if(entro_insert_into){
              for  (int i = 0 ; i < data_recibida.length() ; i++){

                     if(data_recibida[i] != '.'){
                         palabra[j] = data_recibida[i];
                         j++;
                     }if(data_recibida[i] == '.'){
                         lista[contador]=palabra;
                         cout<<"palabra: "<<lista[contador]<<endl;
                         contador++;
                         j=0;
                         for(int i=0;i<300;i++){
                             palabra[i]=0;
                         }
                     }

                 }


              /////////////////////////////////////////////////////////
              for(int i=1; i<49;i=i+2){
                  cout<<"entro segundo"<<endl;
                  if(lista[i]!="0"){
                      string variable_1= lista[i];     // saca la columna
                      string variable_2= lista [i+1];  // saca el tipo de la columna

                      args1.agregarAlFinal(variable_1.c_str(), variable_2.c_str());  //Agraga a un vector para luego mandar                                                                                   // a crear el archivo

                  }
              }

              args1.imprimir();
            string nombre =lista[0];
            cout<<nombre<<endl;
            fsql_manager2.insertInto(nombre.c_str(),&args1);   // manda los datos necesarios para crear la tabla
            //fsql_manager2.Select_asterisco(nombre.c_str());

            for (int j=0; j<49; j++){
                lista[j]="0";             //Inicia lasta principal con ceros string
            }
            contador==0;
            entro_insert_into=false;
          }

          if(data_recibida.compare("insert_into.")==0){
              entro_insert_into=true;
          }

          //**************************************************
          //update

          /*if(entro_update){
              bool bandera_cambios=false;
              bool bandera_lista=true;
              for  (int i = 0 ; i < data_recibida.length() ; i++){
                     if(data_recibida[i] != '.'){
                         palabra[j] = data_recibida[i];
                         j++;
                     }if(data_recibida[i] == '.'){

                         if(bandera_cambios){
                             lista_cambio[contador_cambio]=palabra;
                             cout<<"palabra: "<<lista_cambio[contador_cambio]<<endl;
                             contador_cambio++;
                             j=0;
                             for(int i=0;i<300;i++){
                                 palabra[i]=0;
                             }
                         }
                         if(bandera_lista){
                             if(palabra!="where_update"){
                                 lista[contador]=palabra;
                                 cout<<"palabra: "<<lista[contador]<<endl;
                                 contador++;
                                 j=0;
                                 for(int i=0;i<300;i++){
                                     palabra[i]=0;
                                 }
                             }
                             else{
                                 bandera_lista=false;
                                 bandera_cambios=true;
                             }
                         }
                     }
                 }

              for(int i=1; i<49;i=i+2){
                  cout<<"entro segundo"<<endl;
                  if(lista[i]!="0"){
                      string variable_1= lista[i];     // saca la columna
                      string variable_2= lista [i+1];  // saca el tipo de la columna

                      args1.agregarAlFinal(variable_1.c_str(), variable_2.c_str());  //Agraga a un vector para luego mandar                                                                                   // a crear el archivo

                  }
              }
              for(int i=1; i<49;i=i+2){
                  cout<<"entro segundo"<<endl;
                  if(lista[i]!="0"){
                      string variable_1= lista[i];     // saca la columna
                      string variable_2= lista [i+1];  // saca el tipo de la columna

                      args1.agregarAlFinal(variable_1.c_str(), variable_2.c_str());  //Agraga a un vector para luego mandar                                                                                   // a crear el archivo

                  }
              }

              args1.imprimir();
            string nombre =lista[0];
            cout<<nombre<<endl;
            fsql_manager2.insertInto(nombre.c_str(),&args1);   // manda los datos necesarios para crear la tabla


          }

          if(data_recibida.compare("update.")==0){
              entro_update=true;
          }*/


          //////////////////////////////////////////////////////////////////////////////////////////
          //****************************************************************************************
          //create_user

          if(entro_create_user){
              for  (int i = 0 ; i < data_recibida.length() ; i++){

                     if(data_recibida[i] != '.'){
                         palabra[j] = data_recibida[i];
                         j++;
                     }if(data_recibida[i] == '.'){
                         lista[contador]=palabra;
                         cout<<"palabra: "<<lista[contador]<<endl;
                         contador++;
                         j=0;
                         for(int i=0;i<300;i++){
                             palabra[i]=0;
                         }
                     }

                 }


              /////////////////////////////////////////////////////////

              string variable_1= lista[0];     // saca la columna
              string variable_2= lista [2];  // saca el tipo de la columna

              fsql_manager2.create_user(variable_1.c_str(), variable_2.c_str());

              for (int j=0; j<49; j++){
                  lista[j]="0";             //Inicia lasta principal con ceros string
              }
              contador==0;
              entro_create_user=false;

          }

          if(data_recibida.compare("create_user.")==0){
              entro_create_user=true;
          }

          //////////////////////////////////////////////////////////////////////////////////////////
          //****************************************************************************************
          //drop_user

          if(entro_drop_user){
              for  (int i = 0 ; i < data_recibida.length() ; i++){

                     if(data_recibida[i] != '.'){
                         palabra[j] = data_recibida[i];
                         j++;
                     }if(data_recibida[i] == '.'){
                         lista[contador]=palabra;
                         cout<<"palabra: "<<lista[contador]<<endl;
                         contador++;
                         j=0;
                         for(int i=0;i<300;i++){
                             palabra[i]=0;
                         }
                     }

                 }
              string variable_1= lista[0];     // saca la columna
cout<<"variable_1 : " <<variable_1<<endl;
              fsql_manager2.drop_user(variable_1.c_str());


              for (int j=0; j<49; j++){
                  lista[j]="0";             //Inicia lasta principal con ceros string
              }
              contador==0;
              entro_drop_user=false;

          }

          if(data_recibida.compare("drop_user.")==0){
              entro_drop_user=true;
          }

          //////////////////////////////////////////////////////////////////////////////////////////
          //****************************************************************************************
          //grant
          if(entro_grant){
              for (int i = 0 ; i < data_recibida.length() ; i++){

                     if(data_recibida[i] != '.'){
                         palabra[j] = data_recibida[i];
                         j++;
                     }if(data_recibida[i] == '.'){
                         if(palabra!="on" && palabra!= "to"){
                             lista[contador]=palabra;
                             cout<<"palabra: "<<lista[contador]<<endl;
                             contador++;
                             j=0;
                             for(int i=0;i<300;i++){
                                 palabra[i]=0;
                             }
                         }
                     }
                 }
              string variable_1= lista[0];     // saca la columna
              string variable_2= lista[1];     // saca la columna
              string variable_3= lista[2];     // saca la columna

              fsql_manager2.grant(variable_1.c_str(),variable_2.c_str(),variable_3.c_str());

              for (int j=0; j<49; j++){
                  lista[j]="0";             //Inicia lasta principal con ceros string
              }
              contador==0;
              entro_grant=false;
          }


          if(data_recibida.compare("grant.")==0){
              entro_grant=true;
          }


}
