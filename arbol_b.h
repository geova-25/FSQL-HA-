#ifndef ARBOL_B_H
#define ARBOL_B_H

#include "nodoarbolb.h"
#include "nodoarbolb.cpp"
class Arbol_B
{
public:    
    Arbol_B(int);
    void quicksort(NodoArbolB<int>*, int, int);
    void burbuja(NodoArbolB<int>*);
    bool estaVacia();
    void imprimaArbolB(NodoArbolB<int>*);
    void ingresarAlFondo(int, NodoArbolB<int>*);
    void ingresarNuevo(int);
    void acomodarHijos(NodoArbolB<int>*, int);
    void dividaRaiz();
    void guardarHijosEnLista(NodoArbolB<int>*);
    NodoArbolB<int>** guardar_Nodos(NodoArbolB<int>*);
    void revisar_Demas(NodoArbolB<int>*);
    void verificarDesbordeDeNodos();
    void ingresarDato(int);
    void imprimir();
    NodoArbolB<int>* getRaiz();
private:
        NodoArbolB<int>*nodoArbolRaiz;
        NodoArbolB<int>* lista[30];
        bool explote = false;
        bool explotoRaiz = false;
        bool primera = true;
        int numero_Claves_De_Explote;
};

#endif // ARBOL_B_H
