#include <stdio.h>
#include <string.h>

int invertir (int numero,int aux){
  if (numero < 10) {
    return aux*10+numero;
  }else{
    return invertir (numero/10,aux*10+numero%10);
  }
}

int main() {
  int numero;
  int resultado = 0;

  printf("Ingrese un numero para invertir: ");
  scanf("%d",&numero);
  resultado = invertir(numero,0);
  printf("El numero invertido es: %d ", resultado);
}
