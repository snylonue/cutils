#ifndef CUTILS_VEC_VEC_H
#define CUTILS_VEC_VEC_H

#include <stddef.h>
#include <stdlib.h>

#include "iter.h"
#include "slice.h"

// SAFETY: All fields should not be modified directly.
struct vec {
  void *data;
  size_t len;
  size_t cap;
  size_t elem_size;
};

struct vec vec_create(size_t elem_size);

// struct vec *vec_alloc(size_t elem_size);
struct vec vec_from_array(const void *arr, size_t len, size_t elem_size);

void vec_push(struct vec *v, const void *value);

void *vec_get(struct vec *v, size_t at);

struct slice vec_slice(struct vec *v, size_t from, size_t to);

struct slice vec_slice_all(struct vec *v);

void *vec_pop(struct vec *v);

void vec_set(struct vec *v, void *value, size_t at);

// SAFETY: v should be valid and 0 <= at < v->len
void vec_remove(struct vec *v, size_t at);

struct iter vec_iter(struct vec *v);

void vec_free(struct vec *v);

#endif // VEC_LIBRARY_H
