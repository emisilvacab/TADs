/* 5127389 */

#include <../include/pila.h>
#include <../include/info.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <stdio.h>
#include <math.h>

struct _rep_pila {
  nat tam;
  nat cant;
  nat* ap;
};

TPila crearPila (nat tamanio) {
  TPila p = new _rep_pila;
  p->tam = tamanio;
  p->cant = 0;
  p->ap = new nat[tamanio];
  return p;
}

TPila apilar(nat num, TPila p) {
  if (!estaLlenaPila(p)) {
    p->ap[p->cant] = num;
    p->cant++;
  }
  return p;
}

TPila desapilar(TPila p) {
  p->cant--;
  return p;
}

void liberarPila(TPila p) {
  delete[] p->ap;
  delete p;
}

bool estaVaciaPila(TPila p) {
  return p->cant == 0;
}

bool estaLlenaPila(TPila p) {
  return p->tam == p->cant;
}

nat cima(TPila p) {
  return p->ap[p->cant - 1];
}
