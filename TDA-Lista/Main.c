#include "Main.h"

int main(void){
	int opcion;
	int opcion2;
	int opcion3;
	int opcion4;
	int posicion=0;
	int cantidad=0;
    Dato elDato;

	//CREO LA LISTA
    Lista miLista = inicializarLista();

    //CREO EL TIPO NODO
    Nodo *miNodo;
	do{
		opcion = menu(opcion);
		switch (opcion){
			case 1: do{
					opcion2 = SubMenuAgregar(opcion2);
						switch (opcion2){
						case 1:
                                 printf("Ingrese el elemento a guardar: ");
                                 scanf("%d",&elDato);
                                 miNodo = crearNodo(elDato);
                                if(agregarAlPrincipio(&miLista,miNodo) == OK){
                                    printf("El elemento se agrego Correctamente\n");
                                }else{
                                    printf("Error al pedido de Memoria\n");
                                }
						break;
						case 2:
                                printf("Ingrese el elemento a guardar: ");
                                scanf("%d",&elDato);
                                miNodo = crearNodo(elDato);
                                if(agregarAlFinal(&miLista,miNodo) == OK){
                                    printf("El elemento se agrego Correctamente\n");
                                }else{
                                    printf("Error al pedido de Memoria\n");
                                }
						break;
						case 3:
                                printf("Ingrese la posicion que va a ir el elemento: ");
                                scanf("%d",&posicion);
                                printf("Ingrese el elemento a guardar: ");
                                scanf("%d",&elDato);

                                    miNodo = crearNodo(elDato);
                                    if(agregarEnPosicion(&miLista,miNodo,posicion) == OK){
                                  printf("El elemento se agrego Correctamente\n");
                                    }else{
                                        printf("Error al pedido de Memoria\n");
                                        }
                        break;
					}
				}while (opcion2 < 4);
			break;
			case 2: do{
					opcion3 = SubMenuEliminar(opcion3);
						switch (opcion3){
						case 1:
                                if(eliminarPrimerElemento(&miLista) == OK){
                                    printf("El elemento se elimino Correctamente\n");
                                }else{
                                    printf("No hay elementos en la lista\n");
                                }
						break;
						case 2:
                                if(eliminarUltimoElemento(&miLista) == OK){
                                    printf("El elemento se elimino Correctamente\n");
                                }else{
                                    printf("No hay elementos en la lista\n");
                                }
						break;
						case 3:
                                printf("Ingrese la posicion que va a eliminar el elemento: ");
                                scanf("%d",&posicion);
                                if(posicion < miLista.tamanio){
                                    if(eliminarElementoEnPosicion(&miLista,posicion) == OK){
                                        printf("El elemento se elimino Correctamente\n");
                                    }else{
                                        printf("No hay elementos en la lista\n");
                                    }
                                }else{
                                printf("Por favor introduzca una posicion existente en la lista\n");
                                }

						break;
					}
				}while (opcion3 < 4);
			break;
			case 3:
                    cantidad = cantidadElementos(&miLista);
                    if(cantidad == ERROR){
                        printf("La lista esta vacia\n");
                    }else{
                        printf("La lista tiene %d elementos\n",cantidad);
                    }
			break;
			case 4:
                    Imprimir(&miLista);
			break;
			case 5:
                    if(eliminarLista(&miLista)==OK){
                        printf("La lista se elimino Correctamente");
                    }else{
                        printf("No hay lista que eliminar");
                    }
			break;
			case 6: do{
					opcion4 = SubMenuObtener(opcion4);
						switch (opcion4){
						case 1:
                                elDato.NUMERO = obtenerPrimerElemento(&miLista);
                                if(elDato.NUMERO != ERROR){
                                    printf("El elemento obtenido es %d \n",elDato);
                                }else{
                                   printf("Error no se encontro la posicion o la lista esta vacia\n");
                                }

						break;
						case 2:
                                elDato.NUMERO = obtenerUltimoElemento(&miLista);
                                if(elDato.NUMERO != ERROR){
                                    printf("El elemento obtenido es %d \n",elDato);
                                }else{
                                    printf("Error no se encontro la posicion o la lista esta vacia\n");
                                }
						break;
						case 3:
                                printf("Ingrese la posicion que va a obtener el elemento: ");
                                scanf("%d",&posicion);
                                elDato.NUMERO = obtenerElementoDeterminado(&miLista,posicion);
                                if(elDato.NUMERO != ERROR){
                                    printf("El elemento obtenido es %d \n",elDato);
                                }else{
                                    printf("Error no se encontro la posicion o la lista esta vacia\n");
                                }
						break;
					}
				}while (opcion4 < 4);
			break;
            case 7:
                    if(listaVacia(&miLista) == OK){
                        printf("La lista esta vacia\n");
                    }else{
                        printf("La lista tiene elementos\n");
                    }
			break;
		}
	}while (opcion < 8);
}

int menu(int opcion){
	printf("\n------Trabajo Practico N 3 TDA Lista Doble Enlazada------\n\t1-  Agregar elementos a la lista.\n"
			 "\t2-  Eliminar Elementos de la lista.\n"
             "\t3-  Cantidad de elementos de la lista.\n"
             "\t4-  Listar lista.\n"
			 "\t5-  Eliminar lista.\n"
             "\t6-  Obtener un elemento de la lista.\n"
             "\t7-  Consulta lista vacia.\n"
             "\t8-  Salir del programa.\n"
             "Ingrese una opcion: ");
		scanf("%d",&opcion);
	return opcion;
}

int SubMenuAgregar(int opcion){
	printf("\t1)  Agregar elemento al principio de la lista.\n"
             "\t2)  Agregar elemento al final de la lista.\n"
             "\t3)  Agregar un elemento en una posicion\n"
             "\t4) Volver\n"
             "Ingrese una opcion: ");
		scanf("%d",&opcion);
		return opcion;
	}

int SubMenuEliminar(int opcion){
	printf("\t1)  Eliminar primer elemento de la lista.\n"
             "\t2)  Eliminar ultimo elemento de la lista.\n"
             "\t3)  Eliminar un elemento determinado de la lista.\n"
             "\t4) Volver\n"
             "Ingrese una opcion: ");
		scanf("%d",&opcion);
		return opcion;
}

int SubMenuObtener(int opcion){
	printf("\t1)  Obtener el primer elemento de la lista.\n"
             "\t2)  Obtener el ultimo elemento de la lista.\n"
             "\t3)  Obtener un elemento determinado de la lista.\n"
             "\t4) Volver\n"
             "Ingrese una opcion: ");
		scanf("%d",&opcion);
		return opcion;
}
