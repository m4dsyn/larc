#ifndef _LARC_ARCH64_MEMORY_MODEL_HPP
#define _LARC_ARCH64_MEMORY_MODEL_HPP
#include "../larc-include/larctype.hpp"
#include "vm_config.hpp"

class memory_model {
    size64_t ram_size;
    char * ram;


public:

    memory_model   ();
    memory_model   (size64_t new_ram_size);
    memory_model   (const memory_model&);
    ~memory_model  ();

    size64_t size  () { return ram_size; }
    char& operator [] (uint64_t index);
    char* seq_read (uint64_t index, size64_t len);

    void seq_write (uint64_t offset, char* buff, uint64_t len);



};

memory_model :: memory_model ():
    ram_size ( mem_config::ram_size ),
    ram      ( new char [ram_size] )
    {}

memory_model :: memory_model (size64_t new_ram_size):
    ram_size ( new_ram_size ),
    ram      ( new char [ram_size] )
    {}

memory_model :: memory_model (const memory_model& obj):
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

void memory_model :: seq_write (uint64_t offset, char* buff, uint64_t len) {
    if (offset > ram_size || 
        len > ram_size || 
        offset + len > ram_size || 
        offset + len < offset)
            throw OverflowError;

    for (uint64_t i = offset; i < len + offset; i++)
        ram [i] = buff [i];
}

#endif // _LARC_ARCH64_MEMORY_MODEL_HPP



