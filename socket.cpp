#include "socket.h"
#include <iostream>
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>


Socket::Socket():
    descriptorOfTheSock( -1)
{
    memset(&addresOfTheSocket,0,sizeof(addresOfTheSocket));

}
/**
 * @brief Socket::create crea un nuevo socket
 * usando el parametro que ya tenemos definido como un tipo SOCKET en el header hacemos una
 * abstraccion de la clase de socket que ya esta en uso en c++ para poder manejarla de una
 * manera mas sencilla por lo que en esta función se crea un nuevo socket y se activa
 * la opcion para poder conectarlo a un puerto y direccion ya en uso.
 * @return bool
 */
bool Socket :: isAValidDescriptorForTheSocket() const{
    return this->descriptorOfTheSock != 1;
}

bool Socket :: create(){
    descriptorOfTheSock = socket(AF_INET,SOCK_STREAM,0);/* Creo un nuevo socket con la funcion de la
    libreria de c++, el primer parametro es el formato de la familia de la direccion a internet
    para IPv4 el segundo es el tipo del nuevo socket.
    */

    if(! isAValidDescriptorForTheSocket()){ //verifica si el socket no es nulo
        return false;
    }
    //Para el tiempo de espera
    int on = 1;
    if(setsockopt(descriptorOfTheSock,SOL_SOCKET,SO_REUSEADDR,(const char*) &on,sizeof(on)) == -1)
        /*setsockopt permite cambiar las opciones de sockets
        SOL_SOCKET hace referencia a las opciones de protocolo independiente
        SO_REUSEADDR es la opcion para que permite conectarse a una direccion y puerto que ya
        esta en uso
        */
        return false;
    return true;
}
/**
 * @brief Socket::bind Asigna un puerto a una direccion
 * Cuando el socket esta creado pero no tiene asociasion a algun puerto se usa esta funcion para
 * tal caso al cual le entra el numero de puerto
 * @param newPort
 * @return boolean true si fue exitoso o false si fue algun error
 */
bool Socket :: bind(const int newPort){ //Asocia el socket sin union a una direccion local
    if(! isAValidDescriptorForTheSocket()) //Si el socket no es valido retorna falso
    {        
        return false;
    }
    addresOfTheSocket.sin_family = AF_INET; /*Establece que el tipo de conexion a otros socket es de
    tipo AF_INET para IPv4 o IP4*/
    addresOfTheSocket.sin_addr.s_addr = INADDR_ANY; /*Establece que el socket escuche a todas las IP
    disponibles*/
    addresOfTheSocket.sin_port = htons(newPort); /* Asigna al socket el puerto al que le entro como
    parametro y lo cambia a network byte order o orden de bytes de la red.*/
    int bind_return = ::bind(descriptorOfTheSock,(struct sockaddr*) &addresOfTheSocket,sizeof(addresOfTheSocket)); /*llama a la
    funcion bind de c++ el socket esta creado pero sin direccion esta funcion le asigna la
    direccion del segundo parametro al socket le entran los parametros de el socket, la estructura
    del socket, y la direccion en memoria de la estructura de la direccion
    */
    if(bind_return == -1){ // Si no se puede asignar retorna falso        
        return false;
    }
    return true; // si es exitoso se retorna verdadero
}
/**
 * @brief Socket::listen Se usa para escuchar o esperar que lleguen conexiones el socket
 * que lo llama indica que espera conexiones o que esta disponible para conectarse siempre
 * que no tenga el maximo de conexiones
 * @return true si el fue exitoso, false si no lo fue
 */
bool Socket::listen() const{ //Usada si se esperan peticiones de conexion a nuestra maquina
    if(!isAValidDescriptorForTheSocket()){ //si el socket es nulo no hace nada
        return false;
    }
    int listen_return = ::listen(descriptorOfTheSock,this->MAXCONNECTIONSALLOWED); /*Se llama a la funcion listen()
    de c++ para escuchar conexiones entrantes cuyos parametros son el socket que escucha por
    nuevas conexiones y el numero maximo de conexiones que se aceptan si se sobre pasa, da error*/

    if(listen_return == -1){
        return false;
    }
    return true; // verdadero es el retorno si todo es correcto
}
/**
 * @brief Socket::accept Acepta una conexion con otro socket para compartir informacion
 * @param incoming_socket socket al cual conectar
 * @return boolean true si fue exitoso, false si no lo fue
 */
bool Socket :: accept(Socket& incoming_socket) const { /*funcion usada para aceptar una conexion a
    nuestra maquina*/
    int sizeofAddress = sizeof(addresOfTheSocket); // tamaño de la direccion
    incoming_socket.descriptorOfTheSock = ::accept(descriptorOfTheSock,(sockaddr*)&addresOfTheSocket,(socklen_t*)& sizeofAddress);
    /*Se llama a la funcion
    accept() de c++ la cual recibe como parametro el socket que ya esta escuchando o esperando
    conexiones entrantes,la direccion del socket que esta escuchando, y el tamaño de la direccion
    del socket que esta escuchando y retorna un puntero a un nuevo socket que ahora esta conectado
    al descriptorOfTheSock*/
    if(incoming_socket.descriptorOfTheSock <= 0){
        return false;
    }
    else{
        return true;
    }
}
/**
 * @brief Socket::send Envia un mensaje de un socket ya conectado a otro en forma de string
 * @param outGoingString mensaje a enviar
 * @return boolean true si fue exitoso, false si no lo fue
 */
