#include <signal.h>
#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    int fdrd = 0, fdwr = 0, rv = 0,cnt = 100,fdlog = 0;
    unsigned short delay_4ns =0;
    double delay_by_us = 0;

    fdwr = open("/dev/xdma0_h2c_0", O_WRONLY);
    fdrd = open("/dev/xdma0_c2h_0", O_RDONLY);

    if (fdwr < 0 || fdrd < 0)
    {
        goto abnormal;
    }

    struct pollfd pfd;
    pfd.fd = fdrd;
    pfd.events = POLLIN | POLLERR;

    unsigned char buffer[32] = {0};
    for(int i=0;i<32;i++){
        buffer[i] = i;
    }

    while (cnt--)
    {
        rv = poll(&pfd, 1, -1);
        if (rv < 0)
            goto abnormal;
        // printf("poll:revents = 0x%x rv = %d\n", pfd.revents, rv);
        read(fdrd, buffer, sizeof(buffer));
        delay_4ns = buffer[1] << 8 | buffer[0];
        printf("%.2lf\n",delay_4ns*4e-3);
        write(fdwr,buffer,sizeof(buffer));
    }

    return 0;
abnormal:
    printf("abnormal:%s\n", strerror(errno));
    if (fdwr > 0)
        close(fdwr);
    if (fdrd > 0)
        close(fdrd);

    return rv;
}