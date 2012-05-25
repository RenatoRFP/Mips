#include "stdafx.h"
#include "Memory.h"

unsigned long int Memory::read(unsigned long int address)
{
    return m_array[address];
}

void Memory::write( unsigned long int address,unsigned long int data)
{
    m_array[address] = data;
}
