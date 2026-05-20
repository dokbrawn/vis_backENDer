#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf("Connecting to Python server (port 5555)...\n");
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    for (int i = 0; i < 5; i++) {
        char buffer[64];
        const char *msg = "Hello from C";
        printf("Sending: %s...\n", msg);

        zmq_send(requester, msg, strlen(msg), 0);

        int size = zmq_recv(requester, buffer, 63, 0);
        if (size != -1) {
            buffer[size] = '\0'; // Null-terminate string
            printf("Received: %s\n", buffer);
        }
        sleep(1);
    }

    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}
