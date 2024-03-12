/* 5127722 */

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/grafo.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoBucketVecinos *TBucketV;
typedef struct listaBuckets *TListaBuckets;

struct nodoBucketVecinos {
	nat v;
	double d;
	TBucketV siguiente; 
};

struct listaBuckets {
	nat cantidadBuckets;
	TBucketV primBucket; 
};

struct _rep_grafo{
	nat cantV;
	nat cantA;
	nat cantAT;
	TListaBuckets* vertices;
};

//Funciones auxiliares

static TBucketV agregarABucketV (nat v, double d, TBucketV bucket){
	if (bucket==NULL || (*bucket).v>v ){
		TBucketV nuevo = new nodoBucketVecinos;
		(*nuevo).v=v;
		(*nuevo).d=d;
		(*nuevo).siguiente = bucket;
		return nuevo;
	}
	else{
		(*bucket).siguiente =  agregarABucketV(v,d,(*bucket).siguiente);
		return bucket;
	}	
}

static TBucketV buscarEnBucketV (nat v, TBucketV bucket){
	if (bucket==NULL)
		return NULL;
	else if ((*bucket).v!=v)
		return buscarEnBucketV(v, (*bucket).siguiente);
	else
		return bucket;
}

static void liberarBucketV  (TBucketV bucket){
	if (bucket!=NULL){
		liberarBucketV((*bucket).siguiente);
		delete bucket;
	}
}

//Fin funciones auxiliares

TGrafo crearGrafo(nat N, nat M){
	TGrafo nuevo = new _rep_grafo;
	(*nuevo).cantV=N;
	(*nuevo).cantA=0;
	(*nuevo).cantAT=M;
	(*nuevo).vertices = new TListaBuckets[N+1];
	nat i=0;
	while (i<=N){
		(*nuevo).vertices[i]=new listaBuckets;
		(*(*nuevo).vertices[i]).cantidadBuckets=0;
		(*(*nuevo).vertices[i]).primBucket=NULL;
		i++;
	}	
	return nuevo;
}

nat cantidadVertices(TGrafo g){
	return (*g).cantV;
}

bool hayMParejas(TGrafo g){
	return (*g).cantA==(*g).cantAT;
}

TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){
	(*(*g).vertices[v1]).primBucket=agregarABucketV(v2,d,(*(*g).vertices[v1]).primBucket);
	(*(*g).vertices[v2]).primBucket=agregarABucketV(v1,d,(*(*g).vertices[v2]).primBucket);
	(*(*g).vertices[v1]).cantidadBuckets++;
	(*(*g).vertices[v2]).cantidadBuckets++;
	(*g).cantA++;
	return g;
}

bool sonVecinos(nat v1, nat v2, TGrafo g){
	bool v1TieneMas;
	if ((*(*g).vertices[v2]).cantidadBuckets<(*(*g).vertices[v1]).cantidadBuckets)
		v1TieneMas=true;
	else
		v1TieneMas=false;
	
	if (v1TieneMas)
		return buscarEnBucketV(v1,(*(*g).vertices[v2]).primBucket)!=NULL;
	else
		return buscarEnBucketV(v2,(*(*g).vertices[v1]).primBucket)!=NULL;
}

double distancia(nat v1, nat v2, TGrafo g){
	bool v1TieneMas;
	if ((*(*g).vertices[v2]).cantidadBuckets<(*(*g).vertices[v1]).cantidadBuckets)
		v1TieneMas=true;
	else
		v1TieneMas=false;
	
	if (v1TieneMas)
		return (*buscarEnBucketV(v1,(*(*g).vertices[v2]).primBucket)).d;
	else
		return (*buscarEnBucketV(v2,(*(*g).vertices[v1]).primBucket)).d;
}

TIterador vecinos(nat v, TGrafo g){
	TIterador iter = crearIterador();
	TBucketV vec = (*(*g).vertices[v]).primBucket;
	while (vec!=NULL){
		iter = agregarAIterador((*vec).v, iter);
		vec = (*vec).siguiente;
	}
	return iter;
}

void liberarGrafo(TGrafo g){
	nat i=0;
	while (i<=(*g).cantV){
		liberarBucketV((*(*g).vertices[i]).primBucket);
		delete (*g).vertices[i];
		i++;
	}
	delete [](*g).vertices;
	delete g;
}
