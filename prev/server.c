// socket programming
// Server socket code:

// 1. Create a socket
// 2. Bind the socket
// 3. Listen for connections
// 4. Accept the connection
// 5. Send and receive data
// 6. Close the connection
// 7. Close the socket

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int PORT = 5001;

int main(int argc, char *argv[]) {
  // if(argc > 100){
  // PORT = argc;
  // printf("args : %d\n", argc);
  // printf("New port number : %s\n", argv[1]);
  // while (1) {
  if (argv[1] > 0) {
    PORT = atoi(argv[1]);
  }
  // }
  int sockfd, newsockfd, clilen, n;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  //   int n;

  // 1. Create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }

  // 2. Bind the socket
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT);
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR on binding");
    exit(1);
  }

  // 3. Listen for connections
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);

  // 4. Accept the connection
  newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
  if (newsockfd < 0) {
    perror("ERROR on accept");
    exit(1);
  }

  // 5. Send and receive data
  bzero(buffer, 256);
  n = read(newsockfd, buffer, 255);
  if (n < 0) {
    perror("ERROR reading from socket");
    exit(1);
  }
  printf("Here is the message: %s", buffer);
  n = write(newsockfd, "I got your message", 18);
  if (n < 0) {
    perror("ERROR writing to socket");
    exit(1);
  }

  // 6. Close the connection
  close(newsockfd);

  // 7. Close the socket
  close(sockfd);
  // }
  return 0;
}
