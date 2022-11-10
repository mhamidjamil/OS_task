// socket programming
// Server socket code:

// 1. Create a socket
// 2. Bind the socket
// 3. Listen for connections
// 4. Accept the connection
// 5. Send and receive data
// 6. Close the connection
// 7. Close the socket
#include <pthread.h>
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
#define Buffer 10
#include <ctype.h>
void *charE(void *u);
void *charI(void *u);
void *charO(void *u);
void *charU(void *u);
int sum_ = 0;
char key_[30] = "1101";
int getResult(char *input, char *key)
{
    int i, j, keylen, msglen, reciver_ = 1;
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
    for (i = 0; i < keylen - 1; i++)
    {
        if (rem[i] == '1' && reciver_ == 1)
        {
            printf("Error in reciving data");
            //   reciver_ = 0;
            return 0;
        }

        // printf("%c", rem[i]);
    }
    // printf("\nFinal data is: ");
    // for (i = 0; i < msglen; i++)
    //   printf("%c", input[i]);
    // for (i = 0; i < keylen - 1; i++)
    //   printf("%c", rem[i]);
    // getch();
    // printf("\nCRC Communication succeeded\n");
    return 1;
}

void *sum(void *u)
{
    char *ptr = (char *)u;
    int i, sum = 0, n = 0;

    for (i = 0; i <= Buffer; ++i)
    {
        if (ptr[i] >= '0' && ptr[i] <= '9')
        {
            int val = ptr[i] - '0';
            sum = sum + val;
        }
        else
        {
            n++;
        }
    }
    sum_ = sum;
    printf("The sum is %d\n\n ", sum);
}

void *charA(void *u)
{
    char *ptr = (char *)u;
    int n = 0;
    pthread_t tid2;
    for (int i = 0; i <= Buffer; i++)
    {
        if (ptr[i] == 'a')
        {
            ptr[i] = 'A';
        }
        else
        {
            printf(" ");
        }
    }

    pthread_create(&tid2, NULL, &charE, ptr);
    pthread_join(tid2, NULL);
}

void *charE(void *u)
{
    char *ptr = (char *)u;
    int n = 0;
    pthread_t tid3;
    for (int i = 0; i <= Buffer; i++)
    {
        if (ptr[i] == 'e')
        {
            ptr[i] = 'E';
        }
        else
        {
            printf(" ");
        }
    }

    pthread_create(&tid3, NULL, &charI, ptr);
    pthread_join(tid3, NULL);
}

void *charI(void *u)
{
    char *ptr = (char *)u;
    int n = 0;
    pthread_t tid4;
    for (int i = 0; i <= Buffer; i++)
    {
        if (ptr[i] == 'i')
        {
            ptr[i] = 'I';
        }
        else
        {
            printf(" ");
        }
    }

    pthread_create(&tid4, NULL, &charO, ptr);
    pthread_join(tid4, NULL);
}

void *charO(void *u)
{
    char *ptr = (char *)u;
    int n = 0;
    pthread_t tid5;
    for (int i = 0; i <= Buffer; i++)
    {
        if (ptr[i] == 'o')
        {
            ptr[i] = 'O';
        }
        else
        {
            printf(" ");
        }
    }

    pthread_create(&tid5, NULL, &charU, ptr);
    pthread_join(tid5, NULL);
}

void *charU(void *u)
{
    char *ptr = (char *)u;
    int n = 0;
    for (int i = 0; i <= Buffer; i++)
    {
        if (ptr[i] == 'u')
        {
            ptr[i] = 'U';
        }
        else
        {
            printf(" ");
        }
    }
    // printf("final string after vowels were encountered: %s\n", ptr);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int id;
    pthread_t tid;
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid4;
    pthread_t tid5;
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
        int result = getResult(buffer, key_);
        {
            if (result == 1)
            {
                printf("CRC Communication succeeded\n");
            }
            else
            {
                printf("CRC Communication failed\n");
            }
        }
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        printf("*Here is the message: %s*", buffer);
        pthread_create(&tid, NULL, &sum, &buffer);
        pthread_create(&tid1, NULL, &charA, &buffer);

        pthread_join(tid, NULL);
        pthread_join(tid1, NULL);
        // printf("New buffer : %s", buffer);
        // n = write(newsockfd, "C got your message", 18);

        // sleep(1);
        // printf("Here is the message: %s", buffer);
        n = write(newsockfd, buffer, 18);
        n = write(newsockfd, "\nSum is: ", 9);
        // sum_ (int) to char conversion:
        //--------------------
        char sum_string[10];
        sprintf(sum_string, "%d", sum_);
        n = write(newsockfd, sum_string, 10);
        //--------------------
        n = write(newsockfd, "end", 3);
        // sleep(2);
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
