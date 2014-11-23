#include "fsql_manager.h"

FSQL_Manager::FSQL_Manager()
{
}

bool FSQL_Manager :: createTable(const char* filename, Vector3d<const char*, const char*,const char*>*  args  ){
    file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
    file_manager->initSchema();//se vacia el schema en memoria
    file_manager->setNameOfFile(filename);//es necesario crear un archivo con un nombre
    file_manager->generate_binaryFile();
    file_manager->setNumberOfColumns(args->getLength());
    //contador para tamaño de registro empieza en 8 porque los 8 bytes primeros representan ptr al anterior registro y siguiente
    int tamanio_registro = file_manager->INICIO_DE_REGISTRO_EN_BYTES;
    Nodo3d<const char*,const char*,const char*>* temp;
    temp = args->get_primerNodo();
    args->get_ultimoNodo()->set_siguiente(NULL);
    //agregamos los parametros de create table para armar un schema en memoria
    for(int x=0 ; x<(args->getLength());x++){
        if (file_manager->compare_strings(temp->get_elemento2(),"string")
                ||file_manager->compare_strings( temp->get_elemento2(),"String")){
            //agrego string al schema con tamaño en caracteres
            file_manager->addStringToSchema(temp->get_elemento1() , atoi(temp->get_elemento3()));
            tamanio_registro +=  atoi(temp->get_elemento3());
        }
        else if (file_manager->compare_strings(temp->get_elemento2(), "int")
                 || file_manager->compare_strings(temp->get_elemento2(),"Int")){
            //agrego int al schema con tamaño en caracteres
            file_manager->addIntToSchema(temp->get_elemento1() ,atoi(temp->get_elemento3()));
            tamanio_registro +=  file_manager->BYTES_4;                         //4 bytes de tamaño por el momento
        }
        else if (file_manager->compare_strings(temp->get_elemento2(),"float")
                 || file_manager->compare_strings(temp->get_elemento2(),"Float")){
              //agrego int al schema con su tamaño en caracteres
            file_manager->addFloatToSchema(temp->get_elemento1() ,atoi(temp->get_elemento3()));
            tamanio_registro +=  file_manager->BYTES_4;  //guardo por ahora solo 4 bytes
        }
        temp = temp->get_siguiente();
    }

    file_manager->setSizeOfRegister(tamanio_registro); //actualizo tamaño del registro en bytes
    file_manager->saveSchema();//se guarda el schema en disco
    file_manager->saveHeader();//se guarda el header en disco

    return true;
}

bool FSQL_Manager :: insertInto(const char* filename, VectorRelacional<const char*, const char*>*  campos  ){

    file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
    file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro

    file_manager->initSchema();//se vacia el schema en memoria
    file_manager->loadSchema();//cargo el header a memoria
//creamos el registro
    Register* new_reg = new Register(file_manager , directorioDe_fsql);
    new_reg->initRegister(filename);
    new_reg->fill_Register(campos);//lleno el registro en memoria
    new_reg->setDirty(true);

    register_manager.addRegisterToMap(new_reg); //agrego al mapa de registros en memoria

    file_manager->addNewRegister(new_reg->getBuffer());

    file_manager->saveHeader();//salvo el header antes de agregar un registro
  // file_manager->printHeader();

     return true;
}

bool FSQL_Manager :: update(const char* filename, Vector3d<const char*, const char*,const char*>* condiciones
                            , VectorRelacional<const char*,int>* operadores_logicos,VectorRelacional<const char*,const char*>* sets){
    file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
    file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
    file_manager->initSchema();//se vacia el schema en memoria
    file_manager->loadSchema();//cargo el header a memoria
    file_manager->openFile();

    if(condiciones->getLength() > 0){
        int* accepted_rows = file_manager->where(condiciones,operadores_logicos);


        for (int i = 0 ; i< file_manager->getNumberOfRegisters();i++){
            if(accepted_rows[i] != -1){
                NodoRelacional<const char*,const char*>* temp_ = sets->get_primerNodo();
                sets->get_ultimoNodo()->set_siguiente(NULL);
                while(temp_!= NULL){
                    file_manager->setCampo(temp_->get_elemento1(),temp_->get_elemento2(),accepted_rows[i]);
                    temp_=temp_->get_siguiente();
                }
            }
           // cout<<accepted_rows[i]<<endl;
        }

    }



    file_manager->saveFile();
    file_manager->closeFile();
    return true;

}

