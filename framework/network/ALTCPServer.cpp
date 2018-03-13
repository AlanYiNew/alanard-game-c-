#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <network/ALTCPServer.hpp>
#include <algorithm>
#include <fcntl.h>

#define MAX_BUFFER_SIZE 4096
using namespace ::std;



ALTCPServer::ALTCPServer()
{

    /** set protocol family ipv4 **/
    _st_serv_addr.sin_family = AF_INET;

    /** set address accepting any in_addr using host to network address 
    transalation **/
    _st_serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    /** deafult value **/
    _i_pending_num = 100;
    _i_port = 12000;

    _st_serv_addr.sin_port = htons(this->_i_port);

}

void ALTCPServer::set_port(uint16_t _i_port)
{
    this->_i_port = _i_port;

    /** set input port **/
    _st_serv_addr.sin_port = htons(this->_i_port);
}

void ALTCPServer::set_pending_num(int _i_pending_num)
{
    _i_pending_num = _i_pending_num;
}


int ALTCPServer::starts() {
    /** create a socket **/
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    int err = bind(listenfd, (sockaddr*)&_st_serv_addr, sizeof(sockaddr_in));
    err = listen(listenfd, _i_pending_num);
    socklen_t len = sizeof(sockaddr_in);

    /** creates epollfd **/
    if ((_i_epoll_fd = epoll_create(EPOLL_CLOEXEC)) < 0)
        throw runtime_error("error in creating epoll fd");

    /** add listenfd **/
    err = epoll_add(listenfd);

    while (true) {
        /** wait on the events list and never timeout
          * kind of like blokcing on all events **/
        int nready = epoll_wait(_i_epoll_fd, _ast_events, _i_pending_num, -1);

        for (int i = 0; i < nready; i++) {
            if (_ast_events[i].data.fd == listenfd) {
                int connfd = accept(listenfd, (struct sockaddr *) &_st_serv_addr, &len);
                if (fcntl(connfd, F_SETFL, fcntl(connfd, F_GETFL) | O_NONBLOCK) < 0)
                {
                    //Put log here to indicate fail to put connfd into non-blocking mode TODO
                    shutdown(connfd, SHUT_RDWR);
                    close(connfd);
                }   else{
                    epoll_add(connfd);
                    onAcceptConnection(connfd);
                }
            }
            else if (_ast_events[i].events & EPOLLIN) 
            {
                handle(i);  
            }

        }
    }

    return 0;
}

void ALTCPServer::handle(int i)
{
    int readsize = 0;

    while ((readsize = recv(_ast_events[i].data.fd,  getBuffer(), getBufferSize(), MSG_WAITALL)) && readsize > 0)
    {
        bool cont = onRead(_ast_events[i].data.fd, readsize);
        if (!cont) break;
    }   
   
    if (readsize == 0)
    {
        shutdown(_ast_events[i].data.fd, SHUT_RDWR);
        close(_ast_events[i].data.fd);
        epoll_del(_ast_events[i].data.fd);
        onShutDownConnection(_ast_events[i].data.fd);
    }   
    else if (readsize == EAGAIN)
    {
        onRead(_ast_events[i].data.fd, EAGAIN);
    }  
    else if (readsize)
    {
        throw std::runtime_error("error during reading packet header from socket");
    }
 
}

void ALTCPServer::sendResponse(int fd,const char* buff,unsigned int size)
{
   send(fd,buff,size, 0);
}

ALTCPServer::~ALTCPServer() 
{

}

int ALTCPServer::epoll_del(int fd) 
{
    return epoll_ctl(_i_epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
}

int ALTCPServer::epoll_add(int fd) 
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    return epoll_ctl(_i_epoll_fd, EPOLL_CTL_ADD, fd, &event);
}
