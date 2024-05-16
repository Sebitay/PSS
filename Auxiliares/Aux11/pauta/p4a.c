#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>



char *last_ptr = "Good";
jmp_buf buf_ptr;
char *ultimaDireccionValida(char *ptr);

int main(int argc, char* argv[]) {
  char *bad1;
  char *bad2 = malloc(10);
  free(bad2);
  ultimaDireccionValida(bad1);
  ultimaDireccionValida(bad2);
  ultimaDireccionValida(NULL);
  printf("good!\n");
}

void sigsegv_handler(int sig) {
  siglongjmp(buf_ptr, 1);
}

char *ultimaDireccionValida(char *ptr) {
  void (*old_handler)(int);
  old_handler = signal(SIGSEGV, sigsegv_handler);
  char *res;
  if (sigsetjmp(buf_ptr, 1) == 0) {
    while (1) {
      char c = *ptr;
      last_ptr = ptr;
      ptr++;
    }
  }
  else {
    res = last_ptr--;
  }
  signal(SIGSEGV, old_handler);
  return res;
}
