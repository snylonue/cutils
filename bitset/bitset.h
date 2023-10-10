#ifndef CUTILS_BITSET_BITSET_H
#define CUTILS_BITSET_BITSET_H

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t container_t;

#define BITSET_CONTAINER_SIZE sizeof(container_t)

struct bitset {
  container_t *container;
  size_t len;
};

struct bitset bitset_create(size_t len);

bool bitset_get(struct bitset *b, size_t at);

void bitset_set(struct bitset *b, size_t at, bool value);

#endif