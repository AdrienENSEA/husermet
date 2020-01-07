#include "Server.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

// Includes for microhttpd
#include <microhttpd.h>
#include <string.h>
#define PORT 8888

// Includes for client
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

static int answer_to_connection_test (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls)
{
    const char *page  = "<html><body>Hello, browser!</body></html>";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer (strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    MHD_destroy_response (response);

    return ret;
}

int print_out_key (void *cls, enum MHD_ValueKind kind, 
                   const char *key, const char *value)
{
  printf ("%s: %s\n", key, value);
  return MHD_YES;
}


static int answer_to_connection (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls)
{
    printf ("New %s request for %s using version %s\n", method, url, version);
    MHD_get_connection_values (connection, MHD_HEADER_KIND, &print_out_key, NULL);
    return MHD_NO;
}

namespace server {

    void Server::run () {
        struct MHD_Daemon *daemon;

        daemon = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL, &answer_to_connection_test, NULL, MHD_OPTION_END);
        cout << "Server launched on localhost port 8888" << endl << "http://localhost:8888/" << endl;
        if (NULL == daemon) cout << "Error server" << endl;
        getchar ();

        MHD_stop_daemon (daemon);
        cout << "Server done" << endl;
    }
    
    void Server::talkwith() {
        int clientSocket;
        char buffer[1024];
        struct sockaddr_in serverAddr;
        socklen_t addr_size;

        /*---- Create the socket. The three arguments are: ----*/
        /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
        clientSocket = socket(PF_INET, SOCK_STREAM, 0);

        /*---- Configure settings of the server address struct ----*/
        /* Address family = Internet */
        serverAddr.sin_family = AF_INET;
        /* Set port number, using htons function to use proper byte order */
        serverAddr.sin_port = htons(PORT);
        /* Set IP address to localhost */
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        /* Set all bits of the padding field to 0 */
        memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
        
        /*---- Connect the socket to the server using the address struct ----*/
        addr_size = sizeof serverAddr;
        connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

        /*---- Read the message from the server into the buffer ----*/
        recv(clientSocket, buffer, 1024, 0);

        /*---- Print the received message ----*/
        printf("Data received: %s",buffer); 
    }
    
    
}
