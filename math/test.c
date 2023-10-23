#include "bigint.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

const uint32_t N1 = -1;
const uint32_t N2 = -2;

struct biguint new(uint32_t *a, size_t s) {
  struct vec v = vec_from_array(a, s, sizeof(uint32_t));
  return biguint_create(v);
}

void test(struct biguint a, struct biguint b, struct biguint expected) {
  printf("%s\n", biguint_to_string(&expected));
  biguint_add_assign(&a, &b);
  assert(biguint_eq(&a, &expected));
}

int main() {
  uint32_t a1[] = {0}, b1[] = {0}, e1[] = {0};
  test(new (a1, 1), new (b1, 1), new (e1, 1));
  uint32_t a2[] = {1}, b2[] = {1, 1}, e2[] = {2, 1};
  test(new (a2, 1), new (b2, 2), new (e2, 2));
  uint32_t a3[] = {9, 9}, b3[] = {9, 9}, e3[] = {8, 9, 1};
  test(new (a3, 2), new (b3, 2), new (e3, 3));
  uint32_t a4[] = {4, 1, 5, 4, 1, 1}, b4[] = {0, 1, 8, 9, 1, 9, 1}, e4[] = {4, 2, 3, 4, 3, 0, 2};
  test(new (a4, 6), new (b4, 7), new (e4, 7));
  uint32_t a5[] = {5, 2, 6, 0, 4, 1, 4, 4, 7, 7, 8, 6, 3, 2, 0, 5, 9, 6, 4, 4, 0, 3, 0, 1, 1, 9, 4, 0, 5, 9, 5, 1, 3, 5, 7, 2, 3, 7, 9, 6, 5, 6, 6}, b5[] = {4, 2, 0, 7, 9, 4, 4, 5, 9, 0, 3, 0, 2, 4, 9, 8, 5, 9, 4, 7, 2, 3, 6, 3, 0, 3, 6, 7, 9, 6, 5, 7, 6, 7, 6, 9, 7, 9, 7, 0, 0, 8, 6}, e5[] = {9, 4, 6, 7, 3, 6, 8, 9, 6, 8, 1, 7, 5, 6, 9, 3, 5, 6, 9, 1, 3, 6, 6, 4, 1, 2, 1, 8, 4, 6, 1, 9, 9, 2, 4, 2, 1, 7, 7, 7, 5, 4, 3, 1};
  test(new (a5, 43), new (b5, 43), new (e5, 44));
  return 0;
}