#ifndef BB_THREADED_QUEUE_H
#define BB_THREADED_QUEUE_H

typedef struct
{
    void* address;
} bbThreadedQueue;

bbFlag bbThreadedQueue_init(bbThreadedQueue* queue, bbVPool* pool, void* MORE);


#endif //BB_THREADED_QUEUE_H
