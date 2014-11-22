#include "serversocket.h"
#include "SocketException.h"

/**
 * @brief ServerSocket::ServerSocket
 * Constructor de la clase ServerSocket
 */
ServerSocket::ServerSocket()
{
    this->connectionActivated = true;
    this->outPutMessageStatus = true;
}


/**
 * @brief ServerSocket::ServerSocket Constructor de la clase del server
 * @param port //Puerto por el cual se van a estar conectando los demas
 */
ServerSocket :: ServerSocket ( int port )//Le entra el puerto al cual conectarse de parametro
{
  if ( ! this->socket.create() ) //Se crea un socket nuevo para manejar el server y los datos
    {
      throw SocketException ( "No se pudo crear un nuevo socket" );
    }

  if ( ! this->socket.bind ( port ) ) //Se intenta conectar con el puerto que le entro
    {
      throw SocketException ( "No se pudo usar bin al puerto" );
    }

  if ( ! this->socket.listen() )//Entra en estado de escucha para recibir mas puertos o conexiones
    {
      throw SocketException ( "No se pudo escuchar al socket" );
    }

}

/**
 * @brief ServerSocket::sendMessage
 * @param s
 * Funcion que se usa cuando el socket debe enviar un mensaje
 */
const ServerSocket& ServerSocket::sendMessage(const std::string& s) const//Funcion usada para
{//enviar mensajes atraves de los puertos una vez que ya este conectado a este
  if ( ! this->socket.send ( s ) )
    {
      throw SocketException ( "No se pudo enviar mensaje al socket" );
    }

  return *this;

}

/**
 * @brief ServerSocket::reciveMessage
 * @param s
 * @return
 * Funcion utilizada para saber cuando el socket debe esperar un mensaje
 */
const ServerSocket& ServerSocket::reciveMessage( std::string& s ) const //Funcion usada para
{//recibir mensajes atraves de los puertos una vez que ya este conectado a este
  if ( ! this->socket.recive ( s ) )
    {
      throw SocketException ( "No se pudo recibir el mensaje del soket" );
    }

  return *this;
}

/**
 * @brief ServerSocket::accept
 * @param sock
 * Funcion para conectar con el server otro socket
 */
void ServerSocket::accept ( ServerSocket& sock ) // Funcion que se usa para cuando un nuevo socket
{//intenta hacer conexion con el server
  if ( ! this->socket.accept(sock.socket))//se llama a la funcion de la clase socket accept
    {//para conectar los puertos
      throw SocketException ( "No se pudo aceptar el socket" );
    }
}

/**
 * @brief ServerSocket::getConnectionStatus
 * @return connectionActivated
 * Devuelve un boolean que nos dice si la coneccion esta activa para el server en el momento
 * solicitado
 */
bool ServerSocket ::getConnectionStatus(){
    return this->connectionActivated;
}

/**
 * @brief ServerSocket::getOutputMessageStatus
 * @return outPutMessageStatus
 * Devuelve un boolean que indica si la conexion para enviar un message sigue activa o no
 */
bool ServerSocket::getOutputMessageStatus(){
    return this->outPutMessageStatus;
}
