g:
   bne  a0,zero,L1 # if (a!=NULL) goto L1
   ret             # return
L1:
   lw   t0,0(a0)   # a->x
   bne  t0,a1,L2   # if (a->x!=z) goto L2
   lw   t1,4(a0)   # a->y
   sw   t1,0(a2)   # *pres= a->y
   ret             # return
L2:
   bge  a1,t0,L3   # if (z>=a->x) goto L3
   lw   a0,8(a0)   # a= a->izq
   j    g
L3:
   lw   a0,12(a0)  # a= a->der
   j    g
