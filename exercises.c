#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List* crea_lista() {
   List* L = create_list(); //se crea la lista

   for(int i = 1 ; i <= 10 ; i++) { //recorro la lista del 1 al 10
      int* elem = malloc(sizeof(int)); //reservo la memoria
      *elem = i; //guardo el valor
      pushBack(L, elem); //inserto el elemento al final de la lista
   }
   return L; //retorno la lista
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
   int suma = 0; //creo una variable suma en 0
   int *dato; //creo un puntero para recorrer los datos de la lista

   dato = first(L); //obtengo el primer dato de la lista
   while (dato != NULL) { //mientras haya elementos
      suma += *dato; //sumo el valor apuntado por dato
      dato = next(L); //avanzo al siguiente elemento de la lista
   }
   return suma; //retorno la suma de todos los elementos
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List*L, int elem){
   int *dato = first(L); //me posiciono en el primer elemento de la lista

   while (dato != NULL) { //mientras haya elementos
      if (*dato == elem) { //si el valor actual es igual al elemento que quiero eliminar
         free(popCurrent(L)); //elimino el elemento actual y libero su memoria
         dato = next(L); //avanzo al siguiente
      } else {
         dato = next(L); //si no se elimina, avanzo al siguiente
      }
   }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(Stack* P1, Stack* P2) {
   Stack* aux = create_stack(); //creo una pila aux
   void* dato; //puntero para guardar temporalmente los elementos de la pila

   while (top(P1) != NULL) { //mientras haya elementos
      dato = pop(P1); //saco el elemento que esta en el tope de P1
      push(aux, dato); //lo guardo en la pila aux
   }

   while (top(aux) != NULL) { //mientras haya elementos
      dato = pop(aux); //saco el elemento de la pila aux
      push(P1, dato); //lo devuelvo a P1 para recuperar su orden original
      push(P2, dato); //tambien lo agrego a P2 para hacer la copia
   }
}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

/*
La funcion recorre la cadena y utiliza una pila para guardar los parentesis de apertura. Cuando encuentra uno de cierre, verifica que coincida con el ultimo abierto. Si no coinciden retorna 0, y si al final de la pila queda vacia, retorna 1 indicando que los parentesis estan balanceados.
*/
int parentesisBalanceados(char *cadena) {
   Stack *P = create_stack();
   for (int i = 0; cadena[i] != '\0'; i++) {
      if (cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[') {
         push(P, (void*)(long)cadena[i]);
      }
      else if (cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']') {
         if (top(P) == NULL) {
            return 0;
         }
         char tope = (char)(long)pop(P);
         if ((cadena[i] == ')' && tope != '(') || (cadena[i] == '}' && tope != '{') || (cadena[i] == ']' && tope != '[')) {
            return 0;
         }
      }
   }
   if (top(P) == NULL) {
      return 1;
   }
   return 0;
}

