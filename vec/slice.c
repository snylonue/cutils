#include "slice.h"

void *slice_get(struct slice *s, size_t at) {
  return s->data + (at * s->elem_size);
}