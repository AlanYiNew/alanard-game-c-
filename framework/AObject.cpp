#include "AObject.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>               // std::runtime_error
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"


AObject::AObject()
{
    std::ifstream ifs("filename.json");
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document document;
    document.ParseStream(isw);
    printf("message = %s\n", document["message"].GetString()); 
}

AObject::AObject(const char* filename)
{
    std::ifstream ifs(filename);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document document;
   
    document.ParseStream(isw);
    if (document.HasParseError())
    {
        throw std::runtime_error("Parse Error");
    }

    printf("message = %s\n", document["message"].GetString()); 
}


int main(int argc, char *argv[])
{
    try 
    {
        AObject objAObj("11.json");
    }   
    catch (std::exception const &ex)
    {
        std::cout << "what:" << ex.what() << std::endl;
    }
   

}
