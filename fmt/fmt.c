#include <stdio.h>

void fmt_int(FILE *buf, int val) {
    fprintf(buf, "%d", val);
}

void fmt_float(FILE *buf, float val) {
    fprintf(buf, "%f", val);
}

void fmt_double(FILE *buf, double val) {
    fprintf(buf, "%f", val);
}

void fmt_str(FILE *buf, const char *val) {
    fprintf(buf, "%s", val);
}