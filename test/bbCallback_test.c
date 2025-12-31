
//typedef bbFlag bbCallbackFunction(void* callback);

#include <SFML/System.h>
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbCallback.h"

#include <stdio.h>

bbFlag callcack1(void* Callback);
bbFlag callcack2(void* Callback);

bbFlag callcack1(void* Callback)
{
    bbCallback* callback = (bbCallback*)Callback;
    callback->function = callcack2;
    printf("callback %s\n", callback->args.ptr);
    callback->args.ptr = "string 2";

    return Success;
}

bbFlag callcack2(void* Callback)
{
    bbCallback* callback = (bbCallback*)Callback;
    callback->function = callcack1;
    printf("callback %s\n", callback->args.ptr);
    callback->args.ptr = "string 1";

    return Success;
}

int main(void)
{
    bbPool_Handle handle;
    handle.ptr = "start";
    bbCallback callback;
    bbCallback_init(&callback, callcack1, handle);

    while(1)
    {
        bbCallback_execute(&callback);
        sfSleep(sfSeconds(0.2));
    }
    return 0;
}