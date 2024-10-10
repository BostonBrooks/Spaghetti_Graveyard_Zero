/**
 * @brief functions return flags to indicate success/failure etc;
 *
*/

//many functions return a non-negative index in the result of successful
//execution, and a negative flag otherwise
#define f_Success     0
#define f_None        (-1)
#define f_Break       (-2)
#define f_Continue    1