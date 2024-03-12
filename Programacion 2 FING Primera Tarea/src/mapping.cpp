/* 5127722 */

#include "../include/mapping.h"
#include "../include/lista.h"
#include "../include/utils.h"

struct _rep_mapping {
	TLista lista_m;
};
TMapping crearMapping(){
	TMapping map = new _rep_mapping;
	(*map).lista_m=crearLista();
	return map;
}
TMapping asociar(nat clave, double valor, TMapping map){
	if (!esClave(clave, map)){
		info_t claveNueva;
		claveNueva.natural=clave;
		claveNueva.real=valor;
		(*map).lista_m=insertar(1,claveNueva,(*map).lista_m);
		}
	return map;
}
bool esClave(nat clave, TMapping map){
	return (posNat(clave,(*map).lista_m)!=0);
}
double valor(nat clave, TMapping map){
	return infoLista(posNat(clave,(*map).lista_m),(*map).lista_m).real;
}
TMapping desasociar(nat clave, TMapping map){
	if (esClave(clave,map))
		(*map).lista_m=remover(posNat(clave,(*map).lista_m), (*map).lista_m);
	return map;
}
