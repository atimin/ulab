Mikro-Lineara Algebra biblioteko
==========================================

uLAB - это простая и маленькая библиотека для работы с N-мерными матрицами на Си,
которая должна работать везде даже на 8-битных микроконтроллерах.

Использование
-------------------------------------------
Для использования библиотеки Вам необходимо реализовать две функции: `ulab_dense_create` - для создания матрицы и  `ulab_dense_free`  - для ее уничтожения. Такой дизайн необходим, т.к. разные платформы используют разные способы выделения и освобождения памяти. Пример:

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

Установка
-------------------------------------------

Просто скопируйте файлы в Ваш проект.

Тестирование
-------------------------------------------

Запустите команду в корне директории проекта:  `gcc -o test test.c u_lab.c`

Ссылки
-------------------------------------------

* [Код][1] - проект на GutHub
* [Ligo de Internacia Programado][2] - если вы понимаете что написано, тогда присоединяйтесь!
* [LAPACK][3] - старший брат
* [Komputeko][4] - Эсперанто словарь компьютерных терминов 

[1]:https://github.com/flipback/ulab
[2]:http://www.ldip.org
[3]:http://www.netlib.org/lapack/
[4]:http://komputeko.net/
