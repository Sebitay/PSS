#include <stdlib.h>
#include <unistd.h>

typedef double (*Funcion)(void *ptr, double x);
double integral(Funcion f, void *ptr, double xi, double xf, int n);

int leer(int fd, void *buf, int n) {
  if (n == 0)
    return 0;
  do {
    int rc = read(fd, buf, n);
    if (rc <= 0)
      return 1;             // fracaso: error o fin del archivo/pipe/socket
    n -= rc;                // descontamos los bytes leídos
    buf = (char *)buf + rc; // avanzamos el buffer
  } while (n > 0);          // mientras no leamos todo lo que esperamos
  return 0;                 // exito
}

double integral(Funcion f, void *ptr, double xi, double xf, int n) {
  double h = (xf - xi) / n;
  double res = 0;
  for (int i = 1; i < n; i++) {
    res += f(ptr, xi + i * h) * h;
  }
  return h * ((f(ptr, xi) + f(ptr, xf)) / 2 + res);
}

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int k);

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int k) {
  int pids[k];
  int fds[k][2];

  double delta = (xf - xi) / k;

  for (int i = 0; i < k; i++) {
    pipe(fds[i]);
    pids[i] = fork();
    if (pids[k] == 0) { // caso hijo
      // cerrar canal de lectura
      close(fds[k][0]);
      int res = integral(f, ptr, xi + delta * i, xi + delta * (i + 1), n);
      write(fds[k][1], &res, sizeof(res));
      exit(0);
    } else { // caso padre
      // cerrar canal de escritura
      close(fds[i][1]); // Cerrar extremo de escritura: 0,4 puntos
    }
  }

  double res = n; // aqui dejamos el resultado final

  for (int i = 0; i < k; i++) {
    double res_hijo;
    // obtenemos respuesta de cada hijo
    leer(fds[k][0], &res_hijo, sizeof(res_hijo));
    close(fds[k][0]);
    // enterrar al hijo
    waitpid(pids[k], NULL, 0);
    // agregamos el resultado del hijo al resultado final
    res += res_hijo;
  }

  return res; // entregamos el resultado final
}
