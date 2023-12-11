#include "io.h"

#include <stdio.h>

struct reader reader_new(FILE *f) { return (struct reader){.f = f}; }

struct string reader_read_to_end(struct reader *r) {
    struct string s = string_new();

    int ch = getc(r->f);
    while (ch != EOF) {
        string_push(&s, ch); // NOLINT
        ch = getc(r->f);
    }

    return s;
}

struct string reader_read_until(struct reader *r, char until) {
    struct string s = string_new();

    int ch = getc(r->f);
    while (ch != EOF && ch != until) {
        string_push(&s, ch); // NOLINT
        ch = getc(r->f);
    }

    return s;
}

struct string reader_read_line(struct reader *r) {
    return reader_read_until(r, '\n');
}

struct string reader_read_n(struct reader *r, size_t n) {
    struct string s = string_new();
    string_reserve(&s, n);

    int ch = getc(r->f);
    size_t cnt = 0;
    while (ch != EOF && cnt < n) {
        string_push(&s, ch); // NOLINT
        ch = getc(r->f);
        cnt += 1;
    }

    return s;
}
