#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define SERVER_IP       "127.0.0.1"
#define RELAY_SERVER_PORT 	5000
#define ADD_SERVER_PORT 	6000
#define SUB_SERVER_PORT 	7000
#define SERVER_LENGTH 	10
#define SERVER_BUFF	20

int main()
{

    int sock_fd, data_sock_fd,buffer_len;
    struct sockaddr_in serv_addr; 
    char serv_buffer[SERVER_BUFF];
    char op;

    printf("Emertxe: Server is waiting...\n");

    /* Create a TCP socket */
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    /* Bind it to a particular IP address & port) */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serv_addr.sin_port = htons(RELAY_SERVER_PORT); 

    bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
   // printf("Emertxe: Server is bound to %s:%d\n", SERVER_IP, SERVER_PORT);

    /* listen for incoming connections */
    listen(sock_fd, SERVER_LENGTH);
   // printf("Emertxe: Server is listening for connections...\n");

    /* If there are any, accept and create a new data socket */
    data_sock_fd = accept(sock_fd, (struct sockaddr*)NULL, NULL); 

    memset(serv_buffer, 0, sizeof(serv_buffer));
    /* Try to get some actual data from client */
    recv(data_sock_fd, (void *) serv_buffer,SERVER_BUFF,0);

    /* Print the data received from client */
    //printf("Here is the client data: %s\n",serv_buffer);

    /* Extract the operator from the received data */
    if (sscanf(serv_buffer, "%c", &op) != 1) {
        fprintf(stderr, "Error: Invalid data received from client\n");
        close(data_sock_fd);
        close(sock_fd);
        return 1;
    }
    /* Send a response back to client */
    char client_buff[SERVER_BUFF];
    //memcpy(client_buff, serv_buffer, sizeof(serv_buffer));
    //strcpy(client_buff, serv_buffer);

    if(op == '+') {
        sprintf(client_buff, "%d",ADD_SERVER_PORT);
    } else if(op == '-') {
        sprintf(client_buff, "%d",SUB_SERVER_PORT);
    }/* else if(op == '*') {
        sprintf(client_buff, "Multiplication operation received");
    } else if(op == '/') {
        sprintf(client_buff, "Division operation received");
    } else {
        sprintf(client_buff, "Unknown operation received");
    }*/

    int c_size = send(data_sock_fd, client_buff, strlen(client_buff) + 1, 0);

		if(c_size > 0)
				printf("Message sent to client by RELAY successsfully, please check\n");
		else
				printf("Error: Message send\n");

    /* Close the sockets now */
    close(data_sock_fd);
    close(sock_fd);
}