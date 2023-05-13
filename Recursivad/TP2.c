#include "TP2.h"

int main(void){
	int opcion;
	do{
		opcion = menu(opcion);
		switch (opcion){
			case 1: Vocales();
			break;
			case 2: Palindromo();
			break;
			case 3: Potencia();
			break;
			case 4: SumaArreglo();
			break;
		}
	}while (opcion < 5);
}

int menu(int opcion){
	printf("------Trabajo Practico N 2 Recursividad------\n1) Contador de vocales de una palabra\n2) Saber si una palabra es un palindromo\n3) Calcular la potencia de un numero\n4) Suma de numeros de un arreglo\n5) Salir\nIngrese una opcion: ");
	scanf("%d",&opcion);
	return opcion;
}
//Programa vocales
int Vocales(void){
	int i = 0;
	char cadena[MAXIMO];
	
	printf("\nIngrese un texto: ");
	scanf("%s", cadena);
	//printf("%s", cadena);
	printf("En \"%s\" hay %d vocales en total\n\n", cadena, ContarVocales(cadena,i,strlen(cadena)-1));
}
//Contar vocales

int ContarVocales(char cadena[], int i,int tamano){
	if(i > tamano){
		return 0;
	}else{
		if(cadena[i] == 'a'||cadena[i] == 'e'||cadena[i] == 'i'||cadena[i] == 'o'||cadena[i] == 'u'||
			cadena[i] == 'A'||cadena[i] == 'E'||cadena[i] == 'I'||cadena[i] == 'O'||cadena[i] == 'U'){
			return 1 + ContarVocales(cadena,i + 1,tamano);
		}else{
			return 0 + ContarVocales(cadena,i + 1,tamano);
		}
	}
}
//Programa palindromo
int Palindromo(){
	bool resultado;
	char cadena[MAXIMO];
	
	printf("\nIngrese un texto: ");
	scanf("%s",&cadena);
	resultado = BuscarPalindromo(cadena,0,strlen(cadena)-1);
	if(resultado == true){
	    	printf("Es palindromo\n\n");
	}else{
	    printf("No es palindromo\n\n");
	}
}
//Buscador de palindromo
int BuscarPalindromo(char cadena[],int i, int j){
	if(i<j){
	if(cadena[i] == cadena[j]){
		return true || BuscarPalindromo(cadena,i+1,j-1);
	}else{
		return false;
		}
	}
}
//Programa potencia de un numero
int Potencia(){
	int numero;
	int exponente;
	
	printf("\nIngrese un numero: ");
	scanf("%d",&numero);
	printf("Ingrese una potencia: ");
	scanf("%d",&exponente);
	printf("El resultado es %d \n\n",CalculoPotencia(numero,exponente));
}
//Calculo de la potencia de un numero
int CalculoPotencia(int numero, int exponente){
	if(exponente>1){
		return numero * CalculoPotencia(numero,exponente - 1);
	}else{
		if(exponente = 0){
			return 1;
		}else{
			return numero;
		}
	}
}
//Suma Arreglo
int SumaArreglo(){
	int arreglo[4];
	int resultado;
	int numero;
	
	printf("\nIngrese 1er numero del arreglo: ");
	scanf("%d",&arreglo[0]);
	printf("Ingrese 2do numero del arreglo: ");
	scanf("%d",&arreglo[1]);
	printf("Ingrese 3er numero del arreglo: ");
	scanf("%d",&arreglo[2]);
	printf("Ingrese 4to numero del arreglo: ");
	scanf("%d",&arreglo[3]);
	printf("Ingrese el numero que decidira la suma: ");
	scanf("%d",&numero);
	
	resultado = suma_arreglo(arreglo,numero,0);
	printf("El resultado es %d\n\n",resultado);
}
//Calculo de suma de arreglo
int suma_arreglo(int array[], int numero, int i){
	if (i == 4){
		return 0;
	}else{
		if(array[i] >= numero){
		return array[i] + suma_arreglo(array,numero,i+1);	
		}else{
			return 0 + suma_arreglo(array,numero,i+1);
		}
	}
}
