/* 5127722 */

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_binario {
	TInfo dato;
	TBinario izq;
	TBinario der;
};

static TBinario binarioBalanceadoAux(nat inicio, nat final,ArregloNats elems){
	TBinario b=new _rep_binario;
	(*b).izq=(*b).der=NULL;
	if (final-inicio==0)
		(*b).dato=crearInfo(elems[inicio],0);
	else{
		(*b).dato=crearInfo(elems[(final+inicio)/2],0);
		if (final-inicio==1){
			(*b).der=binarioBalanceadoAux(final,final,elems);
		}
		else{
			(*b).izq = binarioBalanceadoAux(inicio,((final+inicio)/2)-1,elems);
			(*b).der = binarioBalanceadoAux(((final+inicio)/2)+1,final,elems);
		}
	}
	return b;
}

TBinario binarioBalanceado(ArregloNats elems, nat n) {
	TBinario b = crearBinario();
	b = binarioBalanceadoAux(0,n-1,elems);
	return b;
}

/*TBinario mitadArreglo(ArregloNats elems,int anterior,int siguiente){
    if(anterior>siguiente){
        return NULL;
    }else{
        TBinario b=new _rep_binario;
        nat mitad=(anterior+siguiente)/2;
        TInfo t= crearInfo(elems[mitad],0);
        b->dato=t;
        b->izq= mitadArreglo(elems,anterior,mitad-1);
        b->der= mitadArreglo(elems,mitad+1,siguiente);
        return b;
    }
}
TBinario binarioBalanceado(ArregloNats elems, nat n){
    int aux=n-1;
    TBinario b= mitadArreglo(elems,0,aux);
    return b;
}*/

TBinario crearBinario() {
	TBinario nuevo=NULL;
	return nuevo;
}

TBinario insertarEnBinario(TInfo i, TBinario b){
	if (b==NULL){
		b=new _rep_binario;
		(*b).izq=(*b).der=NULL;
		(*b).dato = i;	
	}
	else {
		if (natInfo((*b).dato)<natInfo(i))
			(*b).der = insertarEnBinario(i,(*b).der);
		else if (natInfo((*b).dato)>natInfo(i))
			(*b).izq = insertarEnBinario(i,(*b).izq);
	}
	return b;	
}

TInfo mayor(TBinario b){
	if ((*b).der==NULL)
		return (*b).dato;
	else
		return mayor((*b).der);
}

TBinario removerMayor(TBinario b){
	if ((*b).der==NULL){
		TBinario aBorrar=b;
		b=(*b).izq;
		delete aBorrar;
	}
	else
		(*b).der=removerMayor((*b).der);
	return b;
}

static void esquinaMayor(TBinario &b){
	if ((*b).der==NULL)
		b=(*b).izq;
	else
		esquinaMayor((*b).der);
}

static TBinario punteroMayor(TBinario b){
	if ((*b).der==NULL)
		return b;
	else
		return punteroMayor((*b).der);
}

TBinario removerDeBinario(nat elem, TBinario b){
	if (natInfo((*b).dato) < elem)
		 (*b).der = removerDeBinario(elem,(*b).der);
	else if (natInfo((*b).dato) > elem)
		 (*b).izq = removerDeBinario(elem,(*b).izq);
	else{
		TBinario aBorrar=b;
		if ((*b).izq!=NULL){
			b=punteroMayor((*b).izq);
			esquinaMayor((*aBorrar).izq);
			(*b).izq=(*aBorrar).izq;
			(*b).der=(*aBorrar).der;
		}
		else if ((*b).der!=NULL){
			b=(*aBorrar).der;
		}
		else{
			b=NULL;	
		}
		liberarInfo((*aBorrar).dato);
		delete aBorrar;
	}
	return b;
}

void liberarBinario(TBinario b){
	if (b!=NULL){
		liberarBinario((*b).izq);
		liberarBinario((*b).der);
		liberarInfo((*b).dato);
		delete b;
	}	
}

bool esVacioBinario(TBinario b){
	return b==NULL;
}

static int esAvlAux (bool &avl, TBinario b){
	if (avl && b!=NULL){
		int altDer = esAvlAux(avl,(*b).der)+1;
		int altIzq = esAvlAux(avl,(*b).izq)+1;
		avl = (avl) && (altDer==altIzq || altDer==altIzq-1 || altDer==altIzq+1);
		if (altDer<altIzq)
			return altIzq;
		else
			return altDer;
	}
	return 0;
}

bool esAvl(TBinario b){
	bool avl=true;
	esAvlAux(avl,b);
	return avl;
}

