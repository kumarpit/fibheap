#include "debug.h"

/**
 * @brief Debug print function that uses the kernel sys_print
 */
void debug_log(const char *file, const char *func, int line, const char *fmt,
               ...) {
    va_list args;
    fprintf(stderr,
            "[%s:%d]"
            "[" BLUE "%s" RESET
            "]"
            " ",
            file, line, func);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

/**
 * @brief Debug print function that uses the kernel sys_print with the option to
 * add indentation proportionally to the `level` parameter. Useful for
 * pretty-printing nested structures like tree.
 */
void debug_log_indent(const char *file, const char *func, int line, int level,
                      const char *fmt, ...) {
    va_list args;
    fprintf(stderr,
            "[%s:%d]"
            "[" BLUE "%s" RESET
            "]"
            " ",
            file, line, func);
    for (int i = 0; i < level; i++) {
        fprintf(stderr, "       ");  // 2 tabs per level
    }
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

/**
 * @brief Prints out the message with the location and error information
 * @note: do not use this function directly. Rather use the debug_log_error
 * macro
 */
void debug_log_error(const char *file, const char *func, int line,
                     const char *fmt, ...) {
    va_list args;
    fprintf(stderr,
            "[%s:%d]"
            "[" BLUE "%s" RESET
            "]"
            "[" RED "ERROR" RESET
            "]"
            " ",
            file, line, func);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}
