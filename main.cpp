#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sys/time.h>

using namespace std;

void error(const char* e)
{
    perror(e);
    exit(1);


}

int main()
{
    int portnum = 54000;
    // Create a socket
    // int socket(int domain, int type, int protocol)
    // AF_INET - IP v4
    // returns 0 if succesful
    // listening - file descriptor
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        error("Can't create a socket! Quitting");
    }

    // Bind the ip address and port to a socket
    struct sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_addr.s_addr = INADDR_ANY;

    //htons - host to network short
    hint.sin_port = htons(portnum);

    //inet_pton - internet command pointer to a string to a number
    //- converts the ip address from string
    //                any address   buffer - pointer
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if(bind(listening, (sockaddr*)&hint, sizeof(hint)) < 0){
        error("Bind failed");
    }

    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);





    // Wait for a connection
    struct sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if(clientSocket < 0){
        error("Accept error");
    }



    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on

    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        // ine_ntop - numerical to string
        // ntohs = network to host short
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }

    // Close listening socket
    close(listening);

    // communication between client and server


    // While loop: accept and echo message back to client
    char buf[4096];

    while (true)
    {
        //clear buffer - memset or bzero
        memset(buf, 0, 4096);

        // Wait for client to send data recv/send or read/write
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            error("Error in recv()");
        }

        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }
        string message = string(buf, 0, bytesReceived);
        cout << message << endl;

        // Echo message back t o client

        send(clientSocket, buf, bytesReceived + 1, 0);
    }

    // Close the socket
    close(clientSocket);

    return 0;
}
