/* 5127722 */

#include "../include/pila.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoLista *TNodoLista;
typedef struct repLista *TLista;

struct nodoLista {
	nat dato;
	TNodoLista siguiente; 
};

struct repLista {
	TNodoLista LInicio;
	TNodoLista LFinal;
};

struct _rep_pila {
	TLista datos;
	int cantidadDatos;
	int tamanio;
};

static void liberarLista(TNodoLista aLiberar){
	if (aLiberar!=NULL){
		liberarLista((*aLiberar).siguiente);
		delete aLiberar;
	}	
}

static TLista insertarInicioLista(nat elem, TLista lis) {
	TNodoLista nuevo=new nodoLista;	
	(*nuevo).dato=elem;
	(*nuevo).siguiente=(*lis).LInicio;
	if ((*lis).LInicio==NULL)
		(*lis).LFinal=nuevo;
	(*lis).LInicio=nuevo;		
	return lis;
}

TPila crearPila(nat tamanio) {
	TPila p = new _rep_pila;
	(*p).datos=new repLista;
	(*p).tamanio=tamanio;
	(*p).cantidadDatos=0;
	(*(*p).datos).LInicio=(*(*p).datos).LFinal=NULL;
	return p;
}

TPila apilar(nat num, TPila p){
	if (!estaLlenaPila(p)){
		(*p).datos = insertarInicioLista(num,(*p).datos);
		(*p).cantidadDatos++;
	}
	return p;
}

TPila desapilar(TPila p){
	if (!estaVaciaPila(p)){
		TNodoLista aBorrar=(*(*p).datos).LInicio;
		if ((*p).cantidadDatos==1)
			(*(*p).datos).LInicio=(*(*p).datos).LFinal=NULL;
		else
			(*(*p).datos).LInicio=(*(*(*p).datos).LInicio).siguiente;
		delete aBorrar;
		(*p).cantidadDatos--;
	}
	return p;
}

void liberarPila(TPila p){
	TNodoLista aLiberar=(*(*p).datos).LInicio;
	delete (*p).datos;
	delete p;
	liberarLista(aLiberar);
}

bool estaVaciaPila(TPila p){
	return (*p).cantidadDatos==0;
}

bool estaLlenaPila(TPila p){
	return (*p).cantidadDatos==(*p).tamanio;
}

nat cima(TPila p){
	return (*(*(*p).datos).LInicio).dato;
}
