#include <network/ALWSHandler.hpp>


ALWSHandler::ALWSHandler(unsigned int size):_buff(make_unique<char[]>(size)){}

int ALWSHandler::fetch_http_info()
{
    std::istringstream s(*_buff);
    std::string request;

    std::getline(s, request);
    if (request[request.size()-1] == '\r') 
    {
        request.erase(request.end()-1);
    }   else {
        return -1;
    }

    std::string header;
    std::string::size_type end;

    while (std::getline(s, header) && header != "\r") 
    {
        if (header[header.size()-1] != '\r') 
        {
            continue; //end
        } else {
            header.erase(header.end()-1);    //remove last char
        }

        end = header.find(": ",0);
        if (end != std::string::npos) 
        {
            std::string key = header.substr(0,end);
            std::string value = header.substr(end+2);
            _header_map_[key] = value;
        }
    }

    return 0;
}

ALWS_STATE ALWSHandler::getALWSState()
{
    return _e_alws_state;
}

char** ALWSHandler::getBuff()
{
    return _ac_buff.get();
}
