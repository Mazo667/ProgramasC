#include "TP1.h"

int main(void) {
    int par = 2;
    int impar = 3;
    //Punto 3
    double valorDecimal1 = 5.55;
    double valorDecimal2 = 4.44;
    //Punto 5
    int numeros [MAXIMO] = {0,1,2,3,4,5,6,7,8,9};
    //Punto 6
    char saludo [MAXIMO] = {'H', 'O', 'L','A', 'M', 'U', 'N', 'D', 'O'};
    funcionSumar(par, impar);
    funcionRestar(par, impar);
    funcionDividir(par, impar);
    funcionMultiplicacion(par, impar);
    printf("\n----Funciones con Double----\n\n");
    doubleMultiplicacion(valorDecimal1,valorDecimal2);
    doubleRestar(valorDecimal1,valorDecimal2);
    doubleSumar(valorDecimal1,valorDecimal2);
    doubleDividir(valorDecimal1,valorDecimal2);
    //Punto 7
    printf("\n----Cantidad de veces que se ejecuto una funcion es %d veces----\n\nValor del arreglo de enteros: ",ejecucion);
    for(int i = 0; i<MAXIMO; i++){
		printf("%d",numeros[i]);
	}
	printf("\n\nValor del arreglo de caracteres: ");
	for(int i = 0; i<MAXIMO; i++){
		printf("%c",saludo[i]);
	}
}
//Punto 2
int funcionSumar(int sumando1, int sumando2){
	ejecucion++;
    int resultado = sumando1 + sumando2;
    printf("La suma entre %d y %d es: %d\n",sumando1,sumando2,resultado);
    
}
int funcionRestar(int minuendo, int sustraendo){
	ejecucion++;
    int resultado = minuendo - sustraendo;
    printf("La resta entre %d y %d es: %d\n",minuendo,sustraendo,resultado);
}
int funcionMultiplicacion(int multiplicando, int multiplicador){
	ejecucion++;
    int resultado = multiplicando * multiplicador;
    printf("La multiplicacion entre %d y %d es: %d\n",multiplicando,multiplicador,resultado);
}
int funcionDividir(int dividiendo, int divisor){
	ejecucion++;
    int resultado = dividiendo / divisor;
    printf("La division entre %d y %d es: %d\n",dividiendo,divisor,resultado);
}
//punto 4
int doubleMultiplicacion(double multiplicando, double multiplicador){
	ejecucion++;
    double resultado = multiplicando * multiplicador;
    printf("La division entre %.2f y %.2f es: %.2f\n",multiplicando,multiplicador,resultado);
}
int doubleRestar(double minuendo, double sustraendo){
	ejecucion++;
    double resultado = minuendo - sustraendo;
    printf("La resta entre %.2f y %.2f es: %.2f\n",minuendo,sustraendo,resultado);
}
int doubleSumar(double sumando1, double sumando2){
    ejecucion++;
    double resultado = sumando1 + sumando2;
    printf("La suma entre %.2f y %.2f es: %.2f\n",sumando1,sumando2,resultado);
}
int doubleDividir(double dividiendo, double divisor){
	ejecucion++;
    double resultado = dividiendo / divisor;
    printf("La division entre %.2f y %.2f es: %.2f\n",dividiendo,divisor,resultado);
}
