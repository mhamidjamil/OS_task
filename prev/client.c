// socket programming
// client socket code:

// 1. Create a socket
// 2. Connect to the server
// 3. Send and receive data
// 4. Close the connection
// 5. Close the socket

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int PORT = 5001;

int main(int argc, char *argv[]) {

  // printf("args : %d\n", argc);
  // printf("New port number : %s\n", argv[1]);
  PORT = atoi(argv[1]);
  int sockfd, n;
  char buffer[256];
  struct sockaddr_in serv_addr;

  // 1. Create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }

  // 2. Connect to the server
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR connecting");
    exit(1);
  }

  // 3. Send and receive data
  printf("Please enter the message: ");
  bzero(buffer, 256);
  fgets(buffer, 255, stdin);
  n = write(sockfd, buffer, strlen(buffer));
  if (n < 0) {
    perror("ERROR writing to socket");
    exit(1);
  }
  bzero(buffer, 256);
  n = read(sockfd, buffer, 255);
  if (n < 0) {
    perror("ERROR reading from socket");
    exit(1);
  }
  printf("%s", buffer);

  // 4. Close the connection
  close(sockfd);

  return 0;
}

// 5. Close the socket
