/************************************************************************
* CREATED TIME: 2018-9-22 16:48:53
* LAST MODIFIED TIME: 2018-9-22 16:48:53
* DESCRIPTION: linux poll server (just for practice)
* BY: 357688981@qq.com
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>


#define IPADDRESS "127.0.0.1"
#define PORT      8001
#define MAX_BUF_SIZE   1024
#define BACKLOG   5
#define OPEN_MAX  1000
#define TIMEOUT   5000


int maxi;
struct pollfd clientfds[OPEN_MAX];


// 创建套接字并进行绑定
static int socket_bind(const char* ip, int port);

// IO多路复用poll
static void do_poll(int listenfd);

static int accept_client_proc();
static void recv_client_msg(struct pollfd* connfds, int num);


int main(int argc, char** argv)
{
    int ret;
    int listenfd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;

    listenfd = socket_bind(IPADDRESS, PORT);

    ret = listen(listenfd, BACKLOG);
    if (ret == -1) {
        perror("listen error!");
        exit(1);
    }

    do_poll(listenfd);

    return 0;
}


static int socket_bind(const char* ip, int port)
{
    int ret;
    int listenfd;
    struct sockaddr_in servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if (listenfd == -1) {
        perror("socket error!");
        exit(1);
    }

    // 一个端口释放后会等待两分钟之后才能再被使用, SO_REUSEADDR是让端口释放后立即就可以被再次使用
    int reuse = 1;
    ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (ret == -1) {
        printf("setsockopt error!\n");
        return ret;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret == -1) {
        perror("bind error!");
        exit(1);
    }
    return listenfd;
}

static int accept_client_proc(int listenfd, int* nready)
{
    int connfd;
    int i;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;

    client_addr_len = sizeof(client_addr);
    // 接受新的连接
    do {
        connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addr_len);
    } while(connfd == -1 && errno == EINTR);

    if (connfd == -1) {
        perror("accept error!");
        exit(1);
    }

    // 打印新连接的客户端的ip和port
    fprintf(stdout, "accept a new client: ip = %s, port = %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));


    // 将新的连接描述符添加到数组中
    for (i = 1; i < OPEN_MAX; ++i) {
        if (clientfds[i].fd < 0) {
            clientfds[i].fd = connfd;
            // 将新的描述符添加到读描述符集合中
            clientfds[i].events = POLLIN;
            break;
        }
    }

    if (i == OPEN_MAX) {
        fprintf(stderr, "too many clients.\n");
        exit(1);
    }

    // 记录客户端连接套接字的个数
    maxi = (i > maxi ? i : maxi);

    *nready = *nready - 1;
    if (*nready <= 0) {
        return 0;
    }

    return 0;
}

static void do_poll(int listenfd)
{
    int i;
    int nready;

    // 添加监听描述符
    clientfds[0].fd = listenfd;
    clientfds[0].events = POLLIN;

    // 初始化客户连接描述符
    for (i = 1; i < OPEN_MAX; ++i) {
        clientfds[i].fd = -1;
    }
    maxi = 0;

    // 循环处理
    for (;;) {
        // 获取可用描述符的个数
        nready = poll(clientfds, maxi+1, TIMEOUT);

        if (nready == 0) {
            printf("poll timeout...\n");
            continue;
        }

        if (nready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("poll error!");
            exit(1);
        }

        // 测试监听描述符是否准备好
        if (clientfds[0].revents & POLLIN) {
            accept_client_proc(listenfd, &nready);
        }

        // 接收并处理客户端消息
        recv_client_msg(clientfds, maxi);
    }
}

static void recv_client_msg(struct pollfd* connfds, int num)
{
    int i, n;
    char buf[MAX_BUF_SIZE];
    memset(buf, 0, sizeof(buf));

    for (i = 1; i <= num; ++i) {
        if (connfds[i].fd < 0) {
            continue;
        }
        // 测试客户端描述符是否准备好
        if (connfds[i].revents & POLLIN) {
            // 接受客户端发送的消息
            n = read(connfds[i].fd, buf, MAX_BUF_SIZE);
            if (n == 0) {
                printf("client offline!\n");
                close(connfds[i].fd);
                connfds[i].fd = -1;
                continue;
            }
            printf("recv msg: %s\n", buf);
            // 向客户端发送buf
            printf("send msg: %s\n", buf);
            write(connfds[i].fd, buf, n);
        }
    }
}
