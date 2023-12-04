#include "MathFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdarg.h>


int sum(int a, int b){
    return a + b;
}
// error_functions.cpp

#ifdef __GNUC__
__attribute__((__noreturn__))
#endif
static void
terminate(Boolean useExit3)
{
    char *s;
    s = getenv("EF_DUMPCORE");

    if (s != NULL && *s != '\0')
    {
        abort();
    }
    else if (useExit3)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        _exit(EXIT_FAILURE);
    }
}

static void outputError(Boolean useErr, int err, Boolean flushStdout, const char *format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];
    vsnprintf(userMsg, BUF_SIZE, format, ap);
    if (flushStdout)
        fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
}

void errMsg(const char *format, ...)
{
    va_list argList;
    int savedErrno;

    savedErrno = errno;
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    errno = savedErrno;
}

void errExit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}

void err_exit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, FALSE, format, argList);
    va_end(argList);

    terminate(FALSE);
}

void errExitEN(int errnum, const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errnum, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}

void fatal(const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    outputError(FALSE, 0, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}

void usageErr(const char *format, ...)
{
    va_list argList;
    fflush(stdout);

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...)
{
    va_list argList;
    fflush(stdout);
    fprintf(stderr, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE);
}

// get_num.cpp

static void gnFail(const char *fname, const char *msg, const char *arg, const char *name)
{
    fprintf(stderr, "%s error", fname);
    if (name != NULL)
        fprintf(stderr, "%s", name);
    fprintf(stderr, ": %s\n", msg);
    exit(EXIT_FAILURE);
}

static long getNum(const char *fname, const char *arg, int flags, const char *name)
{
    long res;
    char *endptr;
    int base;
    if (arg == NULL || *arg == '\0')
        gnFail(fname, "null or empty string", arg, name);

    base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8
                                   : (flags & GN_BASE_16)  ? 16
                                                           : 10;

    errno = 0;
    res = strtol(arg, &endptr, base);
    if (errno != 0)
        gnFail(fname, "strtol() fail", arg, name);
    if (*endptr != '\0')
        gnFail(fname, "nonnumeric characters", arg, name);
    if ((flags & GN_NO) && res < 0)
        gnFail(fname, "regative value not allowed", arg, name);
    if ((flags & GN_GET_0) && res <= 0)
        gnFail(fname, "value must > 0", arg, name);
    return res;
}

long getLong(const char *args, int flags, const char *name)
{
    return getNum("getLong", args, flags, name);
}

int getInt(const char *args, int flags, const char *name)
{
    long res;
    res = getNum("getInt", args, flags, name);
    if (res > INT_MAX || res < INT_MIN)
        gnFail("getInt", "int out of range", args, name);
    return (int)res;
}
