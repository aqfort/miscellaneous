#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

#include <cstring>
#include <unistd.h>

#include <vector>
#include <future>

#include <signal.h>

#include <algorithm>

#define PORT 8080       // chat-server port
#define SIZE_BUFFER 128 // max length of username and messages

using namespace std;

// exit via "Ctrl" + "C"
class CtrlC : public exception
{
public:
    string what()
    {
        return "Server stopped...";
    }
};

struct Client
{
    int id;     // client id
    int socket; // file descriptor for client socket
};

vector<Client> clients{}; // clients list
mutex mutex_clients{};    // mutex for interaction with clients list
mutex mutex_stream{};     // mutex for synced cout

void SignalCtrlC(int signal);                          // handler: ctrl + c
void SyncedCout(const string &message, bool end_line); // guarded cout
void Broadcast(const string &message, int sender_id);  // broadcasting message
void EndConnection(int id);                            // close client connection
void ClientHandler(int socket_client, int id);         // for separate threads

int main(int argc, char **argv, char **envp)
{
    try
    {
        int socket_server{};                     // file descriptor for server socket
        int socket_client{};                     // file descriptor for client socket
        int return_recv{};                       // length of message on successful completion
        int client_id{0};                        // client id counter
        int opt{1};                              // specified socket option
        struct sockaddr_in address_server;       // structure for handling server address
        struct sockaddr_in address_client;       // structure for handling client address
        int address_length{sizeof(sockaddr_in)}; // address structure size
        vector<future<void>> futures{};          // client handler futures (async)

        // creating socket file descriptor
        if ((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            throw invalid_argument("socket_server");
        }

        // forcefully attaching socket to defined port
        if (setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            throw invalid_argument("setsockport");
        }

        address_server.sin_family = AF_INET;
        address_server.sin_addr.s_addr = INADDR_ANY;
        address_server.sin_port = htons(PORT);

        // erase and fill with '\0'
        bzero(&address_server.sin_zero, 0);

        // forcefully attaching socket to defined port
        if (bind(socket_server, (struct sockaddr *)&address_server, address_length) < 0)
        {
            throw invalid_argument("bind");
        }

        // listen with max connection queue
        if (listen(socket_server, SOMAXCONN) < 0)
        {
            throw invalid_argument("listen");
        }

        cout << "\n\tWelcome to chat-server" << endl;

        try
        {
            signal(SIGINT, SignalCtrlC);

            while (1)
            {
                // delete finished and got futures
                for (int i = 0; i < futures.size(); i++)
                {
                    if (futures[i].wait_for(chrono::seconds(0)) == future_status::ready)
                    {
                        futures.erase(futures.begin() + i);
                    }
                }

                // wait for new client
                if ((socket_client = accept(socket_server, (struct sockaddr *)&address_client, (socklen_t *)&address_length)) < 0)
                {
                    throw invalid_argument("accept");
                }

                client_id++;

                // create thread for new client
                futures.push_back(async(ClientHandler, socket_client, client_id));
                lock_guard<mutex> guard(mutex_clients);
                clients.push_back(Client{client_id, socket_client});
            }
        }
        catch (CtrlC e)
        {
            cout << endl
                 << e.what() << endl;
        }

        for (auto &&i : futures)
        {
            i.get();
        }

        // closing connected socket
        close(socket_client);

        // closing listening socket
        shutdown(socket_server, SHUT_RDWR);

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
    throw CtrlC();
}

void SyncedCout(const string &message, bool end_line = true)
{
    lock_guard<mutex> guard(mutex_stream);
    cout << message;
    if (end_line)
    {
        cout << endl;
    }
}

void Broadcast(const string &message, int sender_id)
{
    char temp[SIZE_BUFFER]{};
    strcpy(temp, message.c_str());
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].id != sender_id)
        {
            send(clients[i].socket, temp, sizeof(temp), 0);
        }
    }
}

void EndConnection(int id)
{
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].id == id)
        {
            lock_guard<mutex> guard(mutex_clients);
            close(clients[i].socket);
            clients.erase(clients.begin() + i);
            break;
        }
    }
}

void ClientHandler(int socket_client, int id)
{
    char name[SIZE_BUFFER]{};
    char message[SIZE_BUFFER]{};

    int return_recv = recv(socket_client, name, sizeof(name), 0);
    string name_string = string(name);
    name_string.erase(remove_if(name_string.begin(), name_string.end(), ::isspace), name_string.end());
    if (name_string.empty())
    {
        name_string = "Anon";
        strcpy(name, name_string.c_str());
    }
    else
    {
        name_string = string(name);
    }

    string welcome_message = name_string + " has joined";
    Broadcast("#NULL", id);
    Broadcast(welcome_message, id);
    SyncedCout(welcome_message);

    while (1)
    {
        return_recv = recv(socket_client, message, sizeof(message), 0);

        if (return_recv <= 0)
        {
            return;
        }

        if (strcmp(message, "#exit") == 0)
        {
            string message_string = name_string + " has left";
            Broadcast("#NULL", id);
            Broadcast(message_string, id);
            SyncedCout(message_string);
            EndConnection(id);
            return;
        }

        Broadcast(name_string, id);
        Broadcast(string(message), id);
        SyncedCout(name_string + " : " + string(message));
    }
}
