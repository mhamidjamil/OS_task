#include <stdio.h>
// #include <conio.h>
#include <string.h>
char key_[30] = "1101";
char input_[32] = "101101110";
char result[32];
void getResult(char *input, char *key)
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
int main()
{
    getResult(input_, key_);
    // char finalStr[32] = result;
    printf("\nFinal data is: %s", result);
    return 0;
}