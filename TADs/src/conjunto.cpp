/* 5127389 */

#include "../include/conjunto.h"
#include "../include/info.h"
#include "../include/utils.h"
#include <../include/usoTads.h>
#include <../include/avl.h>
#include <../include/iterador.h>
#include <stdio.h>
#include <math.h>

struct _rep_conjunto {
  TAvl avl;
  nat max; 
  nat min;
};

TConjunto crearConjunto() {
  TConjunto nuevo = new _rep_conjunto;
  nuevo->avl = NULL;
  return nuevo;
}

TConjunto singleton(nat elem) {
  TConjunto nuevo = crearConjunto();
  nuevo->max = nuevo->min = elem;
  nuevo->avl = insertarEnAvl(elem, crearAvl());
  return nuevo;
}

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2) {
  TIterador i1 = enOrdenAvl(c1->avl), i2 = enOrdenAvl(c2->avl), ires = enAlguno(i1, i2);
  TConjunto nuevo = crearConjunto();
  ires = reiniciarIterador(ires);
  if (estaDefinidaActual(ires))
    nuevo->min = actualEnIterador(ires);
  while (estaDefinidaActual(ires)) {
    nuevo->avl = insertarEnAvl(actualEnIterador(ires), nuevo->avl);
    nuevo->max = actualEnIterador(ires);
    ires = avanzarIterador(ires);
  }
  liberarIterador(i1);
  liberarIterador(i2);
  liberarIterador(ires);
  return nuevo;
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2) {
  TIterador i1 = enOrdenAvl(c1->avl), i2 = enOrdenAvl(c2->avl), ires = soloEnA(i1, i2);
  TConjunto nuevo = crearConjunto();
  ires = reiniciarIterador(ires);
  if (estaDefinidaActual(ires))
    nuevo->min = actualEnIterador(ires);
  while (estaDefinidaActual(ires)) {
    nuevo->avl = insertarEnAvl(actualEnIterador(ires), nuevo->avl);
    nuevo->max = actualEnIterador(ires);
    ires = avanzarIterador(ires);
  }
  liberarIterador(i1);
  liberarIterador(i2);
  liberarIterador(ires);
  return nuevo;
}

bool perteneceAConjunto(nat elem, TConjunto c) {
  return !estaVacioAvl(buscarEnAvl(elem, c->avl));
}

bool estaVacioConjunto(TConjunto c) {
  return c->avl == NULL;
}

nat cardinalidad(TConjunto c) {
  return cantidadEnAvl(c->avl);
}

nat minimo(TConjunto c) { 
  return c->min;
}

nat maximo(TConjunto c) {
  return c->max;
}

TConjunto arregloAConjunto(ArregloNats elems, nat n) {
  TConjunto nuevo = crearConjunto();
  nuevo->avl = arregloAAvl(elems, n);
  nuevo->min = elems[0];
  nuevo->max = elems[n-1];
  return nuevo;
}

TIterador iteradorDeConjunto(TConjunto c) {
  return enOrdenAvl(c->avl);
}

void liberarConjunto(TConjunto c) {
  liberarAvl(c->avl);
  delete c;
}