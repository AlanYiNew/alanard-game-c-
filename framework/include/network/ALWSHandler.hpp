#include <unordered_map>
#include <string>
#include <memory>

#define WS_FRAME_HEADER_SIZE 1024

//struct ws_frame_t{
    

//};

class ALWSHandler
{
    public:
        enum ALWS_STATE {
            ALWS_STATE_IDLE,
            ALWS_STATE_BUSY,
        };    

        ALWS_STATE getALWSState();


        std::string establish(char * buff, int readsize);
        std::string process(char * buff, int readsize);
    private:
        ALWS_STATE _e_alws_state;
        std::unordered_map<std::string,std::string> _header_map;
        unsigned int getFrameHeaderSize();

        //Websocke logic handle
        int fetch_http_info(char * _buff, int readsize); 
};

inline unsigned int ALWSHandler::getFrameHeaderSize()
{
    return WS_FRAME_HEADER_SIZE;
}

inline ALWSHandler::ALWS_STATE ALWSHandler::getALWSState()
{
    return _e_alws_state;
}
