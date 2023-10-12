#include "bigint.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

const uint32_t N1 = -1;
const uint32_t N2 = -2;

struct biguint new(uint32_t *a, size_t s) {
  struct vec *v = vec_from_array(a, s, sizeof(uint32_t));
  return biguint_create(v);
}

void test(struct biguint a, struct biguint b, struct biguint expected) {
  biguint_add_assign(&a, &b);
  assert(biguint_eq(&a, &expected));
}

int main() {
  uint32_t a1[] = {0}, b1[] = {0}, e1[] = {0};
  test(new (a1, 1), new (b1, 1), new (e1, 1));
  uint32_t a2[] = {1}, b2[] = {1, 1}, e2[] = {2, 1};
  test(new (a2, 1), new (b2, 2), new (e2, 2));
  uint32_t a3[] = {N1, N1}, b3[] = {N1, N1}, e3[] = {N2, N1, 1};
  test(new (a3, 2), new (b3, 2), new (e3, 3));
  return 0;
}