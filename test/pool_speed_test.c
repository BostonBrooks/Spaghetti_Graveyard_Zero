#include <stdio.h>
#include <stdlib.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>

#include "engine/logic/bbVPool.h"

typedef struct
{
    char str[64];
} test_struct;


char global;

int main(void){
    bbVPool* pool;
    bbVPool_newBloated(&pool, sizeof(test_struct), 1024, 1024);
    test_struct* array[1024*1024];
    sfClock* clock = sfClock_create();
    sfTime time;

    sfClock_restart(clock);
    for (int i = 0; i < 1024*1024; i++)
    {
        bbVPool_alloc(pool, (void**)&array[i])
        global = array[i]->str[0];
    }

    time = sfClock_getElapsedTime(clock);

    printf("pool time = %f\n", sfTime_asSeconds(time));

    bbVPool_delete(pool);

    sfClock_restart(clock);

    for (int i = 0; i < 1024*1024; i++)
    {
        array[i] = malloc(sizeof(test_struct));
        global = array[i]->str[0];
    }
    time = sfClock_getElapsedTime(clock);

    printf("malloc time = %f\n", sfTime_asSeconds(time));

    for (int i = 0; i < 1024*1024; i++)
    {
        free(array[i]);
    }

    sfClock_destroy(clock);

    exit (0);
}
