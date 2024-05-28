#include <iostream>
#include <winsock2.h>

using namespace std;

class Client{
public:
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    char buffer[1024];
    Client()
    {
        cout<<"Conectando al servidor..."<<endl<<endl;
        WSAStartup(MAKEWORD(2,0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);
        cout << "¿Casa o Universidad?" << endl;
        char *c;
        cin >> c;
        if (c[0] == 'U' || c[0] == 'u'){

        addr.sin_addr.s_addr = inet_addr("10.207.0.46");
        }else{
            addr.sin_addr.s_addr = inet_addr("192.168.1.141");

        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(5555);
        connect(server, (SOCKADDR *)&addr, sizeof(addr));
        cout << "Conectado al Servidor!" << endl;

    }
    void Enviar()
    {
        string cadena;


        getline(cin, cadena);
        strncpy(buffer,cadena.c_str(),sizeof(buffer));
        send(server, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
    }
    void Recibir()
    {
        ssize_t bytesReceived = recv(server, buffer, sizeof(buffer), 0);
        if (bytesReceived == 0){
            cout << "Bytes recibidos son 0"<< endl;
            
        }
        else{
            for (int i = 0; i < strlen(buffer); ++i) {
                if (buffer[i] == ' '){
                    if (buffer[i+1] == ' '){
                        break;}
                    }
                cout << buffer[i];
            }
            
        memset(buffer, 0, sizeof(buffer));}
        }
    
    void CerrarSocket()
    {
       closesocket(server);
       WSACleanup();
       cout << "Socket cerrado." << endl << endl;
    }
};

int main()
{
    Client *Cliente = new Client();
    int salida = 0;
    while(salida == 0)
    {

        Cliente->Recibir();
        fflush(stdin);

        Cliente->Enviar();
    }
}
