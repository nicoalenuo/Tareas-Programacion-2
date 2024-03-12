/* 5127722 */

#include "../include/binario.h"
#include "../include/colaBinarios.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoListaCola *TNodoListaCola;
typedef struct repListaCola *TListaCola;

struct nodoListaCola {
	TBinario dato;
	TNodoListaCola siguiente;
	TNodoListaCola anterior;
};

struct repListaCola {
	TNodoListaCola LInicio;
	TNodoListaCola LFinal;
};

struct _rep_colaBinarios {
	TListaCola datos;
};

static void liberarListaCola(TNodoListaCola aLiberar){ //No borra los binarios
	if (aLiberar!=NULL){
		liberarListaCola((*aLiberar).siguiente);
		delete aLiberar;
	}	
}

static TListaCola insertarInicioListaCola(TBinario b, TListaCola lis) {
	TNodoListaCola nuevo=new nodoListaCola;	
	(*nuevo).dato=b;
	(*nuevo).siguiente=(*lis).LInicio;
	(*nuevo).anterior=NULL;
	if ((*lis).LInicio==NULL)
		(*lis).LFinal=nuevo;
	else
		(*(*lis).LInicio).anterior=nuevo;
	(*lis).LInicio=nuevo;		
	return lis;
}

TColaBinarios crearColaBinarios(){
	TColaBinarios c = new _rep_colaBinarios;
	(*c).datos=new repListaCola;
	(*(*c).datos).LInicio=(*(*c).datos).LFinal=NULL;
	return c;
}

TColaBinarios encolar(TBinario b, TColaBinarios c){
	(*c).datos = insertarInicioListaCola(b,(*c).datos);
	return c;
}

TColaBinarios desencolar(TColaBinarios c){
	if (!estaVaciaColaBinarios(c)){
		TNodoListaCola aBorrar=(*(*c).datos).LFinal;
		if ((*(*(*c).datos).LInicio).siguiente==NULL)
			(*(*c).datos).LInicio=(*(*c).datos).LFinal=NULL;
		else{
			(*(*(*(*c).datos).LFinal).anterior).siguiente=NULL;
			(*(*c).datos).LFinal=(*(*(*c).datos).LFinal).anterior;
		}
		delete aBorrar;
	}
	return c;
}

void liberarColaBinarios(TColaBinarios c){
	TNodoListaCola aLiberar=(*(*c).datos).LInicio;
	delete (*c).datos;
	delete c;
	liberarListaCola(aLiberar);
}

bool estaVaciaColaBinarios(TColaBinarios c){
	return (*(*c).datos).LInicio==NULL;
}

TBinario frente(TColaBinarios c){
	return (*(*(*c).datos).LFinal).dato;
}
