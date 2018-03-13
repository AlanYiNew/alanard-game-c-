#include <network/ALWSHandler.hpp>
#include <sstream>


int ALWSHandler::fetch_http_info(char * _buff, int readsize)
{
    std::stringstream s;
    s.write(_buff,readsize);
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
            _header_map[key] = value;
        }
    }

    return 0;
}


std::string ALWSHandler::process(char *buff, int readsize)
{
    return "";
}

std::string ALWSHandler::establish(char *buff, int readsize)
{
    fetch_http_info(buff, readsize);
    _e_alws_state = ALWS_STATE_BUSY;
    std::string SHA1 = "123";
    return SHA1;
}


