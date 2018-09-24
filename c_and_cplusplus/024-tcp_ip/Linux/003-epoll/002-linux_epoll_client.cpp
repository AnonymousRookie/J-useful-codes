/************************************************************************
* CREATED TIME: 2018-9-24 17:29:12
* LAST MODIFIED TIME: 2018-9-24 17:29:12
* DESCRIPTION: linux epoll client (just for practice)
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
#include <sys/epoll.h>

#define MAXSIZE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8001
#define FDSIZE 1024
#define EPOLLEVENTS 20
#define TIMEOUT   5000

static void handle_connection(int sockfd);

// 事件处理
static void handle_events(int epollfd, struct epoll_event* events, int num, int sockfd, char* buf);

// 处理读事件
static void do_read(int epollfd, int fd, int sockfd, char* buf);

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
    int sockfd;
    int ret;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);

    ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret == -1) {
        printf("connect error: %d\n", errno);
        close(sockfd);
        return ret;
    }

    handle_connection(sockfd);
    close(sockfd);

    return 0;
}

static void handle_connection(int sockfd)
{
    int ret;
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];

    epollfd = epoll_create(FDSIZE);
    add_event(epollfd, STDIN_FILENO, EPOLLIN);
    for (;;) {
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, TIMEOUT);
        if (ret == 0) {
            printf("epoll timeout...\n");
            continue;
        }
        handle_events(epollfd, events, ret, sockfd, buf);
    }
    close(epollfd);
}


// 事件处理
static void handle_events(int epollfd, struct epoll_event* events, int num, int sockfd, char* buf)
{
    int fd;
    for (int i = 0; i < num; ++i) {
        fd = events[i].data.fd;
        // 根据描述符的类型和事件类型进行处理
        if (events[i].events & EPOLLIN) {        //接收到数据，读socket
            do_read(epollfd, fd, sockfd, buf);
        }
        else if (events[i].events & EPOLLOUT) {  //有数据待发送，写socket
            do_write(epollfd, fd, buf);
        }
    }
}

// 处理读事件
static void do_read(int epollfd, int fd, int sockfd, char* buf)
{
    int nread = read(fd, buf, MAXSIZE);
    if (nread == -1) {
        perror("read error!");
        close(fd);
    }
    else if (nread == 0) {
        fprintf(stderr, "server closed!\n");
        close(fd);
    }
    else {
        if (fd == STDIN_FILENO) {
            add_event(epollfd, sockfd, EPOLLOUT);
        }
        else {
            delete_event(epollfd, sockfd, EPOLLIN);
        }
        add_event(epollfd, STDOUT_FILENO, EPOLLOUT);
    }
}

// 处理写事件
static void do_write(int epollfd, int fd, char* buf)
{
    int nwrite = write(fd, buf, strlen(buf));
    if (nwrite == -1) {
        perror("write error!");
        close(fd);
    }
    else {
        if (fd == STDOUT_FILENO) {
            delete_event(epollfd, fd, EPOLLOUT);
        }
        else {
            modify_event(epollfd, fd, EPOLLIN);
        }
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
