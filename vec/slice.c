#include "slice.h"

#include <stdint.h>

const void *slice_get(const struct slice *s, size_t at) {
  return (void*)((uint8_t *)s->data + (at * s->elem_size));
}

void *slice_get_mut(struct slice_mut *s, size_t at) {
  return (void*)((uint8_t *)s->data + (at * s->elem_size));
}
