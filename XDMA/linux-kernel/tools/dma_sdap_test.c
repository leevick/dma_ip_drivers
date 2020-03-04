#include <signal.h>
#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char *argv[])
{

    int rv = 0,cnt = 100;
    int fds[4] = {0};
    int i = 0;

    fds[0] = open("/dev/xdma0_h2c_2", O_WRONLY);
    fds[1] = open("/dev/xdma0_c2h_2", O_RDONLY);
    fds[2] = open("/dev/xdma0_h2c_3", O_WRONLY);
    fds[3] = open("/dev/xdma0_c2h_3", O_RDONLY);

    i = 4;
    while(i--){
        if (fds[i] < 0)
        {
            rv = fds[i];
            goto abnormal;
        }
    }


    // struct pollfd pfd;
    // pfd.fd = m_dl_fd;
    // pfd.events = POLLIN | POLLERR;

    while (cnt--)
    {
        // rv = poll(&pfd, 1, -1);
        // if (rv < 0)
            // goto abnormal;
        // printf("poll:revents = 0x%x rv = %d\n", pfd.revents, rv);
        // read(fdrd, buffer, sizeof(buffer));
        // delay_4ns = buffer[1] << 8 | buffer[0];
        // printf("%.2lf\n",delay_4ns*4e-3);
        write(fds[0],&cnt,4);
    
    }
    return 0;
abnormal:
    printf("abnormal:%s\n", strerror(errno));
    i = 4;
    while(i--)
    {
        if(fds[i]>0)
            close(fds[i]);
    }
    return rv;
}