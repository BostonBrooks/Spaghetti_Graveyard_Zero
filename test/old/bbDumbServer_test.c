

int main (void)
{
    bbDummySender* server;
    bbDummySender_new(&server);

    U64 gameTime = 0;
    bbDummySender_msg* msg;

    char str[64];
    while (1)
    {
        printf("Message sent: %d\n", gameTime);
        sprintf(str, "%d\n", gameTime);


        bbDummySender_textMessage(server, str, gameTime);
        bbDummyReceiver_receive(server, gameTime );

        sfSleep(sfMilliseconds(16));
        gameTime++;
    }
}