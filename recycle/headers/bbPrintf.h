/**
 * @file
 * @brief This header file contains definitions of some wrappers to printf functions.
 * Functions are defined statically and depend on defined macros,
 * So they can be switched on and off on a per-file basis
 *
*/


#ifndef BBPRINTF_H
#define BBPRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "bbIntTypes.h"


/*
#define BBDEBUG
///If BBDEBUG is defined, print a debug message
static void bbDebug(const char* format, ...){

#ifdef BBDEBUG
	printf("DEBUG: ");
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end (args);

#endif  // BBDEBUG
}
*/

///Same as bbDebug but with the DEBUG: tag
static void bbPrintf(const char* format, ...){

#ifdef BBDEBUG

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end (args);

#endif  // BBDEBUG

}

///If BBVERBOSE is defined, print a verbose message
static void bbVerbose(const char* format, ...){

#ifdef BBVERBOSE

	printf("VERBOSE: ");
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end (args);

#endif // BBVERBOSE

}

/// Print warning and exit TODO read pg 134?
#define bbAssert(expression, ...)                        \
    {                                                    \
        if (!(expression)){                              \
            printf("ASSERTION: ");                       \
        printf(__VA_ARGS__);                             \
        }                                                \
        assert(expression);                              \
    }
/// Print warning and continue
#define bbWarning(expression, ...)                   \
	if (!(expression)){                              \
		printf("WARNING: ");                         \
	printf(__VA_ARGS__);                             \
	}

#define bbDebug(...) \
	printf ("FILE: %s,\tFUNCTION: %s,\tLINE: %d,\nDEBUG: ", __FILE_NAME__, __func__, __LINE__);\
	printf (__VA_ARGS__);                                                                      \

#define bbHere() 	printf ("LINE: %d, FILE: %s, FUNCTION: %s\n",\
                      __LINE__, __FILE_NAME__, __func__);

//in future, we could enter commands via the console while stopped at a breakpoint
#define bbBreakPoint(...) \
	printf ("FILE: %s,\tFUNCTION: %s,\tLINE: %d,\nBREAKPOINT: ", __FILE_NAME__, __func__, __LINE__);\
	printf (__VA_ARGS__);\
	getchar();

#endif // BBPRINTF_H

