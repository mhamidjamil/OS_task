#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define Buffer 10
#include <ctype.h>
void *digit(void *u) {
  char *ptr = (char *)u;
  int i, sum = 0, n = 0;

  for (i = 0; i <= Buffer; ++i) {
    if (ptr[i] >= '0' && ptr[i] <= '9') {
      int val = ptr[i] - '0';
      sum = sum + val;
    } else {
      n++;
    }
  }
  printf("The sum is %d\n\n ", sum);
}

void *charA(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'a') {
      printf("The vowel A was encountered :%c\n\n", toupper(ptr[i]));
    } else {
      printf(" ");
    }
  }
}

void *charE(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'e') {
      printf("The vowel E was encountered :%c\n\n", toupper(ptr[i]));
    } else {
      printf(" ");
    }
  }
}

void *charI(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'i') {
      printf("The vowel i was encountered :%c\n\n", toupper(ptr[i]));
    } else {
      printf(" ");
    }
  }
}

void *charO(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'o') {
      printf("The vowel o was encountered :%c\n\n", toupper(ptr[i]));
    } else {
      printf(" ");
    }
  }
}

void *charU(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'u') {
      printf("The vowel U was encountered :%c\n\n", toupper(ptr[i]));
    } else {
      printf(" ");
    }
  }
}

int main() {
  pthread_t tid;
  pthread_t tid1;
  pthread_t tid2;
  pthread_t tid3;
  pthread_t tid4;
  pthread_t tid5;

  char str[Buffer];
  scanf("%s", str);
  printf("\t\nYour String:%s\n\t", str);

  pthread_create(&tid, NULL, &digit, &str);
  pthread_create(&tid1, NULL, &charA, &str);
  pthread_create(&tid2, NULL, &charE, &str);
  pthread_create(&tid3, NULL, &charI, &str);
  pthread_create(&tid4, NULL, &charO, &str);
  pthread_create(&tid5, NULL, &charU, &str);

  pthread_join(tid, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  pthread_join(tid4, NULL);
  pthread_join(tid5, NULL);
  return 0;
}