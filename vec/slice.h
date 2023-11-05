#include <stddef.h>

struct slice {
  const void *data;
  size_t len;
  size_t elem_size;
};

const void *slice_get(const struct slice *s, size_t at);

struct slice_mut {
  void *data;
  size_t len;
  size_t elem_size;
};

void *slice_get_mut(struct slice_mut *s, size_t at);