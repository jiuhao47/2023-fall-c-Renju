#include "../inc/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

enum log_level this_log_level = DEBUG;
FILE *log_fp = NULL;
int log_destination = LOG_DEST_STDERR;

void set_log_level(enum log_level level) { this_log_level = level; }

void set_log_destination(int dest) { log_destination = dest; }

int open_log_file(const char *path, const char *mode) {
  if (!path)
    return -1;
  FILE *f = fopen(path, mode);
  if (!f)
    return -1;
  if (log_fp && log_fp != stderr)
    fclose(log_fp);
  log_fp = f;
  if (log_destination == LOG_DEST_STDERR)
    log_destination = LOG_DEST_FILE;
  return 0;
}

void set_log_file(FILE *fp) {
  if (log_fp && log_fp != stderr && log_fp != fp)
    fclose(log_fp);
  log_fp = fp;
}

void close_log_file(void) {
  if (log_fp && log_fp != stderr) {
    fclose(log_fp);
    log_fp = NULL;
  }
}

void init_log(void) {
  char *env_file = getenv("LOG_FILE");
  char *env_dest = getenv("LOG_DEST");
  char *env_level = getenv("LOG_LEVEL");

  if (env_file) {
    if (open_log_file(env_file, "a") != 0) {
    }
  }

  if (env_dest) {
    if (strcasecmp(env_dest, "none") == 0)
      set_log_destination(LOG_DEST_NONE);
    else if (strcasecmp(env_dest, "stderr") == 0 ||
             strcasecmp(env_dest, "std") == 0)
      set_log_destination(LOG_DEST_STDERR);
    else if (strcasecmp(env_dest, "file") == 0)
      set_log_destination(LOG_DEST_FILE);
    else if (strcasecmp(env_dest, "both") == 0)
      set_log_destination(LOG_DEST_BOTH);
  }

  if (env_level) {
    if (strcasecmp(env_level, "DEBUG") == 0)
      set_log_level(DEBUG);
    else if (strcasecmp(env_level, "INFO") == 0)
      set_log_level(INFO);
    else if (strcasecmp(env_level, "WARNING") == 0)
      set_log_level(WARNING);
    else if (strcasecmp(env_level, "ERROR") == 0)
      set_log_level(ERROR);
    else {
      int n = atoi(env_level);
      if (n >= DEBUG && n <= ERROR)
        set_log_level((enum log_level)n);
    }
  }
}
