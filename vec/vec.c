#include "vec.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct vec vec_create(size_t elem_size) {
  return (struct vec){.data = NULL, .cap = 0, .len = 0, .elem_size = elem_size};
}

struct vec vec_from_array(const void *arr, size_t len, size_t elem_size) {
  struct vec v = vec_create(elem_size);
  v.data = malloc(len * elem_size);
  memcpy(v.data, arr, len * elem_size);
  v.len = len;
  v.cap = len;
  return v;
}

void vec_realloc(struct vec *v) {
  if (v->cap == 0) {
    v->cap = 1;
  } else {
    v->cap <<= 1;
  }
  v->data = realloc(v->data, v->cap * v->elem_size);
}

void vec_push(struct vec *v, const void *value) {
  if (v->cap <= v->len) {
    vec_realloc(v);
  }

  memcpy(v->data + v->len * v->elem_size, value, v->elem_size);
  v->len += 1;
}

void vec_extend(struct vec *v, const void *arr, size_t len) {
  if (v->cap < v->len + len) {
    v->cap = v->len + len;
    v->data = realloc(v->data, v->cap * v->elem_size);
  }

  memcpy(v->data + v->len * v->elem_size, arr, len * v->elem_size);
  v->len += len;
}

void vec_extend_from(struct vec *v, struct vec other) {
  vec_extend(v, other.data, other.len);
}

void *vec_get(struct vec *v, size_t at) {
  return v->data + (at * v->elem_size);
}

struct slice vec_slice(struct vec *v, size_t from, size_t to) {
  struct slice s = {.data = v->data + from * v->elem_size,
                    .len = to - from,
                    .elem_size = v->elem_size};
  return s;
}

struct slice vec_slice_all(struct vec *v) { return vec_slice(v, 0, v->len); }

void *vec_pop(struct vec *v) {
  void *last = malloc(v->elem_size);
  memcpy(last, vec_get(v, v->len - 1), v->elem_size);
  v->len -= 1;
  return last;
}

void vec_set(struct vec *v, void *value, size_t at) {
  memcpy(vec_get(v, at), value, v->elem_size);
}

void vec_remove(struct vec *v, size_t at) {
  if (at + 1 == v->len) {
    v->len -= 1;
  } else {
    memmove(vec_get(v, at), vec_get(v, at + 1),
            (v->len - at - 1) * v->elem_size);
    v->len -= 1;
  }
}

struct iter vec_iter(struct vec *v) {
  return (struct iter){.ptr = v->data,
                       .end = v->data + v->len * v->elem_size,
                       .elem_size = v->elem_size};
}

void vec_free(struct vec *v) { free(v->data); }