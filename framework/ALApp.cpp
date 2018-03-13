#include <ALApp.hpp>
ALApp::ALApp(const char * fileName) : 
    ALTCPServer(), 
    ALConfig(fileName), 
    _buff(std::make_unique<unsigned char[]>(getConfigParam<unsigned int>("buffer_size"))) 
{

};


ALApp::ALApp() : 
    ALConfig(), 
    ALTCPServer(), 
    _buff(std::make_unique<unsigned char[]>(getConfigParam<unsigned int>("buffer_size"))) 
{

};

void ALApp::onShutDownConnection(int fd) 
{
    std::cout << "onShutDown" << std::endl;
};

bool ALApp::onRead(int fd, int readsize) 
{
    std::cout << "onRead" << std::endl;
};

void ALApp::onAcceptConnection(int fd) 
{
    std::cout << "onAcception Conneciton" << std::endl;
}

unsigned int ALApp::getBufferSize() 
{
    return 1024;
}

unsigned char * ALApp::getBuffer() 
{
    return _buff.get();
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
