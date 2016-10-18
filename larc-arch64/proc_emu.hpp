#ifndef _LARC_ARCH64_PROC_EMU_HPP
#define _LARC_ARCH64_PROC_EMU_HPP
#include "memory_model.hpp"
#include "vm_config.hpp"

namespace proc {

class emu {
    int32_t special [32];
    int32_t common  [32];
    char* cache;


public:

    emu  ();
    emu  (const emu& obj);
    ~emu ();

    run (memory_model mem);



};


emu :: emu ():
    special ({}),
    common  ({}),
    cache (new char [emu_config::cache_size])
    {}

emu :: emu (const emu& obj):
    special (obj.special),
    common  (obj.common ),
    cache (new char [emu_config::cache_size])
{
    for (uint16_t i = 0; i < emu_config::cache_size; i++)
        cache [i] = obj.cache [i];
}

emu :: ~emu () {
    delete [] cache;
}

emu :: run (memory_model mem) {
    memcpy (cache, mem.seq_read (512), 512);
    
}

}; // proc

#endif // _LARC_ARCH64_PROC_EMU_HPP