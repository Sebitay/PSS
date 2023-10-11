# Instrucciones de uso

Para compilar la pauta por ustedes mismos sólo deben correr el siguiente comando: 

```bash
make <pregunta>
```

Donde `<pregunta>` corresponde con la pregunta que quieren probar (ya sea p1, p2 o p3).

Esto hará que se cree el ejecutable. Para ejecutar el binario deben hacer: 

```bash
./<pregunta>.out <args>
```

Si quieren ejecutar directamente desde make, deben anteponer `run-` (ejemplo: `make run-p1`). Sin embargo esto hará que los programas que tomen argumentos desde la consola usen los argumentos especifícados dentro del Makefile bajo la variable `ARGS`.

## Compilación manual

Siempre pueden compilar cada archivo manualmente si se atreven, recuerden que el comando es:

```bash
gcc <archivos> -o output.out -lm
```

En `<archivos>` deben estar todos los archivos necesarios para compilar la pregunta, el resto es lo mismo que vieron en el aux. Lo único distinto es el `-lm` que le dice al compilador que incluya los binarios de la librería matemática de C (que se incluye con `math.h`).
