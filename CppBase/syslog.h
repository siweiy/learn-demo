/*
 * Copyright (C) 2015-2017 ----
 */
/******************************************************************************
 * @file     syslog.h
 * @brief    Defines syslog APIs and usage
 * @version  V1.0
 * @date     24. September 2020
 * @usage    0: Err; 1: Err&Warn; 2: Err&Warn&Info; 3: Err&Warn&Info&Debug
 *           #define LOG_LEVEL 3 // before
 *           #include <syslog.h>
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sys/timeb.h>

#ifndef SYSLOG_H
#define SYSLOG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LOG_LEVEL
#if (LOG_LEVEL >= 3)
#define LOG_ENABLE_D
#endif

#if (LOG_LEVEL >= 2)
#define LOG_ENABLE_I
#endif

#if (LOG_LEVEL >= 1)
#define LOG_ENABLE_W
#endif

#if (LOG_LEVEL >= 0)
#define LOG_ENABLE_E
#endif
#else   
#define LOG_ENABLE_E
#endif

char LogPrefix[24];

#define LOG_COLOR_RED_YELLO_BACK "\033[1;31;43m"
#define LOG_COLOR_RED            "\033[2;31;49m"
#define LOG_COLOR_YELLOW         "\033[2;33;49m"
#define LOG_COLOR_GREEN          "\033[2;32;49m"
#define LOG_COLOR_BLUE           "\033[2;34;49m"
#define LOG_COLOR_GRAY           "\033[1;30m"
#define LOG_COLOR_WHITE          "\033[1;47;49m"
#define LOG_COLOR_RESET          "\033[0m"

/* [LogLevel:FileName:Function:Line] */
const char *PFORMAT_D    = LOG_COLOR_GRAY   "[%s][%sD][%s():%d] " LOG_COLOR_RESET;
const char *PFORMAT_I    = LOG_COLOR_WHITE  "[%s][%sI][%s():%d] " LOG_COLOR_RESET;
const char *PFORMAT_W    = LOG_COLOR_YELLOW "[%s][%sW][%s():%d] " LOG_COLOR_RESET;
const char *PFORMAT_E    = LOG_COLOR_RED    "[%s][%sE][%s():%d] " LOG_COLOR_RESET;
const char *PFORMAT_O    = LOG_COLOR_GREEN  "[%s][%sE][%s():%d] " LOG_COLOR_RESET;

#define LOG_E_BASE_ARGS LogTime(), LogPrefix, __FUNCTION__, __LINE__
#define LOG_W_BASE_ARGS LogTime(), LogPrefix, __FUNCTION__, __LINE__
#define LOG_I_BASE_ARGS LogTime(), LogPrefix, __FUNCTION__, __LINE__
#define LOG_D_BASE_ARGS LogTime(), LogPrefix, __FUNCTION__, __LINE__
#define LOG_O_BASE_ARGS LogTime(), LogPrefix, __FUNCTION__, __LINE__

/* Log in freely format without prefix */
#define LOG_F(fmt, args...) printf(fmt,##args)

// OK, Green color
#define LOG_O(fmt, args...)	\
	do {printf(PFORMAT_O,LOG_O_BASE_ARGS); printf(fmt,##args);} while(0)

/* Log debug */
#ifdef LOG_ENABLE_D
#define LOG_D(fmt, args...) \
    do {printf(PFORMAT_D,LOG_D_BASE_ARGS); printf(fmt,##args);} while(0)
#else
#define LOG_D(fmt, args...)
#endif

/* Log information */
#ifdef LOG_ENABLE_I
#define LOG_I(fmt, args...) \
    do {printf(PFORMAT_I ,LOG_I_BASE_ARGS); printf(fmt,##args);} while(0)
#else
#define LOG_I(fmt, args...)
#endif

/* Log warning */
#ifdef LOG_ENABLE_W
#define LOG_W(fmt, args...) \
    do {printf(PFORMAT_W,LOG_W_BASE_ARGS); printf(fmt,##args);} while(0)
#else
#define LOG_W(fmt, args...)
#endif

/* Log error */
#ifdef LOG_ENABLE_E
#define LOG_E(fmt, args...) \
    do {printf(PFORMAT_E,LOG_E_BASE_ARGS); printf(fmt,##args);} while(0)
#else
#define LOG_E(fmt, args...)
#endif

inline void SetLogPrefix(const char *prefix)
{
    strncpy(LogPrefix, prefix, sizeof(LogPrefix)-1);
    LogPrefix[strlen(LogPrefix)] = ':';
}

inline char* LogTime(void)
{
    struct tm *ptm;
    struct timeb stTimeb;
    static char szTime[24];

    ftime(&stTimeb);
    ptm = localtime(&stTimeb.time);
    sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
         ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, stTimeb.millitm);
    szTime[23] = 0;
    return szTime;
}

#define ENTER()         LOG_D("Enter\n")
#define EXIT_VOID()     do { LOG_D("Exit\n"); return;} while(0)
#define EXIT_INT(val)   do { LOG_D("Exit, return val=%d\n", (int)val); return val;} while(0)
#define EXIT_PTR(ptr)   do { LOG_D("Exit, return ptr=%p\n", (void*)ptr); return ptr;} while(0)

#ifdef __cplusplus
}
#endif

#endif  // SYSLOG_H



