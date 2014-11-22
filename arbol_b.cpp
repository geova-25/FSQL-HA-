#include "arbol_b.h"
#include"nodoarbolb.h"

Arbol_B :: Arbol_B(int numero_De_Claves)
{
    nodoArbolRaiz = new NodoArbolB<int>();
    nodoArbolRaiz->inicializar();
    this->numero_Claves_De_Explote=numero_De_Claves+1;
}

/**
 * @brief Arbol_B::getRaiz
 * @return
 */
NodoArbolB<int>* Arbol_B :: getRaiz(){
    return this->nodoArbolRaiz;
}

/**
 * @brief Arbol_B::quicksort Acomoda las claves
 * @param arreglo
 * @param L
 * @param R
 *
 * Este es un metodo de ordenamiento se realiza para la primera vez que la raiz se desborda
 *  el empieza a funcianar y ordena las claves en sus respectivos nodos.
 */
void Arbol_B :: quicksort (NodoArbolB<int>* arreglo, int L, int R){
    int i,j,pivot;
    i = L;
    j = R;
    pivot = arreglo->getEspecifica((L+R)/2);
    do{
        while(arreglo->getEspecifica(i) < pivot){
            i++;
        }
        while(arreglo->getEspecifica(j) > pivot){
            j--;

        }

        if(i <=j){
            int aux = arreglo->getEspecifica(i);
            arreglo->setEspecifica(i,arreglo->getEspecifica(j));
            arreglo->setEspecifica(j,aux);
            i++;
            j--;
        }
    }
    while(i <= j);
    if (L<j){
        quicksort(arreglo,L,j);
    }
    if (i<R){
        quicksort(arreglo,i,R);
    }
}

/**
 * @brief Arbol_B::estaVacia Revisa si esta vacia
 * @return
 * Un metodo que revisa si la raiz esta vacia
 */
bool Arbol_B :: estaVacia(){
    return  nodoArbolRaiz->estaVacia();
}


/**
 * @brief Arbol_B::imprimir Imprime el arbol
 */
void Arbol_B :: imprimir(){
    imprimaArbolB(nodoArbolRaiz);
}


/**
 * @brief Arbol_B::imprimaArbolB Imprime todos los nodos del arbol b
 * @param impresa
 * Imprime paso a paso el arbol desde el nodo raiz asta el nodo hoja
 */
void Arbol_B :: imprimaArbolB(NodoArbolB<int>* impresa){
    cout << "El nodo raiz es: " << endl;
    impresa->imprimir();
    int valor;
    NodoArbolB<int>* hIzq;
    NodoArbolB<int>* hDer;
    for(Clave<int>* auxHijo = impresa->get_primeraClave(); auxHijo != NULL; auxHijo = auxHijo->get_siguiente()){
        valor = auxHijo->get_elemento();
        cout << endl;
        cout<<"la clave es: "<<valor<<endl;
        cout << endl;
        cout<<"El hijo izquierdo es"<<endl;

        hIzq = (NodoArbolB<int>*) auxHijo->getHijosIzq();
        hIzq->imprimir();
        cout << endl;
        cout<<"El hijo derecho es:"<<endl;
        hDer = (NodoArbolB<int>*) auxHijo->getHijosDer();
        hDer->imprimir();
        cout<<"....................................................................."<<endl;
        }
    if(hIzq->get_primeraClave()->getHijosIzq() != NULL){
        if(primera){
            primera = false;   // bandera para que solo imprima la parte izquierda por primera vez
            cout << ":::::::::::::::::::::::::::::::::Parte Izquierda:::::::::::::::::::::::::::::::: " << endl;
        }
        cout<<"####################################################################"<<endl;
        imprimaArbolB(hIzq);  // manera recursiva para imprimir todos los nodos izquierdos del arbol
        cout << ":::::::::::::::::::::::::::::::::Parte Derecha:::::::::::::::::::::::::::::::::: " << endl;
    }
    if(hDer->get_primeraClave()->getHijosDer() != NULL){
        imprimaArbolB(hDer); // manera recursiva para imprimir todos los nodos derechos del arbol
    }
}



/**
 * @brief Arbol_B::ingresarAlFondo ingresa asta el fondo del arbol el numero
 * @param num
 * @param nodo
 * Este metodo realiza la operacion de ingresar el valor en el nodo correspondiente no importa si este nodo
 * tiene una profundidad muy grande.
 */
