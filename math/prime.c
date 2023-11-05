#include "prime.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct vec primes(int n) {
  struct vec prime = vec_create(sizeof(int));

  if (n <= 1) {
    return prime;
  }

  bool *vis = calloc(n, sizeof(bool));
  vis[0] = true;

  for (int i = 2; i <= n; ++i) {
    if (!vis[i - 1]) {
      vec_push(&prime, &i);
    }
    for (size_t j = 0; j < prime.len; j += 1) {
      int p = *(int *)vec_get(&prime, j);
      if (i > n / p) {
        break;
      }
      vis[i * p - 1] = true;
      if (i % p == 0) {
        break;
      }
    }
  }

  return prime;
}