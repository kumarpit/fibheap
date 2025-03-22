/**
 * \file
 * \brief Debugging functions
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdarg.h>
#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
#define debug_printf(fmt, ...) \
    debug_log(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define debug_error(fmt, ...) \
    debug_log_error(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define debug_printf(fmt, ...) ((void)0)
#define debug_error(fmt, ...) ((void)0)
#endif

// ANSI colors
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define CYAN "\x1b[36m"

void debug_log(const char *file, const char *func, int line, const char *fmt,
               ...) __attribute__((format(printf, 4, 5)));

void debug_log_error(const char *file, const char *func, int line,
                     const char *fmt, ...)
    __attribute__((format(printf, 4, 5)));

#endif
