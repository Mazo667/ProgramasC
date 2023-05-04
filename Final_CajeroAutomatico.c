#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int loguearse(char str[]){
    char clave[] = "1234";
    char contra[] = "0000";
    int vf;
    printf("Ingrese clave: ");
    scanf("%s",contra);
    !strcmp (contra, clave) ?
       vf=1:
       vf==2;
       if (vf==1){
        return 1;
       }else {
        return 2;
       }
       
}
void menu(){
    printf("1) Ingresar dinero\n2) Retirar Dinero\n3) Calcular Saldo\n4) Salir\nIngrese la opcion:  ");
}
void salir(){
    printf("Adios");
}

float ingresardinero(float dinero){
    float monto = 0;
    printf("Ingrese el monto a depositar: ");
    scanf("%f",&monto);
    return monto;
}
float retirardinero(float dinero,float disponible){
    float monto = 0;
    printf("Ingrese el monto a retirar: ");
    scanf("%f",&monto);
    if (monto < disponible){
        return monto;
    }else{
        printf("No dispone el sueldo suficiente\n");
        return 0;
    }
    
}
int main() {
    char clave[4];
    int opcion = 0;
    float sueldo = 10000;
    float operacion = 0;

    if (loguearse(clave) == 1){
        printf("Clave Correcta\n");
        do {
        menu();
        scanf("%d",&opcion);
        switch (opcion){
            case 1: sueldo = (sueldo + ingresardinero(operacion));
            break;
            case 2: sueldo = (sueldo - retirardinero(operacion,sueldo));
            break;
            case 3: printf("%.2f pesos.\n",sueldo);
            break;
            case 4: salir();
            break;
        }
        }
        while (opcion < 4);
    }else{
        printf("Clave Incorrecta");
    }
    return 0;
}
