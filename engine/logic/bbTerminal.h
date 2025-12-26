/**
 * @brief This header file contains some wrappers to the printf function.
 * These are provided to help with debugging, and can be switched off when no
 * longer needed. May have to use only one call to printf for each of the macros
 * defined below to help with thread safety
 *
*/

//TODO all of these are macros, all contain only one printf statement

#ifndef BBTERMINAL_H
#define BBTERMINAL_H

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include <SFML/Network/IpAddress.h>

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbString.h"


static const int stringLength = 512;

///Same as bbDebug but with the DEBUG: tag

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

#define bbPrintf(...) {\
    char string[stringLength];\
	sprintf (string, __VA_ARGS__);\
    printf("bbPrintf: %s", string);\
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
        break;            \
    dafault:              \
        bbDebug ("Flag = unknown\n");\
    }\
}\

#define bbWidgetCommandType_print(flag)\
{\
switch ((bbWidgetCommandType)flag)\
{\
case bbWC_putChar:\
bbDebug ("bbWidgetCommandType = bbWC_putChar\n");\
break;\
case bbWC_putStr:\
bbDebug ("bbWidgetCommandType = bbWC_putStr\n");\
break;\
case bbWC_setBounds:\
bbDebug ("bbWidgetCommandType = bbWC_setBounds\n");\
break;\
case bbWC_setDimensions:\
bbDebug ("bbWidgetCommandType = bbWC_setDimensions\n");\
break;\
case bbWC_setStr:\
bbDebug ("bbWidgetCommandType = bbWC_setStr\n");\
break;\
case bbWC_clrStr:\
bbDebug ("bbWidgetCommandType = bbWC_clrStr\n");\
break;\
dafault:              \
bbDebug ("bbWidgetCommandType = unknown\n");\
}\
}\

#define sfSocketStatus_print(status)\
{\
    switch((sfSocketStatus)status)\
    {\
        case sfSocketDone:\
        bbDebug("status = sfSocketDone\n");\
        break;\
        case sfSocketNotReady:\
        bbDebug("status = sfSocketNotReady\n");\
        break;\
        case sfSocketPartial:\
        bbDebug("status = sfSocketPartial\n");\
        break;\
        case sfSocketDisconnected:\
        bbDebug("status = sfSocketDisconnected\n");\
        break;\
        case sfSocketError:\
        bbDebug("status = sfSocketError\n");\
        break;\
        default:\
        bbDebug("status = unknown\n");\
        \
    }\
}\

//Similar function found in https://github.com/orichalcink/chatroom
static void bbClearLine(I32 lines)
{
    //    \r     #go to the start of the current line
    //    \033[F #back to previous line
    //    \033[K #delete everything from the cursor to the end of the line

    for(I32 i = 0; i <= lines;i++)
    {
        printf("\r\033[K");
        if (i<lines) printf("\033[F");
    }
    fflush(stdout);
}

//Similar function found in https://github.com/orichalcink/chatroom
static I32 bbGetInt(char* prompt)
{
    I32 number;
    char answer[64];
    while(1){
        printf("%s", prompt);

        scanf("%s", answer);

        I32 len = strlen(answer);
        char digits[] = "0123456789";
        I32 int_len = strspn(answer, digits);

        if(len == int_len) {

            number = atoi(answer);
            return (number);
        }
        bbClearLine(1);

        printf("Invalid input. Please enter a valid integer.\n");


    }
}

//Similar function found in https://github.com/orichalcink/chatroom
static I32 bbGetLine(char* string, I32 bufferlength, FILE* fp)
{
    I32 numchars = 0;
    I32 c = '\0';

    while (1)
    {
        c = fgetc(fp);

        if (c == EOF || c == '\n') break;

        string[numchars] = c;

        if (numchars >= bufferlength - 1) break;
        numchars++;
    }

    string[numchars + 1] = '\0';

    return numchars + 1;
}

//Similar function found in https://github.com/orichalcink/chatroom
static sfIpAddress bbGetIPAddress(char* prompt)
{

    fflush(stdout);
    sfIpAddress address;
    while (1)
    {
        printf("%s", prompt);
        fflush(stdout);
        char addressStr[64];
        bbGetLine(addressStr, 64,stdin);
        bbClearLine(1);
        address = sfIpAddress_fromString(addressStr);

        U32 intAddress;
        intAddress = sfIpAddress_toInteger(address);

        if (intAddress != 0) break;
    }

    return (address);
}

//thread tells some of the debugging functions what to name each thread
extern _Thread_local char* thread;

#define THREAD_DEBUG
#ifdef THREAD_DEBUG

#define bbMutexLock(mutex){\
bbDebug("Mutex Lock in thread %s!\n", thread);\
pthread_mutex_lock(mutex);}\


#define bbMutexUnlock(mutex){\
bbDebug("Mutex Unlock in thread %s!\n", thread);\
pthread_mutex_unlock(mutex);}\

#undef bbHere()
#define bbHere() printf ("In FILE: %s, FUNCTION: %s, LINE: %d, THREAD: %s\n",\
__FILE_NAME__, __func__, __LINE__, thread);


#else //#ifdef THREAD_DEBUG


#define bbMutexLock(mutex){\
pthread_mutex_lock(mutex);}\


#define bbMutexUnlock(mutex){\
pthread_mutex_unlock(mutex);}\

#endif //#ifdef THREAD_DEBUG

#endif // BBTERMINAL_H