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
  ULAB_NO_ERROR = 0,      /* Cxio bone */
  ULAB_ALLOC_ERROR,       /* Memoro ne estas eligita */ 
  ULAB_OUT_RANGE_ERROR,   /* Eliro ekster de dimensio */
  ULAB_NO_EQL_FORM        /* Matricoj havas diversajn formojn */
} ulab_error_t;

/* La gxenerala strukturo de densa matrico */
typedef struct 
{
  ulab_dim_t      rows;
  ulab_dim_t      columns;
  ulab_dim_t      count;
  ulab_element_t  *data;    /* elementoj de matrico */
} ulab_matrix_t;

/*================================================================== */

/* ATENDU: Uzanto devas programi la funkcion mem  */
extern void* ulab_malloc(size_t size);

/* ATENDU: Uzanto devas programi la funkcion mem  */
extern void ulab_free(void *ptr);

/* Kreado de matrico 
 * @param rows estas kiomo de vicoj
 * @param columns estas kiomo de kolumnoj
 * @return matrix estas referenco al matrico, kiu estas kreita */
extern ulab_matrix_t* ulab_matrix_new(ulab_dim_t rows, ulab_dim_t columns);

/* Kreado de nula matrico 
 * @param rows estas kiomo de vicoj
 * @param columns estas kiomo de kolumnoj
 * @return matrix estas referenco al matrico, kiu estas kreita */
extern ulab_matrix_t* ulab_matrix_zero(ulab_dim_t rows, ulab_dim_t columns);

/* Kreado de matrico el tabelo
 * @param rows estas kiomo de vicoj
 * @param columns estas kiomo de kolumnoj
 * @param estas referenco al tabelo, kiu estas fonto
 * @return matrix estas referenco al matrico, kiu estas kreita */
extern ulab_matrix_t* ulab_matrix_from_ary(ulab_dim_t rows, ulab_dim_t columns, ulab_element_t* ary);

/* Detruado de matrico */
extern void ulab_matrix_destroy(ulab_matrix_t *m);
/*==================================================================*/

/* Legado de matrica elemento
 * @param matrix estas referenco al matrico
 * @param i estas indekso de vico 
 * @param j estas indekso de kolumno
 * @param value estas referenco al variablo, kiu konservas rezulton 
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_matrix_get_el(ulab_matrix_t* matrix, ulab_dim_t i, ulab_dim_t j, ulab_element_t* value);

/* Skribado de elemento de matrico 
 * @param matrix estas referenco al matrico
 * @param i estas indekso de vico 
 * @param j estas indekso de kolumno
 * @param value estas signifo, kiun oni skribas 
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_matrix_set_el(ulab_matrix_t* matrix, ulab_dim_t i, ulab_dim_t j, ulab_element_t value);

/* Kopiado de matrico
 * @param matrix estas referenco al matrico, kiu estas kopiata 
 * @parar copy estas kopio de la fonta matrico, vi devas pasigi nepravalorizatan referencon
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_matrix_copy(ulab_matrix_t* matrix, ulab_matrix_t* copy);

/* Adicio de du matricoj a + b kaj konservado de rezulto al a
 * @param a unua matrica, gxi konservas rezulton de adicio
 * @param b dua matrica
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_matrix_add(ulab_matrix_t* matrix_a, ulab_matrix_t* matrix_b);

/* Skalara multipliko de matrico 
 * @param matrix matrica, kiu estas multiplikata kaj kiu konservas rezulton
 * @param k skalara faktoro 
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_matrix_smul(ulab_matrix_t* matrix, ulab_element_t k);

/* Multipliko de du matricoj a * b kaj konservado de rezulto al a
 * @param a unua matrica, gxi konservas rezulton de multipliko
 * @param b dua matrica
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_matrix_mmul(ulab_matrix_t* matrix_a, ulab_matrix_t* matrix_b);
#endif
