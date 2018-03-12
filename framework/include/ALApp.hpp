#include <ALConfig.hpp>
#include <network/ALTCPServer.hpp>

class ALApp : public ALConfig, public ALTCPServer{
    public:
        ALApp() = default;
        ALApp(const char* fileName);        
        virtual void onShutDownConnection(int fd);
        virtual void onRead(int fd, const header_t * header, const char * buff , int readsize);
        virtual void onAcceptConnection(int fd);
    private:
        
};
