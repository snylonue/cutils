#include "iter.h"
#include <stdint.h>

const void *iter_next(struct iter *it) {
  const void *cur = it->ptr;
  it->ptr = (uint8_t *)it->ptr + it->elem_size;

  return cur;
}

bool iter_is_end(const struct iter *it) { return it->ptr == it->end; }
