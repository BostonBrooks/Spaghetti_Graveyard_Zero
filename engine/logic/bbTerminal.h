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
#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbString.h"


static const int stringLength = 512;

///Same as bbDebug but with the DEBUG: tag
#define bbPrintf printf

#ifdef BBVERBOSE
    #define bbVerbose printf
#endif

/// Print warning and exit, but preserve the stack for gdb
//SIGTRAP?
#define bbAssert(expression, ...)\
    {\
        if (!(expression)){\
            char string1[stringLength];\
            char string2[stringLength];\
	        sprintf (string1, "In FILE: %s, FUNCTION: %s, LINE: %d,"\
            "\nASSERTION: %s, ", __FILE_NAME__, __func__, __LINE__,\
            #expression );\
\
            sprintf(string2, __VA_ARGS__);\
\
            printf("%s%s", string1, string2);                    \
            int x = 1/0;\
        }\
    }

/// Print warning and continue
#define bbWarning(expression, ...)\
    {\
        if (!(expression)){\
            char string1[stringLength];\
            char string2[stringLength];\
	        sprintf (string1, "In FILE: %s, FUNCTION: %s, LINE: %d,"\
            "\nWARNING: %s, ", __FILE_NAME__, __func__, __LINE__, #expression);\
\
            sprintf(string2, __VA_ARGS__);\
\
            printf("%s%s", string1, string2);\
        }\
    }

#define bbDebug(...) {\
    char string1[stringLength];\
    char string2[stringLength];\
	sprintf (string1, "In FILE: %s, FUNCTION: %s, LINE: %d,\nDEBUG: ",\
        __FILE_NAME__, __func__, __LINE__);\
	sprintf (string2, __VA_ARGS__);\
    printf("%s%s", string1, string2);\
    }

#define bbHere() printf ("In FILE: %s, FUNCTION: %s, LINE: %d\n",\
        __FILE_NAME__, __func__, __LINE__);


#define bbFlag_print(flag)\
{\
    switch ((bbFlag)flag)\
    {\
    case Success:\
        bbDebug ("Flag = Success\n");\
        break;\
    case None:\
        bbDebug ("Flag = None\n");\
        break;\
    case Full:\
        bbDebug ("Flag = Full\n");\
        break;\
    case Empty:\
        bbDebug ("Flag = Empty\n");\
        break;\
    case Break:\
        bbDebug ("Flag = Break\n");\
        break;\
    case Repeat:\
        bbDebug ("Flag = Repeat\n");\
        break;\
    case Continue:\
        bbDebug ("Flag = Continue\n");\
        break;\
    case Delete:\
        bbDebug ("Flag = Delete\n");\
        break;\
    case Head:\
        bbDebug ("Flag = Head\n");\
        break;\
    case Tail:\
        bbDebug ("Flag = Tail\n");\
        break;\
    }\
}\


#endif // BBPRINTF_H