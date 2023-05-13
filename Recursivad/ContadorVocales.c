#include "ContadorVocales.h"

int main(void){
	int i=0;
	char cadena[MAXIMO];
	
	printf("Ingrese un texto: ");
	scanf("%s", cadena);
	printf("En \"%s\" hay %d vocales en total", cadena, contarVocales(cadena,i,MAXIMO));
}

int contarVocales(char cadena[], int i,int tamano){
	
	if(i > tamano){
		return 0;
	}else{
		if(cadena[i] == 'a'||cadena[i] == 'e'||cadena[i] == 'i'||cadena[i] == 'o'||cadena[i] == 'u'||
			cadena[i] == 'A'||cadena[i] == 'E'||cadena[i] == 'I'||cadena[i] == 'O'||cadena[i] == 'U'){
			return 1 + contarVocales(cadena,i + 1,tamano);
		}else{
			return 0 + contarVocales(cadena,i + 1,tamano);
		}
	}
}
