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
uint32_t add_nums(struct slice_mut lhs, const struct slice rhs) {
  uint32_t carry = 0;
  for (size_t i = 0; i < rhs.len; ++i) {
    uint32_t *l = slice_get_mut(&lhs, i);
    const uint32_t r = *(uint32_t *)slice_get(&rhs, i);
    carry = add_with_carry(l, r, carry);
  }

  for (size_t i = rhs.len; i < lhs.len; ++i) {
    carry = add_with_carry(slice_get_mut(&lhs, i), 0, carry);
    if (carry == 0) {
      break;
    }
  }

  return carry;
}

struct biguint biguint_parse(const char *s) {
  struct vec digits = vec_create(sizeof(uint32_t));
  while (*s != '\0') {
    vec_push(&digits, (uint32_t[]){(uint32_t)(*s - '0')});
    ++s;
  }

  uint32_t base = 10000, radix = 10;
  size_t power = 4;
  size_t r = digits.len % power;
  size_t i = (r == 0) ? power : r;
  
  struct slice head = vec_slice(&digits, 0, i), tail = vec_slice(&digits, i, digits.len);

  struct vec nums = vec_create(sizeof(uint32_t));
  uint32_t first = 0;
  for (size_t j = 0; j < head.len; ++j) {
    first = first * radix + *(uint32_t*)slice_get(&head, j);
  }
  vec_push(&nums, &first);

  for (size_t j = 0; j < tail.len; j += power) {
    if (*(uint32_t*)vec_last(&nums) != 0) {
      vec_push(&nums, (uint32_t[]){0});
    }

    uint64_t carry = 0;
    for (size_t k = 0; k < nums.len; ++k) {
      uint32_t *d = vec_get_mut(&nums, k);
      carry += (uint64_t)*d * (uint64_t)base;
      *d = (uint32_t)carry;
      carry >>= 32;
    }

    uint32_t n = 0;
    for (size_t k = 0; k < power; ++k) {
      n = n * radix + *(uint32_t*)slice_get(&tail, j + k);
    }

    add_nums(vec_slice_mut_all(&nums), (struct slice){.data=&n, .len=1, .elem_size=sizeof(uint32_t)});
  }

  while (nums.len > 0 && *(uint32_t*)vec_last(&nums) == 0) {
    vec_pop(&nums);
  }
  return biguint_create(nums);
}

void biguint_add_assign(struct biguint *self, const struct biguint *rhs) {
  size_t self_len = self->nums.len;
  size_t rhs_len = rhs->nums.len;
  uint32_t carry;
  if (self_len >= rhs_len) {
    carry = add_nums(vec_slice_mut_all(&self->nums), vec_slice_all(&rhs->nums));
  } else {
    carry = add_nums(vec_slice_mut_all(&self->nums),
                     vec_slice(&rhs->nums, 0, self_len));
    vec_extend(&self->nums, vec_get(&rhs->nums, self_len), rhs_len - self_len);
    struct biguint left = biguint_from(carry);
    carry = add_nums(vec_slice_mut(&self->nums, self_len, self->nums.len),
                     vec_slice_all(&left.nums));
    biguint_free(&left);
  }
  if (carry != 0) {
    vec_push(&self->nums, &carry);
  }
}

struct biguint biguint_add(const struct biguint *self, const struct biguint *rhs) {
  struct biguint cloned = biguint_zero();
  vec_extend_from(&cloned.nums, self->nums);
  
  biguint_add_assign(&cloned, rhs);
  return cloned;
}

uint32_t mul_with_carry(uint32_t *l, uint32_t r, uint32_t carry) {
  uint64_t mul = (uint64_t)(*l) * (uint64_t)r + (uint64_t)carry;
  *l = (uint32_t)mul;
  return mul >> 32;
}

// takes ownship of res
struct biguint mul_num(const struct slice lhs, uint32_t num, struct vec res) {
  uint32_t carry = 0;
  // vec_extend_slice(&res, lhs);
  for (size_t i = 0; i < lhs.len; ++i) {
    uint32_t val = *(uint32_t*)slice_get(&lhs, i);
    carry = mul_with_carry(&val, num, carry);
    vec_push(&res, &val);
  }

  if (carry) {
    vec_push(&res, &carry);
  }

  return biguint_create(res);
}

struct biguint biguint_mul(const struct biguint *self, const struct biguint *rhs) {
  struct biguint res = biguint_zero();

  for (size_t i = 0; i < rhs->nums.len; ++i) {
    struct vec v = vec_create(sizeof(uint32_t));
    for (size_t j = 0; j < i; ++j) {
      vec_push(&v, (int*){0});
    }
    struct biguint product = mul_num(vec_slice_all(&self->nums), *(uint32_t*)vec_get(&rhs->nums, i), v);
    biguint_add_assign(&res, &product);
    biguint_free(&product);
  }

  return res;
}

bool biguint_eq(const struct biguint *self, const struct biguint *rhs) {
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