void Arbol_B :: ingresarAlFondo(int num, NodoArbolB<int>* nodo){
    for(Clave<int>* auxClaveNodoRaiz = nodo->get_primeraClave(); auxClaveNodoRaiz != NULL;
        auxClaveNodoRaiz = auxClaveNodoRaiz->get_siguiente()){
        NodoArbolB<int>* izq = (NodoArbolB<int>*) auxClaveNodoRaiz->getHijosIzq();
        NodoArbolB<int>* der = (NodoArbolB<int>*) auxClaveNodoRaiz->getHijosDer();
        if(auxClaveNodoRaiz == nodo->get_primeraClave() && auxClaveNodoRaiz->get_elemento() > num){
            if(auxClaveNodoRaiz->getHijosIzq() != NULL){
                ingresarAlFondo(num,izq);
                break;
            }
            else{
                nodo->agregarAlFinal(num);
                quicksort(nodo,0,nodo->getSize()-1);
            }
        }
        else if(auxClaveNodoRaiz == nodo->get_ultimaClave()){
            if(auxClaveNodoRaiz->get_elemento() < num){
                if(auxClaveNodoRaiz->getHijosDer() != NULL){
                    ingresarAlFondo(num,der);
                    break;
                }
                else{
                    nodo->agregarAlFinal(num);
                    quicksort(nodo,0,nodo->getSize()-1);
                }
            }
            else{
                if(auxClaveNodoRaiz->getHijosIzq() != NULL){
                    ingresarAlFondo(num,izq);
                    break;
                }
                else{
                    nodo->agregarAlFinal(num);
                    quicksort(nodo,0,nodo->getSize()-1);
                }
            }
        }
        else if(auxClaveNodoRaiz->get_elemento() < num && auxClaveNodoRaiz->get_siguiente()->get_elemento()
                >=  num){
            if(auxClaveNodoRaiz->getHijosDer() != NULL){
                ingresarAlFondo(num,der);
                break;
            }
            else{
                nodo->agregarAlFinal(num);
                quicksort(nodo,0,nodo->getSize()-1);
            }
        }
    }
}


/**
 * @brief Arbol_B::ingresarNuevo ingresa el numero
 * @param numeNuevo
 * Este metodo ingresa el numero despues de haber reventado la raiz por primera vez, lo ingresa directo a donde
 * corresponde
 */
void Arbol_B :: ingresarNuevo(int numeNuevo){
    if(explotoRaiz){
        ingresarAlFondo(numeNuevo,nodoArbolRaiz);
    }
    else{
        for(Clave<int>* auxClaveNodoRaiz = nodoArbolRaiz->get_primeraClave(); auxClaveNodoRaiz != NULL;
            auxClaveNodoRaiz = auxClaveNodoRaiz->get_siguiente()){
            NodoArbolB<int>* hijoIzquieroDeLaClave = (NodoArbolB<int>*)auxClaveNodoRaiz->getHijosIzq();
            NodoArbolB<int>* hijoDerechoDeLaClave = (NodoArbolB<int>*)auxClaveNodoRaiz->getHijosDer();
            if(auxClaveNodoRaiz->get_elemento() > numeNuevo){
                hijoIzquieroDeLaClave->agregarAlFinal(numeNuevo);
                quicksort(hijoIzquieroDeLaClave, 0 ,hijoIzquieroDeLaClave->getSize()-1);
                break;
            }
            else if(auxClaveNodoRaiz->get_siguiente() != NULL){
                if(auxClaveNodoRaiz->get_elemento() < numeNuevo && auxClaveNodoRaiz->get_siguiente()->get_elemento()
                    >=  numeNuevo ){
                    hijoDerechoDeLaClave->agregarAlFinal(numeNuevo);
                    quicksort(hijoDerechoDeLaClave, 0 ,hijoDerechoDeLaClave->getSize()-1);
                    break;
                }
            }
            else{
                hijoDerechoDeLaClave->agregarAlFinal(numeNuevo);
                quicksort(hijoDerechoDeLaClave,0,hijoDerechoDeLaClave->getSize()-1);
                break;
            }
        }
    }
}


