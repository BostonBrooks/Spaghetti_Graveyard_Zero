/** Loop through event queue and dispatch to handlers
    This function is the only part of the code that handles sfEvent logic.
 */

#ifndef BBDISPATCH_H
#define BBDISPATCH_H


#include "bbIntTypes.h"

I32 EventDispatch(I32 map);

#endif //BBDISPATCH_H