#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <cstdlib> // malloc() & free()
#include"arbol_b.h"

#include "fsql_manager.h"

#include "interpreteserver.h"

#include "interprete_client.h"

#include "listacircular.h"

using namespace std;



int main()
{
    /*
string texto = "nombre.int.4452.cedula.string.34";
    char cubeta [300];
    string lista[50];
    int contador=0;
    int j=0;
    for  (int i = 0 ; texto.length() ; i++){

        if(texto[i] != '.'){
            cubeta[j] = texto[i];
            j++;
        }if(texto[i] == '.'){
            lista[contador]=cubeta;
            cout<<"palabra: "<<lista[contador]<<endl;
            contador++;
            j=0;
            for(int i=0;i<300;i++){
                cubeta[i]=0;
            }
        }
    }*/

    //cout <<cubeta <<endl;

    FSQL_Manager sf ;

    sf.setDirectory("/home/sebastian/Escritorio/BaseDeDatos/");

    Interprete_Cliente* interprete_cliente = new Interprete_Cliente();


    interprete_cliente->run();











    return 0;
}

