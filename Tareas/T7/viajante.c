#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double viajante_par(int z[], int n, double **m, int nperm, int p) {
  int pids[p];
  int fds[p][2];

  int bloque = nperm / p;
  int resto = nperm % p;
  
  for(int i = 0; i < p; i++){
    pipe(fds[i]);
    pids[i] = fork();
    srandom(getUSecsOfDay()*getpid());

    if(pids[i] == 0){
      if(i == p - 1) bloque += resto;
      close(fds[i][0]);
      double res = viajante(z, n, m, bloque);
      write(fds[i][1], &res, sizeof(double));
      write(fds[i][1], z, sizeof(int)*(n+1));
      exit(0);
    }
    else{
      close(fds[i][1]);
    }
  }

  double res = DBL_MAX;

  for(int i = 0; i < p; i++){
    double res_hijo;
    leer(fds[i][0], &res_hijo, sizeof(double));
    if(res_hijo < res){
      res = res_hijo;
      leer(fds[i][0], z, sizeof(int)*(n+1));
    }
    close(fds[i][0]);
    waitpid(pids[i], NULL, 0);
  }
  return res;
}
