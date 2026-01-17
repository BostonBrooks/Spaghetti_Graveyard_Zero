#include "engine/logic/bbCircularBuffer.h"

#include <stdlib.h>
#include <string.h>

#include "engine/logic/bbTerminal.h"

//If necessary, the size of the buffer can be increased
bbFlag bbCircularBufferExpand(bbCircularBuffer* circularBuffer);

bbFlag bbCircularBufferCreate(bbCircularBuffer** buffer, U32 size, U32 count)
{
    bbCircularBuffer* circularBuffer = malloc(sizeof(bbCircularBuffer));
    bbAssert(circularBuffer != NULL, "bad malloc");
    circularBuffer->data = calloc(sizeof(U8), size*count);
    bbAssert(circularBuffer->data != NULL, "bad malloc");

    circularBuffer->size = size;
    circularBuffer->count = count;
    circularBuffer->left = 0;
    circularBuffer->right = 0;

    *buffer = circularBuffer;

    return Success;
}

bbFlag bbCircularBufferPushR(bbCircularBuffer* buffer, void* data)
{
    if (/*buffer full*/)
    {
        bbCircularBufferExpand(buffer);
    }

    void* space;
    if (/*at end of buffer*/)
    {
        //loop around and get next space
    } else {
        //dont loop around, but get next space
    }

    memcpy(space, data, buffer->size);

    return Success;
}