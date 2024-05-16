#include <stdio.h>
#include <string.h>


char *prox_pal(char **pfrase) {
	char* pal = *pfrase;
	while(*pal == ' ') pal++;
	if (*pal == 0) return NULL;
	char* end = pal;
	while(*end != ' ' && *end != 0) end++;
	*end = 0;
	end++;
	*pfrase = end;
	return pal;
}

int main(){
	char s[] = " hola   que  ";
	char *frase = s;
	printf("frase: \"%s\"\n", frase);
	printf("prox_pal: \"%s\"\n", prox_pal(&frase));
	printf("frase: \"%s\"\n", frase);
	printf("prox_pal: \"%s\"\n", prox_pal(&frase));
	printf("frase: \"%s\"\n", frase);
	return 0;
}