bool FSQL_Manager :: Select(const char* filename,  Vector3d<const char*, const char*,const char*>*condiciones
                            , VectorRelacional<const char*,int>* columnas, VectorRelacional<const char*,int>* operadores_logicos ){

    file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
    file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
    file_manager->initSchema();//se vacia el schema en memoria
    file_manager->loadSchema();//cargo el header a memoria
    file_manager->openFile();
     cout<<"-------------------------Select From "<<file_manager->getNameOfFile()<<" --------------------------------"<<endl;

    if(condiciones->getLength() > 0){
        int* accepted_rows = file_manager->where(condiciones,operadores_logicos);
        bool coincidencias= false;

        for (int i = 0 ; i< file_manager->getNumberOfRegisters();i++){
            if(accepted_rows[i] != -1){
                coincidencias= true;
                NodoRelacional<const char*,int>* temp_ = columnas->get_primerNodo();
                columnas->get_ultimoNodo()->set_siguiente(NULL);
                while(temp_!= NULL){
                    cout<<"-------------------------Row "<<accepted_rows[i]<<" --------------------------------"<<endl;
                    file_manager->printValorDeCampo(temp_->get_elemento1(),accepted_rows[i] );
                    temp_=temp_->get_siguiente();
                }
            }
        }
        if(coincidencias == false){
            cout<<"no existe campo que cumple condiciones"<<endl;
        }

    }

    file_manager->closeFile();
    return true;

}
bool FSQL_Manager :: Select_asterisco(const char* filename){
     file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
     file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
     file_manager->initSchema();//se vacia el schema en memoria
     file_manager->loadSchema();//cargo el header a memoria
     file_manager->openFile();

     file_manager->printFile();

     file_manager->closeFile();
 }

bool FSQL_Manager :: DeleteFrom(const char* filename,  Vector3d<const char*, const char*,const char*>*condiciones
                                , VectorRelacional<const char*,int>* operadores_logicos){

   file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
   file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
   file_manager->initSchema();//se vacia el schema en memoria
   file_manager->loadSchema();//cargo el header a memoria
   file_manager->openFile();
  // cout<<"-------------------------Delete From "<<file_manager->getNameOfFile()<<" --------------------------------"<<endl;

   if(condiciones->getLength() > 0){
       int* delete_rows = file_manager->where(condiciones,operadores_logicos);

       for (int i = 0 ; i< file_manager->getNumberOfRegisters();i++){
           if(delete_rows[i] != -1){
               file_manager->delete_row(delete_rows[i]);
           }
       }

   }
   file_manager->saveHeader();
   file_manager->saveFile();
   file_manager->closeFile();
   return true;
}