/**
 * @brief Arbol_B::acomodarHijos Acomoda hijos
 * @param clave
 * @param ind
 * Este metodo es el utilizado para seguir un orden el cual al seguir este orden se tiene que ejecutar para que
 * acomoden cada uno de los hijos.
 */
void Arbol_B :: acomodarHijos(NodoArbolB<int>* clave,int ind){
    NodoArbolB<int>* n2 = (NodoArbolB<int>*)clave->get_primeraClave()->getHijosIzq();
    NodoArbolB<int>* n4 = (NodoArbolB<int>*)clave->get_primeraClave()->getHijosDer();
    for(int x = 0; x != clave->getSize(); x++){
        if(x < ind){
            n2->agregarAlFinal(clave->getEspecifica(x));
            clave->get_primeraClave()->setHijosIzq(n2);
        }
        if(x > ind){
            n4->agregarAlFinal(clave->getEspecifica(x));
            clave->get_primeraClave()->setHijosDer(n4);
        }
    }
}


/**
 * @brief Arbol_B::dividaRaiz Divide la raiz
 * Este metodo se encarga de dividir la raiz la primera vez que revienta para asi tener un mejor control de ella para el
 * manejo de informacion
 */
void Arbol_B :: dividaRaiz(){
    cout << "Clave ordenada: " << endl;
    nodoArbolRaiz->imprimir();
    NodoArbolB<int>* hijosIzq = (NodoArbolB<int>*) malloc(sizeof(NodoArbolB<int>));
    NodoArbolB<int>* hijosDer = (NodoArbolB<int>*) malloc(sizeof(NodoArbolB<int>));
    nodoArbolRaiz->get_primeraClave()->setHijosDer(hijosDer);
    nodoArbolRaiz->get_primeraClave()->setHijosIzq(hijosIzq);
    int valorMitad =  nodoArbolRaiz->getEspecifica( nodoArbolRaiz->getSize()/2);
    acomodarHijos( nodoArbolRaiz, nodoArbolRaiz->getSize()/2);
    Clave<int>* aux = nodoArbolRaiz->get_primeraClave();
    nodoArbolRaiz->vaciar();
    nodoArbolRaiz->agregarAlFinal(valorMitad);
    nodoArbolRaiz->get_primeraClave()->setHijosDer(aux->getHijosDer());
    nodoArbolRaiz->get_primeraClave()->setHijosIzq(aux->getHijosIzq());
    cout << "-------------------------------------o------------------------------------------" << endl;
}


/**
 * @brief Arbol_B::burbuja Ordenamiento
 * @param arreglo
 * El metodo de ordenamiento de burbuja se encarga de ordenar cada clave donde le corresponde cada vez que un nodo se
 * parte en dos y este se agrega al padre;
 */

void Arbol_B :: burbuja(NodoArbolB<int>* arreglo){
    int temp;
    void* hijoIzq;
    void* hijoDer;
    void* hijoIzq1;
    void* hijoDer1;
    for(Clave<int>* auxHijo1 = arreglo->get_primeraClave()->get_siguiente();
        auxHijo1 != NULL; auxHijo1 = auxHijo1->get_siguiente()){
        for(Clave<int>* auxHijo2 = arreglo->get_primeraClave();
            auxHijo2 != arreglo->get_ultimaClave(); auxHijo2 = auxHijo2->get_siguiente()){
            if (auxHijo2->get_elemento() > auxHijo2->get_siguiente()->get_elemento()){
                hijoIzq = auxHijo2->getHijosIzq();
                hijoDer = auxHijo2->getHijosDer();
                hijoIzq1 = auxHijo2->get_siguiente()->getHijosIzq();
                hijoDer1 = auxHijo2->get_siguiente()->getHijosDer();
                temp = auxHijo2->get_elemento();
                auxHijo2->set_elemento(auxHijo2->get_siguiente()->get_elemento());
                auxHijo2->setHijosIzq(hijoIzq1);
                auxHijo2->setHijosDer(hijoDer1);
                auxHijo2->get_siguiente()->set_elemento(temp);
                auxHijo2->get_siguiente()->setHijosDer(hijoDer);
                auxHijo2->get_siguiente()->setHijosIzq(hijoIzq);
            }

        }
    }
}


