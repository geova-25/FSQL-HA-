#include "clientsocket.h"
#include "SocketException.h"

/**
 * @brief ClientSocket::ClientSocket Constructor del cliente
 * Usa los parametros para conectarse al server deseado
 * @param ip ip a la cual conectarse
 * @param port puerto al cual usar
 */
ClientSocket::ClientSocket (std::string ip, int port)
{
  if (!Socket::create()) //Se llama a la funcion crear de socket para inicializar un nuevo socket
    {//si no funciona la creacion modifica
      throw SocketException ("No se puedo crear el socket del cliente");
    }

  if (!Socket::connect(ip, port))//Se llama a la funcion connect para conectar al puerto y
    {//a la ip y si algun error ocurre el mismo programa se lo indicara al usuario
      throw SocketException ("No se le pudo hacer bind al puerto");
    }

}

/**
 * @brief ClientSocket::sendMessage Funcion para enviar mensajes por socket
 * @param s
 * @return
 */
const ClientSocket& ClientSocket::sendMessage(const std::string& outPutText) const //Funcion usada para
{//enviar mensajes atraves de los puertos una vez que ya este conectado a este
  if (!Socket::send(outPutText))//Se llama a la funcion send de la clase socket para enviarlo
    {
      throw SocketException("No se le pudo escribir al socket");
    }

  return *this;

}

/**
 * @brief ClientSocket::reciveMessage Funcion para recibir mensajes por socket
 * @param s
 * @return
 */
const ClientSocket& ClientSocket::reciveMessage(std::string& incomingText) const//Funcion usada para
{//recibir mensajes atraves de los puertos una vez que ya este conectado a este
  if ( ! Socket::recive (incomingText))//Se llama a la funcion send de la clase socket para recibirlo
    {
      throw SocketException ("No se pudo recibir el mensaje del socket");
    }

  return *this;
}
