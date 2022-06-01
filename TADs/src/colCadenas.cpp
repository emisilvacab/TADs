/* 5127389 */

#include <../include/colCadenas.h>
#include <../include/cadena.h>
#include <../include/usoTads.h>
#include <../include/utils.h>
#include <../include/info.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct _rep_colCadenas {
  nat tam;
  TCadena* arcad;
};

TColCadenas crearColCadenas(nat M) {
  TColCadenas nuevo = new _rep_colCadenas;
  nuevo->tam = M;
  nuevo->arcad = new TCadena[M];
  nat pos = 0;
  while (pos < M) {
    nuevo->arcad[pos] = crearCadena();
    pos++;
  }
  return nuevo;
}

TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col) {
  if (pos < col->tam) {
    if (esVaciaCadena(col->arcad[pos]))
      col->arcad[pos] = insertarAlFinal(info, col->arcad[pos]);
    else
      col->arcad[pos] = insertarAntes(info, inicioCadena(col->arcad[pos]), col->arcad[pos]);
  }
  return col;
}

bool estaEnColCadenas(nat dato, nat pos, TColCadenas col) {
  if (pos < col->tam)
    return pertenece(dato, col->arcad[pos]);
  else 
    return false;
}

TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col) {
  return infoCadena(siguienteClave(dato, inicioCadena(col->arcad[pos]), col->arcad[pos]), col->arcad[pos]);
}

TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col) {
  col->arcad[pos] = removerDeCadena(siguienteClave(dato, inicioCadena(col->arcad[pos]), col->arcad[pos]), col->arcad[pos]);
  return col;
}

void liberarColCadenas(TColCadenas col) {
  while (col->tam > 0) {
    liberarCadena(col->arcad[col->tam-1]);
    col->tam--;
  }
  delete[] col->arcad;
  delete col;
}