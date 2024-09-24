#ifndef LOGS_H
#define LOGS_H

#include <stdio.h>
#include <time.h>

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERROR 3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#define LOG_COLOR_RESET   "\x1b[0m"
#define LOG_COLOR_DEBUG   "\x1b[34m" // Blue
#define LOG_COLOR_INFO    "\x1b[32m" // Green
#define LOG_COLOR_WARN    "\x1b[33m" // Yellow
#define LOG_COLOR_ERROR   "\x1b[31m" // Red

#define LOG(level, color, format, ...) \
    do { \
        if (level >= LOG_LEVEL) { \
            time_t rawtime; \
            struct tm *timeinfo; \
            char buffer[80]; \
            time(&rawtime); \
            timeinfo = localtime(&rawtime); \
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); \
            fprintf(stderr, "%s[%s] %s:%d: " format "%s\n", color, buffer, __FILE__, __LINE__, ##__VA_ARGS__, LOG_COLOR_RESET); \
        } \
    } while (0)

#define LOG_DEBUG(format, ...) LOG(LOG_LEVEL_DEBUG, LOG_COLOR_DEBUG, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)  LOG(LOG_LEVEL_INFO, LOG_COLOR_INFO, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  LOG(LOG_LEVEL_WARN, LOG_COLOR_WARN, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) LOG(LOG_LEVEL_ERROR, LOG_COLOR_ERROR, format, ##__VA_ARGS__)

#endif // LOGS_H
