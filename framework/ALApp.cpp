#include <ALApp.hpp>

ALApp::ALApp(const char * fileName) : ALConfig(fileName) 
{
    
};

void ALApp::onShutDownConnection(int fd)
{
    std::cout << "onShutDown" << std::endl;
};

void ALApp::onRead(int fd, const header_t * header, const char * buff , int readsize)
{
    std::cout << "onRead" << std::endl;
};

void ALApp::onAcceptConnection(int fd)
{
    std::cout << "onAcception Conneciton" << std::endl;
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
