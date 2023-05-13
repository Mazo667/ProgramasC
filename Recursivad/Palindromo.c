#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
	bool resultado;
	char cadena[20];
	
	
	printf("Ingrese un texto: ");
	scanf("%s",cadena);
	resultado = palindromo(cadena,0,strlen(cadena)-1);
	if(resultado == true){
		printf("Es palindromo");
		}else{
			printf("No es palindromo");
		}
}

int palindromo(char cadena[],int i, int j){
	
	if(cadena[i] == cadena[j]){
		if(i>=j){
			return true;
		}
		return palindromo(cadena,i+1,j-1);
	}else{
		return false;
	}
}
