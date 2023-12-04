#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void errMsg(const char *format, ...);
#ifdef __GNUC__

#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char *format, ...) NORETURN;
void err_exit(const char *format, ...) NORETURN;
void errExitEN(int errnum, const char *format, ...) NORETURN;
void fatal(const char *format, ...) NORETURN;
void usageErr(const char *format, ...) NORETURN;
void cmdLineErr(const char *format, ...) NORETURN;

typedef enum
{
    FALSE,
    TRUE
} Boolean;


#define GN_NO 01
#define GN_GET_0 02

#define GN_ANY_BASE 0100
#define GN_BASE_8 0200
#define GN_BASE_16 0400

long getLong(const char *args, int flags, const char *name);

int getInt(const char *args, int flags, const char *name);

int sum(int a, int b);
#endif