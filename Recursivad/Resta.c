//Realizar un procedimiento recursivo dado los valores se realice la division mediante restas sucesivas
#include <stdio.h>
#include <string.h>

int resta(int a, int b){
if (a < 0) {
    return a;
  } else {
    a = a - b;
    return resta(a, b);
  }
}

int main(){
int a = 0;
int b = 0;

  printf("Ingrese número a: ");
  scanf("%d", &a);
  printf("Ingrese número b: ");
  scanf("%d", &b);
  printf("La resta de %d entre %d es %d\n", a, b, resta(a, b));
}
