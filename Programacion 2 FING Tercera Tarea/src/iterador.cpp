/* 5127722 */

#include "../include/iterador.h"
#include "../include/info.h"
#include "../include/cadena.h"
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

struct _rep_iterador {
	bool reiniciado;
	TNodoLista posicion;
	TLista datos;
};

static TLista insertarFinalLista(nat elem, TLista lis) {
	TNodoLista nuevo=new nodoLista;
	(*nuevo).siguiente=NULL;	
	(*nuevo).dato=elem;
	if ((*lis).LInicio==NULL)
		(*lis).LInicio=nuevo;
	else
		(*lis).LFinal=(*(*lis).LFinal).siguiente=nuevo;
	(*lis).LFinal=nuevo;	
	
	return lis;
}

TIterador crearIterador(){
	TIterador iter=new _rep_iterador;
	(*iter).datos=new repLista;
	(*(*iter).datos).LInicio=(*(*iter).datos).LFinal=NULL;
	(*iter).posicion=NULL;
	(*iter).reiniciado=false;
	
	return iter;
}

TIterador agregarAIterador(nat elem, TIterador iter){
	if (!(*iter).reiniciado){
		(*iter).datos=insertarFinalLista(elem,(*iter).datos);
	}
	return iter;
}

TIterador reiniciarIterador(TIterador iter){
	(*iter).reiniciado=true;
	if ((*(*iter).datos).LFinal!=NULL)
		(*iter).posicion=(*(*iter).datos).LInicio;
	return iter;
}

TIterador avanzarIterador(TIterador iter){
	if (estaDefinidaActual(iter))
		(*iter).posicion=(*(*iter).posicion).siguiente;
	return iter;
}

nat actualEnIterador(TIterador iter){
	return (*(*iter).posicion).dato;
}

bool estaDefinidaActual(TIterador iter){
	return (*iter).posicion!=NULL;
}

static void liberarLista(TNodoLista aLiberar){
	if (aLiberar!=NULL){
		liberarLista((*aLiberar).siguiente);
		delete aLiberar;
	}	
}

void liberarIterador(TIterador iter){
	TNodoLista aLiberar=(*(*iter).datos).LInicio;
	delete (*iter).datos;
	delete iter;
	liberarLista(aLiberar);	
}
