/* 5127722 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


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
