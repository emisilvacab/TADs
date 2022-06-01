/* 5127389 */

#include <../include/binario.h>
#include <../include/cadena.h>
#include <../include/usoTads.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct _rep_binario {
  TInfo dato;
  TBinario izq;
  TBinario der;
};

TBinario avlABinario(TAvl a) {
  if (estaVacioAvl(a))
    return NULL;
  else {
    TBinario nuevo = new _rep_binario;
    nuevo->dato = crearInfo(raizAvl(a), 0);
    nuevo->izq = avlABinario(izqAvl(a));
    nuevo->der = avlABinario(derAvl(a));
    return nuevo;
  }
}

TBinario binBalaux(ArregloNats elems, nat i, nat s) {
  TBinario nuevo = crearBinario();
  nat m = (s+i)/2;
  if (i <= m) {
      nuevo = insertarEnBinario(crearInfo(elems[m], 0), nuevo);
      if (s == 1) {
        nuevo = insertarEnBinario(crearInfo(elems[1], 0), nuevo);
      }
      else if (m != 0 && m != s)  {
        nuevo->izq = binBalaux(elems, i , m-1);
        nuevo->der = binBalaux(elems, m+1, s);
      }
  }
  return nuevo;
}

TBinario binarioBalanceado(ArregloNats elems, nat n) {
    return binBalaux(elems, 0 , n-1);
}

TBinario crearBinario() {
  return NULL;
}

TBinario insertarEnBinario(TInfo i, TBinario b) {
  if (esVacioBinario(buscarSubarbol(natInfo(i), b))) {
    TBinario nuevo = new _rep_binario;
    nuevo->dato = i;
    nuevo->izq = nuevo->der = NULL;
    if (esVacioBinario(b))
      b = nuevo;
    else {
      TBinario aux = b, ant;
      while (aux != NULL) {
        ant = aux;
        if (natInfo(aux->dato) > natInfo(i))
          aux = aux->izq;
        else 
          aux = aux->der;
      }
      if (natInfo(ant->dato) > natInfo(i))
        ant->izq = nuevo;
      else 
        ant->der = nuevo;
    }
  }
  return b;
}

TInfo mayor(TBinario b) {
  if (b->der == NULL) 
    return b->dato;
  else 
    return mayor(b->der);
}

TBinario removerMayor(TBinario b) {
  if (b->der == NULL) {
    TBinario del = b;
    b = b->izq;
    delete del;
  }
  else 
    b->der = removerMayor(b->der);
  return b;
}

TBinario removerDeBinario(nat elem, TBinario b) {
    if (elem < natInfo(b->dato))
      b->izq = removerDeBinario(elem, b->izq);
    else if (elem > natInfo(b->dato))
      b->der = removerDeBinario(elem, b->der);
    else {
      if (b->der == NULL) {
        TBinario del = b;
        b = b->izq;
        liberarInfo(del->dato);
        delete del;
      }
      else if (b->izq == NULL) {
        TBinario del = b;
        b = b->der;
        liberarInfo(del->dato);
        delete del;
      } 
      else {
        TBinario del = b, d = b->der;
        TInfo may = mayor(b->izq);
        b->izq = removerMayor(b->izq);
        TBinario i = b->izq;
        liberarInfo(b->dato);
        delete del;
        TBinario nuevo = new _rep_binario;
        nuevo->dato = may;
        nuevo->izq = i;
        nuevo->der = d;
        b = nuevo;
      }
    }
  return b;
}

void liberarBinario(TBinario b) {
  if (!esVacioBinario(b)) {
    liberarBinario(b->izq);
    liberarBinario(b->der);
    liberarInfo(b->dato);
    delete b;
  }
}


bool esVacioBinario(TBinario b) {
  return b == NULL;
}

int esAvlaux(TBinario b) {
  if (b == NULL)
    return 0;
  else { 
    int i = esAvlaux(b->izq), d = esAvlaux(b->der);
    if ((fabs(i - d) <= 1) && (i >= 0 && d >= 0)) {
      if (i >= d)
        return i + 1;
      else 
        return d + 1;
    }
    else 
      return -1;
  }
}

bool esAvl(TBinario b) {
  return esAvlaux(b) >= 0;
}

TInfo raiz(TBinario b) {
  return b->dato;
}

TBinario izquierdo(TBinario b) {
  if (esVacioBinario(b))
    return b;
  else 
    return b->izq;
}

TBinario derecho(TBinario b) {
  if (esVacioBinario(b))
    return b;
  else 
    return b->der;
}

TBinario buscarSubarbol(nat elem, TBinario b) {
  if (b == NULL)
    return NULL;
  else if (natInfo(b->dato) == elem)
    return b;
  else if (natInfo(b->dato) > elem)
    return buscarSubarbol(elem, b->izq);
  else 
    return buscarSubarbol(elem, b->der);
}

nat alturaBinario(TBinario b) {
  if (b == NULL) 
    return 0;
  else {
    nat i = alturaBinario(b->izq), d = alturaBinario(b->der);
    if (i >= d)
      return i + 1;
    else 
      return d + 1;
  }
}

nat cantidadBinario(TBinario b) {
  if (b == NULL)
    return 0;
  else 
    return 1 + cantidadBinario(b->izq) + cantidadBinario(b->der);
}

double sumaAlt(nat &i, TBinario b) {
  if (b == NULL)
    return 0;
  else {
    double n1 = sumaAlt(i, b->der);
    if (realInfo(b->dato) > 0 && i > 0) {
      n1 = n1 + realInfo(b->dato);
      i--;
    }
    double n2 = sumaAlt(i, b->izq);
    return n1 + n2;
  }
}

double sumaUltimosPositivos(nat i, TBinario b) {
  return sumaAlt(i, b);
}

TCadena linealizacion(TBinario b) {
  if (b == NULL)
    return crearCadena();
  else {
    TCadena c1 = linealizacion(b->izq);
    c1 = insertarAlFinal(copiaInfo(b->dato), c1);
    TCadena c2 = linealizacion(b->der), conc = concatenar(c1,c2);
    liberarCadena(c1);
    liberarCadena(c2);
    return conc;
  }
}

TBinario menores(double cota, TBinario b) {
  if (b == NULL)
    return NULL;
  else {
    TBinario nizq = menores(cota, b->izq), nder = menores(cota, b->der), nuevo;
    if (realInfo(b->dato) < cota) {
      nuevo = new _rep_binario;
      nuevo->dato = copiaInfo(b->dato);
      nuevo->izq = nizq;
      nuevo->der = nder;
    }
    else if (nizq == NULL)
      nuevo = nder;
    else if (nder == NULL)
      nuevo = nizq;
    return nuevo;
  }
}

void profundidad(nat elem, TBinario a) {
  if (natInfo(a->dato) != elem) {
    if (natInfo(a->dato) > elem) {
      printf("-"); 
      profundidad(elem, a->izq);
    }
    else {
      printf("-");
      profundidad(elem, a->der);
    }
  }
}

void imprimiraux(TBinario b, TBinario a) {
  if (b == NULL)
    printf("\n");
  else {
    imprimiraux(b->der, a);
    profundidad(natInfo(b->dato), a);
    ArregloChars aux = infoATexto(b->dato);
    printf("%s", aux);
    delete[] aux;
    imprimiraux(b->izq, a);
  }
}

void imprimirBinario(TBinario b) {
  imprimiraux(b, b);
}
