#ifndef LOGS_H
#define LOGS_H

#include <stdint.h>

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO  1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_ERROR 3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#define LOG_OUTPUT_STDOUT 0x0001
#define LOG_OUTPUT_FILE   0x0002

#define LOG_FORMAT_LEVEL     0x0004
#define LOG_FORMAT_TIMESTAMP 0x0008
#define LOG_FORMAT_LOCATION  0x0010

int logs_init(uint32_t flags, const char* file_path);

void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_warn(const char* format, ...);
void log_error(const char* format, ...);

#endif // LOGS_H
