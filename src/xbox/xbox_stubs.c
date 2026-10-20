#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


double strtod(const char* nptr, char** endptr) {
    const char* p = nptr;
    double result = 0.0;
    int neg = 0, any = 0;

    if (!p) { if (endptr) *endptr = (char*)nptr; return 0.0; }

    while (isspace((unsigned char)*p)) p++;
    if (*p == '-') { neg = 1; p++; }
    else if (*p == '+') { p++; }

    while (*p >= '0' && *p <= '9') {
        result = result * 10.0 + (*p - '0');
        p++; any = 1;
    }
    if (*p == '.') {
        double scale = 0.1;
        p++;
        while (*p >= '0' && *p <= '9') {
            result += (*p - '0') * scale;
            scale *= 0.1;
            p++; any = 1;
        }
    }
    if (!any) { if (endptr) *endptr = (char*)nptr; return 0.0; }

    if (*p == 'e' || *p == 'E') {
        const char* q = p + 1;
        int eneg = 0, e = 0, edig = 0;
        if (*q == '-') { eneg = 1; q++; }
        else if (*q == '+') { q++; }
        while (*q >= '0' && *q <= '9') {
            if (e < 10000) e = e * 10 + (*q - '0');
            q++; edig = 1;
        }
        if (edig) {
            double m = 1.0;
            while (e-- > 0) m *= 10.0;
            result = eneg ? result / m : result * m;
            p = q;
        }
    }

    if (endptr) *endptr = (char*)p;
    return neg ? -result : result;
}

float strtof(const char* nptr, char** endptr) {
    return (float)strtod(nptr, endptr);
}