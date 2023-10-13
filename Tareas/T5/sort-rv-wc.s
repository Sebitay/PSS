# sort: Ordena ascendentemente un arreglo de enteros sin signo usando un
# algoritmo ridiculamente ineficiente.

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
                        # test-sort.c
    .type sort, @function # typedef unsigned int uint;
sort:                   # void sort(uint nums[], int n) { // registros a0, a1
    addi    sp,sp,-64   #   // Apila registro de activacion
    sw      ra, 60(sp)  #   // resguarda direccion de retorno
    sw      a0,56(sp)   #   uint *p= nums; // p esta en sp+56
    addi    a1,a1,-1    #   uint *ult= &nums[n-1]; // ult esta en sp+52
    slli    a1,a1,2     #   // tamanno del arreglo
    add     a1,a0,a1
    sw      a1,52(sp)
    sw      a0,48(sp)   #   // nums esta en direccion sp+48
    mv      t0,a0       #   // p esta en registro t0
                        #   while (p<ult) {
    j       .while_cond #     // la condicion del while se evalua al final
.while_begin:           #     // del ciclo para mayor eficiencia

    sw      t0,56(sp)   # resguardar p en memoria

    # Hasta aca no puede modificar nada

    #################################################
    ### Comienza el codigo que Ud. debe modificar ###
    #################################################

    # no puede alterar los registros s0-s11, si lo hace debe resguardarlos
    # en 0(sp), 4(sp), ... o 44(sp)
    # El valor de p esta temporalmente en el registro t0
    # No puede hacer mas trabajo que la comparacion (no puede usar ret)

#preparamos while()
    lw      a7,0(t0)            #a7 = p[0]
    lbu     a1,0(a7)            #a1 = *p[0]
    beq     a1,zero,.L9         #si *p[0] == 0 me voy a L9
    li      a0,0                #a0 = count = 0
    li      a2,0                #a2 = anterior = 0
    li      a3,32               #a3 = ' '
    li      a4,1                #a4 = 1
    j       .L3                 #me voy a L3

#while()
.L1:
    mv a2,zero                  #anterior = 0

.L2:
    addi    a7,a7,1             #p[0]++
    lbu     a1,0(a7)            #a1 = *p[0]
    beq     a1,zero,.L4         #si *p[0] == 0 me voy a L4

.L3:
    beq     a1,a3,.L1           #si *p[0] == ' ' me voy a L1
    bne     a2,zero,.L2         #si anterior != 0 me voy a L2
    addi    a0,a0,1             #count++
    mv      a2,a4               #anterior = 1
    j       .L2                 #me voy a L2
#end while()

.L9:
    mv      a0,zero                #count = 0

#preparando while()
.L4:
    lw      a7,4(t0)            #a7 = p[1]
    lbu     a1,0(a7)            #a1 = *p[1]
    beq     a1,zero,.L8         #si *p[1] == 0 me voy a L8
    li      a2,0                #a2 = anterior = 0
    j       .L7                 #me voy a L7

#while()
.L5:
    mv      a2,zero             #anterior = 0

.L6:
    addi    a7,a7,1             #p[1]++
    lbu     a1,0(a7)            #a1 = *p[1]
    beq     a1,zero,.L8         #si *p[1] == 0 me voy a L8

.L7:
    beq     a1,a3,.L5           #si *p[1] == ' ' me voy a L5
    bne     a2,zero,.L6         #si anterior != 0 me voy a L6
    addi    a0,a0,-1            #count--
    mv      a2,a4               #anterior = 1
    j       .L6                 #me voy a L6     
#end while()

.L8:
    mv      t1,a0       #     // Dejar resultado de la comparacion en t1

    # En el registro t1 debe quedar la conclusion de la comparacion:
    # si t1<=0 p[0] y p[1] estan en orden y no se intercambiaran.

    #################################################
    ### Fin del codigo que Ud. debe modificar     ###
    #################################################

    # Desde aca no puede modificar nada
    # Si t1>0 se intercambian p[0] y p[1] y se asigna p= noms para revisar
    # nuevamente que los elementos esten ordenados desde el comienzo del arreglo

.decision:              #     if (0>=rc) {
    lw      t0,56(sp)   #       // p esta en registro t0
    blt     zero,t1,.else
    addi    t0,t0,4     #       p++; // avanzar en arreglo de enteros
    j       .while_cond #     }

.else:                  #     else { // intercambar p[0] y p[1], y reiniciar
    lw      a0,0(t0)    #       int aux= p[0]; // a0
    lw      a1,4(t0)    #       int aux2= p[1];
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
