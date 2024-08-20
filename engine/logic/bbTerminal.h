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


static const int stringLength 512;

///Same as bbDebug but with the DEBUG: tag
#define bbPrintf printf

#ifdef BBVERBOSE
    #define bbVerbose printf
#endif


#define bbAssert(expression, ...)                        \
    {                                                    \
        if (!(expression)){                              \
            char assertstring[stringLength] = "ASSERTION: ";\
            sprintf(&assertstring[10], __VA_ARGS__);      \
            printf("%s", asseetstring);                  \
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
	printf (__VA_ARGS__);

#define bbHere() 	printf ("LINE: %d, FILE: %s, FUNCTION: %s\n",\
                      __LINE__, __FILE_NAME__, __func__);

//in future, we could enter commands via the console while stopped at a breakpoint
#define bbBreakPoint(...) \
	printf ("FILE: %s,\tFUNCTION: %s,\tLINE: %d,\nBREAKPOINT: ", __FILE_NAME__, __func__, __LINE__);\
	printf (__VA_ARGS__);\
	getchar();

#endif // BBPRINTF_H