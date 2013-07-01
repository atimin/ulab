/* Kopirajto (k) 2013 Aleksej Timin

La licenco permesas al personoj, kiuj ricevis kopion de cxi programaro
kaj akompana dokumentaro (sekve la Programaro), senpage uzi la
Programaron sen restriktoj inkludante uzadon, kopiadon, sangon,
aldonon, publikigon, disvastigon kaj vendadon da kopioj de la Programaro
nur kondicxe, ke plenumas sekvajn kondicxojn:

1) La almontrita supre sciigo pri auxtora rajto kaj la kondicxoj devas
esti enigita al cxiuj kopioj kaj signifaj partoj de la Programaro;
2) La lingvo de komentoj al kodo kaj dokumentaro de la Programaro,
se gxi estas Interncia Lingvo (Esperanto), ne devas esti sxangxita al ia ajn alia lingvo.

LA PROGRAMARO ESTAS ENHAVITA "KIEL ESTI", SEN IAJ GARANTIOJ, KIUJ
ESTAS KLARE ESPRIMITA AUX SUBKOMPRENITA, SED NE LIMIGXANTE GARANTIOJ
DE VARA TAUXGECO, KONFORMECO AL KONKRETA DESTINO KAJ FORESTO
RAJTA TROMPO. NENIUOKAZE LA AUXTOROJ AUX LA RAJTHAVANTOJ NE RESPONDECAS
LAUX PLENDO PRI KOMPENSAJXO DE DAMAGXO, MALPROFITO AUX ALIAJ POSTULOJ
LAUX EFIKANTAJ KONTRAKTOJ AUX LAUX IA AJN ALIA KIALO, KIU RILATAS KUN
LA PROGRAMARO AUX GXIA UZADO. */

#include "u_lab.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*==============================================================================*/
ulab_dense_matrix_t* ulab_dense_create(ulab_dim_t dim, ulab_dim_t* shape)
{
  ulab_dense_matrix_t *m;
  int i, count;

  m = malloc(sizeof(ulab_dense_matrix_t));

  m->dim = dim;

  m->shape = malloc(sizeof(ulab_dim_t) * dim);

  count = 1;
  for (i = 0; i < dim; i++) {
    m->shape[i] = shape[i];
    count *= shape[i];
  }

  m->data = malloc(count);

  return m;
}

void ulab_dense_free(ulab_dense_matrix_t *m)
{
  free(m->data);
  free(m->shape);
  free(m);
}
/*=============================================================================*/

void test_ulab_dense_get()
{
  printf("Testas legadon de elemento de densa matrico...");

  ulab_dense_matrix_t *m;
  ulab_element_t val = 0;
  ulab_element_t shape[2] = {4,4};
  ulab_dim_t coord[2] = {3,3};

  m = ulab_dense_create(2, shape);
  m->data[15] = 99;

  ulab_dense_get(m, &val, coord);
  assert(val == m->data[15]);

  printf("\t\[Bone]\n");

  ulab_dense_free(m);
}

void test_ulab_dense_set()
{
  printf("Testas skribadon de elemento de densa matrico...");

  ulab_dense_matrix_t *m;
  ulab_element_t val = 66;
  ulab_element_t shape[2] = {4,4};
  ulab_dim_t coord[2] = {2,1};

  m = ulab_dense_create(2, shape);

  ulab_dense_set(m, val, coord);
  assert(val == m->data[9]);

  printf("\t\[Bone]\n");

  ulab_dense_free(m);
}

void test_checking_coords()
{
  printf("Testas foriron ekstre de densa  matrico...");

  ulab_dense_matrix_t *m;
  ulab_element_t val = 0;
  ulab_element_t shape[2] = {4,4};
  ulab_dim_t coord[2] = {100,100};

  m = ulab_dense_create(2, shape);

  assert(ULAB_ERROR == ulab_dense_set(m, val, coord));
  assert(ULAB_ERROR == ulab_dense_get(m, &val, coord));

  printf("\t\[Bone]\n");

  ulab_dense_free(m);
}

void test_copy()
{
  printf("Testas kopiado de densa matrico...");

  ulab_dense_matrix_t *m, *n;
  ulab_element_t val = 0;
  ulab_element_t shape[2] = {4,4};
  int i;

  m = ulab_dense_create(2, shape);
  ulab_dense_copy(m, n);

  for (i = 0; i < shape[0]*shape[1]; i++) {
    assert(m->data[i] == n->data[i]);
  }


  printf("\t\[Bone]\n");

  ulab_dense_free(m);

}

int main()
{
  test_ulab_dense_get();
  test_ulab_dense_set();
  test_checking_coords();
  test_copy();

  return 1;
}
