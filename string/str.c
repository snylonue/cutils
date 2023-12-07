#include "str.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct string string_new(void) {
    return (struct string) {0};
}

void string_reserve(struct string *s, size_t size) {
    if (size <= s->cap) {
        return;
    }

    s->data = realloc(s->data, size * sizeof(char));
    s->cap = size;
}

struct string string_from_c_str(const char *str) {
    struct string s = string_new();
    size_t len = strlen(str);
    
    string_reserve(&s, len);
    memcpy(s.data, str, len * sizeof(char));

    return s;
}

struct string_view string_into_view(const struct string *s) {
    return (struct string_view){
        .data = s->data,
        .len = s->len,
    };
}

struct string_view string_slice(const struct string *s, size_t l, size_t r) {
    return string_view_slice(string_into_view(s), l, r);
}

struct split string_split(const struct string *s, char delim) {
    return string_view_split(string_into_view(s), delim);
}

void string_free(struct string *s) {
    s->cap = 0;
    s->len = 0;
    free(s->data);
}

struct string_view string_view_slice(struct string_view view, size_t l, size_t r) {
    view.data += l;
    view.len = r - l;
    return view;
}

struct split string_view_split(struct string_view view, char delim) {
    return (struct split) {
        .view = view,
        .pos = 0,
        .delim = delim,
    };
}

struct string_view split_next(struct split *sp) {
    size_t pos = sp->pos;
    while (sp->pos < sp->view.len) {
        if (sp->view.data[pos] == sp->delim) {
            break;
        }
        sp->pos += 1;
    }
    return string_view_slice(sp->view, pos, sp->pos);
}

bool split_is_end(struct split *sp) {
    return sp->pos == sp->view.len;
}
