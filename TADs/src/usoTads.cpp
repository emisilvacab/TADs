/* 5127389 */

#include "../include/usoTads.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/conjunto.h"
#include <limits.h>
#include <stdio.h>

TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2) {
  TConjunto aux = diferenciaDeConjuntos(c1, c2), nuevo = diferenciaDeConjuntos(c1, aux);
  liberarConjunto(aux);
  return nuevo;
}

nat cantidadEnIterador(TIterador it) {
  nat res = 0;
  it = reiniciarIterador(it);
  while (estaDefinidaActual(it)) {
    res++;
    it = avanzarIterador(it);
  }
  return res; 
}

TIterador enAlguno(TIterador a, TIterador b) {
  a = reiniciarIterador(a);
  b = reiniciarIterador(b);
  TIterador nuevo = crearIterador();
  while (estaDefinidaActual(a)) {
    if (estaDefinidaActual(b)) {
      if (actualEnIterador(a) < actualEnIterador(b)) {
        nuevo = agregarAIterador(actualEnIterador(a), nuevo);
        a = avanzarIterador(a);
      }
      else if (actualEnIterador(a) > actualEnIterador(b)) {
        nuevo = agregarAIterador(actualEnIterador(b), nuevo);
        b = avanzarIterador(b);
      }
      else {
        nuevo = agregarAIterador(actualEnIterador(a), nuevo);
        a = avanzarIterador(a);
        b = avanzarIterador(b);
      }
    }
    else {
      nuevo = agregarAIterador(actualEnIterador(a), nuevo);
      a = avanzarIterador(a);
    }
  }
  while (estaDefinidaActual(b)) {
    nuevo = agregarAIterador(actualEnIterador(b), nuevo);
    b = avanzarIterador(b);
  }
  return nuevo;
}

TIterador soloEnA(TIterador a, TIterador b) {
  a = reiniciarIterador(a);
  b = reiniciarIterador(b);
  TIterador nuevo = crearIterador();
  while (estaDefinidaActual(a)) {
    if (estaDefinidaActual(b)) {
      if (actualEnIterador(a) < actualEnIterador(b)) {
        nuevo = agregarAIterador(actualEnIterador(a), nuevo);
        a = avanzarIterador(a);
      }
      else if (actualEnIterador(a) > actualEnIterador(b))
        b = avanzarIterador(b);
      else {
        a = avanzarIterador(a);
        b = avanzarIterador(b);
      }
    }
    else {
      nuevo = agregarAIterador(actualEnIterador(a), nuevo);
      a = avanzarIterador(a);
    }
  }
  return nuevo;
}

TIterador recorridaPorNiveles(TBinario b) {
  TIterador nuevo = crearIterador();
  if (!esVacioBinario(b)) {
    TColaBinarios caux = encolar(b, crearColaBinarios());
    caux = encolar(NULL, caux);
    nat tam = 2*cantidadBinario(b)-1;
    TPila paux = crearPila(tam);
    while (!estaVaciaColaBinarios(caux)) {
      b = frente(caux);
      caux = desencolar(caux);
      if (!estaVaciaColaBinarios(caux)) {
        if (b == NULL) {
          paux = apilar(UINT_MAX, paux);
          caux = encolar(NULL, caux);
        }
        else {
          paux = apilar(natInfo(raiz(b)), paux);
          if (!esVacioBinario(derecho(b))) {
            caux = encolar(derecho(b), caux);
          }
          if (!esVacioBinario(izquierdo(b))) {
            caux = encolar(izquierdo(b), caux);
          } 
        }
      }
    }
    liberarColaBinarios(caux);
    while (!estaVaciaPila(paux)) {
      nuevo = agregarAIterador(cima(paux), nuevo);
      paux = desapilar(paux);
    }
    liberarPila(paux);
  }
  return nuevo;
}

TCadena nivelEnBinario(nat l, TBinario b) {
  if (l > 0 && l <= alturaBinario(b)) {
    if (l == 1) {
      return insertarAlFinal(copiaInfo(raiz(b)), crearCadena());
    }
    else {
      TCadena c1 = nivelEnBinario(l-1, izquierdo(b)), c2 = nivelEnBinario(l-1, derecho(b)), 
      conc = concatenar(c1,c2);
      liberarCadena(c1);
      liberarCadena(c2);
      return conc;
    }
  }
  else 
    return crearCadena();
}

