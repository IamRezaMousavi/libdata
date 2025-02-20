#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <time.h>

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO  1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_ERROR 3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

static FILE *log_file = NULL;

static inline void log_set_file(const char *filename) {
    if (filename)
        log_file = fopen(filename, "a");
}

static inline void log_close() {
    if (log_file)
        fclose(log_file);
}

#define LOG_TIME(buffer)                                    \
    do {                                                    \
        time_t     t       = time(NULL);                    \
        struct tm *tm_info = localtime(&t);                 \
        strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", tm_info); \
    } while (0)

#define LOG_PRINT(level, fmt, ...)                                                                             \
    do {                                                                                                       \
        char tstr[20];                                                                                         \
        LOG_TIME(tstr);                                                                                        \
        fprintf(stdout, "[%s] [%s] (%s:%d): " fmt "\n", tstr, level, __FILE__, __LINE__, ##__VA_ARGS__);       \
        if (log_file) {                                                                                        \
            fprintf(log_file, "[%s] [%s] (%s:%d): " fmt "\n", tstr, level, __FILE__, __LINE__, ##__VA_ARGS__); \
            fflush(log_file);                                                                                  \
        }                                                                                                      \
    } while (0)

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_DEBUG(fmt, ...) LOG_PRINT("DEBUG", fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...) \
    do {                    \
    } while (0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(fmt, ...) LOG_PRINT("INFO", fmt, ##__VA_ARGS__)
#else
#define LOG_INFO(fmt, ...) \
    do {                   \
    } while (0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LOG_WARN(fmt, ...) LOG_PRINT("WARN", fmt, ##__VA_ARGS__)
#else
#define LOG_WARN(fmt, ...) \
    do {                   \
    } while (0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_ERROR(fmt, ...) LOG_PRINT("ERROR", fmt, ##__VA_ARGS__)
#else
#define LOG_ERROR(fmt, ...) \
    do {                    \
    } while (0)
#endif

#endif /* __LOGGER_H__ */
