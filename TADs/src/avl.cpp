/* 5127389 */

#include <../include/avl.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <../include/usoTads.h>
#include <../include/pila.h>
#include <stdio.h>
#include <math.h>

struct _rep_avl {
  nat dato;
  TAvl izq;
  TAvl der;
  nat cant;
  nat alt;
};

TAvl crearAvl() {
  return NULL;
}

bool estaVacioAvl(TAvl avl) {
  return avl == NULL;
}

nat calcalt(TAvl avl) {
  if (alturaDeAvl(avl->izq) >= alturaDeAvl(avl->der))
    return alturaDeAvl(avl->izq) + 1;
  else 
    return alturaDeAvl(avl->der) + 1;
}

nat calcant(TAvl avl) {
  return cantidadEnAvl(avl->der) + cantidadEnAvl(avl->izq) + 1;
}

int fe(TAvl avl) {
  return alturaDeAvl(avl->der) - alturaDeAvl(avl->izq);
}

TAvl insertarEnAvl(nat elem, TAvl avl) {
  if (avl == NULL) {
    TAvl nuevo = new _rep_avl;
    nuevo->dato = elem;
    nuevo->izq = nuevo->der = NULL;
    nuevo->alt = nuevo->cant = 1;
    return nuevo;
  }
  else {
    avl->cant++;
    if (avl->dato > elem)
      avl->izq = insertarEnAvl(elem, avl->izq);
    else 
      avl->der = insertarEnAvl(elem, avl->der);
    avl->alt = calcalt(avl);
    if (fe(avl) == 2) {
      if (fe(avl->der) == -1) {
        TAvl aux = avl->der->izq;
        avl->der->izq = avl->der->izq->der;
        aux->der = avl->der;
        avl->der = aux; 
        avl->der->der->alt = calcalt(avl->der->der);
        avl->der->alt = calcalt(avl->der);
        avl->der->der->cant = calcant(avl->der->der);
        avl->der->cant = calcant(avl->der);
      }
      TAvl aux = avl->der;
      avl->der = avl->der->izq;
      aux->izq = avl;
      avl = aux;
      avl->izq->alt = calcalt(avl->izq);
      avl->alt = calcalt(avl);
      avl->izq->cant = calcant(avl->izq);
      avl->cant = calcant(avl);
    }
    else if (fe(avl) == -2) {
      if (fe(avl->izq) == 1) {
        TAvl aux = avl->izq->der; 
        avl->izq->der = avl->izq->der->izq;
        aux->izq = avl->izq;
        avl->izq = aux; 
        avl->izq->izq->alt = calcalt(avl->izq->izq);
        avl->izq->alt = calcalt(avl->izq);
        avl->izq->izq->cant = calcant(avl->izq->izq);
        avl->izq->cant = calcant(avl->izq);
      }
      TAvl aux = avl->izq;
      avl->izq = avl->izq->der;
      aux->der = avl;
      avl = aux; 
      avl->der->alt = calcalt(avl->der);
      avl->alt = calcalt(avl);
      avl->der->cant = calcant(avl->der);
      avl->cant = calcant(avl);
    }
    return avl;
  }
}

TAvl buscarEnAvl(nat elem, TAvl avl) {
  if (avl == NULL)
    return NULL;
  else if (avl->dato == elem)
    return avl;
  else if (avl->dato > elem)
    return buscarEnAvl(elem, avl->izq);
  else
    return buscarEnAvl(elem, avl->der);
}

nat raizAvl(TAvl avl) {
  return avl->dato;
}

TAvl izqAvl(TAvl avl) {
  return avl->izq;
}

TAvl derAvl(TAvl avl) {
  return avl->der;
}

nat cantidadEnAvl(TAvl avl) {
  if (avl == NULL)
    return 0;
  else
    return avl->cant;
}

nat alturaDeAvl(TAvl avl) {
  if (avl == NULL)
    return 0;
  else 
    return avl->alt;
}

TIterador enOrdenAvlaux(TIterador nuevo, TAvl avl) {
  if (avl->izq != NULL)
    nuevo = enOrdenAvlaux(nuevo, avl->izq);
  nuevo = agregarAIterador(avl->dato, nuevo);
  if (avl->der != NULL)
    nuevo = enOrdenAvlaux(nuevo, avl->der);
  return nuevo;
}

TIterador enOrdenAvl(TAvl avl) {
  if (avl == NULL)
    return crearIterador();
  else 
    return enOrdenAvlaux(crearIterador(), avl);
}

TAvl aravlaux(ArregloNats elems, nat i, nat s) {
  TAvl nuevo = crearAvl();
  nat m = (s+i)/2;
  if (i <= m) {
      nuevo = insertarEnAvl(elems[m], nuevo);
      if (s == 1) {
        nuevo = insertarEnAvl(elems[1], nuevo);
      }
      else if (m != 0 && m != s)  {
        nuevo->izq = aravlaux(elems, i , m-1);
        nuevo->der = aravlaux(elems, m+1, s);
      }
      nuevo->alt = calcalt(nuevo);
      nuevo->cant = cantidadEnAvl(nuevo->izq) + cantidadEnAvl(nuevo->der) + 1;
  }
  return nuevo;
}

TAvl arregloAAvl(ArregloNats elems, nat n) {
  return aravlaux(elems, 0 , n-1);
}

TAvl avlMinaux(nat &elem, nat i, nat h, TAvl avl) {
  if (i == h) {
    avl = new _rep_avl;
    avl->dato = elem;
    avl->izq = avl->der = NULL;
    avl->alt = avl->cant = 1;
    elem++;
  }
  else if (i < h) {
    avl = new _rep_avl;
    i++;
    avl->izq = avlMinaux(elem, i, h, NULL);
    avl->dato = elem;
    elem++;
    avl->alt = calcalt(avl->izq) + 1;
    avl->der = avlMinaux(elem, i, h - 1, NULL);
    avl->cant = calcant(avl);
  }
  return avl;
}

TAvl avlMin(nat h) {
  if (h == 0)
    return NULL;
  else {
    nat elem = 1;
    return avlMinaux(elem , 1, h, crearAvl());
  }
}

void liberarAvl(TAvl avl) {
  if (!estaVacioAvl(avl)) {
    liberarAvl(avl->izq);
    liberarAvl(avl->der);
    delete avl;
  }
}