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
ulab_dense_matrix_t* make_2d_matrix(ulab_dim_t a, ulab_dim_t b)
{
  ulab_dense_matrix_t *m;

  m = malloc(sizeof(ulab_dense_matrix_t));

  m->dim = 2;

  m->shape = malloc(sizeof(ulab_dim_t) * 2);
  m->shape[0] = a;
  m->shape[1] = b;

  m->data = malloc(sizeof(ulab_element_t) * a * b);

  return m;
}

void free_matrix(ulab_dense_matrix_t *m)
{
  free(m->data);
  free(m->shape);
  free(m);
}
/*=============================================================================*/

void test_ulab_dense_init()
{
  ulab_dense_matrix_t m;
  ulab_dim_t shape[2] = {2,2};
  ulab_element_t data[4];

  printf("Testas pravalorizon de denso matrico...");

  assert(ulab_dense_init(&m, 2, shape, data));
  assert(m.dim ==  2);
  assert(m.shape ==  shape);
  assert(m.data ==  data);

  printf("\t\[Bone]\n");
  
}

void test_ulab_dense_get()
{
  printf("Testas prenadon de elemento de denso matrico...");

  ulab_dense_matrix_t *m;
  ulab_element_t val = 0;
  ulab_dim_t coord[2] = {3,3};

  m = make_2d_matrix(4,4);
  m->data[15] = 99;

  ulab_dense_get(m, &val, coord);
  assert(val == m->data[15]);

  printf("\t\[Bone]\n");

  free_matrix(m);
}

int main()
{
  test_ulab_dense_init();
  test_ulab_dense_get();
  return 1;
}