bool Socket :: send(const string outGoingString) const{
    /*Función usada para enviar un mensaje atravez de un socket que se encuentra ya conectado
    con otro*/
    int state = ::send(descriptorOfTheSock,outGoingString.c_str(),outGoingString.size(),MSG_NOSIGNAL);
    /*Se llama a send() la cual es una funcion de c++ para enviar un mensaje entre sockets de
    parametros recibe el socket que tiene las conexiones,la direccion en memoria del string a
    salir, el tamaño del  string saliente y el ultimo es la opcion para que el programa no
    termine o muera cuando se intente conectar o enviar una señal a un socket que no sigue
    conectado*/
    if(state == -1)
    {
        return false;
    }
    else{
        return true;
    }
}

/**
 * @brief Socket::recive recibe datos de otro socket y los guarda en un buffer de memoria
 * para su uso
 * @param newString string entrante atravez de otra conexion
 * @return retorna un valor numerico de representacion para saber que se realizo correctamente
|**/
int Socket :: recive(string& newString) const{ // Usada para recibir datos de otro socket
    char bufferToRecive[MAXRECIVECHARACTERSALLOWED + 1]; //buffer donde se guardara el string a recibir
    newString = "";
    memset(bufferToRecive,0,MAXRECIVECHARACTERSALLOWED + 1);/*Se le asigna en memoria un espacio al buffer donde se
    guardaran los datos*/

    int state = ::recv(descriptorOfTheSock,bufferToRecive,MAXRECIVECHARACTERSALLOWED,0);/*Hace uso de la funcion recv cuyos
    argumentos usados son primero el socket por el cuale se leeran los datos, el buffer donde
    se guardaran los datos recibidos y por ultimo la longitud maxima que se puede recibir*/
    if(state == -1){
        std::cout << "state == -1 error numero == " <<
                errno << "in Socket::recv/n";
    }
    else if(state == 0){
        return 0;
    }
    else{
        newString = bufferToRecive;
        return state;
    }
}

/**
 * @brief Socket::connect conecta el socket a un puerto especifico y a una direccion especifica
 * @param ip direccion ip a utilizar
 * @param port puerto a utilizar para la conexion
 * @return boolean true si fue exitoso, false si no lo fue
 */
bool Socket :: connect(const string ip,const int port){
    //Conecta el socket a una direccion específica
    if(!isAValidDescriptorForTheSocket()){
        return false;

    }
    addresOfTheSocket.sin_family = AF_INET;/*Establece el tipo de familia a conectar como AF_INET
    para IPv4 o IP4*/
    addresOfTheSocket.sin_port = htons(port); /*Asigna el puerto entrante a la direccion del socket y lo
    convierte al formato network */

    int state = inet_pton(AF_INET,ip.c_str(),&addresOfTheSocket.sin_addr); /* convierte una direccion ip de
    de entrada leida de la forma xxx.xx.xx.xx donde cada x es una representacion numerica en
    formato binario para ser guardado en la direccion de memoria que entra en el tercer parametro
    */        
    if(errno == EAFNOSUPPORT){
        return false;
    }
    state = ::connect ( descriptorOfTheSock, ( struct sockaddr * ) &addresOfTheSocket, sizeof ( addresOfTheSocket ) );
    if(state == 0){        
        return true;
    }
    else{
        return false;
    }
}
/**
 * @brief Socket::set_non_blocking funcion utilizada para establecer en true o en false la bandera
 * del socket que indica si esta o no esta bloqueado
 * @param boolean indica si fue exitosa la operacion o no
 */
void Socket :: blockThisSocket(const bool boolean){ /* Cuando un socket es creado esta en estado
    bloqueado,las funciones de read(),write() o en este caso send() y recive() bloquean sus
    acciones hasta que se termine el proceso, en estado de no-bloqueado entonces estas operaciones
    retornan inmediatamente todas*/
    int banderas; // Se define una variable para guardar el archivo de modos de acceso
    banderas = fcntl(descriptorOfTheSock,F_GETFL); //La funcion fcntl devuelve el archivo de las variables
    //de acceso;

    if(banderas < 0){ //Si el valor es nullo termina
        return;
    }
    if(boolean){//Si el valor de entrada pide ser cambiado a true
        banderas = (banderas | O_NONBLOCK); /*Se le aplica un OR a las banderas lo que sobre
        cualquier valor de banderas dara un true y prendera banderas, TRUE OR Lo que sea = True*/
    }
    else{ //Si mas bien la solicitud es apagar la bandera
        banderas = (banderas & ~O_NONBLOCK);/* entonces se le aplica a banderas un AND y con un
        complemento a uno a O_NONBLOCK lo que dara False*/
    }
    fcntl(descriptorOfTheSock,F_SETFL,banderas);
}


