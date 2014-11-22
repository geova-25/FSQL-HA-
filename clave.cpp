#include "clave.h"


/**
 * @brief constructor de la clase Nodo
 * @param
 * @return
 */
template <class T>
Clave<T>::Clave()
{
    this->elemento ;
    this->siguiente_elemento = NULL;
    this->anterior_elemento = NULL;
    this->indice = 0;

}
/**
 * @brief Destructor de Nodo
 * @param
 * @return
 */
template <class T>
Clave<T>::~Clave() {
    // TODO Auto-generated destructor stub
}

using namespace std;

/**
 * @brief Constructor con parametro de Nodo asignandole un elemento T al nodo
 * @param T ele
 * @return
 */
template <class T>
Clave<T> :: Clave(T ele)
{
    this->elemento = ele;
    this->siguiente_elemento = NULL;
}
/**
 * @brief Establece un elemento T al nodo
 * @param T nume
 * @return void
 */
template <class T>
void Clave<T>:: set_elemento(T nume)
{
    this->elemento = nume;
    return;
}
/**
 * @brief Establece el siguiente nodo de la lista
 * @param Nodo *punt
 * @return void
 */
template <class T>
void Clave<T>::set_siguiente(Clave *punt)
{
    this->siguiente_elemento = punt;
}
/**
 * @brief Establece el puntero al nodo anterior de la lista
 * @param Clave *punt
 * @return void
 */
template <class T>
void Clave<T>::set_anterior(Clave *punt)
{
    this->anterior_elemento = punt;
}

/**
 * @brief Obtiene el elemento del nodo
 * @param
 * @return T elemento
 */
template <class T>
T Clave<T> :: get_elemento()
{
    return this->elemento;
}
/**
 * @brief Obtiene el siguiente nodo de la lista a partir de algun nodo
 * @param
 * @return Clave<T>* siguiente_elemento
 */
template <class T>
Clave<T>* Clave<T> :: get_siguiente()
{
    return this->siguiente_elemento;
}
/**
 * @brief Obtiene el nodo anterior de la lista a partir de algun nodo
 * @param
 * @return Clave<T>* siguiente_elemento
 */

template <class T>
Clave<T>* Clave<T> :: get_anterior()
{
    return this->anterior_elemento;
}

/**
 * @brief Establece un indice para poder recorrer o obtener mejor un nodo de la lista
 * @param int n establece el indice en un numero especifico.
 */

template <class T>
void Clave<T> :: setIndice(int n){
    this->indice = n;
}

/**
 * @brief Establece un indice para poder recorrer o obtener mejor un nodo de la lista
 * @param int n establece el indice en un numero especifico.
 */

template <class T>
int Clave<T> :: getIndice(){
    return indice;
}

/**
 * @brief obtiene la lista void* de los hijos derechos de la clave especifica.
 * @return lista hijos derechos
 */

template <class T>
void* Clave<T> ::  getHijosDer(){
    return this->hijosDer;
}

/**
 * @brief obtiene la lista void* de los hijos izquierdos de la clave especifica.
 * @return lista hijos izquierda
 */

template <class T>
void* Clave<T> ::  getHijosIzq(){
    return this->hijosIzq;
}

/**
 * @brief establece la lista void* de los hijos derechos de la clave especifica.
 *
 */

template <class T>
void Clave<T> ::  setHijosDer(void* nuevoHijoDer){
    this->hijosDer = nuevoHijoDer;
}

/**
 * @brief establece la lista void* de los hijos izquierdos de la clave especifica.
 *
 */

template <class T>
void Clave<T> ::  setHijosIzq(void* nuevoHijoIzq){
    this->hijosIzq = nuevoHijoIzq;

}
