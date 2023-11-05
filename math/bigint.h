#ifndef CUTILS_MATH_BIGINT_H
#define CUTILS_MATH_BIGINT_H

#include "../vec/vec.h"

#include <stdbool.h>
#include <stdint.h>

// Inspired by https://docs.rs/num-bigint
struct biguint {
  struct vec nums; // vec<uint32_t>
};

struct biguint biguint_create(struct vec nums);

struct biguint biguint_zero();

struct biguint biguint_one();

struct biguint biguint_from(uint32_t n);

// Computes `self + rhs` and stores result in `self`
void biguint_add_assign(struct biguint *self, const struct biguint *rhs);

void biguint_mul_assign(struct biguint *self, const struct biguint *rhs);

bool biguint_eq(const struct biguint *self, const struct biguint *rhs);

void biguint_free(struct biguint *n);

#endif