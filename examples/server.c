#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    printf("C Server started on port 5555\n");

    while (1) {
        char buffer [256];
        int size = zmq_recv (responder, buffer, 255, 0);
        if (size == -1) break;
        buffer[size] = '\0';
        printf ("Received request: %s\n", buffer);

        char response[300];
        sprintf(response, "C Echo: %s", buffer);
        zmq_send (responder, response, strlen(response), 0);
    }
    return 0;
}
