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

#ifndef _ULAB_
#define _ULAB_

#include <stdio.h>

/* Tipo, kiun uzas por difino de dimensioj 
 * Vi povas sxangxi gxin por via tasko */
typedef unsigned int ulab_dim_t;

/* Tipo, kiun uzas por elementoj de matrico
 * Vi povas same sxangxi gxin kiel necese */
typedef int ulab_element_t;

/* Tipo de eraro. Eraro egalas 0, se kodo ruligxis sen problemoj */
typedef enum {
  ULAB_ERROR = -1,
  ULAB_OK
} ulab_error_t;

/* La gxenerala strukturo de densa matrico */
typedef struct 
{
  ulab_dim_t      dim;      /* dimension de matrico */ 
  ulab_dim_t      *shape;   /* formo de matrico - multo da linioj, kolumnoj k.t.p */ 
  ulab_dim_t      count;    /* kiomo de elementoj */
  ulab_dim_t      *strides; /* pasxoj de matrico por sercxado de elementoj */
  ulab_element_t  *data;    /* elementoj de matrico */
} ulab_dense_matrix_t;

/*================================================================== */

/* ATENDU: Uzanto devas programi la funkcion mem  */
extern void* ulab_malloc(size_t size);

/* ATENDU: Uzanto devas programi la funkcion mem  */
extern void ulab_free(void *ptr);

/* Kreado de densa matrico 
 * @param dim estas dimension de matrico 
 * @param shape estas referenco al tabelo, kiu prezentos formo de matrico 
 * @return matrix estas referenco al matrico, kiu estas kreita */
extern ulab_dense_matrix_t* ulab_dense_create(ulab_dim_t dim, ulab_dim_t* shape);

/* Detruado de matrico
 * @param matrix estas referenco al matrico, kiu estas pravalorizata */
extern void ulab_dense_free(ulab_dense_matrix_t *m);


/* Kreado de nula densa matrico 
 * @param dim estas dimension de matrico 
 * @param shape estas referenco al tabelo, kiu prezentos formo de matrico 
 * @return matrix estas referenco al matrico, kiu estas kreita */
extern ulab_dense_matrix_t* ulab_dense_create_zero(ulab_dim_t dim, ulab_dim_t* shape);
/*==================================================================*/

/* Legado de matrica elemento
 * @param matrix estas referenco al matrico
 * @param value estas referenco al variablo, kiu konservas rezulton 
 * @param coord estas referenco al tabulo da koordinatoj de elementoj, kies valoron estas prenata 
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_dense_get(ulab_dense_matrix_t* matrix, ulab_element_t *value, ulab_dim_t *coord);

/* Skribado de elemento de matrico 
 * @param matrix estas referenco al matrico
 * @param value estas referenco al variablo, kiun oni skribas 
 * @param coord estas referenco al tabulo da koordinatoj de elementoj, kies valoron estas prenata 
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_dense_set(ulab_dense_matrix_t* matrix, ulab_element_t value, ulab_dim_t *coord);

/* Kopiado de matrico
 * @param matrix estas referenco al matrico, kiu estas kopiata 
 * @parar copy estas kopio de la fonta matrico, vi devas pasigi nepravalorizatan referencon
 * @return kopio aŭ 0, se eraro estas. */
extern ulab_dense_matrix_t* ulab_dense_copy(ulab_dense_matrix_t* matrix);

/* Adicio de du matricoj a + b kaj konservado de rezulto al a
 * @param a unua matrica, gxi konservas rezulton de adicio
 * @param b dua matrica
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_dense_add(ulab_dense_matrix_t* matrix_a, ulab_dense_matrix_t* matrix_b);

/* Skalara multipliko de matrico 
 * @param matrix matrica, kiu estas multiplikata kaj kiu konservas rezulton
 * @param k skalara faktoro 
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_dense_smul(ulab_dense_matrix_t* matrix, ulab_element_t k);

/* Multipliko de du matricoj a * b kaj konservado de rezulto al a
 * @param a unua matrica, gxi konservas rezulton de multipliko
 * @param b dua matrica
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_dense_mmul(ulab_dense_matrix_t* matrix_a, ulab_dense_matrix_t* matrix_b);
#endif
