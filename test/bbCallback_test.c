
//typedef bbFlag bbCallbackFunction(void* callback);

#include <SFML/System.h>
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbCallback.h"

#include <stdio.h>

typedef bbFlag bbCallbackFunction(void* callback, bbPool_Handle handle);
bbFlag callcack1(void* Callback, bbPool_Handle handle);
bbFlag callcack2(void* Callback, bbPool_Handle handle);

bbFlag callcack1(void* Callback, bbPool_Handle handle)
{
    bbCallback* callback = (bbCallback*)Callback;
    callback->function = callcack2;
    printf("callback %s, i = %llu\n", (char*)callback->args.ptr, handle.u64);
    callback->args.ptr = "string 2";

    return Success;
}

bbFlag callcack2(void* Callback, bbPool_Handle handle)
{
    bbCallback* callback = (bbCallback*)Callback;
    callback->function = callcack1;
    printf("callback %s, i = %llu\n", (char*)callback->args.ptr, handle.u64);
    callback->args.ptr = "string 1";

    return Success;
}

int main(void)
{
    bbPool_Handle handle;
    handle.ptr = "start";
    bbCallback callback;
    bbCallback_init(&callback, callcack1, handle);

    I32 i = 0;
    while(1)
    {
        bbPool_Handle handle;
        handle.u64 = i;
        bbCallback_execute(&callback, handle);
        sfSleep(sfSeconds(0.2));
        i++;
    }
    return 0;
}