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

struct biguint biguint_zero(void);

struct biguint biguint_one(void);

struct biguint biguint_from(uint32_t n);

struct biguint biguint_parse(const char *s);

struct biguint biguint_add(const struct biguint *self,
                           const struct biguint *rhs);

// Computes `self + rhs` and stores result in `self`
void biguint_add_assign(struct biguint *self, const struct biguint *rhs);

struct biguint biguint_sub(const struct biguint *self, const struct biguint *rhs);

bool biguint_sub_assign(struct biguint *self, const struct biguint *rhs);

struct biguint biguint_mul(const struct biguint *self,
                           const struct biguint *rhs);

void biguint_mul_assign(struct biguint *self, const struct biguint *rhs);

struct biguint biguint_div(struct biguint *self, const struct biguint *rhs);

bool biguint_eq(const struct biguint *self, const struct biguint *rhs);

void biguint_free(struct biguint *n);

#endif
