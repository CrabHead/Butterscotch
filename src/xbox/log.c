#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <hal/debug.h>
#include <xboxkrnl/xboxkrnl.h>

#include "log.h"

#define LOG_BUFFER_SIZE 1024
#define XLOG_SIZE 65536
char xlog_buf[XLOG_SIZE];
volatile unsigned xlog_pos = 0;

void xlog(const char* fmt, ...) {
    char tmp[256];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(tmp, sizeof tmp, fmt, ap);
    va_end(ap);
    if (n < 0) return;
    if (n > (int)sizeof tmp - 1) n = sizeof tmp - 1;
    for (int i = 0; i < n; i++)
        xlog_buf[(xlog_pos++) % XLOG_SIZE] = tmp[i];
}

void platformLog(const logType type, const char *format, va_list va) {
    const char* textPrefix = "";
    char buffer[LOG_BUFFER_SIZE];

    switch (type) {
        case LOG_TYPE_NORMAL:
            break;
        case LOG_TYPE_WARNING:
            textPrefix = "Warning: ";
            break;
        case LOG_TYPE_ERROR:
            textPrefix = "Error: ";
            break;
        case LOG_TYPE_DEBUG:
            textPrefix = "Debug: ";
            break;
    }

    int written = snprintf(buffer, sizeof(buffer), "%s", textPrefix);

    if (written >= 0 && written < (int)sizeof(buffer)) {
        vsnprintf(buffer + written, (int)sizeof(buffer) - written, format, va);
    }
    buffer[sizeof(buffer) - 1] = '\0';

    debugPrint("%s", buffer);
    DbgPrint("%s", buffer);
    
    for (const char* p = buffer; *p; p++)
    xlog_buf[(xlog_pos++) % XLOG_SIZE] = *p;
}