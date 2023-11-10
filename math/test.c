#include "bigint.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void test_add(const char *a, const char *b, const char *c) {
  struct biguint b1 = biguint_parse(a), b2 = biguint_parse(b),
                 expected = biguint_parse(c);

  assert(biguint_eq((struct biguint[]){biguint_add(&b1, &b2)}, &expected));
}

void test_mul(const char *a, const char *b, const char *c) {
  struct biguint b1 = biguint_parse(a), b2 = biguint_parse(b),
                 b3 = biguint_parse(c);

  struct biguint res = biguint_mul(&b1, &b2);

  assert(biguint_eq(&res, &b3));
}

void test_sub(const char *a, const char *b, const char *c) {
  struct biguint b1 = biguint_parse(a), b2 = biguint_parse(b),
                 expected = biguint_parse(c);

  assert(biguint_eq((struct biguint[]){biguint_sub(&b1, &b2)}, &expected));
}

int main() {
  test_add("0", "0", "0");
  test_add("114514", "1919810", "2034324");
  test_add("6656973275315950491103044695023687744140625",
           "6800797967675697630363274958942030954497024",
           "13457771242991648121466319653965718698637649");

  test_mul("114514", "1919810", "219845122340");

  test_sub("1928376598709876567", "129384769", "1928376598580491798");

  return 0;
}