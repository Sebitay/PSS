#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"

double g(double x) {
    return x*x;
}

double f(double x) {
    return 1/(1+x);
}

void suma(double x0, double dx, int n, double *pres) {
    double s= 0;
    for (int k= 0; k<n; k++) {
        s+= f(g(x0+dx*k));
    }
    *pres= s;
}

int leer(int fd, void *buf, int n) {
  if (n==0)
    return 0;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
    return 1; // fracaso: error o fin del archivo/pipe/socket
    n-= rc; // descontamos los bytes leídos
    buf= (char*)buf + rc; // avanzamos el buffer
  } while (n>0); // mientras no leamos todo lo que esperamos
  return 0; // exito
}

// Esta solución se realizó en pizarra porque esta pensada para resolverse en control.
// la misma interpretación de suma pero en paralelo.
// Tal que el hijo llama a g y el padre a f.
void suma_par(double x0, double dx, int n, double *pres) {
    double s= 0;
    int fds[n][2];
    for (int k= 0; k<n; k++) {
        if (pipe(fds[k]) == -1) {
            perror("pipe");
            exit(1);
        }
    }
    pid_t pid = fork();
    for (int k= 0; k<n; k++) {
        if (pid == 0) {
            close(fds[k][0]);
            double x = g(x0+dx*k);
            write(fds[k][1], &x, sizeof(double));
            close(fds[k][1]);
        }
        else {
            close(fds[k][1]);
            double x;
            leer(fds[k][0], &x, sizeof(double));
            s+= f(x);
            close(fds[k][0]);
        }
    }
    if (pid == 0) {
        exit(0);
    }
    else {
        waitpid(pid, NULL, 0);
    }
    *pres= s;
}

int main(){
    double s1=0;
    double s2=0;
    suma(0, 1, 10, &s1);
    printf("suma: %f\n", s1);
    suma_par(0, 1, 10, &s2);
    printf("suma_par: %f\n", s2);
    return 0;
}