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

typedef void (*test_func)(ulab_matrix_t*);
void test_frame(const char *msg, test_func f)
{
  printf(msg);
  
  ulab_matrix_t *m;


  m = ulab_matrix_new(4,5);

  f(m);

  printf("\t\[Bone]\n");
  ulab_matrix_destroy(m);
}
/*=============================================================================*/

void test_creating_zero(ulab_matrix_t *m)
{
  ulab_dim_t i;

  ulab_matrix_t *a = ulab_matrix_zero(12,10);

  for (i = 0; i < 120; i++) {
    assert(a->data[i] == 0);
  }

  ulab_free(a);
}

void test_from_ary(ulab_matrix_t *m)
{
  ulab_matrix_t *n;
  ulab_element_t v;
  ulab_element_t ary[] = { 1,2, 3,4, 5,6 };

  n = ulab_matrix_from_ary(3, 2, ary);

  assert(ulab_matrix_get_el(n, 2, 1, &v) == ULAB_NO_ERROR);
  assert(v == 6);

  ulab_matrix_destroy(n);
}
void test_ulab_get(ulab_matrix_t* m)
{
  ulab_element_t val = 0;
  m->data[6] = 99;
  ulab_matrix_get_el(m, 1, 1, &val);

  assert(val == m->data[6]);
}

void test_ulab_set(ulab_matrix_t* m)
{
  ulab_element_t val = 66;
  ulab_matrix_set_el(m, 3, 3, val);

  assert(val == m->data[18]);
}

void test_checking_coords(ulab_matrix_t* m)
{
  ulab_element_t val = 0;

  assert(ULAB_OUT_RANGE_ERROR == ulab_matrix_set_el(m, 5, 4, val));
  assert(ULAB_OUT_RANGE_ERROR == ulab_matrix_get_el(m, 4,6, &val));
}

void test_copy(ulab_matrix_t* m)
{
  ulab_matrix_t *n;
  int i;

  assert(ulab_matrix_copy(m, n) == ULAB_NO_ERROR);

  for (i = 0; i < m->count; i++) {
    assert(m->data[i] == n->data[i]);
  }
}

void test_adiciado(ulab_matrix_t* m)
{
  ulab_element_t v = 0;
  ulab_matrix_t* b = ulab_matrix_new(4,5);
  
  /* Testu per tri elementoj */
  ulab_matrix_set_el(m, 1, 2, 1);
  ulab_matrix_set_el(b, 1, 2, 3);


  ulab_matrix_set_el(m, 3, 4, -1);
  ulab_matrix_set_el(b, 3, 4, 0);

  ulab_matrix_set_el(m, 2, 2, 4);
  ulab_matrix_set_el(b, 2, 2, 8);

  assert(ulab_matrix_add(m,b) == ULAB_NO_ERROR);

  ulab_matrix_get_el(m, 1, 2, &v);
  assert(v == 4);

  ulab_matrix_get_el(m, 3, 4, &v);
  assert(v == -1);

  ulab_matrix_get_el(m, 2, 2, &v);
  assert(v == 12);

  ulab_free(b);
}

void test_adiciado_checking(ulab_matrix_t *m)
{
  
  ulab_matrix_t* b = ulab_matrix_new(3, 2);

  assert(ulab_matrix_add(m,b) == ULAB_NO_EQL_FORM);

  ulab_free(b);
}

void test_scalar_multiplication(ulab_matrix_t *m)
{
  ulab_element_t v = 0;
  ulab_element_t k = 2;
  
  /* Testu per tri elementoj */
  ulab_matrix_set_el(m, 1, 2, 1);
  ulab_matrix_set_el(m, 3, 4, -1);
  ulab_matrix_set_el(m, 2, 2, 4);

  assert(ulab_matrix_smul(m, k) == ULAB_NO_ERROR);

  ulab_matrix_get_el(m, 1, 2, &v);
  assert(v == 2);

  ulab_matrix_get_el(m, 3, 4, &v);
  assert(v == -2);

  ulab_matrix_get_el(m, 2, 2, &v);
  assert(v == 8);
}

void test_matrix_multiplication(ulab_matrix_t* m)
{
  ulab_element_t v;
  
  ulab_element_t arr_a[] = {1, 3, 1, 2};
  ulab_element_t arr_b[] = {1, 2, 1, 3, 1, 0};
  ulab_element_t arr_result[] = {10, 5, 1, 7, 4, 1};



  ulab_matrix_t* a = ulab_matrix_from_ary(2, 2, arr_a);
  ulab_matrix_t* b = ulab_matrix_from_ary(2, 3, arr_b);

  assert(ulab_matrix_mmul(a, b) == ULAB_NO_ERROR);
  
  
  /* Testu elementojn */
  ulab_matrix_get_el(a, 0, 0, &v);
  assert(v == 10);

  ulab_matrix_get_el(a, 0, 1, &v);
  assert(v == 5);

  ulab_matrix_get_el(a, 0, 2, &v);
  assert(v == 1);

  ulab_matrix_get_el(a, 1, 0, &v);
  assert(v == 7);

  ulab_matrix_get_el(a, 1, 1, &v);
  assert(v == 4);

  ulab_matrix_get_el(a, 1, 2, &v);
  assert(v == 1);

  ulab_free(a);
  ulab_free(b);
}

int main()
{
  test_frame("Testas kreado de nula matrico.", test_creating_zero);
  test_frame("Testas kreado de matrico el tabelo.", test_from_ary);
  test_frame("Testas legadon de elemento de matrico.", test_ulab_get);
  test_frame("Testas skribadon de elemento de matrico.", test_ulab_set);
  test_frame("Testas foriron ekstre de matrico.", test_checking_coords);
  test_frame("Testas kopiadon de matrico.", test_copy);
  test_frame("Testas adiciadon de matricoj.", test_adiciado);
  test_frame("Testas testo de gxustaj datumoj por adiciadon de matricoj.", test_adiciado_checking);
  test_frame("Testas skalaran multiplikon de matricoj.", test_scalar_multiplication);
  test_frame("Testas matrican multiplikon de densaj matricoj.", test_matrix_multiplication);
  return 1;
}
