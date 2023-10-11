#include <string.h>

void sort(char **noms, int n) {
  char **ult = &noms[n - 1];
  char **p = noms;
  while (p < ult) {
    char *ap1 = p[0];
    char *ap2 = p[1];
    char *nom1 = p[0];
    char *nom2 = p[1];

    while (*ap1 != ' ')
      ap1++;
    while (*ap2 != ' ')
      ap2++;

    int t1 = strcmp(ap1, ap2);
    if (t1 == 0) // son iguales
      t1 = strcmp(nom1, nom2);

    if (t1 <= 0) {
      p++;
    } else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= noms;
    }

    // if (strcmp(p[0], p[1])<=0)
    //   p++;
    // else {
    //   char *tmp= p[0];
    //   p[0]= p[1];
    //   p[1]= tmp;
    //   p= noms;
    // }
  }
}
