#include <stdio.h>

#include "../dependency/map-macro/map.h"

#define def_fmt(buf, val) _Generic((val), \
    int: fmt_int, \
    float: fmt_float, \
    double: fmt_double, \
    char*: fmt_str \
)((buf), (val))

#define __stdout_buf(val) def_fmt(stdout, val) 

#define print(...) MAP_LIST(__stdout_buf, __VA_ARGS__)

#define tail(t, ...) __VA_ARGS__, t

#define println(...) print(tail("\n", __VA_ARGS__))

#define quote(x) "\"", x, "\""

#define __sep_space(x) " ", x

#define sep_space(x, ...)  x, MAP_LIST(__sep_space, __VA_ARGS__)

#define __sep_comma(x) ",", x

#define sep_comma(x, ...) x, MAP_LIST(__sep_comma, __VA_ARGS__)

#define __list_impl(x) ", ", x

#define list(x, ...) x, MAP_LIST(__list_impl, __VA_ARGS__)

void fmt_int(FILE *buf, int val);

void fmt_float(FILE *buf, float val);

void fmt_double(FILE *buf, double val);

void fmt_str(FILE *buf, const char *val);
