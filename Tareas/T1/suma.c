#include <stdio.h>

#include "suma.h"

Bcd sumaBcd(Bcd x, Bcd y){
  Bcd ans = 0x0,z,m = 0xf,e = 0x0;
  for(int i = 0; i<64; i += 4){
      z = ((x >> i) & m) + ((y >> i) & m) + e;
      if (z > 0x9){
          z -= 0xa;
          e = 0x1;
      }else{
          e = 0x0;
      }
      ans |= (z<<i);
  }
  if(e == 0){
    return ans;
  }else{
    return 0xffffffffffffffff;
  }
}