int FSQL_Manager:: logic(){



    createFile_Users_And_Permissions();
    create_user("sebas1995", "1111");
    create_user("Ruben", "2222");
    create_user("Will", "3333");
    create_user("andres", "4444");





  //drop_user("Ruben");
    grant("update" , "casas", "sebas1995");
     grant("update" , "propiedades", "Ruben");

  grant("delete" , "casas", "sebas1995");
   grant("insert" , "casas", "sebas1995");
   grant("update" , "casas", "sebas1995");


//Select_asterisco(Nombre_archivo_permisos);

  grant("delete" , "casas", "Ruben");
   revoke("delete" , "casas", "sebas1995");


  Select_asterisco(Nombre_Archivo_usuario);
   //Select_asterisco(Nombre_archivo_permisos);



    /*const char* nombre_archivo = "test";
    // ---------------------------------------------------------Create table

    Vector3d<const char*, const char*,const char*>  args;

    args.agregarAlFinal("Nombre","string","10");

    args.agregarAlFinal("Apellido","string","10");

    args.agregarAlFinal("cedula","int","4");

    args.agregarAlFinal("institucion","string","10");

    args.agregarAlFinal("direccion","string","10");

    args.agregarAlFinal("edad","float","4");

    args.agregarAlFinal("id","int","4");


    createTable(nombre_archivo , &args);



    //---------------------------------------------------------insert into


   VectorRelacional<const char* , const char*> args1;
   VectorRelacional<const char* , const char*> args2;
   VectorRelacional<const char* , const char*> args4;
   VectorRelacional<const char* , const char*> args5;

    args1.agregarAlFinal("id" , "22");
    args1.agregarAlFinal("Nombre","will");
    args1.agregarAlFinal("cedula","345");
    args1.agregarAlFinal("direccion" , "sanjose");
    args1.agregarAlFinal("edad" , "19");

    args2.agregarAlFinal("id" , "52");
    args2.agregarAlFinal("Nombre","daniel");
    args2.agregarAlFinal("cedula","7233150");


    args4.agregarAlFinal("edad" , "20.5");
    args4.agregarAlFinal("id" , "02");
    args4.agregarAlFinal("Nombre","Ruben");
    args4.agregarAlFinal("cedula","1111");
    args4.agregarAlFinal("direccion" , "cartago");


    args5.agregarAlFinal("Nombre","carlos");
    args5.agregarAlFinal("cedula","1111");
    args5.agregarAlFinal("direccion" , "alajuela");


  insertInto(nombre_archivo , &args1);
  insertInto(nombre_archivo , &args2);
  insertInto(nombre_archivo , &args2);
  insertInto(nombre_archivo , &args4);
  insertInto(nombre_archivo , &args5);


//--------------------------------------update-------------------------------------
  Vector3d<const char* , const char*, const char*> condiciones;
  VectorRelacional<const char*,int> operadores_logic;
  VectorRelacional<const char*,const char*> sets;

  //set
  sets.agregarAlFinal("direccion","Guanacaste");
  sets.agregarAlFinal("institucion","ICE");

  //where
  condiciones.agregarAlFinal("Nombre","=","Ruben");
  operadores_logic.agregarAlFinal("AND",1);
  condiciones.agregarAlFinal("Nombre","=","daniel");
  operadores_logic.agregarAlFinal("OR",2);
  condiciones.agregarAlFinal("cedula","=","1111");
  operadores_logic.agregarAlFinal("OR",3);
  condiciones.agregarAlFinal("direccion","=","sanjose");



 // update(nombre_archivo,&condiciones,&operadores_logic, &sets );

 //---------------------------------------select From-------------------------------------------
  Vector3d<const char* , const char*, const char*> condiciones2;
  VectorRelacional<const char*,int> operadores_logic2;
  VectorRelacional<const char*,int> columnas2;

  //select


  columnas2.agregarAlFinal("cedula",0);

  //where
  condiciones2.agregarAlFinal("id","=","02");
  operadores_logic2.agregarAlFinal("AND",1);
  condiciones2.agregarAlFinal("edad","=","20.5");

 // Select(nombre_archivo,&condiciones2,&columnas2,&operadores_logic2);


//--------------------------------------------delete from--------------------------------
  Vector3d<const char* , const char*, const char*> condiciones3;
  VectorRelacional<const char*,int> operadores_logic3;


  condiciones3.agregarAlFinal("Nombre","=", "Ruben");
  operadores_logic3.agregarAlFinal("OR",0);
  condiciones3.agregarAlFinal("direccion","=", "alajuela");
  //Select_asterisco(nombre_archivo);

  //DeleteFrom(nombre_archivo,&condiciones3,&operadores_logic3);



  //------------------------------------Select asterisco----------------------------------
 file_manager->printHeader();
  Select_asterisco(nombre_archivo);

  //----------------------------------------------prints------------------------------

  file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
  file_manager->loadHeader(nombre_archivo);//cargo el header del aqrchivo que quiero agregar registro
  file_manager->initSchema();//se vacia el schema en memoria
  file_manager->loadSchema();//cargo el header a memoria
  file_manager->openFile();


 //file_manager->printFile();*/





    return 0;

}
void FSQL_Manager ::  setDirectory( const char* dir ){
    directorioDe_fsql = dir;
    file_manager->set_directory(directorioDe_fsql);
}
 bool FSQL_Manager ::createFile_Users_And_Permissions(){

     //se llena la estructura args que contiene las columnas
     Vector3d<const char*, const char*,const char*>  args;
     args.agregarAlFinal("user_name","string","120");
     args.agregarAlFinal("password","string","10");
     //creo el archivo de usuarios
     createTable(Nombre_Archivo_usuario , &args);

     //se llena la estructura args2 que contiene las columnas
     Vector3d<const char*, const char*,const char*>  args2;
     args2.agregarAlFinal("user_name","string","120");
     args2.agregarAlFinal("file_name","string","64");
     args2.agregarAlFinal("create_table","int","1");
     args2.agregarAlFinal("delete","int","1");
     args2.agregarAlFinal("select","int","1");
     args2.agregarAlFinal("insert","int","1");
     args2.agregarAlFinal("update","int","1");
     args2.agregarAlFinal("create_user","int","1");
     args2.agregarAlFinal("drop_user","int","1");
     args2.agregarAlFinal("grant","int","1");
     args2.agregarAlFinal("revoke","int","1");
     //creo el archivo de pemisos
     createTable(Nombre_archivo_permisos , &args2);
 }
 bool FSQL_Manager :: create_user(const char* usuario, const char* contrasenia){
     VectorRelacional<const char* , const char*> args5;
     //meto un usuario en la columna contraseña en el achivo de usuarios
     args5.agregarAlFinal("user_name" , usuario);
     //meto una constraseña en la columna passsword
     args5.agregarAlFinal("password" , contrasenia);
     insertInto(Nombre_Archivo_usuario , &args5);

 }
