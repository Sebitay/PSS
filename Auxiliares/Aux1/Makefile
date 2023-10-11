ARGS=110100


MAKEFLAGS += --no-print-directory

%.out: %
%: %.o
%: %.c
%: %.out

all: p1 p2 p3

p1: p1.out

p2: p2.out

p3: p3.out

run-%: %
	./$*.out $(ARGS)

# Reglas especificas
p2.out: p2.o decimal.o
	gcc $? -o $@ -lm


# Reglas sencillas :D
%.out: %.o
	gcc $< -o $@

%.o : %.c
	gcc -c $< -o $@

clean:
	rm -f *.o *.out
