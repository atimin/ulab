Mikro-Lineara Algebra biblioteko
==========================================

uLAB estas simpla kaj eta biblioteko de agoj kun 2-dimensiaj matricoj skribata per C, kiu devas funkcii cxie ecx por 8-bitaj mikroreguliloj. 


Ecoj
-------------------------------------------

1. Nur *2-N* matricoj.
2. Kreado de nula matrico kaj el tabelo
3. Skribado kaj legado de elemento per linio kaj kolumno
4. Adicio de matricoj
5. Skalara kaj matrica multipliko

Uzado
-------------------------------------------
Por uzi la bibliotekon en via programo vi devas programi du funkciojn: `ulab_malloc` por eligo de memoro kaj `ulab_free` por liberigo gxin. Tia dizajno necesas pro diversaj platformoj povas uzi diversajn metodon de eligo kaj liberigo de memoro. Ekzemplo por la plej simpla okazo:

```C
  void *ulab_malloc(size_t size)
  {
    return malloc(size);
  }

  void ulab_free(void *ptr)
  {
    free(ptr);
  }
```

Deflauxte tipo de elementoj de matrico estas `int`, sed vi povas sxangxi gxin por via tasko en komenco de dosiero `ulab.h`. 

Ekzemplo
-------------------------------------------

```C
  #include "ulab.h"

  /* ..... */

  ulab_matrix_t *m;
  ulab_element_t v;
  ulab_element_t ary[] = { 1,2, 3,4, 5,6 };

  m = ulab_matrix_from_ary(3, 2, ary);        /* Kreado matrico el tabelo */

  
  ulab_matrix_get_el(m, 2, 1, &v);            /* Prenado de elemento */
  
  ulab_matrix_smul(m, 10);                    /* Multipliko per skalaro */


  ulab_matrix_destroy(m);

```

Instalado
-------------------------------------------

Simple kopiu dosierojn en via projekto.


Testado
-------------------------------------------

Provu en radiko de projekto:  `gcc -o test test.c ulab.c`

Ligiloj
-------------------------------------------

* [Kodo][1] - la projekto en GutHub
* [Ligo de Internacia Programado][2] - se vi komprenas cxi tekston, partoprenu!
* [LAPACK][3] - la granda frato
* [Komputeko][4] - la vortaro da komputikaj terminoj

[1]:https://github.com/flipback/ulab
[2]:http://www.ldip.org
[3]:http://www.netlib.org/lapack/
[4]:http://komputeko.net/