/**
 * @brief Arbol_B::revisar_Demas Revisa si se desvorda
 * @param nodo
 * Este metodo el uno de los mas importantes ya que con este revisa si hay desvorde si el mismo existe en un determinado
 * nodo lo parte y los acomoda donde corresponde de la manera mas optima posible
 */
void Arbol_B :: revisar_Demas(NodoArbolB<int>* nodo){
    NodoArbolB<int>* hIzq = new NodoArbolB<int>();
    NodoArbolB<int>* hDer = new NodoArbolB<int>();
    NodoArbolB<int>* temp = new NodoArbolB<int>();
    for(Clave<int>* temporal = nodo->get_primeraClave(); temporal != NULL;
        temporal = temporal->get_siguiente()){
        hDer = (NodoArbolB<int>*) temporal->getHijosDer();
        hIzq = (NodoArbolB<int>*) temporal->getHijosIzq();
        if(hDer->getNumeroDeClaves()==numero_Claves_De_Explote){
            cout<<"entro derecha"<<endl;
            NodoArbolB<int>* nuevoIzq = new NodoArbolB<int>();
            NodoArbolB<int>* nuevoDer = new NodoArbolB<int>();
            Clave<int>* auxMitadNodoRaiz = new Clave<int>(hDer->getEspecifica(hDer->getSize()/2));
            for(Clave<int>* temporal = hDer->get_primeraClave(); temporal != NULL;
                temporal = temporal->get_siguiente()){
                int valor = hDer->getEspecifica(hDer->getSize()/2);

                if(temporal->get_elemento() < valor){
                    nuevoIzq->agregarClaveAlFinal(temporal);
                    cout << "Izq: " << endl;
                }
                else if(temporal->get_elemento() > valor){
                    nuevoDer->agregarClaveAlFinal(temporal);
                    cout << "Der: " << endl;
                }
            }
            nuevoIzq->get_ultimaClave()->set_siguiente(NULL);
            nuevoDer->get_primeraClave()->set_anterior(NULL);
            nodo->agregarClaveAlFinal(auxMitadNodoRaiz);
            for(Clave<int>* temporal = nodo->get_primeraClave(); temporal != NULL;
                temporal = temporal->get_siguiente()){
                if(temporal->get_elemento()==auxMitadNodoRaiz->get_elemento()){
                    temporal->setHijosDer(nuevoDer);
                    temporal->setHijosIzq(nuevoIzq);
                    if(temporal->get_anterior()!=NULL){
                        temporal->get_anterior()->setHijosDer(nuevoIzq);
                    }
                    if(temporal->get_siguiente()!=NULL){
                        temporal->get_siguiente()->setHijosIzq(nuevoDer);
                    }
                }
            }
            burbuja(nodo);
        }
        else if (hIzq->getNumeroDeClaves()==numero_Claves_De_Explote) {
            cout<<"entro Izquierda"<<endl;
            NodoArbolB<int>* nuevoIzq = new NodoArbolB<int>();
            NodoArbolB<int>* nuevoDer = new NodoArbolB<int>();
            Clave<int>* auxMitadNodoRaiz = new Clave<int>(hIzq->getEspecifica(hIzq->getSize()/2));
            for(Clave<int>* temporal = hIzq->get_primeraClave(); temporal != NULL;
                temporal = temporal->get_siguiente()){
                int valor = hIzq->getEspecifica(hIzq->getSize()/2);

                if(temporal->get_elemento() < valor){
                    nuevoIzq->agregarClaveAlFinal(temporal);
                    cout << "Izq: " << endl;
                }
                else if(temporal->get_elemento() > valor){
                    nuevoDer->agregarClaveAlFinal(temporal);
                    cout << "Der: " << endl;
                }
            }
            nuevoIzq->get_ultimaClave()->set_siguiente(NULL);
            nuevoDer->get_ultimaClave()->set_siguiente(NULL);
            nodo->get_primeraClave()->setHijosIzq(nuevoDer);
            nodo->agregarClaveAlFinal(auxMitadNodoRaiz);
            for(Clave<int>* temporal = nodo->get_primeraClave(); temporal != NULL;
                temporal = temporal->get_siguiente()){
                if(temporal->get_elemento()==auxMitadNodoRaiz->get_elemento()){
                    temporal->setHijosDer(nuevoDer);
                    temporal->setHijosIzq(nuevoIzq);
                }
            }
            burbuja(nodo);
        }
        if (hIzq->get_primeraClave()->getHijosIzq()!=NULL){
            revisar_Demas(hIzq);
            cout<<"esto entro bien izquierda"<<endl;
        }
        if(hDer->get_primeraClave()->getHijosDer()!=NULL){
            revisar_Demas(hDer);
            cout<<"esto entro bien derecha"<<endl;
        }
        cout<<"esto entro bien en todo lado"<<endl;
    }
}


