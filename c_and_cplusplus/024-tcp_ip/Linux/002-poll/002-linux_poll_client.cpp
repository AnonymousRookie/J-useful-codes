/************************************************************************
* CREATED TIME: 2018-9-22 19:23:11
* LAST MODIFIED TIME: 2018-9-22 19:23:11
* DESCRIPTION: linux poll client (just for practice)
* BY: 357688981@qq.com
************************************************************************/

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>
#include <poll.h>


#define MAX_BUF_SIZE    1024
#define IPADDRESS  "127.0.0.1"
#define SERV_PORT  8001


static void handle_connection(int sockfd);

int main(int argc, char** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // 处理连接描述符
    handle_connection(sockfd);

    return 0;
}

static void handle_connection(int sockfd)
{
    char sendline[MAX_BUF_SIZE], recvline[MAX_BUF_SIZE];
    int maxfdp, stdineof;

    struct pollfd pfds[2];

    int n;

    // 添加连接描述符
    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN;

    // 添加标准输入描述符
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;

    for (;;) {
        poll(pfds, 2, -1);

        if (pfds[0].revents & POLLIN) {
            memset(recvline, 0, sizeof(recvline));
            n = read(sockfd, recvline, MAX_BUF_SIZE);
            if (n == 0) {
                fprintf(stderr, "server is closed!\n");
                close(sockfd);
            }
            else
            {
                fprintf(stdout, "recv msg: %s\n", recvline);
            }
        }

        // 检查标准输入是否准备好
        if (pfds[1].revents & POLLIN) {
            memset(sendline, 0, sizeof(sendline));
            n = read(STDIN_FILENO, sendline, MAX_BUF_SIZE);
            if (n == 0) {
                shutdown(sockfd, SHUT_WR);
                continue;
            }

            write(sockfd, sendline, n);
        }
    }
}
