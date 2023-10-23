#include <stdbool.h>
#include <stddef.h>

#define ITER_GET(it, T) (const T *)((it).ptr)

#define ITER_GET_VAL(it, T) *ITER_GET(it, T)

struct iter {
  const void *ptr;
  const void *end;
  size_t elem_size;
};

typedef struct iter iter_t;

// SAFETY: should not be called after the end is reached.
const void *iter_next(struct iter *it);

bool iter_is_end(const struct iter *it);

struct iter_mut {
  void *ptr;
  void *end;
  size_t elem_size;
};