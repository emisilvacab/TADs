/* 5127389 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include <stdio.h>

#include <assert.h>

#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador ant;
  TLocalizador sig;
};

struct _rep_cadena {
  TLocalizador ini;
  TLocalizador fin;
};

bool esLocalizador(TLocalizador loc) {
  return loc != NULL;
}

TCadena crearCadena() {
  TCadena nueva = new _rep_cadena;
  nueva->ini = nueva->fin = NULL;
  return nueva;
}

void liberarCadena(TCadena cad) {
  TLocalizador del, aux = cad->ini;
  while (aux != NULL) {
    del = aux;
    liberarInfo(aux->dato);
    aux = aux->sig;
    delete del;
  }
  delete cad;
}

bool esVaciaCadena(TCadena cad) {
  return cad->ini == NULL;
}

TLocalizador inicioCadena(TCadena cad) {
  return cad->ini;
}

TLocalizador finalCadena(TCadena cad) {
  return cad->fin;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  return loc->dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad){
  if (esFinalCadena(loc , cad))
    return NULL;
  else
    return loc->sig;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
  if (esInicioCadena(loc, cad))
    return NULL;
  else
    return loc->ant;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
  return !esVaciaCadena(cad) && loc == cad->fin;
}

bool esInicioCadena(TLocalizador loc, TCadena cad){
  return !esVaciaCadena(cad) && loc == cad->ini ; 
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
  TLocalizador nuevo = new nodoCadena;
  nuevo->dato = i;
  nuevo->sig = NULL;
  if (esVaciaCadena(cad)) {
    cad->ini = nuevo;
    nuevo->ant = NULL;
  }
  else {
    cad->fin->sig = nuevo;
    nuevo->ant = cad->fin;
  }
  cad->fin = nuevo;
  return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
  TLocalizador nuevo = new nodoCadena;
  nuevo->dato = i;
  nuevo->ant = loc->ant;
  nuevo->sig = loc;
  if (loc->ant != NULL)
    loc->ant->sig = nuevo;
  loc->ant = nuevo;
  if (loc == cad->ini)
    cad->ini = nuevo;
  return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  if (cad->ini == loc && loc == cad->fin) 
    cad->ini = cad->fin = NULL;
  else {
    if (loc->ant != NULL) {
      loc->ant->sig = loc->sig;
      if (loc == cad->fin)
        cad->fin = loc->ant;
    }
    if (loc->sig != NULL) {
      loc->sig->ant = loc->ant;
      if (loc == cad->ini)
        cad->ini = loc->sig;
    }
  }
  liberarInfo(loc->dato);
  delete loc;
  return cad;
}

void imprimirCadena(TCadena cad) {
  ArregloChars aux;
  TLocalizador pos = cad->ini;
  while (pos != NULL) {
    aux = infoATexto(pos->dato);
    printf("%s", aux);
    pos = pos->sig;
    delete[] aux;
  }
  delete pos;
  printf("\n");
}

TLocalizador kesimo(nat k, TCadena cad) {
  TLocalizador pos = cad->ini;
  while (k>1 && pos != NULL) {
    pos = pos->sig;
    k--;
  }
  if (k==0) 
    return NULL;
  else
    return pos;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  TLocalizador aux = cad->ini;
  while (loc != aux && aux != NULL) {
    aux = aux->sig;
  }
  return aux != NULL;
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  if (localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad)) {
    TLocalizador aux = loc1;
    while(aux != loc2 && aux != loc2->sig) {
      aux = aux->sig;
    }
    return aux == loc2;
  }
  else 
    return false;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
  if (!esVaciaCadena(sgm)) {
    if (esVaciaCadena(cad)) {
      cad->ini = sgm->ini;
      cad->fin = sgm->fin;
    }
    else if (localizadorEnCadena(loc, cad)) {
      if (loc->sig != NULL) {
        loc->sig->ant = sgm->fin;
        sgm->fin->sig = loc->sig;
      }
      else {
        cad->fin = sgm->fin;
      }
      loc->sig = sgm->ini;
      sgm->ini->ant = loc;
    }
  }
  delete sgm;
  return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TCadena nueva = crearCadena();
  if (!esVaciaCadena(cad)) {
    TLocalizador nodo1 = new nodoCadena;
    nueva->ini = nodo1;
    nodo1->dato = copiaInfo(desde->dato);
    nodo1->ant = NULL;
    desde = desde->sig;
    while (desde != hasta->sig) {
      TLocalizador nodo2 = new nodoCadena;
      nodo1->sig = nodo2;
      nodo2->dato = copiaInfo(desde->dato);
      nodo2->ant = nodo1;
      nodo1 = nodo2;
      desde = desde->sig;
    }
    nodo1->sig = NULL;
    nueva->fin = nodo1;
  }
  return nueva;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  if (!esVaciaCadena(cad)) {
    TLocalizador final = hasta->sig;
    while (desde != final) {
      TLocalizador del = desde;
      desde = desde->sig;
      cad = removerDeCadena(del, cad);
    }
  }
  return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  loc->dato = i;
  return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  if (!esVaciaCadena(cad)) {
    TInfo copia = loc1->dato;
    loc1->dato = loc2->dato;
    loc2->dato = copia;
  }
  return cad;
}


TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  while (loc != NULL && natInfo(loc->dato) != clave) {
    loc=loc->sig;
  }
  return loc;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  while (loc != NULL && natInfo(loc->dato) != clave) {
    loc=loc->ant;
  }
  return loc;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  nat nmenor = natInfo(loc->dato);
  TLocalizador locmenor = loc;
  loc = loc->sig;
  while (loc != NULL) {
    if (natInfo(loc->dato) < nmenor) {
      nmenor = natInfo(loc->dato);
      locmenor = loc;
    }
    loc=loc->sig;
  }
  return locmenor; 
}

TCadena insertarAlInicio(TInfo i, TCadena cad) {
  TLocalizador nuevo = new nodoCadena;
  nuevo->dato = i;
  nuevo->ant = NULL;
  if (esVaciaCadena(cad)) {
    cad->fin = nuevo;
    nuevo->sig = NULL;
  }
  else {
    cad->ini->ant = nuevo;
    nuevo->sig = cad->fin;
  }
  cad->ini = nuevo;
  return cad;
}

