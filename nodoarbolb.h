#ifndef NODOARBOLB_H
#define NODOARBOLB_H

#include "clave.h"
#include "clave.cpp"



#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include <stdlib.h>
#include <string>
using std::string;

template <class T> class NodoArbolB {
public:
    NodoArbolB(int);
    NodoArbolB();
    virtual ~NodoArbolB();
    NodoArbolB<void*>* getHijosDer();
    NodoArbolB<void*>* getHijosIzq();
    int getNumeroDeClaves();
    void ingresarHijosIzq(NodoArbolB<T>*);
    void ingresarHijosDer(NodoArbolB<T>*);
    void setEspecifica(int, T);
    void inicializar();
    void imprimir();
    void agregarAlFrente(T p );
    void eliminarDelFrente();
    void eliminarDelFinal();
    void agregarAlFinal(T num);
    void agregarClaveAlFinal(Clave<T>*);
    void vaciar();
    int getSize();
    bool estaVacia();
    void* getNodoPadre();
    void setNodoPadre(void*); 
    T getEspecifica(int);
    Clave<T>* get_primeraClave();
    Clave<T>* get_ultimaClave();


protected:
    void* nodoPadre;
    int counter;
    int counterIndice;
    Clave<T>* primerNodo;
    Clave<T>* ultimoNodo;


};

#endif // NODOARBOLB_H
