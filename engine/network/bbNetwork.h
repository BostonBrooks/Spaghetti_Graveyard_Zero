#ifndef BB_NETWORK_H
#define BB_NETWORK_H

#include <pthread.h>

#include "engine/includes/CSFML.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbVPool.h"
#include "engine/threadsafe/bbThreadedQueue.h"
#include "engine/threadsafe/bbThreadedPool.h"


extern pthread_mutex_t network_mutex;

typedef struct
{
    sfIpAddress address;
    I32 port;
    sfTcpSocket* socket;
    sfTcpListener* listener;
    pthread_mutex_t mutex;
    bbVPool* messagePool;
    bbThreadedQueue inbox;
    bbThreadedQueue outbox;
} bbNetwork;

bbFlag bbNetwork_init(bbNetwork** self, sfIpAddress address, I32 port);

#endif  // BB_NETWORK_H