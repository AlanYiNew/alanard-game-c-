#include <string>
#include <nlohmann/json.hpp>
#include <iostream>

class ALConfig
{
    public:
        ALConfig(const char* fileName);        
        ALConfig();
        template<typename T>
        T getConfigParam(const char* path);
      
    private:
        nlohmann::json objJsonConfig;    

};


template<typename T>
T ALConfig::getConfigParam(const char* path)
{
    auto memberJson = objJsonConfig;
    
    int s = 0, e = 0;
    for (int i = 0; ; ++i)
    {
        if (path[i] == '.' || path[i] == '\0')
        {
            if (path[i] == '.' && path[i] == '\0')
                throw ("Invalid path"); 
            else
            {
                e = i;
                std::string member(&path[s], &path[e]);
                s = i + 1;                
                memberJson = memberJson[member];
                if (path[i] == '\0')
                    break;
            }
        }

    }
    try
    {
        auto result = memberJson.get<T>();
    }   
    catch (std::exception &ex)
    {
        throw std::runtime_error("Invalid query type");
    }

    return memberJson.get<T>();
}
