/* 5127389 */

#include <../include/colaDePrioridad.h>
#include <../include/cadena.h>
#include <../include/usoTads.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct _nodo_heap *TNodoh;

struct _nodo_heap {
  double pri;
  nat num;
};

struct _rep_colaDePrioridad {
  nat tam;
  nat cant;
  nat* ubi;
  TNodoh* heap;
};

TColaDePrioridad crearCP(nat N) {
  TColaDePrioridad nuevo = new _rep_colaDePrioridad;
  nuevo->tam = N;
  nuevo->cant = 0;
  nuevo->ubi = new nat[N];
  for (nat i = 0; i < N; i++) {
    nuevo->ubi[i] = N + 1;
  }
  nuevo->heap = new TNodoh[N + 1];
  for (nat i = 0; i < N + 1; i++) {
    nuevo->heap[i] = NULL;
  }
  return nuevo;
}

nat rangoCP(TColaDePrioridad cp) {
  return cp->tam;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  cp->cant++;
  cp->heap[cp->cant] = new _nodo_heap;
  cp->heap[cp->cant]->num = elem;
  cp->heap[cp->cant]->pri = valor;
  nat i = cp->cant;
  TNodoh aux = cp->heap[i];
  while ((i > 1) && (cp->heap[i/2]->pri > aux->pri)) {
    cp->heap[i] = cp->heap[i/2];
    cp->ubi[cp->heap[i]->num - 1] = i; 
    i = i/2;
  }
  cp->heap[i] = aux;
  cp->ubi[elem - 1] = i;
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) {
  return cp->cant == 0;
}

nat prioritario(TColaDePrioridad cp) {
  return cp->heap[1]->num;
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp) {
  cp->ubi[cp->heap[1]->num - 1] = cp->tam + 1;
  delete cp->heap[1];
  if (cp->cant == 1) {
    cp->heap[1] = NULL;
    cp->cant--;
  }
  else {
    cp->heap[1] = cp->heap[cp->cant];
    cp->ubi[cp->heap[cp->cant]->num - 1] = 1;
    TNodoh aux = cp->heap[cp->cant];
    cp->heap[cp->cant] = NULL;
    cp->cant--;
    nat j, i = 1;
    while (2*i <= cp->cant) {
      if ((2*i + 1 <= cp->cant) && (cp->heap[2*i]->pri > cp->heap[2*i + 1]->pri)) 
        j = 2*i + 1;
      else 
        j = 2*i;
      if (aux->pri > cp->heap[j]->pri) {
        cp->heap[i] = cp->heap[j];
        cp->ubi[cp->heap[i]->num - 1] = i;
        cp->heap[j] = aux;
        cp->ubi[cp->heap[j]->num - 1] = j;
      }
      i = j;
    }
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp) {
  return cp->ubi[elem - 1] != cp->tam + 1;
}

double prioridad(nat elem, TColaDePrioridad cp) {
  return cp->heap[cp->ubi[elem - 1]]->pri;
}

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  if (valor < cp->heap[cp->ubi[elem - 1]]->pri) {
    cp->heap[cp->ubi[elem - 1]]->pri = valor;
    nat i = cp->ubi[elem - 1];
    TNodoh aux = cp->heap[i];
    while ((i > 1) && (cp->heap[i/2]->pri > aux->pri)) {
      cp->heap[i] = cp->heap[i/2];
      cp->ubi[cp->heap[i]->num - 1] = i; 
      i = i/2;
    }
    cp->heap[i] = aux;
    cp->ubi[elem - 1] = i;
  }
  else if (valor > cp->heap[cp->ubi[elem - 1]]->pri) {
    cp->heap[cp->ubi[elem - 1]]->pri = valor;
    nat j,i = cp->ubi[elem - 1];
    TNodoh aux = cp->heap[i];
    while (2*i <= cp->cant) {
      if ((2*i + 1 <= cp->cant) && (cp->heap[2*i]->pri > cp->heap[2*i + 1]->pri)) 
        j = 2*i + 1;
      else 
        j = 2*i;
      if (aux->pri > cp->heap[j]->pri) {
        cp->heap[i] = cp->heap[j];
        cp->ubi[cp->heap[i]->num - 1] = i;
        cp->heap[j] = aux;
        cp->ubi[cp->heap[j]->num - 1] = i;
      }
      i = j;
    }
  }
  return cp;
}

void liberarCP(TColaDePrioridad cp) {
  nat i = 0;
  while (cp->cant != 0) {
    if (cp->heap[i] != NULL) {
      cp->cant--;
      delete cp->heap[i];
    }
    i++; 
  }
  delete[] cp->heap;
  delete[] cp->ubi;
  delete cp;
}
