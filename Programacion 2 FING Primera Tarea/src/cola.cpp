/* 5127722 */

#include "../include/cola.h"
#include "../include/lista.h"
#include "../include/utils.h"

#include<stdio.h>

struct _rep_cola {
	TLista lista_c;
};
TCola crearCola(){
	TCola cola=new _rep_cola;
	(*cola).lista_c=crearLista();
	return cola;
}	
bool esVaciaCola(TCola cola){
	return (longitud((*cola).lista_c)==0);
}
TCola encolar(info_t nuevo, TCola cola){
	if (longitud((*cola).lista_c)<MAX)
		(*cola).lista_c=insertar(1,nuevo,(*cola).lista_c);
	return cola;
}
info_t frente(TCola cola){
	return infoLista(longitud((*cola).lista_c),(*cola).lista_c);
}
TCola desencolar(TCola c){
	if (!esVaciaCola(c))
		(*c).lista_c=remover(longitud((*c).lista_c),(*c).lista_c);
	return c;
}
