/* 5127722 */

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/avl.h"
#include "../include/mapping.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoBucket *TBucket;

struct nodoBucket {
	TInfo dato;
	TBucket siguiente; 
};

struct _rep_mapping{
	nat cantAsociacionesT;
	nat cantAsociaciones;
	TBucket* buckets;
};

//Funciones auxiliares

static TBucket agregarABucket (nat clave, double valor, TBucket bucket){
	TBucket nuevo = new nodoBucket;
	(*nuevo).dato = crearInfo(clave,valor);
	(*nuevo).siguiente = bucket;
	return nuevo;
}

static TBucket eliminarDeBucket (nat clave, TBucket bucket){
	if (natInfo((*bucket).dato)!=clave){
		(*bucket).siguiente = eliminarDeBucket(clave, (*bucket).siguiente);
		return bucket;
	}
	else{
		TBucket aux=(*bucket).siguiente;
		liberarInfo((*bucket).dato);
		delete bucket;
		return aux;
	}	
}

static TBucket buscarEnBucket (nat clave, TBucket bucket){
	if (bucket==NULL)
		return NULL;
	else if (natInfo((*bucket).dato)!=clave)
		return buscarEnBucket(clave, (*bucket).siguiente);
	else
		return bucket;
}

static void liberarBucket(TBucket bucket){
	if (bucket!=NULL){
		liberarBucket((*bucket).siguiente);
		liberarInfo((*bucket).dato);
		delete bucket;
	}
}

//Fin funciones auxiliares

TMapping crearMap(nat M){
	TMapping nuevo = new _rep_mapping;
	(*nuevo).cantAsociacionesT=M;
	(*nuevo).cantAsociaciones=0;
	(*nuevo).buckets = new TBucket[M];
	nat i=0;
	while (i<=(*nuevo).cantAsociacionesT-1){
		(*nuevo).buckets[i]=NULL;
		i++;
	}
	return nuevo;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map){
	(*map).buckets[clave%(*map).cantAsociacionesT] = agregarABucket(clave,valor,(*map).buckets[clave%(*map).cantAsociacionesT]);
	(*map).cantAsociaciones++;
	return map;
}

TMapping desasociarEnMap(nat clave, TMapping map){
	(*map).buckets[clave%(*map).cantAsociacionesT] = eliminarDeBucket(clave,(*map).buckets[clave%(*map).cantAsociacionesT]);
	(*map).cantAsociaciones--;
	return map;
}
bool existeAsociacionEnMap(nat clave, TMapping map){
	TBucket bucket = buscarEnBucket(clave, (*map).buckets[clave%(*map).cantAsociacionesT]);
	return bucket!=NULL;
}

double valorEnMap(nat clave, TMapping map){
	TBucket bucket = buscarEnBucket(clave, (*map).buckets[clave%(*map).cantAsociacionesT]);
	return realInfo((*bucket).dato);
}

bool estaLlenoMap(TMapping map){
	return (*map).cantAsociaciones==(*map).cantAsociacionesT;
}

void liberarMap(TMapping map){
	nat i=0;
	while (i<=(*map).cantAsociacionesT-1){
		liberarBucket((*map).buckets[i]);
		i++;
	}
	delete [](*map).buckets;
	delete map;
}
