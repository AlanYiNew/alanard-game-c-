cmake_minimum_required(VERSION 3.5)


#header file path  
MESSAGE("${CMAKE_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

#source directory  
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)  



ADD_EXECUTABLE(me ${DIR_SRCS})
#set environment variable  
#SET(TEST_MATH  
#${DIR_SRCS}  
#)  

#set extern libraries  
#SET(LIBRARIES  
#libm.so  
#)  

