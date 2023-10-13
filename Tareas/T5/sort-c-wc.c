#include <string.h>


int wordcount(char *s){
  int count = 0;
  int anterior = 0;
      while(*s){
      if(*s != ' '){
        if(!anterior)
          count++;
        anterior = 1;
      }
      else
        anterior = 0;
      s++;
    }
  return count;
}


int strCmp(char *s1, char *s2) {
    return wordcount(s1) - wordcount(s2);
}

void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {

    int t1= strCmp(p[0], p[1]);

    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}
