#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<sys/epoll.h>
#include<vector>
//
// Created by alan on 9/17/17.
//

#ifndef __TCPSERVER_H_
#define __TCPSERVER_H_
class ALTCPServer{
    enum ConnectionType{
        CONNECTION_NORMAL,
        CONNECTION_WS
    };


    private : 
        uint16_t _i_port;
        sockaddr_in _st_serv_addr;
        epoll_event _ast_events[65535];
        int _i_epoll_fd;
        int _i_pending_num;
        ConnectionType _e_conn_mode;   

        int epoll_add(int fd);
        int epoll_del(int fd);

        void handle_normal(int i);
        void handle_ws(int i);

    public :
        struct header_t{
            int cmd;
            unsigned int size;
        };
        
        /** TCPServer class constructor **/
        ALTCPServer();
        ~ALTCPServer();

        /** Param configuration **/
        void set_port(uint16_t _i_port);
        void set_pending_num(int _i_pending_num);
        
        /** starts the TCPServer **/
        int starts();


        /** pure event driven virtual function **/
        virtual void onShutDownConnection(int fd)=0;
        virtual void onRead(int fd, const header_t * header, const char * buff , int readsize)=0;
        virtual void onAcceptConnection(int fd)= 0;
 
};

#endif //__TCPSERVER_H_
