#include "vec.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct vec *vec_create(size_t elem_size) {
  struct vec *v = malloc(sizeof(struct vec));
  v->data = NULL;
  v->cap = 0;
  v->len = 0;
  v->elem_size = elem_size;
  return v;
}

struct vec *vec_from_array(void *arr, size_t len, size_t elem_size) {
  struct vec *v = vec_create(elem_size);
  v->data = malloc(len * elem_size);
  memcpy(v->data, arr, len * elem_size);
  v->len = len;
  v->cap = len;
  return v;
}

void vec_realloc(struct vec *v) {
  if (v->cap == 0) {
    v->data = malloc(v->elem_size);
    v->cap = 1;
  } else {
    v->cap *= 2;
    v->data = realloc(v->data, v->cap * v->elem_size);
  }
}

void vec_push(struct vec *v, void *value) {
  if (v->cap <= v->len) {
    vec_realloc(v);
  }

  memcpy(v->data + v->len * v->elem_size, value, v->elem_size);
  v->len += 1;
}

void *vec_get(struct vec *v, size_t at) {
  if ((!v) || at >= v->len || (!v->data)) {
    return NULL;
  }

  return v->data + (at * v->elem_size);
}

struct slice vec_slice(struct vec *v, size_t from, size_t to) {
  struct slice s = { .data = v->data + from * v->elem_size, .len = to - from, .elem_size = v->elem_size };
  return s;
}

struct slice vec_slice_all(struct vec *v) {
  return vec_slice(v, 0, v->len);
}

void *vec_pop(struct vec *v) {
  if ((!v) || (!v->len)) {
    return NULL;
  }

  void *last = malloc(v->elem_size);
  memcpy(last, vec_get(v, v->len - 1), v->elem_size);
  v->len -= 1;
  return last;
}

void vec_set(struct vec *v, void *value, size_t at) {
  if ((!v) || at >= v->len || (!v->data)) {
    return;
  }

  memcpy(vec_get(v, at), value, v->elem_size);
}

void vec_free(struct vec *v) { free(v->data); }

void *slice_get(struct slice *s, size_t at) {
  return s->data + (at * s->elem_size);
}