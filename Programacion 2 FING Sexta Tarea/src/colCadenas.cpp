/* 5127722 */

#include "../include/colCadenas.h"
#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct _rep_colCadenas{
	nat cantidadDeCadenas;
	TCadena* cadenas;
};

TColCadenas crearColCadenas(nat M){
	TColCadenas nuevo = new _rep_colCadenas;
	(*nuevo).cantidadDeCadenas=M-1;
	(*nuevo).cadenas = new TCadena[M];
	nat i=0;
	while (i<=(*nuevo).cantidadDeCadenas){
		(*nuevo).cadenas[i]=crearCadena();
		i++;
	}
	return nuevo;
}

TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col){
	if (pos<=(*col).cantidadDeCadenas){
		if (!esVaciaCadena((*col).cadenas[pos]))
			(*col).cadenas[pos] = insertarAntes(info,inicioCadena((*col).cadenas[pos]),(*col).cadenas[pos]);
		else
			(*col).cadenas[pos] = insertarAlFinal(info,(*col).cadenas[pos]);
	}
	return col;
}

bool estaEnColCadenas(nat dato, nat pos, TColCadenas col){
	if (pos>(*col).cantidadDeCadenas)
		return false;
	else
		return pertenece(dato, (*col).cadenas[pos]);
}

TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col){
	TLocalizador loc = inicioCadena((*col).cadenas[pos]);
	while (natInfo(infoCadena(loc,(*col).cadenas[pos]))!=dato)
		loc = siguiente(loc,(*col).cadenas[pos]);
	return infoCadena(loc,(*col).cadenas[pos]);
}

TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col){
	TLocalizador loc = inicioCadena((*col).cadenas[pos]);
	while (natInfo(infoCadena(loc,(*col).cadenas[pos]))!=dato)
		loc = siguiente(loc,(*col).cadenas[pos]);
	(*col).cadenas[pos] = removerDeCadena(loc  ,(*col).cadenas[pos]);
	return col;
}

void liberarColCadenas(TColCadenas col){
	nat i=0;
	while (i<=(*col).cantidadDeCadenas){
		liberarCadena((*col).cadenas[i]);
		i++;
	}
	delete [](*col).cadenas;
	delete col;
}

