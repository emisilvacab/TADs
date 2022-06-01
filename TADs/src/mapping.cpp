/* 5127389 */

#include <../include/mapping.h>
#include <../include/cadena.h>
#include <../include/usoTads.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct _nodo_cad *TNodoc;

struct _nodo_cad {
  double dato;
  nat elem;
  TNodoc sig;
};

typedef struct _cad *TCad;

struct _cad {
  TNodoc ini;
  TNodoc fin;
};

struct _rep_mapping {
  nat tam;
  nat cant;
  TCad* arr;
};

TMapping crearMap(nat M) {
  TMapping nuevo = new _rep_mapping;
  nuevo->tam = M;
  nuevo->cant = 0;
  nuevo->arr = new TCad[M];
  for (nat i = 0; i < M; i++) {
    nuevo->arr[i] = NULL;
  }
  return nuevo;
}

nat mhash(nat clave, nat M) {
  return (clave) % M;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
  TNodoc nuevon = new _nodo_cad;
  nuevon->dato = valor;
  nuevon->elem = clave;
  nuevon->sig = NULL;
  if (map->arr[mhash(clave, map->tam)] == NULL) {
    map->arr[mhash(clave, map->tam)] = new _cad;
    map->arr[mhash(clave, map->tam)]->ini = map->arr[mhash(clave, map->tam)]->fin = nuevon;
  }
  else {
    map->arr[mhash(clave, map->tam)]->fin->sig = nuevon;
    map->arr[mhash(clave, map->tam)]->fin = nuevon;
  }
  map->cant++;
  return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
  TNodoc aux = map->arr[mhash(clave, map->tam)]->ini;
  if (aux->elem == clave) {
    if (aux == map->arr[mhash(clave, map->tam)]->fin) {
      delete aux;
      delete map->arr[mhash(clave, map->tam)];
      map->arr[mhash(clave, map->tam)] = NULL;
    } 
    else {
    map->arr[mhash(clave, map->tam)]->ini = map->arr[mhash(clave, map->tam)]->ini->sig;
    delete aux;
    }
  }
  else {
    while (aux->sig->elem != clave)
      aux = aux->sig;
    if (aux->sig == map->arr[mhash(clave, map->tam)]->fin)
      map->arr[mhash(clave, map->tam)]->fin = aux;
    TNodoc del = aux->sig;
    aux->sig = aux->sig->sig;
    delete del;
  }
  map->cant--;
  return map;
}

bool existeAsociacionEnMap(nat clave, TMapping map) {
  if (map->arr[mhash(clave, map->tam)] == NULL)
    return false;
  else {
    TNodoc aux = map->arr[mhash(clave, map->tam)]->ini;
    while (aux != NULL && aux->elem != clave) 
      aux = aux->sig;
    if (aux == NULL)
      return false;
    else 
      return true;
  }
}

double valorEnMap(nat clave, TMapping map) {
  TNodoc aux = map->arr[mhash(clave, map->tam)]->ini;
  while (aux->elem != clave) 
    aux = aux->sig;
  return aux->dato;
}


bool estaLlenoMap(TMapping map) {
  return map->cant == map->tam;
}

void liberarMap(TMapping map) {
  for (nat i = 0; i < map->tam; i++) {
    if (map->arr[i] != NULL) {
      TNodoc del = map->arr[i]->ini, aux;
      while (del != NULL) {
        aux = del->sig;
        delete del;
        del = aux; 
      }
      delete map->arr[i];
    }
  }
  delete[] map->arr;
  delete map;
}
