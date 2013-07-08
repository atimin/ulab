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

  m->data = malloc(count * sizeof(ulab_element_t));

  return m;
}

void ulab_dense_free(ulab_dense_matrix_t *m)
{
  free(m->data);
  free(m->shape);
  free(m);
}

typedef void (*test_func)(ulab_dense_matrix_t*);
void test_frame(const char *msg, test_func f)
{
  printf(msg);
  
  ulab_dense_matrix_t *m;
  ulab_element_t shape[3] = {4,5,6};


  m = ulab_dense_create(3, shape);

  f(m);

  printf("\t\[Bone]\n");
  ulab_dense_free(m);
}
/*=============================================================================*/

void test_ulab_dense_get(ulab_dense_matrix_t* m)
{
  ulab_element_t val = 0;
  ulab_dim_t coord[3] = {3,3,3};
  m->data[111] = 99;
  ulab_dense_get(m, &val, coord);

  assert(val == m->data[111]);
}

void test_ulab_dense_set(ulab_dense_matrix_t* m)
{
  ulab_element_t val = 66;
  ulab_dim_t coord[3] = {2,1,4};
  ulab_dense_set(m, val, coord);

  assert(val == m->data[70]);
}

void test_checking_coords(ulab_dense_matrix_t* m)
{
  ulab_element_t val = 0;
  ulab_dim_t coord[3] = {4,5,6};

  assert(ULAB_ERROR == ulab_dense_set(m, val, coord));
  assert(ULAB_ERROR == ulab_dense_get(m, &val, coord));
}

void test_copy(ulab_dense_matrix_t* m)
{
  ulab_dense_matrix_t *n;
  int i;
  n = ulab_dense_copy(m);

  assert(n);
  for (i = 0; i < m->shape[0] * m->shape[1] * m->shape[2]; i++) {
    assert(m->data[i] == n->data[i]);
  }
}

void test_adiciado(ulab_dense_matrix_t* m)
{
  ulab_dim_t coord1[3] = {1,1,1};
  ulab_dim_t coord2[3] = {3,2,1};
  ulab_dim_t coord3[3] = {2,1,3};
  ulab_element_t v = 0;
  ulab_dense_matrix_t* b = ulab_dense_create(3, m->shape);
  
  /* Testu per tri elementoj */
  ulab_dense_set(m, 1, coord1);
  ulab_dense_set(b, 3, coord1);


  ulab_dense_set(m, -1, coord2);
  ulab_dense_set(b, 0, coord2);

  ulab_dense_set(m, 4, coord3);
  ulab_dense_set(b, 8, coord3);

  assert(ulab_dense_sum(m,b) == ULAB_OK);

  ulab_dense_get(m, &v, coord1);
  assert(v == 4);

  ulab_dense_get(m, &v, coord2);
  assert(v == -1);

  ulab_dense_get(m, &v, coord3);
  assert(v == 12);

  ulab_dense_free(b);
}

void test_adiciado_checking(ulab_dense_matrix_t *m)
{
  ulab_dim_t wrong_shape[3] = {1,2,3};
  
  ulab_dense_matrix_t* b = ulab_dense_create(3, wrong_shape);

  assert(ulab_dense_sum(m,b) == ULAB_ERROR);

  ulab_dense_free(b);
}

int main()
{
  test_frame("Testas legadon de elemento de densa matrico.", test_ulab_dense_get);
  test_frame("Testas skribadon de elemento de densa matrico.", test_ulab_dense_set);
  test_frame("Testas foriron ekstre de densa  matrico.", test_checking_coords);
  test_frame("Testas kopiadon de densa matrico.", test_copy);
  test_frame("Testas adiciadon de densaj matricoj.", test_adiciado);
  test_frame("Testas testo de gxustaj datumoj por adiciadon de densaj matricoj.", test_adiciado_checking);

  return 1;
}
