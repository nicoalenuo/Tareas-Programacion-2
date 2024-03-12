/* 5127722 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
	TInfo dato;
	TLocalizador anterior;
	TLocalizador siguiente;
};

struct _rep_cadena {
	TLocalizador inicio;
	TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { 
	return loc!=NULL; 
}

TCadena crearCadena() {
	TCadena cad = new _rep_cadena;
	(*cad).inicio = (*cad).final = NULL;
	return cad;
}

void liberarCadena(TCadena cad) {
	cad = borrarSegmento(inicioCadena(cad),finalCadena(cad),cad);
	delete cad;
}

bool esVaciaCadena(TCadena cad) {
	return (*cad).inicio==NULL;
}

TLocalizador inicioCadena(TCadena cad) {
	return (*cad).inicio;
}

TLocalizador finalCadena(TCadena cad) {
	return (*cad).final;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
	return (*loc).dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
	return (*loc).siguiente;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
	return (*loc).anterior;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
	if (!esVaciaCadena(cad))
		return loc==(*cad).final;
	else
		return false;
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
	if (!esVaciaCadena(cad))
		return loc==(*cad).inicio;
	else
		return false;
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
	TLocalizador nuevo=new nodoCadena;
	(*nuevo).siguiente=NULL;	
	(*nuevo).dato=i;	
	if (esVaciaCadena(cad)){
		(*cad).inicio=nuevo;
		(*nuevo).anterior=NULL;
	}
	else{
		(*nuevo).anterior=(*cad).final;
		(*(*cad).final).siguiente=nuevo;	
	}
	(*cad).final=nuevo; 
		
	return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
	TLocalizador nuevo = new nodoCadena;
	(*nuevo).dato=i;
	if (loc==(*cad).inicio){
		(*nuevo).anterior=NULL;
		(*(*cad).inicio).anterior=nuevo;
		(*cad).inicio=nuevo;	
	}
	else{
		(*nuevo).anterior=(*loc).anterior;	
		(*(*loc).anterior).siguiente=nuevo;
		(*loc).anterior=nuevo;	
	}
	(*nuevo).siguiente=loc;
	return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
	if (esInicioCadena(loc,cad) && esFinalCadena(loc,cad)){
		(*cad).inicio=(*cad).final=NULL;
	}
	else{
		if (esInicioCadena(loc, cad))
			(*cad).inicio=(*loc).siguiente;
		else
			(*(*loc).anterior).siguiente=(*loc).siguiente;
		
		if (esFinalCadena(loc, cad))
			(*cad).final=(*loc).anterior;	
		else
			(*(*loc).siguiente).anterior=(*loc).anterior;		
	}
	
	liberarInfo((*loc).dato);
	delete loc;
	return cad;	
}

void imprimirCadena(TCadena cad) {
	TLocalizador paux=(*cad).inicio;
		while (paux!=NULL){
			printf("(%d,%.2f)",natInfo((*paux).dato) ,realInfo((*paux).dato));
			paux=(*paux).siguiente;
		}
		printf("\n");
}	

TLocalizador kesimo(nat k, TCadena cad) {
	TLocalizador paux=(*cad).inicio;
	nat cont=1;
	if (k==0)
		return NULL;
	else{	
		while (paux!=NULL && cont<k){
			cont++;
			paux=(*paux).siguiente;
		}
		return paux;
	}
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
	if (esVaciaCadena(cad)){
			(*cad).inicio=(*sgm).inicio;
			(*cad).final=(*sgm).final;
	}	
	else{	
		if (!esVaciaCadena(sgm)){
			if (!esFinalCadena(loc,cad))
				(*(*loc).siguiente).anterior=(*sgm).final;
			else
				(*cad).final=(*sgm).final;
			(*(*sgm).final).siguiente=(*loc).siguiente;
			(*loc).siguiente=(*sgm).inicio;
			(*(*sgm).inicio).anterior=loc;
		}
	}
	delete sgm;
	return cad;	
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	TCadena cadN = crearCadena();
	if (!esVaciaCadena(cad))
		while (desde!=(*hasta).siguiente){	
			TInfo nuevo=copiaInfo((*desde).dato);
			cadN = insertarAlFinal(nuevo,cadN);
			desde=(*desde).siguiente;				
	}
	return cadN;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	if (!esVaciaCadena(cad)){
		TLocalizador paux;
		TLocalizador ultimo=(*hasta).siguiente;
		while (desde!=ultimo){
			paux=desde;
			desde=(*desde).siguiente;
			cad = removerDeCadena(paux, cad);		
		}
	}
	return cad;	
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
	(*loc).dato=i;
	return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
		TInfo aux=(*loc1).dato;
		(*loc1).dato=(*loc2).dato;
		(*loc2).dato=aux;
		return cad;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad){
	bool pertenece=false;
	TLocalizador paux=(*cad).inicio;
	while (paux!=NULL && pertenece==false){
		if (paux==loc)
			pertenece=true;
		paux=(*paux).siguiente;
	}
	return pertenece;
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	while (loc1!=NULL && loc1!=loc2)
			loc1=(*loc1).siguiente;	
	return (loc1!=NULL && loc2!=NULL);
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
	if (esVaciaCadena(cad))
		return NULL;
	else{
		TLocalizador paux=loc;
		loc=NULL;
		while (paux!=NULL && loc==NULL){
			if (natInfo((*paux).dato)==clave)
				loc=paux;
			paux=(*paux).siguiente;
		}
		return loc;		
	}
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
	if (esVaciaCadena(cad))
		return NULL;
	else{
		TLocalizador paux=loc;
		loc=NULL;
		while (paux!=NULL && loc==NULL){
			if (natInfo((*paux).dato)==clave)
				loc=paux;
			paux=(*paux).anterior;
		}
		return loc;		
	}
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
	TLocalizador paux=loc;
	TLocalizador menor=loc;
	while (paux!=NULL){
		if (natInfo((*paux).dato)<natInfo((*menor).dato))
			menor=paux;
		paux=(*paux).siguiente;
	}	
	return menor;
}
