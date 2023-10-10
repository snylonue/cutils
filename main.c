// Hello world! Cplayground is an online sandbox that makes it easy to try out
// code.

#include "bitset/bitset.h"
#include "math/prime.h"
#include "vec/vec.h"


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct bitset b = bitset_create(10);
  bitset_set(&b, 3, true);
  bitset_set(&b, 4, true);
  bitset_set(&b, 3, false);

  printf("%d %d\n", bitset_get(&b, 3), bitset_get(&b, 4));

  struct vec *v = primes(121);

  for (size_t i = 0; i < v->len; ++i) {
    printf("%d ", *(int *)vec_get(v, i));
  }

  return 0;
}