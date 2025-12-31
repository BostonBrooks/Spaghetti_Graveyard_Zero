#ifndef BBCALLBACK_H
#define BBCALLBACK_H
#include "bbFlag.h"
#include "bbPoolHandle.h"

typedef bbFlag bbCallbackFunction(void* callback);


typedef struct
{
    bbCallbackFunction* function;
    bbPool_Handle args;
}  bbCallback;

static bbFlag bbCallback_execute(bbCallback* callback)
{
    return callback->function(callback);
}

static bbFlag bbCallback_init(bbCallback* self, bbCallbackFunction* function, bbPool_Handle args)
{
    self->function = function;
    self->args = args;
    return Success;
}

#endif // BBCALLBACK_H