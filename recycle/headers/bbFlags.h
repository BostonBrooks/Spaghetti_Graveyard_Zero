/**
 * @file
 * @brief This header file contains flags passed by functions
 */


#ifndef FLAGS_H
#define FLAGS_H

#define f_Success               0

///have reached the end of the list
#define f_None                 -1

#define f_Continue             -2
#define f_Repeat               -3
#define f_Break                -4

/// After iterating over object, remove object from any lists then delete object
#define f_Delete               -5

/// Trying to create new object in a pool that's already full
#define f_Full                 -6






#endif //FLAGS_H