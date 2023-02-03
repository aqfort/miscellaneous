#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

#include <cstring>
#include <unistd.h>

#include <vector>
#include <future>

#include <signal.h>

#define PORT 8080       // chat-server port
#define SIZE_BUFFER 128 // max length of username and messages

using namespace std;

// exit via "Ctrl" + "C"
class CtrlC : public exception
{
public:
    string what()
    {
        return "Press Enter...";
    }
};

bool exit_flag{false}; // flag for exit
int socket_server{};   // file descriptor for server socket
int socket_client{};   // file descriptor for client socket

void SignalCtrlC(int signal); // handler: ctrl + c
void EraseText(int count);    // clean up line from "You : "
void SendMessage();           // for sending thread
void RecvMessage();           // for receiving thread

int main()
{
    try
    {
        struct sockaddr_in address_client; // structure for handling client address
        char name[SIZE_BUFFER]{};          // message buffer
        future<void> f1;
        future<void> f2;

        if ((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            throw invalid_argument("socket_server");
        }

        address_client.sin_family = AF_INET;
        address_client.sin_addr.s_addr = INADDR_ANY;
        address_client.sin_port = htons(PORT);

        bzero(&address_client.sin_zero, 0);

        if (socket_client = connect(socket_server, (struct sockaddr *)&address_client, sizeof(address_client)) < 0)
        {
            throw invalid_argument("connect");
        }

        signal(SIGINT, SignalCtrlC);

        cout << "Enter your name : ";
        cin.getline(name, SIZE_BUFFER);
        send(socket_server, name, sizeof(name), 0);

        cout << "\n\tWelcome to chat-client" << endl;

        f1 = async(RecvMessage);
        f2 = async(SendMessage);

        try
        {
            f1.get();
            f2.get();
        }
        catch (CtrlC e)
        {
            cout << endl
                 << e.what();
        }

        close(socket_client);

        cout << endl;
    }
    catch (const exception &my_exception)
    {
        cerr << my_exception.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void SignalCtrlC(int signal)
{
    char message[SIZE_BUFFER]{"#exit"};
    exit_flag = true;
    send(socket_server, message, sizeof(message), 0);
    close(socket_client);
    throw CtrlC();
}

void EraseText(int count)
{
    int i{};
    char back_space{'\b'};
    for (i = 0; i < count; i++)
    {
        cout << back_space;
    }
    for (i = 0; i < count; i++)
    {
        cout << ' ';
    }
    for (i = 0; i < count; i++)
    {
        cout << back_space;
    }
}

void SendMessage()
{
    while (1)
    {
        if (exit_flag)
        {
            return;
        }

        cout << "You : ";
        char message[SIZE_BUFFER];
        cin.getline(message, SIZE_BUFFER);
        send(socket_server, message, sizeof(message), 0);

        if (strcmp(message, "#exit") == 0)
        {
            exit_flag = true;
            close(socket_client);
            return;
        }
    }
}

void RecvMessage()
{
    while (1)
    {
        if (exit_flag)
        {
            return;
        }

        char name[SIZE_BUFFER], message[SIZE_BUFFER];

        if (recv(socket_server, name, sizeof(name), 0) <= 0)
        {
            continue;
        }

        recv(socket_server, message, sizeof(message), 0);

        EraseText(sizeof("You : "));

        if (strcmp(name, "#NULL") != 0)
        {
            cout << name << " : " << message << endl;
        }
        else
        {
            cout << message << endl;
        }

        cout << "You : ";
        fflush(stdout);
    }
}
