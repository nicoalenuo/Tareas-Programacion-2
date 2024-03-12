/* 5127722 */

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/colaBinarios.h"
#include "../include/conjunto.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/iterador.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2){
	TConjunto dif = diferenciaDeConjuntos(c2,c1);
	TConjunto res = diferenciaDeConjuntos(c2, dif);
	liberarConjunto(dif);
	
	return res;
}

nat cantidadEnIterador(TIterador it){
	it = reiniciarIterador(it);
	int cont=0;
	while (estaDefinidaActual(it)){
		cont++;
		avanzarIterador(it);
	}
	return cont;
}

TIterador recorridaPorNiveles(TBinario b){
	TIterador t = crearIterador();
	if (b!=NULL){
		TPila p = crearPila(INT_MAX);
		TColaBinarios c = crearColaBinarios();
		c = encolar(b,c);
		c = encolar(NULL,c);
		while (!estaVaciaColaBinarios(c)){
			b = frente(c);
			c = desencolar(c);
			if (b==NULL && !estaVaciaColaBinarios(c)){
				p = apilar(UINT_MAX,p);
				c = encolar(NULL,c);
			}
			else if (b!=NULL){
				p = apilar(natInfo(raiz(b)),p);
				if (!esVacioBinario(derecho(b)))
					c = encolar (derecho(b),c);
				if (!esVacioBinario(izquierdo(b)))
					c = encolar(izquierdo(b),c);
			}
		}
		liberarColaBinarios(c);
		while (!estaVaciaPila(p)){
			agregarAIterador(cima(p),t);
			p = desapilar(p);					
		}
		liberarPila(p);
	}
	return t;
}

static void enAlgunoAux (TIterador a, TIterador b, TIterador &res){
	bool defA=estaDefinidaActual(a);
	bool defB=estaDefinidaActual(b);
	if (defA || defB){
		if (defA && !defB){
			res = agregarAIterador(actualEnIterador(a),res);
			avanzarIterador(a);
		}
		else if (defA && defB){
			if (actualEnIterador(a) < actualEnIterador(b)){
				res = agregarAIterador(actualEnIterador(a),res);
				a = avanzarIterador(a);
			}
			else if (actualEnIterador(a) > actualEnIterador(b)){
				res = agregarAIterador(actualEnIterador(b),res);
				b = avanzarIterador(b);
			}
			else{
				res = agregarAIterador(actualEnIterador(a),res);
				a = avanzarIterador(a);
				b = avanzarIterador(b);
			}
		}
		else{
			res = agregarAIterador(actualEnIterador(b),res);
			avanzarIterador(b);
		}
		enAlgunoAux(a,b,res);
	}
}

TIterador enAlguno(TIterador a, TIterador b){
	TIterador res = crearIterador();
	a=reiniciarIterador(a);
	b=reiniciarIterador(b);
	enAlgunoAux(a,b,res);
	return res;
}

TIterador soloEnA(TIterador a, TIterador b){
	TIterador res = crearIterador();
	a=reiniciarIterador(a);
	b=reiniciarIterador(b);
	while (estaDefinidaActual(a)){
		if (!estaDefinidaActual(b) || actualEnIterador(a) < actualEnIterador(b)){
			res = agregarAIterador(actualEnIterador(a),res);
			a = avanzarIterador(a);
		}
		else if (actualEnIterador(a) == actualEnIterador(b)){
			a = avanzarIterador(a);
			b = avanzarIterador(b);
		}
		else
			b = avanzarIterador(b);
	}
	return res;
}

static TCadena nivelEnBinarioAux(nat l,TCadena &cad, TBinario b){
	if (!esVacioBinario(b)){
		if (l==1){
			cad = insertarAlFinal(copiaInfo(raiz(b)),cad);
		}
		else{
			cad = nivelEnBinarioAux(l-1,cad,izquierdo(b));	
			cad = nivelEnBinarioAux(l-1,cad,derecho(b));
		}
	}
	
	return cad;
}

TCadena nivelEnBinario(nat l, TBinario b){
	TCadena nuevo=crearCadena();
	nuevo = nivelEnBinarioAux(l,nuevo,b);
	return nuevo;
}

