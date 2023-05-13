#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(){

int n;
char *puntcadena;
printf("Ingrese el numero de caracteres de la cadena:");
scanf("%d",&n);
getchar();
puntcadena=(char*)malloc(n*sizeof(char));

printf("\nSe ha reservado espacio de memoria para %d caracteres", n);

printf("\nIngrese la cadena:");
scanf("%[^\n]",puntcadena);


printf("El valor almacenado en la variable de la cadena es %s", puntcadena);

return 0;
}
