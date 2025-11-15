#ifndef BB_CIRCULAR_BUFFER_H
#define BB_CIRCULAR_BUFFER_H
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"

typedef struct
{
    U8* data;
    U32 size;
    U32 count;
    U32 left;
    U32 right;

} bbCircularBuffer;

bbFlag bbCircularBufferCreate(bbCircularBuffer** buffer, U32 size, U32 count);
bbFlag bbCircularBufferPushL(bbCircularBuffer* buffer, void* data);
bbFlag bbCircularBufferPushR(bbCircularBuffer* buffer, void* data);
bbFlag bbCircularBufferPopL(bbCircularBuffer* buffer, void* data);
bbFlag bbCircularBufferPopR(bbCircularBuffer* buffer, void* data);




#endif //BB_CIRCULAR_BUFFER_H