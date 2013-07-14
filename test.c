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

void *ulab_malloc(size_t size)
{
  return malloc(size);
}

void ulab_free(void *ptr)
{
  free(ptr);
}

typedef void (*test_func)(ulab_dense_matrix_t*);
void test_frame(const char *msg, test_func f)
{
  printf(msg);
  
  ulab_dense_matrix_t *m;


  m = ulab_dense_create(4,5);

  f(m);

  printf("\t\[Bone]\n");
  ulab_dense_free(m);
}
/*=============================================================================*/

void test_creating_zero(ulab_dense_matrix_t *m)
{
  ulab_dim_t i;

  ulab_dense_matrix_t *a = ulab_dense_create_zero(12,10);

  for (i = 0; i < 120; i++) {
    assert(a->data[i] == 0);
  }

  ulab_dense_free(a);
}
void test_ulab_dense_get(ulab_dense_matrix_t* m)
{
  ulab_element_t val = 0;
  m->data[6] = 99;
  ulab_dense_get(m, &val, 1,1);

  assert(val == m->data[6]);
}

void test_ulab_dense_set(ulab_dense_matrix_t* m)
{
  ulab_element_t val = 66;
  ulab_dense_set(m, val, 3,3);

  assert(val == m->data[18]);
}

void test_checking_coords(ulab_dense_matrix_t* m)
{
  ulab_element_t val = 0;

  assert(ULAB_ERROR == ulab_dense_set(m, val, 5, 4));
  assert(ULAB_ERROR == ulab_dense_get(m, &val, 4,6));
}

void test_copy(ulab_dense_matrix_t* m)
{
  ulab_dense_matrix_t *n;
  int i;
  n = ulab_dense_copy(m);

  assert(n);
  for (i = 0; i < m->count; i++) {
    assert(m->data[i] == n->data[i]);
  }
}

void test_adiciado(ulab_dense_matrix_t* m)
{
  ulab_element_t v = 0;
  ulab_dense_matrix_t* b = ulab_dense_create(4,5);
  
  /* Testu per tri elementoj */
  ulab_dense_set(m, 1, 1, 2);
  ulab_dense_set(b, 3, 1, 2);


  ulab_dense_set(m, -1, 3, 4);
  ulab_dense_set(b, 0, 3, 4);

  ulab_dense_set(m, 4, 2, 2);
  ulab_dense_set(b, 8, 2, 2);

  assert(ulab_dense_add(m,b) == ULAB_OK);

  ulab_dense_get(m, &v, 1, 2);
  assert(v == 4);

  ulab_dense_get(m, &v, 3, 4);
  assert(v == -1);

  ulab_dense_get(m, &v, 2, 2);
  assert(v == 12);

  ulab_dense_free(b);
}

void test_adiciado_checking(ulab_dense_matrix_t *m)
{
  
  ulab_dense_matrix_t* b = ulab_dense_create(3, 2);

  assert(ulab_dense_add(m,b) == ULAB_ERROR);

  ulab_dense_free(b);
}

void test_scalar_multiplication(ulab_dense_matrix_t *m)
{
  ulab_element_t v = 0;
  ulab_element_t k = 2;
  
  /* Testu per tri elementoj */
  ulab_dense_set(m, 1, 1, 2);
  ulab_dense_set(m, -1, 3, 4);
  ulab_dense_set(m, 4, 2, 2);

  assert(ulab_dense_smul(m, k) == ULAB_OK);

  ulab_dense_get(m, &v, 1, 2);
  assert(v == 2);

  ulab_dense_get(m, &v, 3, 4);
  assert(v == -2);

  ulab_dense_get(m, &v, 2, 2);
  assert(v == 8);
}

int main()
{
  test_frame("Testas kreado de nula densa matrixo.", test_creating_zero);
  test_frame("Testas legadon de elemento de densa matrico.", test_ulab_dense_get);
  test_frame("Testas skribadon de elemento de densa matrico.", test_ulab_dense_set);
  test_frame("Testas foriron ekstre de densa  matrico.", test_checking_coords);
  test_frame("Testas kopiadon de densa matrico.", test_copy);
  test_frame("Testas adiciadon de densaj matricoj.", test_adiciado);
  test_frame("Testas testo de gxustaj datumoj por adiciadon de densaj matricoj.", test_adiciado_checking);
  test_frame("Testas skalaran multiplikon de densaj matricoj.", test_scalar_multiplication);
  /* test_frame("Testas matrican multiplikon de densaj matricoj.", test_matrico_multiplication); */
  return 1;
}
