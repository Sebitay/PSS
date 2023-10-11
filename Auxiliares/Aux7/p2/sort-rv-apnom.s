# sort: Ordena alfabeticamente un arreglo de strings usando un algoritmo
# ridiculamente ineficiente.

# La funcion sort esta programada en assembler RiscV. El codigo equivalente
# en C esta comentado, mostrando la ubicacion de las variables en los
# registros.  La funcion recorre el arreglo revisando que los elementos
# consecutivos esten ordenados.  Si encuentra 2 elementos consecutivos
# desordenados, los intercambia y reinicia el recorrido del arreglo
# desde el comienzo.  El arreglo esta ordenado cuando se recorre
# completamente sin encontrar elementos consecutivos desordenados.

    .file "sort-rv.s"
    .text
    .globl sort         # Se necesita para que la etiqueta sea conocida en
                        # test-sort-x86.c
    .type sort, @function
sort:                   # void sort(char *noms[], int n) { // registros a0, a1
    addi    sp,sp,-64   #   // Apila registro de activacion
    sw      ra, 60(sp)  #   // resguarda direccion de retorno
    sw      a0,56(sp)   #   char **p= noms; // p esta en sp+56
    addi    a1,a1,-1    #   char **ult= &noms[n-1]; // ult esta en sp+52
    slli    a1,a1,2     #   // tamanno del arreglo
    add     a1,a0,a1
    sw      a1,52(sp)
    sw      a0,48(sp)   #   // noms esta en direccion sp+48
    mv      t0,a0       #   // p esta en registro t0
                        #   while (p<ult) {
    j       .while_cond #     // la condicion del while se evalua al final
.while_begin:           #     // del ciclo para mayor eficiencia

    # Hasta aca no puede modificar nada

    #################################################
    ### Comienza el codigo que Ud. debe modificar ###
    #################################################

    # no puede alterar los registros s0-s11, si lo hace debe resguardarlos
    # en 0(sp), 4(sp), ... o 48(sp)
    # El valor de p esta temporalmente en el registro t0
    lw      a0,0(t0) # cargamos en a0 p[0]
    lw      a1,4(t0) # a1 = p[1]
    li      a3,32    # a3 = 32 (= ' ')
.buscar_ap1:
    lbu     a2,0(a0) # a2 = *a0;
    addi    a0,a0,1  # a0++
    bne     a2,a3,.buscar_ap1 # si a2 no es ' ' nos devolvemos
    # hacemos lo mismo para a1
.buscar_ap2:
    lbu     a2,0(a1) # a2 = *a1;
    addi    a1,a1,1  # a1++
    bne     a2,a3,.buscar_ap2 # si a2 no es ' ' nos devolvemos

    addi    a0,a0,-1  # a0--, para compensar el pasito extra
    addi    a1,a1,-1  # a1--
    sw      t0,56(sp)   # resguardar p en memoria antes de llamar a strcmp
    call    strcmp      # valor retornado queda en registro a0
                        # p ya no esta en el registro t0
    bne     a0,zero,.comp_end # si el resultado de la comparación no fue zero
                        #       entonces los apellidos son distintos 
                        #       y no se comparan los nombres

    lw      t0,56(sp)   # recuperamos p
    lw      a0,0(t0)    # a0 = p[0]
    lw      a1,4(t0)    # a1 = p[0]
    sw      t0,56(sp)   # resguardar
    call    strcmp      # comparamos los nombres
.comp_end:
    mv      t1,a0       # resultado de la comparacion en t1
    #################################################
    ### Fin del codigo que Ud. debe modificar     ###
    #################################################

    # Desde aca no puede modificar nada

    # En el registro t1 debe quedar la conclusion de la comparacion:
    # si t1<=0 p[0] y p[1] estan en orden y no se intercambiaran.
    # Si no, se intercambian p[0] y p[1] y se asigna p= noms para revisar
    # nuevamente que los elementos esten ordenados desde el comienzo del arreglo
.decision:              #     if (0>=rc) {
    lw      t0,56(sp)   #       // p esta en registro t0
    blt     zero,t1,.else
    addi    t0,t0,4     #       p++; // avanzar en arreglo de enteros
    j       .while_cond #     }

.else:                  #     else { // intercambar p[0] y p[1], y reiniciar
    lw      a0,0(t0)    #       char *aux= p[0]; // a0
    lw      a1,4(t0)    #       char *aux2= p[1];
    sw      a0,4(t0)    #       p[0]= aux2;
    sw      a1,0(t0)    #       p[1]= aux;
    lw      t0,48(sp)   #       p= noms;
                        #     }

.while_cond:            #     // se evalua la condicion del while
    lw      t1,52(sp)   #     // ult esta en t1
    bltu    t0,t1,.while_begin #  // Condicion del while es p<ult
			#   }
    lw      ra,60(sp)   #   // Se restaura direccion de retorno
    addi    sp,sp,64    #   // Desapila registro de activacion
    ret			# }
