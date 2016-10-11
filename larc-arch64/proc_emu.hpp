#ifndef _LARC_ARCH64_PROC_EMU_HPP
#define _LARC_ARCH64_PROC_EMU_HPP
#include "memory_model.hpp"



class emu {
    int32_t special [32];
    int32_t common  [32];
    char* cache;
    size64_t cache_size;

public:

    emu  ();
    emu  (size64_t new_cache_size);
    emu  (const emu& obj);
    ~emu ();

    run (memory_model mem);



};



#endif // _LARC_ARCH64_PROC_EMU_HPP