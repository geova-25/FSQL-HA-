#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H


#include "socket.h"


class ClientSocket : private Socket
{
 public:
  ClientSocket (){}
  ClientSocket ( std::string host, int port );
  virtual ~ClientSocket(){};

  const ClientSocket& sendMessage ( const std::string& ) const;
  const ClientSocket& reciveMessage ( std::string& ) const;

};


#endif // CLIENTSOCKET_H
