Mikro-Lineara Algebra biblioteko
==========================================

uLAB estas simpla kaj eta biblioteko de agoj kun N-dimensiaj matricoj skribata per C, kiu devas funkcii cxie ecx por 8-bitaj mikroreguliloj. 

Uzado
-------------------------------------------
Por uzi la bibliotekon en via programo vi devas programi du funkciojn: `ulab_malloc` por eligo de memoro kaj `ulab_free` por liberigo ĝin. Tia dizajno necesas pro diversaj platformoj povas uzi diversajn metodon de eligo kaj liberigo de memoro. Ekzemplo por la plej simpla okazo:

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

Instalado
-------------------------------------------

Simple kopiu dosierojn en via projekto.


Testado
-------------------------------------------

Provu en radiko de projekto:  `gcc -o test test.c u_lab.c`

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
