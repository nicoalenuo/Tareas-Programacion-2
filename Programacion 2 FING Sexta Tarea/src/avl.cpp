/* 5127722 */

#include "../include/avl.h"
#include "../include/binario.h"
#include "../include/info.h"
#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_avl{
	TAvl izquierda;
	TAvl derecha;
	nat dato;
	nat altura;
	nat cantidad;
};

static nat alturaTotal(TAvl avl){
	TAvl avlI=(*avl).izquierda;
	TAvl avlD=(*avl).derecha;
	if (avlI==NULL && avlD==NULL)
		return 0;
	else if (avlI==NULL && avlD!=NULL)
		return (*avlD).altura;
	else if (avlI!=NULL && avlD==NULL)
		return (*avlI).altura;
	else{
		if ((*avlI).altura>=(*avlD).altura)
			return (*avlI).altura;
		else
			return (*avlD).altura;
	}	
}

static nat cantidadTotal (TAvl avl){
	if ((*avl).izquierda == NULL && (*avl).derecha==NULL)
		return 0;
	else{
		if ((*avl).izquierda==NULL)
			return (*(*avl).derecha).cantidad;
		else if ((*avl).derecha==NULL) 
			return (*(*avl).izquierda).cantidad;
		else
			return (*(*avl).izquierda).cantidad + (*(*avl).derecha).cantidad;
	}
}

static TAvl rotarDer(TAvl avl){
    TAvl aux = (*avl).izquierda;
    (*avl).izquierda = (*aux).derecha;
    (*aux).derecha = avl;
	avl=aux;
	aux=(*aux).derecha;
	(*aux).altura = alturaTotal(aux) + 1;
    (*avl).altura = alturaTotal(avl) + 1;
    (*aux).cantidad = cantidadTotal(aux) + 1;
    (*avl).cantidad = cantidadTotal(avl) + 1;
    return avl;
}

static TAvl rotarIzq(TAvl avl){
    TAvl aux = (*avl).derecha;
    (*avl).derecha = (*aux).izquierda;
    (*aux).izquierda = avl;
    avl = aux;
    aux = (*aux).izquierda;
    (*aux).altura = alturaTotal(aux) + 1;
    (*avl).altura = alturaTotal(avl) + 1;
    (*aux).cantidad = cantidadTotal(aux) + 1;
    (*avl).cantidad = cantidadTotal(avl) + 1;
    return avl;
}

static TAvl rotarDerDoble(TAvl avl){
    (*avl).derecha = rotarDer((*avl).derecha);
	return rotarIzq(avl);
}

static TAvl rotarIzqDoble(TAvl avl){
     (*avl).izquierda =  rotarIzq((*avl).izquierda);
     return rotarDer(avl);
}

TAvl crearAvl(){
	TAvl avl=NULL;
	return avl;
}

bool estaVacioAvl(TAvl avl){
	return avl==NULL;
}

TAvl insertarEnAvl(nat elem, TAvl avl){
    if (avl == NULL){
        avl = new _rep_avl;
        (*avl).izquierda = (*avl).derecha = NULL;
        (*avl).dato = elem;
        (*avl).altura=1;
        (*avl).cantidad=1;
    }
    else{
		if ((*avl).dato < elem)
			(*avl).derecha  = insertarEnAvl(elem, (*avl).derecha);
        else 
			(*avl).izquierda = insertarEnAvl(elem, (*avl).izquierda);     
        (*avl).altura = alturaTotal(avl) + 1;
        (*avl).cantidad = cantidadTotal(avl) + 1;
        int dif = alturaDeAvl((*avl).izquierda)-alturaDeAvl((*avl).derecha);
        if (dif>1 && elem < (*(*avl).izquierda).dato)
			return rotarDer(avl);
        if (dif<-1 && elem > (*(*avl).derecha).dato)
			return rotarIzq(avl);	
        if (dif>1 && elem > (*(*avl).izquierda).dato)
            return rotarIzqDoble(avl);
        if (dif<-1 && elem < (*(*avl).derecha).dato)
			return rotarDerDoble(avl);
    }
    return avl;
}

TAvl buscarEnAvl(nat elem, TAvl avl){
	if (avl==NULL)
		return NULL;
	else{
		if (elem == (*avl).dato)
			return avl;
		else if ((*avl).dato < elem)
			return buscarEnAvl(elem, (*avl).derecha);
		else
			return buscarEnAvl(elem, (*avl).izquierda);
	}
}

nat raizAvl(TAvl avl){
	return (*avl).dato;
}

TAvl izqAvl(TAvl avl){
	return (*avl).izquierda;
}

TAvl derAvl(TAvl avl){
	return (*avl).derecha;
}

nat cantidadEnAvl(TAvl avl){
	if (avl!=NULL)
		return (*avl).cantidad;
	else
		return 0;
}

nat alturaDeAvl(TAvl avl){
	if (avl!=NULL)
		return (*avl).altura;
	else
		return 0;
}

static void enOrdenAvlAux(TIterador &it, TAvl avl){
	if (avl!=NULL){
		enOrdenAvlAux(it,(*avl).izquierda);
		it = agregarAIterador((*avl).dato,it);
		enOrdenAvlAux(it,(*avl).derecha);
	}	
}

TIterador enOrdenAvl(TAvl avl){
	TIterador nuevo=crearIterador();
	enOrdenAvlAux(nuevo,avl);
	return nuevo;
}

static TAvl arregloAAvlAux(nat inicio, nat final,ArregloNats elems){
	TAvl avl=new _rep_avl;
	(*avl).izquierda=(*avl).derecha=NULL;
	if (final-inicio==0){
		(*avl).dato=elems[inicio];
		(*avl).altura=1;
		(*avl).cantidad=1;
	}
	else{
		(*avl).dato=elems[(final+inicio)/2];
		if (final-inicio==1){
			(*avl).derecha=arregloAAvlAux(final,final,elems);
		}
		else{
			(*avl).izquierda = arregloAAvlAux(inicio,((final+inicio)/2)-1,elems);
			(*avl).derecha = arregloAAvlAux(((final+inicio)/2)+1,final,elems);
		}	
	}
	(*avl).altura = alturaTotal(avl) + 1;
	(*avl).cantidad = cantidadTotal(avl) + 1;
	return avl;
}

TAvl arregloAAvl(ArregloNats elems, nat n){
	TAvl avl = NULL;
	avl = arregloAAvlAux(0,n-1,elems);
	return avl;
}

static TAvl avlMinAux(int h, int &cont){
	TAvl nuevo=NULL;
	if (h>0){
		nuevo = new _rep_avl;
		(*nuevo).izquierda = avlMinAux(h-1,cont);	
		cont++;
		(*nuevo).dato=cont;
		(*nuevo).derecha = avlMinAux(h-2,cont);
		if (h==1){
			(*nuevo).altura=1;
			(*nuevo).cantidad=1;
		}
		else{
			(*nuevo).altura = alturaTotal(nuevo) + 1;
			(*nuevo).cantidad = cantidadTotal(nuevo) + 1;
		}
	}
	return nuevo;	
}

TAvl avlMin(nat h){
	TAvl nuevo = NULL;
	int cont=0;
	nuevo = avlMinAux(h,cont);
	if (nuevo!=NULL){
		(*nuevo).cantidad = cont;
		(*nuevo).altura=h;
	}
	return nuevo;
}

void liberarAvl(TAvl avl){
	if (avl!=NULL){
		liberarAvl((*avl).derecha);
		liberarAvl((*avl).izquierda);
		delete avl;
	}
}
