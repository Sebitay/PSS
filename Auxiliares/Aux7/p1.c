int n = 4;

int start() {
  int a5 = n;
  int a4 = 1;
  int a0 = 1;

  if (a5 <= a4)
    return a0;

  do {
    a0 = a0 * a5;
    a5--;
  } while (a5 != 0);
  
  return a0;
}



