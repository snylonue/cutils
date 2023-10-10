#include "bitset.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct bitset bitset_create(size_t len) {
  size_t size = ceil((double)len / BITSET_CONTAINER_SIZE);
  container_t *container = calloc(size, BITSET_CONTAINER_SIZE);

  struct bitset b = {.container = container, .len = len};

  return b;
}

bool bitset_get(struct bitset *b, size_t at) {
  return b->container[at / BITSET_CONTAINER_SIZE] &
         (1 << (at % BITSET_CONTAINER_SIZE));
}

void bitset_set(struct bitset *b, size_t at, bool value) {
  container_t location = ((1 << (at % BITSET_CONTAINER_SIZE)));
  if (value) {
    b->container[at / BITSET_CONTAINER_SIZE] |= location;
  } else {
    b->container[at / BITSET_CONTAINER_SIZE] &= ~location;
  }
}