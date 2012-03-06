#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int 
main (int argc, char *argv[])
{
	int port,clientsockfd,n;
	struct hostent *server;
    struct sockaddr_in serv_addr;
    char * buffer;
	
    if (argc != 2)
    {
      fprintf (stderr, "Usage: %s [port]\n", argv[0]);
      exit (EXIT_FAILURE);
    }
	// server port
    port = atoi(argv[1]);
    
    // create socket for client
    clientsockfd = socket(AF_INET, SOCK_STREAM, 0);    
    if (clientsockfd < 0) 
        error("ERROR opening socket");
        
    //get server    
    server = gethostbyname("localhost");

	// try connecting    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(clientsockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    // Write something to buffer        
    buffer = (char *)malloc(1024 * sizeof(char));
    buffer = "Hello server";
    n = write(clientsockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
       
    return 0;
}
