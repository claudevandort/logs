#include "logs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define MAX_LOG_LENGTH 1024
#define LOG_LEVEL_WIDTH 7

static uint32_t active_log_flags = 0;
static const char* log_file_path = NULL;

static const char* LOG_LEVEL_NAMES[] = {"DEBUG", "INFO", "WARN", "ERROR"};
static const char* LOG_LEVEL_COLORS[] = {
    "\x1b[34m",  // Blue for DEBUG
    "\x1b[32m",  // Green for INFO
    "\x1b[33m",  // Yellow for WARN
    "\x1b[31m"   // Red for ERROR
};

int logs_init(uint32_t flags, const char* file_path) {
    active_log_flags = flags;

    if (!(flags & LOG_OUTPUT_FILE)) {
        return 1;  // No file output requested, initialization successful
    }

    if (!file_path) {
        fprintf(stderr, "Error: File path is required when LOG_OUTPUT_FILE is set\n");
        return 0;
    }

    log_file_path = strdup(file_path);
    if (!log_file_path) {
        fprintf(stderr, "Error: Unable to allocate memory for file path\n");
        return 0;
    }

    // Test if we can open the log file
    FILE* test_file = fopen(log_file_path, "a");
    if (!test_file) {
        fprintf(stderr, "Error: Unable to open log file %s\n", log_file_path);
        free((void*)log_file_path);
        log_file_path = NULL;
        return 0;
    }
    fclose(test_file);

    return 1;  // Initialization successful
}

void logs_close(void) {
    if (log_file_path) {
        free((void*)log_file_path);
        log_file_path = NULL;
    }
    active_log_flags = 0;
}

static void append_log_level(char* buffer, size_t buffer_size, int level) {
    snprintf(buffer, buffer_size, "[%-5s] ", LOG_LEVEL_NAMES[level]);
}

static void append_timestamp(char* buffer, size_t buffer_size) {
    time_t raw_time;
    struct tm *time_info;
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    strftime(buffer, buffer_size, "[%Y-%m-%d %H:%M:%S] ", time_info);
}

static void append_location(char* buffer, size_t buffer_size, const char* file, int line) {
    snprintf(buffer, buffer_size, "%s:%d: ", file, line);
}

static void write_to_file(const char* message) {
    FILE* log_file = fopen(log_file_path, "a");
    if (log_file) {
        fprintf(log_file, "%s\n", message);
        fclose(log_file);
    }
}

static void log_message(int level, const char* file, int line, const char* format, va_list args) {
    if (level < LOG_LEVEL) return;

    char log_entry[MAX_LOG_LENGTH] = {0};
    size_t remaining_space = MAX_LOG_LENGTH;
    char* current_position = log_entry;

    if (active_log_flags & LOG_FORMAT_LEVEL) {
        append_log_level(current_position, remaining_space, level);
        size_t written = strlen(current_position);
        current_position += written;
        remaining_space -= written;
    }

    if (active_log_flags & LOG_FORMAT_TIMESTAMP) {
        append_timestamp(current_position, remaining_space);
        size_t written = strlen(current_position);
        current_position += written;
        remaining_space -= written;
    }

    if (active_log_flags & LOG_FORMAT_LOCATION) {
        append_location(current_position, remaining_space, file, line);
        size_t written = strlen(current_position);
        current_position += written;
        remaining_space -= written;
    }

    vsnprintf(current_position, remaining_space, format, args);

    if (active_log_flags & LOG_OUTPUT_STDOUT) {
        fprintf(stdout, "%s%s%s\n", LOG_LEVEL_COLORS[level], log_entry, "\x1b[0m");
    }
    
    if ((active_log_flags & LOG_OUTPUT_FILE) && log_file_path) {
        write_to_file(log_entry);
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
