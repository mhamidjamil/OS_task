#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define Buffer 10
#include <ctype.h>
void *charE(void *u);
void *charI(void *u);
void *charO(void *u);
void *charU(void *u);

void *sum(void *u) {
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
  pthread_t tid2;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'a') {
      ptr[i] = 'A';
    } else {
      printf(" ");
    }
  }

  pthread_create(&tid2, NULL, &charE, ptr);
  pthread_join(tid2, NULL);
}

void *charE(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  pthread_t tid3;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'e') {
      ptr[i] = 'E';
    } else {
      printf(" ");
    }
  }

  pthread_create(&tid3, NULL, &charI, ptr);
  pthread_join(tid3, NULL);
}

void *charI(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  pthread_t tid4;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'i') {
      ptr[i] = 'I';
    } else {
      printf(" ");
    }
  }

  pthread_create(&tid4, NULL, &charO, ptr);
  pthread_join(tid4, NULL);
}

void *charO(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  pthread_t tid5;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'o') {
      ptr[i] = 'O';
    } else {
      printf(" ");
    }
  }

  pthread_create(&tid5, NULL, &charU, ptr);
  pthread_join(tid5, NULL);
}

void *charU(void *u) {
  char *ptr = (char *)u;
  int n = 0;
  for (int i = 0; i <= Buffer; i++) {
    if (ptr[i] == 'u') {
      ptr[i] = 'U';
    } else {
      printf(" ");
    }
  }
  printf("final string after vowels were encountered: %s\n", ptr);
}

int main() {
  pthread_t tid;
  pthread_t tid1;
  pthread_t tid2;
  pthread_t tid4;
  pthread_t tid5;

  char str[Buffer];
  scanf("%s", str);

  pthread_create(&tid, NULL, &sum, &str);
  pthread_create(&tid1, NULL, &charA, &str);

  pthread_join(tid, NULL);
  pthread_join(tid1, NULL);

  return 0;
}
