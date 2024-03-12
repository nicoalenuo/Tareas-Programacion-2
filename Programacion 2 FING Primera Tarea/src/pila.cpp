/* 5127722 */

#include "../include/pila.h"
#include "../include/lista.h"
#include "../include/utils.h"

#include<stdio.h>

struct _rep_pila {
	TLista lista_p;
};
TPila crearPila(){
	TPila pila = new _rep_pila;
	(*pila).lista_p=crearLista();
	return pila;
}
bool esVaciaPila(TPila pila){
	return (longitud((*pila).lista_p)==0);
}
TPila apilar(info_t nuevo, TPila pila){
	(*pila).lista_p=insertar(1, nuevo, (*pila).lista_p);
	return pila;
}
info_t cima(TPila pila){
	return infoLista(1,(*pila).lista_p);
}
TPila desapilar(TPila pila){
	(*pila).lista_p=remover(1,(*pila).lista_p);
	return pila;
}
