#include "Main.h"

int main(void){
	int opcion;
	int opcion2;
	int opcion3;
	int opcion4;
	int posicion=0;
	int cantidad=0;
    Dato elDato;

	//CREO LA COLA
    Cola laCola = inicializarCola();

    //CREO EL TIPO NODO
    Nodo *miNodo;
	do{
		opcion = menu(opcion);
		switch (opcion){
			case 1:
                     if(colaVacia(&laCola) == OK){
                        printf("La Cola esta vacia\n");
                    }else{
                        printf("La Cola tiene elementos\n");
                    }
			break;
			case 2:
                    cantidad = cantidadElementos(&laCola);
                    if(cantidad == ERROR){
                        printf("La Cola esta vacia\n");
                    }else{
                        printf("La Cola tiene %d elementos\n",cantidad);
                    }
			break;
			case 3:
                    Imprimir(&laCola);
			break;
			case 4:
                    do{
                    opcion2 = subMenuEliminar(opcion2);
                    switch(opcion2){
                    case 1:
                            if(eliminarCola(&laCola)==OK){
                                printf("La Cola se elimino Correctamente");
                            }else{
                                printf("No hay una Cola que eliminar");
                            }
                            opcion2 = 2;
                    break;
                    }
                    }while(opcion2 < 2);

			break;
			case 5:
                     elDato.numero = obtenerElementoCabeza(&laCola);
                                if(elDato.numero != ERROR){
                                    printf("El elemento obtenido es %d \n",elDato);
                                }else{
                                   printf("La cola esta vacia\n");
                                }
			break;
			case 6:
                    if(Desencolar(&laCola) == OK){
                        printf("El elemento se elimino Correctamente\n");
                    }else{
                        printf("La cola esta vacia");
                    }
			break;
			case 7:
                    printf("Ingrese el elemento a guardar: ");
                    scanf("%d",&elDato);
                    miNodo = crearNodo(elDato);
                    if(encolar(&laCola,miNodo) == OK){
                        printf("El elemento se agrego Correctamente\n");
                    }else{
                        printf("Error al guardar el elemento\n");
                        }
            break;
		}
	}while (opcion < 8);
}

int menu(int opcion){
	printf("\n------Trabajo Practico N 4 TDA Cola------\n\t1-  Consulta Cola Vacia.\n"
			 "\t2-  Determinar la cantidad de elementos de la Cola.\n"
             "\t3-  Listar Cola.\n"
			 "\t4-  Eliminar Cola.\n"
             "\t5-  Obtener el elemento de la cabeza de la cola.\n"
             "\t6-  Desencolar un elemento de la Cola.\n"
             "\t7-  Encolar un elemento de la Cola.\n"
             "\t8-  Salir del programa.\n"
             "Ingrese una opcion: ");
		scanf("%d",&opcion);
	return opcion;
}

int subMenuEliminar(int opcion2){
    printf("\n Seguro que desea eliminar la Cola\n"
           "\t1- Si eliminar Cola\n"
           "\t2- Volver\n"
           "Ingrese una opcion: ");
           scanf("%d",&opcion2);
           return opcion2;
}
