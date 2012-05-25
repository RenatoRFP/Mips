#ifndef __MEMORY_H__
#define __MEMORY_H__
#define MEM_SIZE  1024
class Memory
{
public:
        unsigned long int read(unsigned long int address);

        void write(unsigned long int address, unsigned long int data);

    private:
        unsigned long int m_array[MEM_SIZE];
};
#endif
