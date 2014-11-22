#ifndef FSQL_MANAGER_H
#define FSQL_MANAGER_H



#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "register.h"
#include "filemanager.h"
#include "registermanager.h"


using namespace std;

class FSQL_Manager
{
public:
    FSQL_Manager();


    int logic();
    bool createTable(const char* filename, Vector3d<const char*, const char*,const char*>*  );

    bool insertInto(const char* filename, VectorRelacional<const char*, const char*>*  args  ) ;
    bool update(const char* filename,  Vector3d<const char*, const char*,const char*>* , VectorRelacional<const char*,int>* operadores_logicos,
                VectorRelacional<const char*,const char*>*);
    bool Select(const char* filename,  Vector3d<const char*, const char*,const char*>* , VectorRelacional<const char*,int>*
                , VectorRelacional<const char*,int>* operadores_logicos);
    bool Select_asterisco(const char* filename);
    bool DeleteFrom(const char* filename,  Vector3d<const char*, const char*,const char*>*condiciones
                                    , VectorRelacional<const char*,int>* operadores_logicos);

    void setDirectory( const char* );

    bool createFile_Users_And_Permissions();
    bool create_user(const char* usuario, const char* contrasenia);
    bool drop_user(const char* usuario);
    bool grant(const char* permiso , const char* nombre_archivo, const char* user);
    bool revoke(const char* permiso , const char* nombre_archivo, const char* user);

    bool isThereField(const char* filename,  Vector3d<const char*, const char*,const char*>*condiciones
                                , VectorRelacional<const char*,int>* operadores_logicos );


private:
    const char* directorioDe_fsql="/home/sebastian/Escritorio/"; // se inicializa

    FileManager* file_manager = new FileManager();
    RegisterManager register_manager;

    const char* Nombre_Archivo_usuario = "users";
    const char* Nombre_archivo_permisos = "permissions";
    const char* permiso_negativo= "0";
    const char* permiso_positivo= "1";


};

#endif // FSQL_MANAGER_H
