#define CHECK_PARAM_RET(v, r) \                                                                                                                                         do { \
    if (!(v)) \
    { \
        return r; \
    }\
}   while(0);  
