#include "interpreteserver.h"

InterpreteServer :: InterpreteServer(FSQL_Manager* manager)
{

    fsql_manager = manager;

}



void InterpreteServer :: escuchar(string data_recibida ){
   cout<<data_recibida<<endl;
   //cout<<"escucha"<<endl;


   Vector3d<const char*, const char*,const char*>  args;

          //create table
          string caracteristica;// tomar la primer varable de columnas
          string tipo;   // tipo de varable (string, int)
          string caracteres;  // cantidad de caracteres que le va a entrar a la caracteristica

         /* char cubeta[data_recibida.length()];
          int numero_caracteres=0;
          for(numero_caracteres ; data_recibida[numero_caracteres] != '/0'; numero_caracteres++){
              cubeta[numero_caracteres] = data_recibida[numero_caracteres];
          }*/




         /* cout << cubeta << endl;
          if(data_recibida.compare("create_table.")==0){
              entro_create_table=true;
          }*/






        /*  if (bol_raid && bol_create_table){
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
          }*/

}
