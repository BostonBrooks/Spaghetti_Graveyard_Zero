/**
 * @brief functions return flags to indicate success/failure etc;
 *
*/

#ifndef BBFLAG_H
#define BBFLAG_H

//some modules use positive values for indices and negative values for other
#define f_Success     0
#define f_None        (-1)
#define f_Break       (-2)
#define f_Continue    1

typedef enum {
    Success,
    None,
    Full,
    Break,
    Continue,
    Delete
} bbFlag;

#endif // BBFLAG_H