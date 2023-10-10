#ifndef CUTILS_VEC_VEC_H
#define CUTILS_VEC_VEC_H

#include <stdlib.h>

struct vec {
  void *data;
  size_t len;
  size_t cap;
  size_t elem_size;
};

struct vec *vec_create(size_t elem_size);

// struct vec *vec_alloc(size_t elem_size);
struct vec *vec_from_array(void *arr, size_t len, size_t elem_size);

static void vec_realloc(struct vec *v) {
  if (v->cap == 0) {
    v->data = malloc(v->elem_size);
    v->cap = 1;
  } else {
    v->cap *= 2;
    v->data = realloc(v->data, v->cap * v->elem_size);
  }
}

void vec_push(struct vec *v, void *value);

void *vec_get(struct vec *v, size_t at);

void *vec_pop(struct vec *v);

void vec_set(struct vec *v, void *value, size_t at);

void vec_free(struct vec *v);

#endif // VEC_LIBRARY_H
