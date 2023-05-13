#include <stdio.h>
#include <string.h>

int multiplicar(int a, int b) {
	if (b == 1) {
	   return a;
	}else{
	   return a + multiplicar(a,b -1);
	}
}

int main() {
int a = 0;
int b = 0;
int resultado = 0;

printf("Escriba un valor: ");
scanf("%d",&a);
printf("Escriba un valor a Multiplicar: ");
scanf("%d",&b);
resultado = multiplicar(a,b);
printf("El resultado es: %d",resultado);
}