TInfo raiz(TBinario b){
	return (*b).dato;
}

TBinario izquierdo(TBinario b){
	return (*b).izq;
}

TBinario derecho(TBinario b){
	return (*b).der;
}

TBinario buscarSubarbol(nat elem, TBinario b){
	if (b!=NULL){
		if (natInfo((*b).dato)==elem)
			return b;
		else if (natInfo((*b).dato)<elem)
			return buscarSubarbol(elem,(*b).der);
		else
			return buscarSubarbol(elem,(*b).izq);
	}
	else
		return b;
}

nat alturaBinario(TBinario b){
	if (esVacioBinario(b))
		return 0;
	else{
		int alturaIzq=alturaBinario((*b).izq);
		int alturaDer=alturaBinario((*b).der);
		if (alturaIzq<alturaDer)
			return alturaDer+1;
		else
			return alturaIzq+1;
	}
}

nat cantidadBinario(TBinario b){
	if (b==NULL)
		return 0;
	else
		return cantidadBinario((*b).izq)+cantidadBinario((*b).der)+1;
}

static double sumaUltimosPositivosAux (nat &i, double real, TBinario b){
	if (b!=NULL){
		real = sumaUltimosPositivosAux(i,real,(*b).der);
		if (i>0 && realInfo(raiz(b))>0){
			i=i-1;
			real=real+realInfo(raiz(b));
		}							
		real = sumaUltimosPositivosAux(i,real,(*b).izq);	
	}
	return real;
}

double sumaUltimosPositivos(nat i, TBinario b){
	return sumaUltimosPositivosAux(i,0,b);
}

static TCadena linealizacionAux(TCadena &cad, TBinario b){
	if (!esVacioBinario(b)){
		cad = linealizacionAux(cad,(*b).izq);
		cad = insertarAlFinal(copiaInfo(raiz(b)),cad);
		cad = linealizacionAux(cad,(*b).der);
	}
	
	return cad;
}

TCadena linealizacion(TBinario b){		
	TCadena nuevo=crearCadena();
	nuevo=linealizacionAux(nuevo,b);
	return nuevo;
}

static bool hayMenores(TBinario b, double cota){
	if (b==NULL)
		return false;
	else
		if (realInfo(raiz(b)) < cota)
			return true;
		else
			return hayMenores((*b).izq,cota) || hayMenores((*b).der,cota);
}

static void mayorCota (TBinario b, TBinario &mayor, double cota){
	if (b!=NULL){
		mayorCota((*b).der,mayor,cota);
		if (realInfo(raiz(b))<cota && mayor==NULL)
				mayor=b;
		if (mayor==NULL)
			mayorCota((*b).izq,mayor,cota);
	}
}

static TBinario menoresAux(double cota, TBinario nuevo, TBinario b){
	if (b!=NULL){
		if (realInfo(raiz(b))<cota){
			nuevo=insertarEnBinario(copiaInfo(raiz(b)),nuevo);
			nuevo=menoresAux(cota,nuevo,(*b).izq);
			nuevo=menoresAux(cota,nuevo,(*b).der);
		}
		else{
			bool hayMenoresDer=hayMenores((*b).der,cota);
			TBinario mayor;
			mayor=NULL;		
			mayorCota((*b).izq,mayor,cota);
			if (hayMenoresDer){
				if (mayor!=NULL){
					nuevo=insertarEnBinario(copiaInfo(raiz(mayor)),nuevo);
					nuevo=menoresAux(cota,nuevo,(*b).izq);
					nuevo=menoresAux(cota,nuevo,(*b).der);
				}
				else
					nuevo=menoresAux(cota,nuevo,(*b).der);
			}
			else
				if (mayor!=NULL)
					nuevo=menoresAux(cota,nuevo,(*b).izq);
		}
	}	
	return nuevo;
}

TBinario menores(double cota, TBinario b){
	TBinario nuevo=crearBinario();
	nuevo = menoresAux(cota,nuevo,b);
	return nuevo;
}

static void imprimirBinarioAux(TBinario b, int profundidad){
	int cont=0;
	if (b!=NULL){
		imprimirBinarioAux((*b).der,profundidad+1);
		while (cont<profundidad){
			printf("-");
			cont++;
		}
		printf("(%d,%.2f)\n",natInfo((*b).dato),realInfo((*b).dato));
		imprimirBinarioAux((*b).izq,profundidad+1);
	}
}

void imprimirBinario(TBinario b){
	printf("\n");
	imprimirBinarioAux(b,0);
}
