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

/* Pravalorizo de matrico dense matrico */
ulab_error_t  ulab_dense_init(ulab_dense_matrix_t *matrix, ulab_dim_t dim, ulab_dim_t *shape, ulab_element_t *data)
{
  matrix->dim = dim;
  matrix->shape = shape;
  matrix->data = data;

  return ULAB_OK;
}

/* Preni elementon de matrico */
ulab_error_t ulab_dense_get(ulab_dense_matrix_t* matrix, ulab_element_t *value, ulab_dim_t *coord)
{
  ulab_dim_t strides[matrix->dim];
  int i;

  /* TODO: Aldonu teston por eliro de koordinatoj ekster dimensio de matrico. */
  /* Kalkulu pasxojn por sercxado de elemento cxe linia tabulo */
  strides[matrix->dim - 1] = 1;        

  for(i = matrix->dim - 2; i >= 0; i--) {
    strides[i] = strides[i+1] * matrix->shape[i+1];
  }

  /* Serxado de elemento */
  ulab_dim_t p = 0;
  for(i=0; i < matrix->dim; i++)
    p += strides[i] * coord[i];

  *value = matrix->data[p];

  return ULAB_OK;
}
