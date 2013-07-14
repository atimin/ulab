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
/*======================================================================
 * Privataj funkcioj 
 * ===================================================================*/

/*======================================================================
 * Publikaj funkcioj 
 * ===================================================================*/

/* Kreado de densa matrico  */
ulab_dense_matrix_t* ulab_dense_create(ulab_dim_t rows, ulab_dim_t columns)
{
  ulab_dense_matrix_t *m;
  int i;

  m = ulab_malloc(sizeof(ulab_dense_matrix_t));

  m->rows = rows;
  m->columns = columns;
  m->count = rows * columns;
  m->data = ulab_malloc(m->count * sizeof(ulab_element_t));

  return m;
}

/* Detruado de matrico */
void ulab_dense_free(ulab_dense_matrix_t *m)
{
  ulab_free(m->data);
  ulab_free(m);
}

/* Kreado de nula densa matrico */
ulab_dense_matrix_t* ulab_dense_create_zero(ulab_dim_t rows, ulab_dim_t columns)
{ 
  ulab_dim_t i,c;

  ulab_dense_matrix_t *matrix = ulab_dense_create(rows, columns);

  c = rows * columns;
  for (i = 0; i < c; i++) {
    matrix->data[i] = 0;
  }

  return matrix;
}

/* Legadi de matrica elemento */
ulab_error_t ulab_dense_get(ulab_dense_matrix_t* matrix, ulab_element_t *value, ulab_dim_t i, ulab_dim_t j)
{
  ulab_dim_t index = i*matrix->columns + j;

  if (index >= matrix->count) return ULAB_ERROR;

  *value = matrix->data[index];

  return ULAB_OK;
}

/* Skribado de matrica elemento */
ulab_error_t ulab_dense_set(ulab_dense_matrix_t* matrix, ulab_element_t value, ulab_dim_t i, ulab_dim_t j)
{
  ulab_dim_t index = i*matrix->columns + j;

  if (index >= matrix->count) return ULAB_ERROR;
 
  matrix->data[index] = value;

  return ULAB_OK;
}

/* Kopiado de matrico */
ulab_dense_matrix_t* ulab_dense_copy(ulab_dense_matrix_t* matrix) 
{
  ulab_dim_t i, c;
  ulab_dense_matrix_t *copy;

  /* Eligu memoro por la kopio */
  copy = ulab_dense_create(matrix->rows, matrix->columns);
  if (copy == NULL)
    return copy;
  
  /* Kopiu elementojn po unu */
  for (i = 0; i < matrix->count; i++) {
    copy->data[i] = matrix->data[i];
  }
  
  return copy;
}

/* Adicio de du matricoj a + b kaj konservado de rezulto al a */
ulab_error_t ulab_dense_add(ulab_dense_matrix_t* matrix_a, ulab_dense_matrix_t* matrix_b)
{
  ulab_dim_t i;

  /* Testu dimensiojn de matricoj. Ili devas esti egalaj */
  if (matrix_a->rows != matrix_b->rows 
      || matrix_a->columns != matrix_b->columns) return ULAB_ERROR;

  /* Adiciu elementojn de matricoj */
  for (i = 0; i < matrix_a->count; i++) {
    matrix_a->data[i] += matrix_b->data[i];
  }

  return ULAB_OK;
}

/* Skalara multipliko de matrico */
ulab_error_t ulab_dense_smul(ulab_dense_matrix_t* matrix, ulab_element_t k)
{
  ulab_dim_t i, c;

  for (i = 0; i < matrix->count; i++) {
    matrix->data[i] *= k;
  }

  return ULAB_OK;
}

/* Multipliko de du matricoj a * b kaj konservado de rezulto al a */
ulab_error_t ulab_dense_mmul(ulab_dense_matrix_t* matrix_a, ulab_dense_matrix_t* matrix_b)
{
  return ULAB_ERROR;
}
