/* 5127722 */

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/colaDePrioridad.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_colaDePrioridad{
	nat sig;
	nat cantT;
	TInfo* cola;
	nat* posiciones;
};

//Funciones auxiliares

static TColaDePrioridad swap (nat pos1,nat pos2, TColaDePrioridad cp){
	TInfo original = (*cp).cola[pos1];
	(*cp).cola[pos1] = (*cp).cola[pos2];
	(*cp).cola[pos2] = original;
	if ((*cp).cola[pos1]!=NULL)
		(*cp).posiciones[natInfo((*cp).cola[pos1])] = pos1;
	if ((*cp).cola[pos2]!=NULL)
		(*cp).posiciones[natInfo((*cp).cola[pos2])] = pos2;
	
	return cp;
}

static bool estaOrdenado(nat pos, TColaDePrioridad cp){
	if (pos*2>(*cp).cantT)
		return true;
	else if ((pos*2)+1>(*cp).cantT){
		if ((*cp).cola[pos*2]==NULL)
			return true;
		else
			return realInfo((*cp).cola[pos])<=realInfo((*cp).cola[pos*2]);
	}
	else if ((*cp).cola[pos*2]==NULL && (*cp).cola[(pos*2)+1]==NULL)
		return true;
	else if ((*cp).cola[pos*2]!=NULL && (*cp).cola[(pos*2)+1]==NULL)
		return realInfo((*cp).cola[pos])<=realInfo((*cp).cola[pos*2]);
	else 
		return realInfo((*cp).cola[pos])<=realInfo((*cp).cola[pos*2]) && realInfo((*cp).cola[pos])<=realInfo((*cp).cola[(pos*2)+1]);	
}

static nat buscarLugar (nat pos, double valor, TColaDePrioridad cp){
	if (pos*2 > (*cp).cantT)
		return pos;
	else if ((pos*2)+1 > (*cp).cantT){
		if ((*cp).cola[pos*2]==NULL)
			return pos;
		else if (valor<=realInfo((*cp).cola[pos*2]))
			return pos;
		else{
			(*cp).cola[pos] = (*cp).cola[pos*2];
			(*cp).cola[pos*2]=NULL;
			(*cp).posiciones[natInfo((*cp).cola[pos])] = pos;
			return pos*2;
		}	
	}	
	else if ((*cp).cola[pos*2]==NULL)
		return pos;
	else if ((*cp).cola[(pos*2)+1]==NULL){
		if (valor<=realInfo((*cp).cola[pos*2]))
			return pos;
		else{
			(*cp).cola[pos] = (*cp).cola[pos*2];
			(*cp).cola[pos*2]=NULL;
			(*cp).posiciones[natInfo((*cp).cola[pos])] = pos;
			return pos*2;
		}	
	}
	else if (valor<=realInfo((*cp).cola[pos*2]) && valor<=realInfo((*cp).cola[(pos*2)+1]))
		return pos;
	else{
		if (realInfo((*cp).cola[pos*2])<=realInfo((*cp).cola[(pos*2)+1])){
			cp = swap(pos,pos*2,cp);
			return buscarLugar(pos*2,valor,cp);
		}
		else{
			cp = swap(pos,(pos*2)+1,cp);
			return buscarLugar((pos*2)+1,valor,cp);	
		}		
	}	
}

//Fin funciones auxiliares

TColaDePrioridad crearCP(nat N){
	TColaDePrioridad nuevo = new _rep_colaDePrioridad;
	(*nuevo).sig=1;
	(*nuevo).cantT=N;
	(*nuevo).cola = new TInfo[N+1];
	(*nuevo).posiciones = new nat[N+1];
	nat i=0;
	while (i<=N){
		(*nuevo).cola[i]=NULL;
		(*nuevo).posiciones[i]=0;
		i++;
	}
	return nuevo;
}

nat rangoCP(TColaDePrioridad cp){
	return (*cp).cantT;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
	nat pos = (*cp).sig;
	if (pos==1)
		(*cp).cola[pos] = crearInfo(elem,valor);
	else{
		while (pos!=1 && valor < realInfo((*cp).cola[pos/2])){
			cp = swap(pos,pos/2, cp);
			pos = pos/2;
		}
		(*cp).cola[pos] = crearInfo(elem,valor);
	}
	(*cp).posiciones[elem] = pos;
	(*cp).sig++;
	
	return cp;
}

bool estaVaciaCP(TColaDePrioridad cp){
	return (*cp).cola[1]==NULL;
}

nat prioritario(TColaDePrioridad cp){
	return natInfo((*cp).cola[1]);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
	(*cp).sig--;
	(*cp).posiciones[natInfo((*cp).cola[1])] = 0;
	liberarInfo((*cp).cola[1]);
	(*cp).cola[1]=NULL;
	if ((*cp).sig!=1){
		nat lugar  = buscarLugar(1,realInfo((*cp).cola[(*cp).sig]),cp);
		(*cp).cola[lugar] = (*cp).cola[(*cp).sig];
		(*cp).cola[(*cp).sig] = NULL;
		(*cp).posiciones[natInfo((*cp).cola[lugar])] = lugar;
	}
	return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp){
		return (*cp).posiciones[elem]!=0;
}

double prioridad(nat elem, TColaDePrioridad cp){
	return realInfo((*cp).cola[(*cp).posiciones[elem]]);
}

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
	nat pos = (*cp).posiciones[elem];
	if (valor<realInfo((*cp).cola[pos])){
		liberarInfo((*cp).cola[pos]);
		(*cp).cola[pos] = crearInfo(elem,valor);
		while (pos!=1 && realInfo((*cp).cola[pos])<realInfo((*cp).cola[pos/2])){
			cp = swap(pos,pos/2,cp);
			pos = pos/2;
		}
	}
	else if (valor>realInfo((*cp).cola[pos])){
		liberarInfo((*cp).cola[pos]);
		(*cp).cola[pos] = crearInfo(elem,valor);	
		while (!estaOrdenado(pos,cp)){
			if ((*cp).cola[(pos*2)+1]!=NULL){
				if (realInfo((*cp).cola[pos*2])<=realInfo((*cp).cola[(pos*2)+1])){
					cp = swap(pos,pos*2,cp);
					pos=pos*2;
				}
				else{
					cp = swap(pos,(pos*2)+1,cp);
					pos=(pos*2)+1;			
				}	
			}
			else{
				cp = swap(pos,pos*2,cp);
				pos=pos*2;
			}
		}
	}
	return cp;
}

void liberarCP(TColaDePrioridad cp){
	nat i=0;
	while (i<=(*cp).cantT){
		if ((*cp).cola[i]!=NULL)
			liberarInfo((*cp).cola[i]);
		i++;
	}
	delete[] (*cp).cola;
	delete[] (*cp).posiciones;
	delete cp;
}

