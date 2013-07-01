Mikro-Lineara Algebra biblioteko
==========================================

uLAB estas simpla kaj eta biblioteko de agoj kun N-dimensiaj matricoj skribata per C, kiu devas funkcii cxie ecx por 8-bitaj mikroreguliloj. 

Uzado
-------------------------------------------
Por uzi la bibliotekon en via programo vi devas programi du funkciojn: `ulab_dense_create` por kreado de matrico kaj `ulab_dense_free` por detrui ĝin. Tia dizajno necesas pro diversaj platformoj povas uzi diversajn metodon de eligo kaj liberigo de memoro. Ekzemple:

```C
  ulab_dense_matrix_t* ulab_dense_create(ulab_dim_t dim, ulab_dim_t* shape)
  {
    ulab_dense_matrix_t *m;
    int i, count;

    m = malloc(sizeof(ulab_dense_matrix_t));

    m->dim = dim;

    m->shape = malloc(sizeof(ulab_dim_t) * dim);

    count = 1;
    for (i = 0; i < dim; i++) {
      m->shape[i] = shape[i];
      count *= shape[i];
    }

    m->data = malloc(count);

    return m;
  }

  void ulab_dense_free(ulab_dense_matrix_t *m)
  {
    free(m->data);
    free(m->shape);
    free(m);
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
