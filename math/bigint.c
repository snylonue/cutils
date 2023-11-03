#include "bigint.h"

#include "../vec/vec.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct biguint biguint_create(struct vec nums) {
  struct biguint n = {.nums = nums};
  return n;
}

struct biguint biguint_from(uint32_t n) {
  struct vec nums = vec_from_array(&n, 1, sizeof(uint32_t));
  return biguint_create(nums);
}

struct biguint biguint_zero() { return biguint_from(0); }

struct biguint biguint_one() { return biguint_from(1); }

uint32_t add_with_carry(uint32_t *l, uint32_t r, uint32_t carry) {
  uint64_t sum = (uint64_t)*l + (uint64_t)r + (uint64_t)carry;
  *l = (uint32_t)sum;
  return sum >> 32;
}

// Caller must guarantee `lhs.len >= rhs.len`
// Returns carry
uint32_t add_nums(struct slice lhs, struct slice rhs) {
  uint32_t carry = 0;
  for (size_t i = 0; i < rhs.len; ++i) {
    uint32_t *l = slice_get(&lhs, i);
    const uint32_t r = *(uint32_t *)slice_get(&rhs, i);
    carry = add_with_carry(l, r, carry);
  }

  for (size_t i = rhs.len; i < lhs.len; ++i) {
    carry = add_with_carry(slice_get(&lhs, i), 0, carry);
    if (carry == 0) {
      break;
    }
  }

  return carry;
}

void biguint_add_assign(struct biguint *self, struct biguint *rhs) {
  size_t self_len = self->nums.len;
  size_t rhs_len = rhs->nums.len;
  uint32_t carry;
  if (self_len >= rhs_len) {
    carry = add_nums(vec_slice_all(&self->nums), vec_slice_all(&rhs->nums));
  } else {
    carry = add_nums(vec_slice_all(&self->nums),
                     vec_slice(&rhs->nums, 0, self_len));
    vec_extend(&self->nums, vec_get(&rhs->nums, self_len), rhs_len - self_len);
    struct biguint left = biguint_from(carry);
    carry = add_nums(vec_slice(&self->nums, self_len, self->nums.len),
                     vec_slice_all(&left.nums));
    biguint_free(&left);
  }
  if (carry != 0) {
    vec_push(&self->nums, &carry);
  }
}

bool biguint_eq(struct biguint *self, struct biguint *rhs) {
  if (self->nums.len != rhs->nums.len) {
    return false;
  }
  for (size_t i = 0; i < self->nums.len; ++i) {
    if (*(uint32_t *)vec_get(&self->nums, i) !=
        *(uint32_t *)vec_get(&rhs->nums, i)) {
      return false;
    }
  }
  return true;
}

void biguint_free(struct biguint *n) { vec_free(&n->nums); }