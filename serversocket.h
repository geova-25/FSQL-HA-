#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include"socket.h"
using namespace std;

class ServerSocket
{
public:
    ServerSocket();
    ServerSocket(int port);
    const ServerSocket& sendMessage (const string&) const;
    const ServerSocket& reciveMessage (string&) const;
    void accept (ServerSocket & );
    bool getConnectionStatus();
    bool getOutputMessageStatus();
private:
    Socket socket;
    bool connectionActivated;
    bool outPutMessageStatus;
};

#endif // SERVERSOCKET_H
