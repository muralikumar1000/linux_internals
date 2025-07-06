#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define SERVER_IP_ADDRESS 	"127.0.0.1"
#define RELAY_SERVER_PORT    5000
#define CLIENT_BUFF_SIZE	20

int main()
{
		int sock_fd,c_size;
		char client_buff[CLIENT_BUFF_SIZE];
		struct sockaddr_in serv_addr;
        int num1, num2;
        char op;
        printf("Enter two numbers and an operator (e.g., 5 3 +):\n");
        scanf("%d %d %c", &num1, &num2, &op);

		/* Create a client socket */
		if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
				printf("Error: Could not create socket\n");
				return 1;
		} 

		/* Populate it with server's address details */
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(RELAY_SERVER_PORT); 
		serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);

		
		/* Get the message from client */
        sprintf(client_buff, "%c", op);
		if(connect(sock_fd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) != 0)
		{
				perror("connect");
				printf("Error connecting to server\n");
				close(sock_fd);
				exit(1);
		}
		else
				printf("Connection successful\n");

		/* Send the message to relay server */
		c_size = send(sock_fd, client_buff, strlen(client_buff) + 1, 0);

		if(c_size > 0)
				printf("Message sent to relay server successsfully, please check\n");
		else
				printf("Error: Message send\n");
////////////////////////////////////////////////////////////////////////////////////////////////////////

        /* Receive the response from server */
        char relay_serv_buffer[CLIENT_BUFF_SIZE];
        memset(relay_serv_buffer, 0, sizeof(relay_serv_buffer));
        c_size = recv(sock_fd, (void *) relay_serv_buffer, CLIENT_BUFF_SIZE, 0);   
        close(sock_fd);

        /* Extract the port number from the received data */
        if (c_size <= 0) {
            fprintf(stderr, "Error: No data received from server\n");
            return 1;
        }
        int port_number;
        if (sscanf(relay_serv_buffer, "%d",&port_number) != 1) {
            fprintf(stderr, "Error: Invalid port number received from server\n");
            return 1;
        }
        serv_addr.sin_port = htons(port_number);

       

        // Create a new socket for the addition server
        if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
				printf("Error: Could not create addition server socket\n");
				return 1;
		}

        if(connect(sock_fd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) != 0)
		{
				perror("connect");
				printf("Error connecting to server\n");
				close(sock_fd);
				exit(1);
		}
		else
				printf("Connection successful\n");

        /* Send the message to server */
        memset(client_buff, 0, sizeof(client_buff));
        sprintf(client_buff, "%d %d", num1, num2);
		c_size = send(sock_fd, client_buff, strlen(client_buff) + 1, 0);

		if(c_size > 0)
				printf("Message sent to arthematic server successsfully, please check\n");
		else
				printf("Error: Message send\n");

        /* Receive the response from arthematic server */
        memset(relay_serv_buffer, 0, sizeof(relay_serv_buffer));
        c_size = recv(sock_fd, (void *) relay_serv_buffer, CLIENT_BUFF_SIZE, 0);   
        close(sock_fd);

        if (c_size <= 0) {
            fprintf(stderr, "Error: No data received from server\n");
            return 1;
        }

        /* Print the result received from server */
        int result;
        sscanf(relay_serv_buffer, "%d", &result);
        printf("Result from server: %d\n",result);
        //printf("%s", relay_serv_buffer);

}