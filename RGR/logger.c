#include <stdio.h>
#include <time.h>
#include "logger.h"

static const char *LOG_FILE = "log.txt";

static void write_log(const char *level, const char *message){
    FILE *f = fopen(LOG_FILE, "a");
    if(!f) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(f,"[%s] %02d:%02d:%02d : %s\n",
        level,
        t->tm_hour,
        t->tm_min,
        t->tm_sec,
        message);

    fclose(f);
}

void log_info(const char *message){
    write_log("INFO", message);
}

void log_warning(const char *message){
    write_log("WARNING", message);
}

void log_error(const char *message){
    write_log("ERROR", message);
}