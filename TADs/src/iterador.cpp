/* 5127389 */

#include <../include/iterador.h>
#include <../include/cadena.h>
#include <../include/usoTads.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct nodoColeccion *TColeccion;

struct nodoColeccion {
  TColeccion sig;
  nat dato;
};

struct _rep_iterador {
  bool agregar; 
  TColeccion act;
  TColeccion ini;
  TColeccion fin;
};

TIterador crearIterador() {
  TIterador nuevo = new _rep_iterador;
  nuevo->agregar = true;
  nuevo->fin = nuevo->ini = nuevo->act = NULL;
  return nuevo;
}

TIterador agregarAIterador(nat elem, TIterador iter) {
  if (iter->agregar) {
    if (iter->ini == NULL) {
      TColeccion nuevo = new nodoColeccion;
      nuevo->sig = NULL;
      nuevo->dato = elem;
      iter->ini = iter->fin = nuevo;
    }
    else {
      TColeccion nuevo = new nodoColeccion;
      nuevo->sig = NULL;
      nuevo->dato = elem;
      iter->fin->sig = nuevo;
      iter->fin = nuevo;
    }
  }
  return iter;
}

TIterador reiniciarIterador(TIterador iter) {
  if (iter->ini != NULL) {
    iter->agregar = false;
    iter->act = iter->ini;
  }
  return iter;
}

TIterador avanzarIterador(TIterador iter) {
  if (estaDefinidaActual(iter))
    iter->act = iter->act->sig;
  return iter;
}

nat actualEnIterador(TIterador iter) {
  return iter->act->dato;
}

bool estaDefinidaActual(TIterador iter) {
  if (iter->act == NULL)
    return false;
  else 
    return true;
}

void liberarIterador(TIterador iter) {
  iter = reiniciarIterador(iter);
  while (iter->act != NULL) {
    TColeccion del = iter->act;
    iter->act = iter->act->sig;
    delete del;
  }
  delete iter;
}
