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

/* Tipo, kiun uzas por difino de dimensioj 
 * Vi povas sxangxi gxin por via tasko */
typedef unsigned int ulab_dim_t;

/* Tipo, kiun uzas por elementoj de matrico
 * Vi povas same sxangxi gxin kiel necese */
typedef int ulab_element_t;

/* Tipo de eraro. Eraro egalas 1, se kodo ruligxis sen problemoj */
typedef enum {
  ULAB_ERROR = 0,
  ULAB_OK
} ulab_error_t;

/* La gxenerala strukturo de densa matrico */
typedef struct 
{
  ulab_dim_t      dim;      /* dimension de matrico */ 
  ulab_dim_t      *shape;   /* formo de matrico - multo da linioj, kolumnoj k.t.p */ 
  ulab_element_t  *data;    /* elementoj de matrico */
} ulab_dense_matrix_t;

/* Kreado de matrico dense matrico 
 * ATENDU: cxi funkcion uzanto de biblioteko devas programi mem
 * @param dim estas dimension de matrico 
 * @param shape estas referenco al tabelo, kiu prezentos formo de matrico 
 * @param data estas tableto de elementoj de matrico
 * @return matrix estas referenco al matrico, kiu estas kreita */
extern ulab_dense_matrix_t* ulab_create_dense_matrix(ulab_dim_t dim, ulab_dim_t* shape);

/* Detrui matricon 
 * ATENDU: cxi funkcion uzanto de biblioteko devas programi mem
 * @param matrix estas referenco al matrico, kiu estas pravalorizata */
extern void ulab_free_dense_matrix(ulab_dense_matrix_t *m);

/* Pravalorizo de matrico dense matrico 
 * @param matrix estas referenco al matrico, kiu estas pravalorizata 
 * @param dim estas dimension de matrico 
 * @param shape estas referenco al tabelo, kiu prezentos formo de matrico 
 * @param data estas tableto de elementoj de matrico
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_dense_init(ulab_dense_matrix_t* matrix, ulab_dim_t dim,  ulab_dim_t *shape, ulab_element_t *data);

/* Legi elementon de matrico 
 * @param matrix estas referenco al matrico, kiu estas pravalorizata 
 * @param value estas referenco al variablo, kiu konservas rezulton 
 * @param coord estas referenco al tabulo da koordinatoj de elementoj, kies valoron estas prenata 
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_dense_get(ulab_dense_matrix_t* matrix, ulab_element_t *value, ulab_dim_t *coord);

/* Skribi en elementon de matrico 
 * @param matrix estas referenco al matrico, kiu estas pravalorizata 
 * @param value estas referenco al variablo, kiun oni skribas 
 * @param coord estas referenco al tabulo da koordinatoj de elementoj, kies valoron estas prenata 
 * @return kodo de eraro @see ulab_error_t*/
extern ulab_error_t ulab_dense_set(ulab_dense_matrix_t* matrix, ulab_element_t value, ulab_dim_t *coord);


#endif
