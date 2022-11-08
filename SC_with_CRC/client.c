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
char key_[30] = "1101";
char input_[32] = "101101110";
char result[32];
void maintainResult(char *input, char *key)
{
    int i, j, keylen, msglen;
    char temp[30], quot[100], rem[30], key1[30];
    //    clrscr();
    // printf("Enter Data: ");
    // // gets(input);
    // scanf("%s", input);
    // printf("Enter Key: ");
    // // gets(key);
    // scanf("%s", key);
    keylen = strlen(key);
    msglen = strlen(input);
    strcpy(key1, key);
    for (i = 0; i < keylen - 1; i++)
    {
        input[msglen + i] = '0';
    }
    for (i = 0; i < keylen; i++)
        temp[i] = input[i];
    for (i = 0; i < msglen; i++)
    {
        quot[i] = temp[0];
        if (quot[i] == '0')
            for (j = 0; j < keylen; j++)
                key[j] = '0';
        else
            for (j = 0; j < keylen; j++)
                key[j] = key1[j];
        for (j = keylen - 1; j > 0; j--)
        {
            if (temp[j] == key[j])
                rem[j - 1] = '0';
            else
                rem[j - 1] = '1';
        }
        rem[keylen - 1] = input[i + keylen];
        strcpy(temp, rem);
    }
    strcpy(rem, temp);
    // printf("\nQuotient is ");
    // for (i = 0; i < msglen; i++)
    //     printf("%c", quot[i]);
    // printf("\nRemainder is ");
    // for (i = 0; i < keylen - 1; i++)
    //     printf("%c", rem[i]);
    // printf("\nFinal data is: ");
    for (i = 0; i < msglen; i++)
    {
        // printf("%c", input[i]);
        result[i] = input[i];
    }
    for (i = 0; i < keylen - 1; i++)
    {
        // printf("%c", rem[i]);
        result[i + msglen] = rem[i];
    }
    // getch();
}

int main(int argc, char *argv[])
{

    // printf("args : %d\n", argc);
    // printf("New port number : %s\n", argv[1]);
    if (argv[1] > 0)
    {
        PORT = atoi(argv[1]);
    }
    int sockfd, n;
    char buffer[256];
    struct sockaddr_in serv_addr;

    // 1. Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    // 2. Connect to the server
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        exit(1);
    }
    maintainResult(input_, key_);
    n = write(sockfd, result, strlen(result));
    // 3. Send and receive data
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }
    bzero(buffer, 256);
    // getData:
    int noofinput = 3;
    do
    {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
        {
            perror("ERROR reading from socket");
            exit(1);
        }
        printf("%s", buffer);
        noofinput--;
    } while (noofinput > 0);
    // 4. Close the connection
    close(sockfd);

    return 0;
}

// 5. Close the socket