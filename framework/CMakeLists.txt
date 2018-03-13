cmake_minimum_required(VERSION 3.5)


#header file path  
MESSAGE("${CMAKE_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

#Use CXX 14
set(CMAKE_CXX_STANDARD 14)

#source directory  
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)  
set (OTHER_SRCS network/ALTCPServer.cpp)

#AUX_SOURCE_DIRECTORY(./network NETWORK_SRCS)


ADD_EXECUTABLE(me ${DIR_SRCS} ${OTHER_SRCS})
#set environment variable  
#SET(TEST_MATH  
#${DIR_SRCS}  
#)  

#set extern libraries  
#SET(LIBRARIES  
#libm.so  
#)  

