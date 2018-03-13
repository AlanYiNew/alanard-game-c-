#include <ALConfig.hpp>
#include <network/ALTCPServer.hpp>
#include <memory>

class ALApp : public ALConfig, public ALTCPServer{
    public:
        ALApp();
        ALApp(const char* fileName);        
        virtual void onShutDownConnection(int fd) override;
        virtual bool onRead(int fd, int readsize) override;
        virtual void onAcceptConnection(int fd) override;
        virtual unsigned char* getBuffer() override;
        virtual unsigned int getBufferSize() override;   
    private:
        std::unique_ptr<unsigned char[]> _buff;
};
