#include <unordered_map>
#include <string>
#include <memory>

struct ws_frame_t{
    

}

class ALWSHanlder
{
    public:
        enum ALWS_STATE {
            ALWS_STATE_IDLE,
            ALWS_STATE_BUSY,
        }        

        ALWS_STATE getALWSState();
        ALWSHandler(); 

        char** getBuff();
    private:
        ALWS_STATE _e_alws_state;
        std::unordered_map<std::string,std::string> _header_map;
        std::unique_ptr<char[]> _ac_buff;    



}
