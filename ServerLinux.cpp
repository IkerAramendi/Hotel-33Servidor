#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cerrno>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int main(void) 
{
    int iResult;
    int ListenSocket = -1;
    int ClientSocket = -1;

    struct addrinfo hints, *result, *ptr;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize the addrinfo structure
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE; // Use my IP

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        return 1;
    }

    // Create a SOCKET for connecting to server
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        ListenSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ListenSocket == -1) {
            printf("socket failed with error: %d\n", errno);
            continue;
        }

        // Setup the TCP listening socket
        iResult = bind(ListenSocket, ptr->ai_addr, ptr->ai_addrlen);
        if (iResult == -1) {
            printf("bind failed with error: %d\n", errno);
            close(ListenSocket);
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ptr == NULL) {
        printf("Unable to bind to any address\n");
        return 1;
    }

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == -1) {
        printf("listen failed with error: %d\n", errno);
        close(ListenSocket);
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == -1) {
        printf("accept failed with error: %d\n", errno);
        close(ListenSocket);
        return 1;
    }

    // No longer need server socket
    close(ListenSocket);

    // Receive until the peer shuts down the connection
    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == -1) {
                printf("send failed with error: %d\n", errno);
                close(ClientSocket);
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", errno);
            close(ClientSocket);
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SHUT_WR);
    if (iResult == -1) {
        printf("shutdown failed with error: %d\n", errno);
        close(ClientSocket);
        return 1;
    }

    // cleanup
    close(ClientSocket);

    return 0;
}