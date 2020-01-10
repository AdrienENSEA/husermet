#include "Server.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

// Includes for microhttpd
#include <microhttpd.h>
#include <string.h>
#define PORT 8080 
#define MAXLINE 1024

// Includes for client
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SOCKET_ERROR -1

using namespace std;
class Request {
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request() {
        if (pp) MHD_destroy_post_processor (pp);
    }
};
static int
main_handler (void *cls,      
          struct MHD_Connection *connection,
          const char *url, // 
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr) 
{
    // Données pour une requête (en plusieurs appels à cette fonction)
    Request *request = (Request*)*ptr;

    // Premier appel pour cette requête
    if (!request) { 
        request = new Request();
        if (!request) {
            return MHD_NO;
        }
        *ptr = request;

        return MHD_YES;
    }    
    
    // Cas où il faut récupérer les données envoyés par l'utilisateur
    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
     || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
        if (*upload_data_size != 0) {
            request->data = upload_data;
            *upload_data_size = 0;
            return MHD_YES;
        }    
    }
    return 0;
}
/*
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
*/

int print_out_key (void *cls, enum MHD_ValueKind kind, 
                   const char *key, const char *value)
{
  printf ("%s: %s\n", key, value);
  return MHD_YES;
}

/*
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
*/

namespace server {

    void Server::run () {
        struct MHD_Daemon *daemon;

        daemon = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL, &main_handler, NULL, MHD_OPTION_END);
        cout << "Server launched on localhost port " + to_string(PORT) << endl << "http://localhost:" + to_string(PORT) + "/" << endl;
        if (NULL == daemon) cout << "Error server" << endl;
        getchar ();

        MHD_stop_daemon (daemon);
        cout << "Server done" << endl;
    }
    
    void Server::talkwith() {
        int sockfd; 
        //char buffer[MAXLINE]; 
        const char* hello = "GET /dontcare HTTP/1.1 \0"; 
        struct sockaddr_in     servaddr; 

        // Creating socket file descriptor 
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 

        memset(&servaddr, 0, sizeof(servaddr)); 
          
        // Filling server information 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_port = htons(PORT); 
        servaddr.sin_addr.s_addr = INADDR_LOOPBACK; //INADDR_ANY all local interfaces; 
        
        if (connect(sockfd, (sockaddr *) &servaddr, sizeof(sockaddr)) == SOCKET_ERROR) {
            perror("Connection to server failed");
            exit(errno);
        }
        
        //int n;
        //socklen_t len; 
        int succes;
        succes=send(sockfd, (const char *)hello, strlen(hello), 
            MSG_CONFIRM); 
        printf("Hello message sent.\n"); 
        cout <<succes;
        /*
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, (struct sockaddr *) &servaddr, 
                    &len); 
        buffer[n] = '\0'; 
        printf("Server : %s\n", buffer); 
        */
        close(sockfd);
}
}
