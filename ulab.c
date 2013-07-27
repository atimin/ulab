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

#include "ulab.h"
/*======================================================================
 * Privataj funkcioj 
 * ===================================================================*/

/*======================================================================
 * Publikaj funkcioj 
 * ===================================================================*/

/* Kreado de matrico  */
ulab_matrix_t* ulab_matrix_new(ulab_dim_t rows, ulab_dim_t columns)
{
  ulab_matrix_t *m;
  int i;

  m = ulab_malloc(sizeof(ulab_matrix_t));

  m->rows = rows;
  m->columns = columns;
  m->count = rows * columns;
  m->data = ulab_malloc(m->count * sizeof(ulab_element_t));

  return m;
}

/* Detruado de matrico */
void ulab_matrix_destroy(ulab_matrix_t *m)
{
  ulab_free(m->data);
  ulab_free(m);
}

/* Kreado de nula matrico */
ulab_matrix_t* ulab_matrix_zero(ulab_dim_t rows, ulab_dim_t columns)
{ 
  ulab_dim_t i,c;

  ulab_matrix_t *m = ulab_matrix_new(rows, columns);

  c = rows * columns;
  for (i = 0; i < c; i++) {
    m->data[i] = 0;
  }

  return m;
}

/* Kreado de matrico el tabelo */
ulab_matrix_t* ulab_matrix_from_ary(ulab_dim_t rows, ulab_dim_t columns, ulab_element_t* ary)
{
  ulab_dim_t i,c;

  ulab_matrix_t *m = ulab_matrix_new(rows, columns);
  
  c = rows * columns;
  for (i = 0; i < c; i++) {
    m->data[i] = ary[i];
  }

  return m;
}

/* Legadi de matrica elemento */
ulab_error_t ulab_matrix_get_el(ulab_matrix_t* m, ulab_dim_t i, ulab_dim_t j, ulab_element_t* v)
{
  ulab_dim_t index = i*m->columns + j;

  if (index >= m->count) return ULAB_OUT_RANGE_ERROR;

  *v = m->data[index];

  return ULAB_NO_ERROR;
}

/* Skribado de matrica elemento */
ulab_error_t ulab_matrix_set_el(ulab_matrix_t* m, ulab_dim_t i, ulab_dim_t j, ulab_element_t v)
{
  ulab_dim_t index = i*m->columns + j;

  if (index >= m->count) return ULAB_OUT_RANGE_ERROR;
 
  m->data[index] = v;

  return ULAB_NO_ERROR;
}

/* Kopiado de matrico */
ulab_error_t ulab_matrix_copy(ulab_matrix_t* m, ulab_matrix_t* mc) 
{
  ulab_dim_t i, c;

  /* Kopiu elementojn po unu */
  for (i = 0; i < m->count; i++) {
    mc->data[i] = m->data[i];
  }
  
  return ULAB_NO_ERROR;
}

/* Adicio de du matricoj a + b kaj konservado de rezulto al a */
ulab_error_t ulab_matrix_add(ulab_matrix_t* ma, ulab_matrix_t* mb)
{
  ulab_dim_t i;

  /* Testu dimensiojn de matricoj. Ili devas esti egalaj */
  if (ma->rows != mb->rows 
      || ma->columns != mb->columns) return ULAB_FORM_ERROR;

  /* Adiciu elementojn de matricoj */
  for (i = 0; i < ma->count; i++) {
    ma->data[i] += mb->data[i];
  }

  return ULAB_NO_ERROR;
}

/* Skalara multipliko de matrico */
ulab_error_t ulab_matrix_smul(ulab_matrix_t* m, ulab_element_t k)
{
  ulab_dim_t i, c;

  for (i = 0; i < m->count; i++) {
    m->data[i] *= k;
  }

  return ULAB_NO_ERROR;
}

/* Multipliko de du matricoj a * b kaj konservado de rezulto al a */
ulab_error_t ulab_matrix_mmul(ulab_matrix_t* ma, ulab_matrix_t* mb)
{
  ulab_dim_t i, j, n, count, rows, columns, com;

  /* Testo de formoj de matricoj */
  if (ma->columns != mb->rows) return ULAB_FORM_ERROR;

  rows = ma->rows;
  columns = mb->columns;
  com = mb->rows;
  count = rows * columns;

  ulab_element_t *data = ulab_malloc(sizeof(ulab_element_t) * count);
  
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns; j++) {
      data[columns*i + j] = 0;
      for (n = 0; n < com; n++) {
        data[columns*i + j] += ma->data[ma->columns*i + n] * mb->data[mb->columns*n + j];
      }
    }
  }

  ulab_free(ma->data);

  ma->rows = rows;
  ma->columns = columns;
  ma->count = count;
  ma->data = data;
  
  return ULAB_NO_ERROR;
}