static bool esCaminoAux (TCadena c, TLocalizador l, TBinario b){
	if  (natInfo(raiz(b))==natInfo(infoCadena(l,c))){
			TBinario der=derecho(b);
			TBinario izq=izquierdo(b);
			TLocalizador sig=siguiente(l,c);
			if (der==NULL && izq==NULL && sig==NULL)
				return true;
			else if (der==NULL && izq==NULL && sig!=NULL)
				return false;
			else if ((der!=NULL || izq!=NULL) && sig==NULL)
				return false;
			else if (der==NULL && izq!=NULL && sig!=NULL)
				return esCaminoAux(c,sig,izq);
			else if (der!=NULL && izq==NULL && sig!=NULL)
				return esCaminoAux(c,sig,der);
			else
				return (esCaminoAux(c,sig,der) || esCaminoAux(c,sig,izq));
		}
		else
			return false;
}

bool esCamino(TCadena c, TBinario b){
	if (b==NULL && inicioCadena(c)==NULL)
		return true;
	else
		return esCaminoAux(c,inicioCadena(c),b);
}

bool pertenece(nat elem, TCadena cad) {
	TLocalizador paux=inicioCadena(cad);
	paux=siguienteClave(elem,paux,cad);
	return paux!=NULL;
}

nat longitud(TCadena cad) {
	TLocalizador paux=inicioCadena(cad);
	int cont=0;
	while (paux!=NULL){
		cont++;
		paux=siguiente(paux,cad);
	}
	return cont;
}

bool estaOrdenadaPorNaturales(TCadena cad) {
	if (esVaciaCadena(cad))
		return true;
	else{
		TLocalizador paux = inicioCadena(cad);
		while (paux!=NULL && menorEnCadena(paux,cad)==paux)
			paux=siguiente(paux,cad);
		return paux==NULL;	
	}			
}

bool hayNatsRepetidos(TCadena cad) {
	bool repite=false;
	if (!esVaciaCadena(cad)){
		TLocalizador paux1=inicioCadena(cad);
		TLocalizador paux2=inicioCadena(cad);
		
		while (paux2!=NULL && !repite){
			paux1=siguiente(paux2,cad);
			while (paux1!=NULL && !repite){
				if (natInfo(infoCadena(paux1,cad))==natInfo(infoCadena(paux2,cad)))
					repite=true;
				paux1=siguiente(paux1,cad);
			}
			paux2=siguiente(paux2,cad);
		}
	}
	return repite;
}

bool sonIgualesCadena(TCadena c1, TCadena c2) {
	TLocalizador paux1=inicioCadena(c1);
	TLocalizador paux2=inicioCadena(c2);
	while ((paux1!=NULL && paux2!=NULL) && (sonIgualesInfo(infoCadena(paux1,c1),infoCadena(paux2,c2)))){
		paux1=siguiente(paux1,c1);
		paux2=siguiente(paux2,c2);
	}
	return (paux1==NULL && paux2==NULL);
}

TCadena concatenar(TCadena c1, TCadena c2) {
	TCadena c3 = crearCadena();
	TCadena c1Cop = copiarSegmento(inicioCadena(c1), finalCadena(c1),c1);
	TCadena c2Cop = copiarSegmento(inicioCadena(c2), finalCadena(c2),c2);
	c3 = insertarSegmentoDespues(c1Cop,inicioCadena(c3),c3);
	c3 = insertarSegmentoDespues(c2Cop, finalCadena(c3),c3);
	
	return c3;
}

TCadena ordenar(TCadena cad) {
	TLocalizador menor;
	TLocalizador paux=inicioCadena(cad);
	while (paux!=NULL){
		menor=menorEnCadena(paux,cad);
		if (menor!=NULL)
			intercambiar(menor, paux,cad);
		paux=siguiente(paux,cad);
	}
	return cad;
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
	TLocalizador paux=inicioCadena(cad);
	TInfo agregarInfo;
	while (paux!=NULL){
			if (natInfo(infoCadena(paux,cad))==original){
				agregarInfo = crearInfo(nuevo, realInfo(infoCadena(paux,cad)));
				insertarAlFinal(agregarInfo,cad);
				cad = intercambiar(paux, finalCadena(cad),cad);
				cad = removerDeCadena(finalCadena(cad),cad);		
			}
			paux=siguiente(paux,cad);
		}
	return cad;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad) {
	TLocalizador desde=siguienteClave(menor,inicioCadena(cad),cad);
	TLocalizador hasta=siguienteClave(mayor,desde,cad);
	while (siguiente(hasta,cad)!=NULL && natInfo(infoCadena(siguiente(hasta,cad),cad))==mayor)
		hasta=siguiente(hasta,cad);
	TCadena cadN = copiarSegmento(desde,hasta,cad);
	return cadN;
}
