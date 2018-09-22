/************************************************************************
* CREATED TIME: 2018-9-1 15:00:13
* LAST MODIFIED TIME: 2018-9-1 15:00:13
* DESCRIPTION: linux select server (just for practice)
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
#include <sys/select.h>
#include <sys/types.h>


#define IPADDR  "127.0.0.1"
#define PORT    50001
#define BACKLOG 5

#define MAX_CLIENT_SIZE  10
#define MAX_BUF_SIZE 1024


typedef struct server_context_st
{
    int cli_cnt;      // 客户端个数
    int clifds[MAX_CLIENT_SIZE]; // 所有客户端
    fd_set allfds;   // 保存所有最新的未被修改的文件描述符
    fd_set readfds;  // 当事件发生后，文件描述符和时间都被内核修改了
    int maxfd;       // 保存最大文件描述符
} server_context_st;

static server_context_st* s_srv_ctx = NULL;

static int create_server_proc(const char* ip, int port, int* listenfd)
{
    int ret;
    int fd;
    struct sockaddr_in servaddr;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("create socket failed: err = %d\n", errno);
        return -1;
    }
    // 一个端口释放后会等待两分钟之后才能再被使用, SO_REUSEADDR是让端口释放后立即就可以被再次使用
    int reuse = 1;
    ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (ret == -1) {
        printf("setsockopt error!\n");
        return ret;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    // servaddr.sin_addr.s_addr =inet_addr(ip);
    inet_pton(AF_INET, ip, &servaddr.sin_addr);

    ret = bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret == -1) {
        printf("bind error!\n");
        return ret;
    }

    ret = listen(fd, BACKLOG);
    if (ret == -1) {
        printf("listen error!\n");
        return ret;
    }

    *listenfd = fd;

    return ret;
}

static int accept_client_proc(int listenfd, int* nready)
{
    struct sockaddr_in cli_addr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cli_addr);
    int connfd = -1;
    do {
        // 处理accept
        connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &cliaddrlen);
    } while(connfd == -1 && errno == EINTR);

    if (connfd == -1) {
        printf("accept error!\n");
        return -1;
    }

    // 打印新连接的客户端的ip和port
    printf("accept a new client: ip = %s, port = %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    // 将新的连接描述符添加到数组中, 并更新已连接的客户端个数
    int i = 0;
    for (; i < MAX_CLIENT_SIZE; ++i) {
        if (s_srv_ctx->clifds[i] < 0) {
            s_srv_ctx->clifds[i] = connfd;
            ++s_srv_ctx->cli_cnt;
            break;
        }
    }

    if (i == MAX_CLIENT_SIZE) {
        printf("too many clients!\n");
        return -1;
    }

    // 把新的连接放入集合中
    FD_SET(connfd, &s_srv_ctx->allfds);
    // 更新maxfd，维护最大描述符
    if (connfd > s_srv_ctx->maxfd) {
        s_srv_ctx->maxfd = connfd;
    }

    *nready = *nready - 1;
    if (*nready <= 0) {
        return 0;
    }

    return 0;
}

static int handle_client_msg(int fd, char* buf)
{
    if (!buf) {
        return -1;
    }
    printf("recv buf: %s\n", buf);
    write(fd, buf, strlen(buf)+1);
    return 0;
}

static int recv_client_msg(fd_set* readfds, int* nready)
{
    int clifd;
    char buf[MAX_BUF_SIZE] = {0};
    int cli_cnt = s_srv_ctx->cli_cnt;
    for (int i = 0; i < cli_cnt; ++i) {
        clifd = s_srv_ctx->clifds[i];
        if (clifd < 0) {
            continue;
        }
        // 检测已连接的套接字conn是否可读
        if (FD_ISSET(clifd, readfds)) {
            // 接收客户端发送的数据
            memset(buf, 0, sizeof(buf));
            int n = read(clifd, buf, MAX_BUF_SIZE);
            // n == 0表示读取完成, 客户端关闭了套接字
            if (n == 0) {
                close(clifd);
                // 若对方已退出，则从集合中清除
                FD_CLR(clifd, &s_srv_ctx->allfds);
                // 保存连接的数组，也置成-1, 并更新已连接客户端个数
                s_srv_ctx->clifds[i] = -1;
                --s_srv_ctx->cli_cnt;
                continue;
            }
            handle_client_msg(clifd, buf);

            *nready = *nready - 1;
            if (*nready <= 0) {
                break;
            }
        }
    }
    return 0;
}

static int handle_client_proc(int listenfd)
{
    int connfd = -1;
    int nready = 0;

    // 添加监听套接字
    FD_SET(listenfd, &s_srv_ctx->allfds);

    s_srv_ctx->maxfd = listenfd;

    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    while(1) {
        // 每次调用select前都要重新设置文件描述符和超时时间，因为事件发生后，文件描述符和时间都被内核修改了
        s_srv_ctx->readfds = s_srv_ctx->allfds;
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        // 开始轮询接收处理服务端和客户端套接字
        // On success, select() return the number of file descriptors contained in the three returned descriptor sets.
        nready = select(s_srv_ctx->maxfd + 1, &s_srv_ctx->readfds, NULL, NULL, &tv);
        if (nready == -1) {
            if (errno == EINTR) {
                continue;
            }
            printf("select error!\n");
            return nready;
        }
        if (nready == 0) {
            printf("select timeout...\n");
            continue;
        }
        // 若侦听套接口产生可读事件，说明三次握手已完成，有客户端已经连接建立
        if (FD_ISSET(listenfd, &s_srv_ctx->readfds)) {
            // 监听客户端请求
            accept_client_proc(listenfd, &nready);
        }
        // 检测已连接的套接字conn是否可读
        else {
            // 接收并处理客户端消息
            recv_client_msg(&s_srv_ctx->readfds, &nready);
        }
    }
}

static int server_release()
{
    if (s_srv_ctx) {
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
    return 0;
}

static int server_init()
{
    if (MAX_CLIENT_SIZE > FD_SETSIZE) {
        printf("server_init failed: client size > FD_SETSIZE!\n");
    }
    s_srv_ctx = (server_context_st*)malloc(sizeof(server_context_st));
    if (s_srv_ctx == NULL) {
        return -1;
    }
    memset(s_srv_ctx, 0, sizeof(server_context_st));
    for (int i = 0; i < MAX_CLIENT_SIZE; ++i) {
        s_srv_ctx->clifds[i] = -1;
    }
    return 0;
}


int main()
{
    int listenfd;
    int ret;
    // 初始化服务端context
    ret = server_init();
    if (ret < 0) {
        server_release();
        return ret;
    }

    // 创建服务, 开始监听客户端请求
    ret = create_server_proc(IPADDR, PORT, &listenfd);
    if (ret < 0) {
        server_release();
        return ret;
    }
    // 开始接受并处理客户端的请求
    handle_client_proc(listenfd);

    server_release();

    return ret;
}