/**
 * @brief Arbol_B::verificarDesbordeDeNodos verifica si la raiz se produce un segundo desvorde
 * Este metodo se utiliza cuando hay un segundo desvorde en la raiz y si fuera el caso de que no exista llama a revisa_Demas
 * para ver si otro nodo diferente a la raiz esta desvordado y si asi lo es lo ejecuta
 */
void Arbol_B :: verificarDesbordeDeNodos(){
    if(nodoArbolRaiz->getNumeroDeClaves() == numero_Claves_De_Explote){
        explotoRaiz = true;
        cout << "Se desbordo la raiz :O" << endl;
        NodoArbolB<int>* nuevoHijoRaizIzq = new NodoArbolB<int>();
        NodoArbolB<int>* nuevoHijoRaizDer = new NodoArbolB<int>();
        Clave<int>* auxMitadNodoRaiz = new Clave<int>(nodoArbolRaiz->getEspecifica(nodoArbolRaiz->getSize()/2));
        nodoArbolRaiz->imprimir();
        for(Clave<int>* temporal = nodoArbolRaiz->get_primeraClave(); temporal != NULL;
            temporal = temporal->get_siguiente()){
            int valor = nodoArbolRaiz->getEspecifica(nodoArbolRaiz->getSize()/2);
            if(temporal->get_elemento() < valor){
                nuevoHijoRaizIzq->agregarClaveAlFinal(temporal);
                cout << "Izq: " << endl;
            }
            else if(temporal->get_elemento() > valor){
                nuevoHijoRaizDer->agregarClaveAlFinal(temporal);
                cout << "Der: " << endl;
            }
        }
        nuevoHijoRaizIzq->get_ultimaClave()->set_siguiente(NULL);
        nuevoHijoRaizDer->get_ultimaClave()->set_siguiente(NULL);
        nuevoHijoRaizIzq->imprimir();
        nuevoHijoRaizDer->imprimir();
        NodoArbolB<int>* nodo= new NodoArbolB<int>();
        nodo->agregarClaveAlFinal(auxMitadNodoRaiz);
        nodoArbolRaiz=nodo;
        nodoArbolRaiz->get_primeraClave()->setHijosDer(nuevoHijoRaizDer);
        nodoArbolRaiz->get_primeraClave()->setHijosIzq(nuevoHijoRaizIzq);
        NodoArbolB<int>* prueba = (NodoArbolB<int>*) nodoArbolRaiz->get_primeraClave()->getHijosIzq();
        cout<<"hijos"<<endl;
        NodoArbolB<int>* p = (NodoArbolB<int>*) prueba->get_primeraClave()->getHijosIzq();
        p->imprimir();
    }
    else{
        revisar_Demas(nodoArbolRaiz);
    }
}


/**
 * @brief Arbol_B::ingresarDato Administra la insercion
 * @param num
 * Este metodo maneja la insercion de datos para asi saber si la raiz se devorda por primera vez o si ya se devordo y se esta
 * desvordando otro nodo entonces lo revisa lo parte y asigna donde corresponde
 */
void  Arbol_B :: ingresarDato(int num){
    if (explote){
        ingresarNuevo(num);
        verificarDesbordeDeNodos();
        cout<<"\n"<<"\n"<<"\n"<<endl;
        cout << "-------------------------------------o------------------------------------------" << endl;
    }
    else if (nodoArbolRaiz->getNumeroDeClaves() == 4 && !explote){
        explote = true;
        nodoArbolRaiz->agregarAlFinal(num);
        quicksort( nodoArbolRaiz, 0 ,  nodoArbolRaiz->getSize()-1);
        dividaRaiz();
    }
    else{
         nodoArbolRaiz->agregarAlFinal(num);
    }
}
