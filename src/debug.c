#include "debug.h"

void debug_log(const char *file, const char *func, int line, const char *fmt,
               ...) {
    va_list args;
    fprintf(stderr, "[%s:%d]" BLUE "[%s]" RESET " ", file, line, func);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}
