#include "logger.h"
 
#include <stdarg.h>

Logger *getLogger(void)
{
    static Logger _instance;

    if ((void*)(_instance.init) == nullptr) {
        _instance.init = &loggerInit;
        _instance.logger = &loggerOut;
        _instance.close = &loggerClose;
    }
 
    return &_instance;
}
 
Logger *loggerInit(const char* initializ_file)
{
    Logger* logger = getLogger();
 
    if (!logger->opened) {
        logger->ofp = fopen(initializ_file, "w");
        logger->opened = (logger->ofp != nullptr);
    }
 
    return logger;
}
 
int loggerOut(const char *format, ...)
{
    FILE* fp = getLogger()->ofp;
 
    if (!fp) {
        return -1;
    }
 
    va_list list;
    va_start(list, format);
 
    int io;
 
    io = vfprintf(fp, format, list);

    fflush(fp);
    va_end(list);
 
    return io;
}
 
void loggerClose(void)
{
    if (getLogger()->opened) {
        fclose(getLogger()->ofp);
        getLogger()->ofp = nullptr;
        getLogger()->opened = false;
    }
}