bool FSQL_Manager :: drop_user(const char* usuario){
      VectorRelacional<const char*,int> operadores_logic3;

     Vector3d<const char* , const char*, const char*> condiciones3;

     //asigno la condicion que el campo user name sea del achivo de usuarios = a usuario
     condiciones3.agregarAlFinal("user_name","=", usuario);
     //borro el registro que cumpla la condicion anterios en el arch de permisos
     DeleteFrom(Nombre_Archivo_usuario,&condiciones3,&operadores_logic3);

     Vector3d<const char* , const char*, const char*> condiciones4;
     //asigno la condicion que el campo user name sea del achivo de usuarios = a usuario
     condiciones4.agregarAlFinal("user_name","=", usuario);
     //borro el registro que cumpla la condicion anterios en el arch de permisos
     DeleteFrom(Nombre_archivo_permisos,&condiciones4,&operadores_logic3);

 }
 bool FSQL_Manager :: grant(const char* permiso , const char* nombre_archivo, const char* user){
     Vector3d<const char* , const char*, const char*> condiciones2;
     VectorRelacional<const char*,int> operadores_logic2;
     //where ,  se establecenlas condiciones de donde se quiere buscar un valor de un campo
     condiciones2.agregarAlFinal("file_name","=",nombre_archivo);
     operadores_logic2.agregarAlFinal("AND",1);
     condiciones2.agregarAlFinal("user_name","=",user);
     //si el usuario ya cuenta con un registro de permisos para el archivo, en el archivo permisos
     //solo se actualiza
     if(isThereField(Nombre_archivo_permisos,&condiciones2,&operadores_logic2)){

         Vector3d<const char* , const char*, const char*> condiciones;
         VectorRelacional<const char*,int> operadores_logic;
         VectorRelacional<const char*,const char*> sets;
         //set
         sets.agregarAlFinal(permiso,permiso_positivo);
         //where
         condiciones.agregarAlFinal("user_name","=",user);
         operadores_logic.agregarAlFinal("AND",1);
         condiciones.agregarAlFinal("file_name","=",nombre_archivo);
        update(Nombre_archivo_permisos,&condiciones,&operadores_logic, &sets );
     }
     else{ //si no se crea un nuevo registro para el usuario con ese archivo

         VectorRelacional<const char* , const char*> args4;
         //meto un usuario en la columna contraseña del archvo de permisos
         args4.agregarAlFinal("user_name" , user);
         args4.agregarAlFinal("file_name" , nombre_archivo);
         args4.agregarAlFinal(permiso , permiso_positivo);
         insertInto(Nombre_archivo_permisos , &args4);
     }
 }
 bool FSQL_Manager :: revoke(const char* permiso , const char* nombre_archivo, const char* user){
     Vector3d<const char* , const char*, const char*> condiciones2;
     VectorRelacional<const char*,int> operadores_logic2;
     //where ,  se establecenlas condiciones de donde se quiere buscar un valor de un campo
     condiciones2.agregarAlFinal("file_name","=",nombre_archivo);
     operadores_logic2.agregarAlFinal("AND",1);
     condiciones2.agregarAlFinal("user_name","=",user);
     //si el usuario ya cuenta con un registro de permisos para el archivo, en el archivo permisos
     //solo se actualiza
     if(isThereField(Nombre_archivo_permisos,&condiciones2,&operadores_logic2)){
         Vector3d<const char* , const char*, const char*> condiciones;
         VectorRelacional<const char*,int> operadores_logic;
         VectorRelacional<const char*,const char*> sets;
         //set
         sets.agregarAlFinal(permiso,permiso_negativo);
         //where
         condiciones.agregarAlFinal("user_name","=",user);
         operadores_logic.agregarAlFinal("AND",1);
         condiciones.agregarAlFinal("file_name","=",nombre_archivo);
         update(Nombre_archivo_permisos,&condiciones,&operadores_logic, &sets );
     }
     else{
         cout<<"No existe permiso que elminar"<<endl;
     }
 }

 bool FSQL_Manager :: isThereField(const char* filename,  Vector3d<const char*, const char*,
     const char*>*condiciones, VectorRelacional<const char*,int>* operadores_logicos ){

     file_manager->initHeader();//establecer valores iniciales de un header de archivo vacío,en memoria
     file_manager->loadHeader(filename);//cargo el header del aqrchivo que quiero agregar registro
     file_manager->initSchema();//se vacia el schema en memoria
     file_manager->loadSchema();//cargo el header a memoria
     file_manager->openFile();
    //bandera que describe si existe un campo que cumpla las condiciones
     bool coincidencias= false;

     if(condiciones->getLength() > 0){
         int* accepted_rows = file_manager->where(condiciones,operadores_logicos);
         for (int i = 0 ; i< file_manager->getNumberOfRegisters();i++){
             if(accepted_rows[i] != -1){
                 //si hay una columna que cumpla las condiciones de enciende la bandera coincidencias
                 coincidencias= true;
             }
         }

     }
     //se cierra el archivo
     file_manager->closeFile();
     //retorno la bandera
     return coincidencias;
 }




