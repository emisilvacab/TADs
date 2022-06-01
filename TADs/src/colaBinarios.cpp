/* 5127389 */

#include <../include/colaBinarios.h>
#include <../include/info.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <stdio.h>
#include <math.h>

typedef struct _nodo_colab *TColabnodo;

struct _nodo_colab {
  TBinario arb;
  TColabnodo sig;
};

struct _rep_colaBinarios {
  TColabnodo ini;
  TColabnodo fin;
};

TColaBinarios crearColaBinarios() {
  TColaBinarios nuevo = new _rep_colaBinarios;
  nuevo->ini = nuevo->fin = NULL;
  return nuevo;
}

TColaBinarios encolar(TBinario b, TColaBinarios c) {
  TColabnodo nuevo = new _nodo_colab;
  nuevo->arb = b;
  nuevo->sig = NULL;
  if (c->ini == NULL)
    c->ini = nuevo;
  else 
    c->fin->sig = nuevo;
  c->fin = nuevo;
  return c;
}

TColaBinarios desencolar(TColaBinarios c) {
  if (!estaVaciaColaBinarios(c)) {
    if (c->ini == c->fin)
      c->fin = NULL;
    TColabnodo del = c->ini;
    c->ini = c->ini->sig;
    delete del;
  }
  return c;
}

void liberarColaBinarios(TColaBinarios c) {
  while (c->ini != NULL) {
    c = desencolar(c);
  }
  delete c;
}

bool estaVaciaColaBinarios(TColaBinarios c) {
  return c->ini == NULL;
}

TBinario frente(TColaBinarios c) {
  if (!estaVaciaColaBinarios(c))
    return c->ini->arb;
  else 
    return NULL;
}
