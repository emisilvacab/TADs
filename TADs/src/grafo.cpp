/* 5127389 */

#include <../include/grafo.h>
#include <../include/cadena.h>
#include <../include/usoTads.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct _nodo_cadn *TNodocdn;

struct _nodo_cadn {
  double dato;
  nat elem1;
  nat elem2;
  TNodocdn sig;
};

typedef struct _cadn *TCadn;

struct _cadn {
  TNodocdn ini;
  TNodocdn fin;
};

struct _rep_grafo {
  nat tamv;
  nat tama;
  nat canta;
  TAvl* ver;
  TCadn* ari;
};

TGrafo crearGrafo(nat N, nat M) {
  TGrafo nuevo = new _rep_grafo;
  nuevo->tamv = N;
  nuevo->tama = M;
  nuevo->canta = 0;
  nuevo->ver = new TAvl[N];
  for (nat i = 0; i < N; i++) {
    nuevo->ver[i] = crearAvl();
  }
  nuevo->ari = new TCadn[M];
  for (nat i = 0; i < M; i++) {
    nuevo->ari[i] = NULL;
  }
  return nuevo;
}
  
nat cantidadVertices(TGrafo g) {
  return g->tamv;
}

bool hayMParejas(TGrafo g) {
  return g->canta == g->tama;
}

nat ghash(nat v1, nat v2, TGrafo g) {
  if (v1 >= v2) 
    return ((v2 - 1) * g->tamv + (v1 + 1)) % g->tama;
  else
    return ((v1 - 1) * g->tamv + (v2 + 1)) % g->tama;
}

TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g) {
  g->ver[v1-1] = insertarEnAvl(v2, g->ver[v1-1]);
  g->ver[v2-1] = insertarEnAvl(v1, g->ver[v2-1]); 
  g->canta++;
  TNodocdn nuevo = new _nodo_cadn;
  nuevo->dato = d;
  nuevo->elem1 = v1;
  nuevo->elem2 = v2;
  nuevo->sig = NULL;
  if (g->ari[ghash(v1, v2, g)] == NULL) {
    g->ari[ghash(v1, v2, g)] = new _cadn;
    g->ari[ghash(v1, v2, g)]->ini = g->ari[ghash(v1, v2, g)]->fin = nuevo;
  }
  else {
    g->ari[ghash(v1, v2, g)]->fin->sig = nuevo;
    g->ari[ghash(v1, v2, g)]->fin = nuevo;
  }
  return g;
}

bool sonVecinos(nat v1, nat v2, TGrafo g) {
  if (g->ari[ghash(v1, v2, g)] == NULL) {
    return false;
  }
  else {
    TNodocdn aux = g->ari[ghash(v1, v2, g)]->ini;
    while (aux != NULL) {
      if ((aux->elem1 == v1 && aux->elem2 == v2) || (aux->elem1 == v2 && aux->elem2 == v1))
        return true;
      else 
        aux = aux->sig;
    }
    return false;
  }
}

double distancia(nat v1, nat v2, TGrafo g) {
  TNodocdn aux = g->ari[ghash(v1, v2, g)]->ini;
  while ((aux->elem1 != v1 && aux->elem2 == v2) || (aux->elem1 != v2 && aux->elem2 == v1))
    aux = aux->sig;
  return aux->dato;
}

TIterador vecinos(nat v, TGrafo g) {
  return enOrdenAvl(g->ver[v - 1]);
}

void liberarGrafo(TGrafo g) {
  for (nat i = 0; i < g->tamv; i++) {
    liberarAvl(g->ver[i]);
  }
  for (nat i = 0; i < g->tama; i++) {
    if (g->ari[i] != NULL) {
      TNodocdn del = g->ari[i]->ini, aux;
      while (del != NULL) {
        aux = del->sig;
        delete del;
        del = aux; 
      }
    }
    delete g->ari[i];
  }
  delete[] g->ver;
  delete[] g->ari;
  delete g;
}
