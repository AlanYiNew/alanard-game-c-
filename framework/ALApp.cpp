#include <ALApp.hpp>
ALApp::ALApp(const char * fileName) : 
    ALTCPServer(), 
    ALConfig(fileName), 
    _buff(std::make_unique<char[]>(getConfigParam<unsigned int>("buffer_size"))) 
{

};


ALApp::ALApp() : 
    ALConfig(), 
    ALTCPServer(), 
    _buff(std::make_unique<char[]>(getConfigParam<unsigned int>("buffer_size"))) 
{

};

/** public event driven function **/
void ALApp::onShutDownConnection(int fd) 
{
    std::cout << "onShutDown" << std::endl;
};

bool ALApp::onRead(int fd, int readsize) 
{
    std::cout << "onRead " << readsize << std::endl;
    switch (_e_conn_mode)
    {
        //NORMAL
        case AL_CONNECTION_TYPE_NORMAL:
        {
            return true; 
        };
        break;

        //WS
        case AL_CONNECTION_TYPE_WS:
        {
            if (_ws_handler.getALWSState() == ALWSHandler::ALWS_STATE_IDLE)
            {
                if (readsize < 0)
                {       
                    std::string response = _ws_handler.establish(_buff.get(), readsize);
                    sendResponse(fd, response.c_str(), response.length()); 
                }
                return true;
            }   
            else 
            {   
                auto response = _ws_handler.process(_buff.get(), readsize);
                return response.length() == 0;
            }
                   
        };
        break;

        //default
        default:
            return true;
    }
};

void ALApp::onAcceptConnection(int fd) 
{
    std::cout << "onAcception Conneciton" << std::endl;
}

unsigned int ALApp::getBufferSize() 
{
    switch (_e_conn_mode)
    {
        case AL_CONNECTION_TYPE_NORMAL:
        {
            return 1024; 
        };
        break;
        case AL_CONNECTION_TYPE_WS:
        {
            return _buffer_size;
        };
        break;
        default:
            return 1024;
    }
}

char * ALApp::getBuffer() 
{
    return _buff.get();
}


/*private member function*/
int ALApp::init_buffer_size()
{
    switch (_e_conn_mode)
    {
        case AL_CONNECTION_TYPE_NORMAL:
        {
            return 1024;
        };
        break;
        case AL_CONNECTION_TYPE_WS:
        {
            return 1;
        }
        break;
        default:
            return 1024;        
    };
}

int main(int argc, char *argv[])
{
    try 
    {
        ALApp objALApp("filename.json");
        std:: cout << objALApp.getConfigParam<std::string>("message.try") << std::endl;
        objALApp.starts();
    }   
    catch (std::exception const &ex)
    {
        std::cout << "what:" << ex.what() << std::endl;
    }
}
