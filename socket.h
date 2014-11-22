#ifndef SOCKET_H
#define SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


using namespace std;

class Socket
{
public:
    Socket();
    // Para la inicialización del server
    bool create();
    bool bind(const int port);
    bool listen() const;
    bool accept(Socket&) const;
    // Para la inicialización del cliente
    bool connect(const string host,const int port);
    // Para la transmisión de datos
    bool send(const string newString) const;
    int recive( string&) const;
    void blockThisSocket(const bool);
    bool isAValidDescriptorForTheSocket() const;
private:
    const int MAXIPNAME = 200;
    const int MAXCONNECTIONSALLOWED = 5;
    const int MAXRECIVECHARACTERSALLOWED = 500;
    int descriptorOfTheSock;
    sockaddr_in addresOfTheSocket;
};

#endif // SOCKET_H
