#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>

#define LOG_DEBUG

enum log_level { DEBUG = 0, INFO, WARNING, ERROR };

extern enum log_level this_log_level;
extern FILE *log_fp;

#define LOG_DEST_NONE 0
#define LOG_DEST_STDERR 1
#define LOG_DEST_FILE 2
#define LOG_DEST_BOTH (LOG_DEST_STDERR | LOG_DEST_FILE)

extern int log_destination;

void set_log_destination(int dest);

static const char *log_level_str[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

void set_log_level(enum log_level level);
int open_log_file(const char *path, const char *mode);
void set_log_file(FILE *fp);
void close_log_file(void);
void init_log(void);

#ifdef LOG_DEBUG
#define log_it(fmt, level_str, ...)                                            \
  do {                                                                         \
    if ((log_destination & LOG_DEST_FILE) && log_fp)                           \
      fprintf(log_fp, "[%s:%u] %s: " fmt "\n", __FILE__, __LINE__, level_str,  \
              ##__VA_ARGS__);                                                  \
    if (log_destination & LOG_DEST_STDERR)                                     \
      fprintf(stderr, "[%s:%u] %s: " fmt "\n", __FILE__, __LINE__, level_str,  \
              ##__VA_ARGS__);                                                  \
  } while (0)
#else
#define log_it(fmt, level_str, ...)                                            \
  do {                                                                         \
    if ((log_destination & LOG_DEST_FILE) && log_fp)                           \
      fprintf(log_fp, "%s: " fmt "\n", level_str, ##__VA_ARGS__);              \
    if (log_destination & LOG_DEST_STDERR)                                     \
      fprintf(stderr, "%s: " fmt "\n", level_str, ##__VA_ARGS__);              \
  } while (0)
#endif

#define log(level, fmt, ...)                                                   \
  do {                                                                         \
    if (level < this_log_level)                                                \
      break;                                                                   \
    log_it(fmt, log_level_str[level], ##__VA_ARGS__);                          \
  } while (0)

#endif
