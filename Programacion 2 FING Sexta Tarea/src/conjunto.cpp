/* 5127722 */

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/conjunto.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoListaConjunto *TNodoListaConjunto;

struct nodoListaConjunto {
	nat dato;
	TNodoListaConjunto sig;
};

struct _rep_conjunto {
	TNodoListaConjunto primDato;
	TNodoListaConjunto ultDato;
	int cantidadDatos;
};

TConjunto crearConjunto(){
	TConjunto nuevo = new _rep_conjunto;
	(*nuevo).primDato=(*nuevo).ultDato=NULL;
	(*nuevo).cantidadDatos=0;
	return nuevo;
}

static TConjunto insertarAlFinalConjunto (nat elem, TConjunto c){
	TNodoListaConjunto nuevo = new nodoListaConjunto;
	(*nuevo).dato = elem;
	(*nuevo).sig=NULL;
	if ((*c).cantidadDatos==0)
		(*c).primDato = nuevo;
	else
		(*(*c).ultDato).sig = nuevo;		
	(*c).ultDato = nuevo;
	(*c).cantidadDatos=(*c).cantidadDatos+1;
	return c;
}

TConjunto singleton(nat elem){
	TConjunto c = crearConjunto();
	c = insertarAlFinalConjunto(elem, c);
	return c;
}

static void unionDeConjuntosAux (TNodoListaConjunto c1, TNodoListaConjunto c2, TConjunto res){
	bool defC1=c1!=NULL;
	bool defC2=c2!=NULL;
	while (defC1 || defC2){
		if (defC1 && !defC2){
			res = insertarAlFinalConjunto((*c1).dato,res);
			c1 = (*c1).sig;
		}
		else if (defC1 && defC2){
			if ((*c1).dato < (*c2).dato){
				res = insertarAlFinalConjunto((*c1).dato,res);
				c1 = (*c1).sig;
			}
			else if ((*c1).dato > (*c2).dato){
				res = insertarAlFinalConjunto((*c2).dato,res);
				c2 = (*c2).sig;
			}
			else{
				res = insertarAlFinalConjunto((*c1).dato,res);
				c1 = (*c1).sig;
				c2 = (*c2).sig;
			}
		}
		else{
			res = insertarAlFinalConjunto((*c2).dato,res);
			c2 = (*c2).sig;		
		}
		defC1=c1!=NULL;
		defC2=c2!=NULL;
	}
}

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
	TConjunto res = crearConjunto();
	unionDeConjuntosAux((*c1).primDato,(*c2).primDato,res);
	return res;
}

static void diferenciaDeConjuntosAux (TNodoListaConjunto c1, TNodoListaConjunto c2, TConjunto res){
	bool defC1=c1!=NULL;
	bool defC2=c2!=NULL;
	while (defC1){
		if (defC1 && !defC2){
			res = insertarAlFinalConjunto((*c1).dato,res);
			c1 = (*c1).sig;
		}
		else if (defC1 && defC2){
			if ((*c1).dato < (*c2).dato){
				res = insertarAlFinalConjunto((*c1).dato,res);
				c1 = (*c1).sig;
			}
			else if ((*c1).dato > (*c2).dato){
				c2 = (*c2).sig;
			}
			else{
				c1 = (*c1).sig;
				c2 = (*c2).sig;
			}
		}
		defC1=c1!=NULL;
		defC2=c2!=NULL;
	}
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
	TConjunto res = crearConjunto();
	diferenciaDeConjuntosAux((*c1).primDato,(*c2).primDato,res);
	return res;
}

bool perteneceAConjunto(nat elem, TConjunto c){
	TNodoListaConjunto l=(*c).primDato;
	while (l!=NULL && (*l).dato!=elem)
		l=(*l).sig;
	return l!=NULL;
}

bool estaVacioConjunto(TConjunto c){
	return (*c).cantidadDatos==0;
}

nat cardinalidad(TConjunto c){
	return (*c).cantidadDatos;
}

nat minimo(TConjunto c){
	return (*(*c).primDato).dato;
}

nat maximo(TConjunto c){
	return (*(*c).ultDato).dato;
}

TConjunto arregloAConjunto(ArregloNats elems, nat n){
	TConjunto nuevo = crearConjunto();
	nat cont=0;
	while (cont<n){
		nuevo = insertarAlFinalConjunto(elems[cont],nuevo);
		cont++;		
	}
	return nuevo;
}

TIterador iteradorDeConjunto(TConjunto c){
	TIterador nuevo = crearIterador();
	TNodoListaConjunto aux = (*c).primDato;
	while (aux!=NULL){
		agregarAIterador((*aux).dato,nuevo);
		aux=(*aux).sig;
	}
	return nuevo;
}

void liberarConjunto(TConjunto c){
	TNodoListaConjunto aux = (*c).primDato;
	TNodoListaConjunto ant=aux;
	while (ant!=NULL){
		aux=(*aux).sig;
		delete ant;
		ant=aux;
	}
	delete c;
}
