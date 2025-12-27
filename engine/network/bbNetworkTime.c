{
    network_time->localClock = sfClock_create();
    network_time->packets_sent = 0;
    bbVPool_newLean(&network_time->pool, sizeof(bbNetwork_record), 1024);
    bbList_init(&network_time->pending, network_time->pool, NULL, offsetof(bbNetwork_record, list_element), NULL);
    bbList_init(&network_time->recorded, network_time->pool, NULL, offsetof(bbNetwork_record, list_element), NULL);

    return None;
}