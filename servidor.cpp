#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include "cabecera.h"

using namespace std;
using namespace containers;

int main() {
    Server *servidor = new Server();
    main2(servidor);
    
}