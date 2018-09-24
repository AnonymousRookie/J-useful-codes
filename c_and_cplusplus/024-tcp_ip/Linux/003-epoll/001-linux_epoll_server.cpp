/************************************************************************
* CREATED TIME: 2018-9-24 16:44:34
* LAST MODIFIED TIME: 2018-9-24 16:44:34
* DESCRIPTION: linux epoll server (just for practice)
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
#include <sys/epoll.h>


#define IPADDRESS "127.0.0.1"
#define PORT 8001
#define MAXSIZE 1024
#define BACKLOG 5
#define FDSIZE 1000
#define EPOLLEVENTS 100
#define TIMEOUT   5000

// 创建套接字并进行绑定
static int socket_bind(const char* ip, int port);

// IO多路复用epoll
static void do_epoll(int listenfd);

// 事件处理
static void handle_events(int epollfd, struct epoll_event* events, int num, int listenfd, char* buf);

// 处理连接事件
static void handle_accept(int epollfd, int listenfd);

// 处理读事件
static void do_read(int epollfd, int fd, char* buf);

// 处理写事件
static void do_write(int epollfd, int fd, char* buf);

// 添加事件
static void add_event(int epollfd, int fd, int state);

// 修改事件
static void modify_event(int epollfd, int fd, int state);

// 删除事件
static void delete_event(int epollfd, int fd, int state);


int main()
{
    int listenfd;
    int ret;
    listenfd = socket_bind(IPADDRESS, PORT);
    ret = listen(listenfd, BACKLOG);
    if (ret == -1) {
        printf("listen error!\n");
        return ret;
    }
    do_epoll(listenfd);
    return 0;
}


// 创建套接字并进行绑定
static int socket_bind(const char* ip, int port)
{
    int ret;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket error!");
        exit(1);
    }

    // 一个端口释放后会等待两分钟之后才能再被使用, SO_REUSEADDR是让端口释放后立即就可以被再次使用
    int reuse = 1;
    ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (ret == -1) {
        perror("setsockopt error!");
        exit(1);
    }

    struct sockaddr_in servaddr;
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

// IO多路复用epoll
static void do_epoll(int listenfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    int ret;
    char buf[MAXSIZE];
    memset(buf, 0, sizeof(buf));

    // 创建一个描述符
    epollfd = epoll_create(FDSIZE);
    // 添加监听描述符事件
    add_event(epollfd, listenfd, EPOLLIN);
    for (;;) {
        // 获取已经准备好的描述符事件
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, TIMEOUT);
        if (ret == 0) {
            printf("epoll timeout...\n");
            continue;
        }
        handle_events(epollfd, events, ret, listenfd, buf);
    }
    close(epollfd);
}

// 事件处理
static void handle_events(int epollfd, struct epoll_event* events, int num, int listenfd, char* buf)
{
    int fd;
    for (int i = 0; i < num; ++i) {
        fd = events[i].data.fd;
        // 根据描述符的类型和事件类型进行处理
        if ((fd == listenfd) && (events[i].events & EPOLLIN)) {
            handle_accept(epollfd, listenfd);
        }
        else if (events[i].events & EPOLLIN) {
            do_read(epollfd, fd, buf);
        }
        else if (events[i].events & EPOLLOUT) {
            do_write(epollfd, fd, buf);
        }
    }
}

// 处理连接事件
static void handle_accept(int epollfd, int listenfd)
{
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    
    do {
        // 处理accept
        clifd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
    } while(clifd == -1 && errno == EINTR);

    if (clifd == -1) {
        perror("accept error!");
    }
    else {
        printf("accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        // 添加一个客户描述符和事件
        add_event(epollfd, clifd, EPOLLIN);
    }
}

// 处理读事件
static void do_read(int epollfd, int fd, char* buf)
{
    int nread = read(fd, buf, MAXSIZE);
    if (nread == -1) {
        perror("read error!");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    else if (nread == 0) {
        fprintf(stderr, "client closed!\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    else {
        printf("recv: %s\n", buf);
        // 修改描述符对应的事件, 读->写
        modify_event(epollfd, fd, EPOLLOUT);
    }
}

// 处理写事件
static void do_write(int epollfd, int fd, char* buf)
{
    int nwrite = write(fd, buf, strlen(buf));
    if (nwrite == -1) {
        perror("write error!");
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    }
    else {
        modify_event(epollfd, fd, EPOLLIN);
    }
    memset(buf, 0, MAXSIZE);
}

// 添加事件
static void add_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

// 修改事件
static void modify_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

// 删除事件
static void delete_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

