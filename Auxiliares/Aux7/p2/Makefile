# Si desea agregar un programa con archivos test-ejemplo.c, ejemplo.c y
# ejemplo.h, agregue un par de reglas que digan:
# test-ejemplo.o ejemplo.o: ejemplo.h
# test-ejemplo: test-ejemplo.o ejemplo.o

RISCV = /opt/riscv
TARGET = riscv64-unknown-elf
CC = ${RISCV}/bin/${TARGET}-gcc
CXX = ${RISCV}/bin/${TARGET}-g++
AS = ${RISCV}/bin/${TARGET}-as
LD = ${RISCV}/bin/${TARGET}-ld
STRIP = ${RISCV}/bin/${TARGET}-strip
GDB = ${RISCV}/bin/${TARGET}-gdb
PK = ${RISCV}/${TARGET}/bin/pk

COMFLAGS= -Wall -pedantic -std=c99 -march=rv32im -mabi=ilp32

CFLAGS= -g ${COMFLAGS}
LDFLAGS= -g ${COMFLAGS}
LDLIBS=
#CFLAGS= -O2 ${COMFLAGS}
#LDFLAGS=
#LDLIBS= -lm

sort-rv: test-sort.o sort-rv.o

sort-c: test-sort.o sort-c.o

sort-rv-apnom: test-sort.o sort-rv-apnom.o

sort-c-apnom: test-sort.o sort-c-apnom.o

clean:
	rm -f *.o sort-rv sort-rv-apnom sort-c sort-c-apnom sort-c.s sort-c-apnom.s

%.s: %.c
	${CC} -O -S ${COMFLAGS} $<

%.ddd:
	bash -c "qemu-riscv32 -g 1234 $(*F) & "
	ddd --debugger ${GDB} --command target.gdb $(*F)

%.o: %.s
	${CC} -c ${COMFLAGS} $< -o $@
