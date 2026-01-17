#ifndef BBCALLBACK_H
#define BBCALLBACK_H
#include "bbFlag.h"
#include "bbPoolHandle.h"

typedef bbFlag bbCallbackFunction(void* callback, bbPool_Handle handle);


typedef struct bbCallback
{
    bbCallbackFunction* function;
    bbPool_Handle args;
    struct bbCallback* daisyChain;
}  bbCallback;

static bbFlag bbCallback_execute(bbCallback* callback, bbPool_Handle handle)
{
    return callback->function(callback, handle);
}

static bbFlag bbCallback_init(bbCallback* self, bbCallbackFunction* function, bbPool_Handle args)
{
    self->function = function;
    self->args = args;
    self->daisyChain = NULL;
    return Success;
}

#endif // BBCALLBACK_H