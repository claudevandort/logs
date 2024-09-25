#include "logs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define LOG_LEVEL_WIDTH 7

static uint32_t log_flags = 0;
static const char* log_file_path = NULL;

static const char* level_strings[] = {"DEBUG", "INFO", "WARN", "ERROR"};
static const char* level_colors[] = {"\x1b[34m", "\x1b[32m", "\x1b[33m", "\x1b[31m"};

int logs_init(uint32_t flags, const char* file_path) {
    log_flags = flags;

    if (flags & LOG_OUTPUT_FILE) {
        if (!file_path) {
            fprintf(stderr, "Error: File path is required when LOG_OUTPUT_FILE is set\n");
            return 0;
        }
        log_file_path = strdup(file_path);
        if (!log_file_path) {
            fprintf(stderr, "Error: Unable to allocate memory for file path\n");
            return 0;
        }
        
        FILE* test_file = fopen(log_file_path, "a");
        if (!test_file) {
            fprintf(stderr, "Error: Unable to open log file %s\n", log_file_path);
            free((void*)log_file_path);
            log_file_path = NULL;
            return 0;
        }
        fclose(test_file);
    }

    return 1;
}

static void log_message(int level, const char* file, int line, const char* format, va_list args) {
    if (level < LOG_LEVEL) return;

    char buffer[MAX_LINE_LENGTH] = {0};
    int offset = 0;

    if (log_flags & LOG_FORMAT_LEVEL) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "[%-5s] ", level_strings[level]);
    }

    if (log_flags & LOG_FORMAT_TIMESTAMP) {
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        offset += strftime(buffer + offset, sizeof(buffer) - offset, "[%Y-%m-%d %H:%M:%S] ", timeinfo);
    }

    if (log_flags & LOG_FORMAT_LOCATION) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%s:%d: ", file, line);
    }

    vsnprintf(buffer + offset, sizeof(buffer) - offset, format, args);

    if (log_flags & LOG_OUTPUT_STDOUT) {
        fprintf(stdout, "%s%s%s\n", level_colors[level], buffer, "\x1b[0m");
    }
    
    if ((log_flags & LOG_OUTPUT_FILE) && log_file_path) {
        FILE* log_file = fopen(log_file_path, "a");
        if (log_file) {
            fprintf(log_file, "%s\n", buffer);
            fclose(log_file);
        }
    }
}

void log_debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, args);
    va_end(args);
}

void log_info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_LEVEL_INFO, __FILE__, __LINE__, format, args);
    va_end(args);
}

void log_warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_LEVEL_WARN, __FILE__, __LINE__, format, args);
    va_end(args);
}

void log_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_LEVEL_ERROR, __FILE__, __LINE__, format, args);
    va_end(args);
}
