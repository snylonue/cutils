#include <stddef.h>

struct slice {
  void *data;
  size_t len;
  size_t elem_size;
};

void *slice_get(struct slice *s, size_t at);