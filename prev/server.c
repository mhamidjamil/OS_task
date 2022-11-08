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
#include <time.h>
#include <unistd.h>
#define inputSize 10
int PORT = 5001;
// function get char array print it and return char array:
char *get_string(char *str);
char *charA(char *str);
char *charE(char *str);
char *charI(char *str);
char *charO(char *str);
char *charU(char *str);
int sum(char *str);
int main(int argc, char *argv[])
{
  int id;

  if (argv[1] > 0)
  {
    char buf[30];
    snprintf(buf, 30, "fuser -k %d/tcp", atoi(argv[1]));

    PORT = atoi(argv[1]);
    system(buf);
  }
  else
  {
    // kill port if it is already in use
    system("fuser -k 5001/tcp");
  }
  // }
  int sockfd, newsockfd, clilen, n;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  //   int n;

  // 1. Create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("ERROR opening socket");
    exit(1);
  }

  // 2. Bind the socket
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT);
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("ERROR on binding");
    exit(1);
  }

  // 3. Listen for connections
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);

  // 4. Accept the connection
  newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
  if (newsockfd < 0)
  {
    perror("ERROR on accept");
    exit(1);
  }

  // 5. Send and receive data
  bzero(buffer, 256);
  n = read(newsockfd, buffer, 255);
  if (n < 0)
  {
    perror("ERROR reading from socket");
    exit(1);
  }
  else
  {
    id = fork();
    if (id < 0)
    {
      perror("ERROR on fork");
    }
    else
    {
      printf("ID : %d\n", id);
      if (id == 0)
      {
        printf("child : Here is the message: %s", (get_string(buffer)));
        // n = write(newsockfd, "C got your message", 18);
      }
      else
      {
        printf("parent : Here is the message: %s", buffer);
        char buf[18];
        snprintf(buf, 18, "%s", (get_string(buffer)));
        n = write(newsockfd, buf, 18);
        sleep(2);
      }
    }
  }
  if (id != 0)
  {
    printf("fininsh\n");
  }
  else
  {
    printf("child fininsh\n");
  }
  if (n < 0)
  {
    perror("ERROR writing to socket");
    exit(1);
  }

  // 6. Close the connection
  close(newsockfd);

  // 7. Close the socket
  close(sockfd);
  return 0;
}
char *get_string(char *str)
{
  printf("function got : %s", str);
  char *str1 = charA(str);
  printf("function A return : %s", str1);
  char *str2 = charE(str);
  printf("function E return : %s", str2);
  char *str3 = charI(str);
  printf("function I return : %s", str3);
  char *str4 = charO(str);
  printf("function O return : %s", str4);
  char *str5 = charU(str);
  printf("function U return : %s", str5);
  int sum1 = sum(str1);
  printf("sum1 : %d\n", sum1);
  return str;
}
char *charA(char *str)
{
  // capetalize char a in string
  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] == 'a')
    {
      str[i] = 'A';
    }
  }
  // printf("char a changed to A : %s", str);
  return str;
}
char *charE(char *str)
{
  // capetalize char e in string
  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] == 'e')
    {
      str[i] = 'E';
    }
  }
  // printf("char e changed to E : %s", str);
  return str;
}
char *charI(char *str)
{
  // capetalize char i in string
  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] == 'i')
    {
      str[i] = 'I';
    }
  }
  // printf("char i changed to I : %s", str);
  return str;
}
char *charO(char *str)
{
  // capetalize char o in string
  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] == 'o')
    {
      str[i] = 'O';
    }
  }
  // printf("char o changed to O : %s", str);
  return str;
}
char *charU(char *str)
{
  // capetalize char u in string
  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] == 'u')
    {
      str[i] = 'U';
    }
  }
  // printf("char u changed to U : %s", str);
  return str;
}
int sum(char *str)
{
  int sum = 0;
  // add all digits in string
  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] >= '0' && str[i] <= '9')
    {
      sum += str[i] - '0';
    }
  }
  // printf("sum of digits : %d", sum);
  return sum;
}
