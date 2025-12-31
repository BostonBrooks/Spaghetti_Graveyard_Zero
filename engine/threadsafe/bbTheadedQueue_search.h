#ifndef BB_TQ_SEARCH_H
#define BB_TQ_SEARCH_H

#include "engine/logic/bbCallback.h"
#include "engine/threadsafe/bbThreadedQueue.h"

///pop element when callback == Success
bbFlag bbThreadedQueue_search(bbThreadedQueue* queue, void** element, bbCallback* callback);



#endif // BB_TQ_SEARCH_H