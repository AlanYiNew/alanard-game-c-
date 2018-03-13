#include <ALConfig.hpp>
#include <network/ALTCPServer.hpp>
#include <network/ALWSHandler.hpp>
#include <memory>

class ALApp : public ALConfig, public ALTCPServer{

    public:
        enum AL_CONNECTION_TYPE
        {
            AL_CONNECTION_TYPE_NORMAL,
            AL_CONNECTION_TYPE_WS
        };

        ALApp();
        ALApp(const char* fileName);        
        virtual void onShutDownConnection(int fd) override;
        virtual bool onRead(int fd, int readsize) override;
        virtual void onAcceptConnection(int fd) override;
        virtual char* getBuffer() override;
        virtual unsigned int getBufferSize() override;   
    private:
        std::unique_ptr<char[]> _buff;
        AL_CONNECTION_TYPE _e_conn_mode;
        ALWSHandler _ws_handler;

        //Logic handling variable.
        unsigned int _buffer_size;
        int init_buffer_size();
};
