#ifndef CUTILS_IO_IO_H
#define CUTILS_IO_IO_H

#include "../string/str.h"

#include <stdio.h>

struct reader {
    FILE *f;
};

struct reader reader_new(FILE *f);
struct string reader_read_to_end(struct reader *r);
struct string reader_read_until(struct reader *r, char until);
struct string reader_read_line(struct reader *r);
struct string reader_read_n(struct reader *r, size_t n);

#endif
