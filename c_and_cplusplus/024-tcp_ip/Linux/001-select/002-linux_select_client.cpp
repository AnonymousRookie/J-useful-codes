/************************************************************************
* CREATED TIME: 2018-9-1 20:02:49
* LAST MODIFIED TIME: 2018-9-1 20:02:49
* DESCRIPTION: linux select client (just for practice)
* BY: 357688981@qq.com
************************************************************************/

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>


#define IPADDR  "127.0.0.1"
#define PORT    50001
#define MAX_MSG_LEN 1024


static int handle_recv_msg(int sockfd, char* buf)
{
    printf("client recv msg is: %s\n", buf);
    sleep(2);
    write(sockfd, buf, strlen(buf)+1);
    return 0;
}

static int handle_connection(int sockfd)
{
    char recvline[MAX_MSG_LEN] = {0};

    int maxfdp;
    maxfdp = sockfd;

    fd_set readfds;
    fd_set allfds;

    FD_SET(sockfd, &allfds);

    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    int ret = -1;

    while(1) {
        readfds = allfds;
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        ret = select(maxfdp + 1, &readfds, NULL, NULL, &tv);
        if (ret == -1) {
            if (errno == EINTR) {
                continue;
            }
            printf("select error!\n");
            return ret;
        }
        if (ret == 0) {
            printf("select timeout...\n");
            continue;
        }
        if (FD_ISSET(sockfd, &readfds)) {
            memset(recvline, 0, sizeof(recvline));
            int n = read(sockfd, recvline, MAX_MSG_LEN);
            if (n <= 0) {
                close(sockfd);
                FD_CLR(sockfd, &readfds);
                printf("server is closed!\n");
                return -1;
            }
            handle_recv_msg(sockfd, recvline);
        }
    }
}


int main(int argc, char** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, IPADDR, &servaddr.sin_addr);

    int ret = 0;
    ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret == -1) {
        printf("connect error: %d\n", errno);
        return ret;
    }

    char sendline[MAX_MSG_LEN] = {0};
    strcpy(sendline, "hello server!");
    write(sockfd, sendline, strlen(sendline));

    handle_connection(sockfd);

    return 0;
}