#ifndef LOGGER_H
#define LOGGER_H
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdio.h>
#include <stdbool.h>
 
#ifndef nullptr
#define nullptr NULL
#endif
 
typedef struct st_logger {
 
    bool opened;
 
    FILE* ofp;
 
    struct st_logger* (*init)(const char* initializ_file);
 
    int (*logger)(const char* format, ...);
 
    void (*close)(void);
 
}Logger;
 
Logger *getLogger(void);
 
Logger* loggerInit(const char* initializ_file);
 
int loggerOut(const char* format, ...);
 
void loggerClose(void);
 
#ifdef __cplusplus
}
#endif
 
#endif // LOGGER_H
