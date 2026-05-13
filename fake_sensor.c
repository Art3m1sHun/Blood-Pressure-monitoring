#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define M_PI 3.14

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <server_ip> <port>\n",
               argv[0]);

        return 1;
    }

    char *server_ip = argv[1];

    int port = atoi(argv[2]);

    //--------------------------------
    // CREATE SOCKET
    //--------------------------------

    int sock =
        socket(AF_INET,
               SOCK_STREAM,
               0);

    if(sock < 0)
    {
        perror("socket");

        return 1;
    }

    //--------------------------------
    // SERVER ADDRESS
    //--------------------------------

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;

    server_addr.sin_port =
        htons(port);

    inet_pton(AF_INET,
              server_ip,
              &server_addr.sin_addr);

    //--------------------------------
    // CONNECT
    //--------------------------------

    if(connect(sock,
               (struct sockaddr*)&server_addr,
               sizeof(server_addr)) < 0)
    {
        perror("connect");

        close(sock);

        return 1;
    }

    printf("Connected to gateway %s:%d\n",
           server_ip,
           port);

    //--------------------------------
    // FAKE SIGNAL GENERATION
    //--------------------------------

    double t = 0.0;

    while(1)
    {
        //--------------------------------
        // ECG FAKE
        //--------------------------------

        double ecg =
            1000.0 +
            300.0 * sin(2.0 * M_PI * 1.2 * t);

        //--------------------------------
        // PPG FAKE
        //--------------------------------

        double ppg =
            2000.0 +
            500.0 * sin(2.0 * M_PI * 1.2 * t + 0.4);

        //--------------------------------
        // PACKET
        //--------------------------------

        char buffer[128];

        snprintf(buffer,
                 sizeof(buffer),
                 "%.2f %.2f\n",
                 ecg,
                 ppg);

        //--------------------------------
        // SEND
        //--------------------------------

        send(sock,
             buffer,
             strlen(buffer),
             0);

        printf("SEND -> %s",
               buffer);

        //--------------------------------
        // SAMPLE RATE
        //--------------------------------

        t += 0.004;

        struct timespec ts =
        {
            .tv_sec = 0,
            .tv_nsec = 4000000
        };

        nanosleep(&ts, NULL);
    }

    close(sock);

    return 0;
}