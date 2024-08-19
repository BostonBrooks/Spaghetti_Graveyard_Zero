/**
 * @brief This header file contains some wrappers to the printf function.
 * These are provided to help with debugging, and can be switched off when no
 * longer needed. May have to use only one call to printf for each of the macros
 * defined below to help with thread safety
 *
*/

//TODO all of these are macros, all contain only one printf statement

#ifndef BBPRINTF_H
#define BBPRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbString.h"




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
                     \
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