#include <stdio.h>

int F1(int n) {
  if(n <=2) {
    return n;
  }

  int f0 = 0, f1 = 1, f2 = 2, f;

  for(int i = 3; i <= n; i++) {
    f = f0 + f1;
    f0 = f1;
    f1 = f2;
    f2 = f;
  }
  return f;
}