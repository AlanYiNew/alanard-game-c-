#include "ALConfig.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>               // std::runtime_error
#include <AErr.hpp>


ALConfig::ALConfig()
{
    std::ifstream ifs("filename.json");
    ifs >> objJsonConfig;
    std::cout << objJsonConfig.dump() << std::endl;
}

ALConfig::ALConfig(const char* filename)
{
    std::ifstream ifs(filename);
    ifs >> objJsonConfig;    
}


