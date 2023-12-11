#ifndef CUTILS_STR_H
#define CUTILS_STR_H

#include <stdbool.h>
#include <stddef.h>

// SAFETY: All fields should not be modified directly.
struct string {
  char *data;
  size_t len;
  size_t cap;
};

struct string string_new(void);
void string_reserve(struct string *s, size_t size);
struct string string_from_c_str(const char *str);
struct string_view string_into_view(const struct string *s);
struct string_view string_slice(const struct string *s, size_t l, size_t r);
struct split string_split(const struct string *s, char delim);
void string_free(struct string *s);

struct string_view {
  const char *data;
  size_t len;
};

struct string_view string_view_slice(struct string_view view, size_t l, size_t r);
struct split string_view_split(struct string_view view, char delim);

struct split {
  struct string_view view;
  size_t pos;
  char delim;
};

struct string_view split_next(struct split *sp);
bool split_is_end(struct split *sp);

#endif