bool caminoigual(TLocalizador aux, TCadena c, TBinario b) {
  if (esVacioBinario(b) && !esLocalizador(aux))
    return true;
  else {
    if (esVacioBinario(b) || !esLocalizador(aux))
      return false;
    else if (esFinalCadena(aux, c) && alturaBinario(b) > 1)
      return false;
    else if (natInfo(raiz(b)) == natInfo(infoCadena(aux, c)))
      return (caminoigual(siguiente(aux, c), c, izquierdo(b)) || caminoigual(siguiente(aux, c), c, derecho(b)));
    else 
      return false;
  }
}

bool esCamino(TCadena c, TBinario b) {
  return caminoigual(inicioCadena(c), c, b);
}

bool pertenece(nat elem, TCadena cad) {
  return localizadorEnCadena((siguienteClave(elem, inicioCadena(cad), cad)), cad);
}

nat longitud(TCadena cad) {
  nat res = 0;
  if (!esVaciaCadena(cad)) {
    res = 1;
    TLocalizador aux = inicioCadena(cad);
    while (!esFinalCadena(aux, cad)) {
      res++;
      aux = siguiente(aux, cad);
    }
  }
  return res;
}

bool estaOrdenadaPorNaturales(TCadena cad) {
  if (!esVaciaCadena(cad) && finalCadena(cad) != inicioCadena(cad)) {
    TLocalizador aux = inicioCadena(cad);
    while (siguiente(aux, cad) != siguiente(finalCadena(cad), cad)) {
      if (natInfo(infoCadena(aux, cad)) > natInfo(infoCadena(siguiente(aux, cad), cad)))
        return false;
      else 
        aux = siguiente(aux, cad);
    }
  }
  return true;
}

bool hayNatsRepetidos(TCadena cad) {
  if (!esVaciaCadena(cad)) {
    TLocalizador aux1 = inicioCadena(cad), aux2;
    while (aux1 != siguiente(finalCadena(cad),cad)) {
      aux2 = siguiente(aux1, cad);
      while (aux2 != siguiente(finalCadena(cad),cad)) {
        if (natInfo(infoCadena(aux1, cad)) == natInfo(infoCadena(aux2, cad))) 
          return true;
        else 
          aux2 = siguiente(aux2, cad);
      }
      aux1 = siguiente(aux1, cad);
    }
  }
  return false;
}

bool sonIgualesCadena(TCadena c1, TCadena c2) {
  TLocalizador aux1 = inicioCadena(c1), aux2 = inicioCadena(c2);
  if (!esVaciaCadena(c1) && !esVaciaCadena(c2)) {
    while (aux1 != siguiente(finalCadena(c1),c1) && aux2 != siguiente(finalCadena(c2),c2)) {
      if (!sonIgualesInfo(infoCadena(aux1, c1), infoCadena(aux2, c2))) 
        return false;
      else {
        aux1 = siguiente(aux1 , c1);
        aux2 = siguiente(aux2 , c2);
      }
    }
  }
  return aux1 == aux2;
}

TCadena concatenar(TCadena c1, TCadena c2) {
  TCadena nc1 = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1), nc2 = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
  return insertarSegmentoDespues(nc2, finalCadena(nc1), nc1); 
}

TCadena ordenar(TCadena cad) {
  if (inicioCadena(cad) != finalCadena(cad)) {
    TLocalizador aux1 = inicioCadena(cad), aux2 = siguiente(inicioCadena(cad), cad);
    while (aux1 != finalCadena(cad)) {
      while (aux2 != siguiente(finalCadena(cad), cad)) {
        if (natInfo(infoCadena(aux1, cad)) > natInfo(infoCadena(aux2, cad)))
          intercambiar(aux1, aux2, cad);
        aux2 = siguiente(aux2, cad);
      }
      aux1 = siguiente(aux1, cad);
      aux2 = siguiente(aux1, cad);
    }
  }
  return cad;
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
  if (!esVaciaCadena(cad)) {
    TLocalizador aux = inicioCadena(cad);
    while (aux != siguiente(finalCadena(cad), cad)) {
      if (natInfo(infoCadena(aux, cad)) == original) {
        TLocalizador del = aux;
        cad = insertarAntes(crearInfo(nuevo, realInfo((infoCadena(del, cad)))), del, cad);
        aux = siguiente(aux, cad);
        cad = removerDeCadena(del, cad);
      }
      else
        aux = siguiente(aux, cad);
    }
  }
  return cad;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad) { 
  return copiarSegmento(siguienteClave(menor, inicioCadena(cad), cad), anteriorClave(mayor, finalCadena(cad), cad), cad);
}
