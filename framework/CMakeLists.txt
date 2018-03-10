#header file path  
INCLUDE_DIRECTORIES("network/include")  
INCLUDE_DIRECTORIES("third_party_lib/boost/property_tree/include")  

#source directory  
AUX_SOURCE_DIRECTORY(. DIR_SRCS)  
#set environment variable  
SET(TEST_MATH  
${DIR_SRCS}  
)  
#set extern libraries  
SET(LIBRARIES  
libm.so  
)  

