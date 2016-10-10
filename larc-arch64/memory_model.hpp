#ifndef _LARC_ARCH64_MEMORY_MODEL_HPP
#define _LARC_ARCH64_MEMORY_MODEL_HPP
#include "../larc-include/larctype.hpp"


class memory_model {
    int32_t special [32];
    int32_t common  [32];
    size64_t ram_size;
    char * ram;


public:

    memory_model  ();
    memory_model  (size64_t new_ram_size);
    memory_model  (const memory_model&);
    ~memory_model ();

    size64_t size () { return ram_size; }
    char& operator [] (uint64_t index);
    char* seq_read (uint64_t index, size64_t len);

    int32_t get_reg (byte index); // firstly special then common





};

memory_model :: memory_model ():
    special  ( {} ),
    common   ( {} ),
    ram_size ( 8192 ),
    ram      ( new char [ram_size] )
    {}

memory_model :: memory_model (size64_t new_ram_size):
    special  ( {} ),
    common   ( {} ),
    ram_size ( new_ram_size ),
    ram      ( new char [ram_size] )
    {}

memory_model :: memory_model (const memory_model& obj):
    special  ( obj.special ),
    common   ( obj.common ),
    ram_size ( obj.ram_size ),
    ram      ( new char [ram_size] )
{
    for (size64_t i = 0; i < ram_size; i++)
        ram [i] = obj.ram [i];
}

memory_model :: ~memory_model () {
    delete [] ram;
}

char& memory_model :: operator [] (uint64_t index) {
    if (index > ram_size)
        throw OverflowError;
    else
        return ram [index];
}

char * memory_model :: seq_read (uint64_t index, size64_t len) {
    if (index > ram_size)
        throw OverflowError;
    else if (index + len > ram_size)
        throw OverflowError;
    else if (len > ram_size)
        throw OverflowError;

    else
        return &(ram [index]);
}

int32_t memory_model :: get_reg (byte index) {
    if (index > 64)
        throw RegisterAccessError;
    else {
        if (index < 32) 
            return special [index];
        else
            return common  [index];
    }
}


#endif // _LARC_ARCH64_MEMORY_MODEL_HPP


