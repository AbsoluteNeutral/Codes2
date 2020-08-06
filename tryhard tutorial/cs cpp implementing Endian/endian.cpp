
#include "endian.h"

namespace zg{
    enum _ENDIAN_BYTE
    {
        BYTE1 = 0x00000000000000FF,   
        BYTE2 = 0x000000000000FF00,   
        BYTE3 = 0x0000000000FF0000,   
        BYTE4 = 0x00000000FF000000,

        BYTE5 = 0x000000FF00000000,   
        BYTE6 = 0x0000FF0000000000,   
        BYTE7 = 0x00FF000000000000,   
        BYTE8 = 0xFF00000000000000
    };

    
    bool IsLittleEndian()
    {
      /*
      Little Endian
      -> casting starts here memory : low  0x01
                          in memory :      0x00
                          in memory :      0x00
                          in memory : high 0x00
      Big Endian
      -> casting starts here memory : low  0x00
                          in memory :      0x00
                          in memory :      0x00
                          in memory : high 0x01
      */
      int a = 1; //0x00000001 (store in memory of 4 bytes)
      return *reinterpret_cast<char*>(&a) == 1;
    }

    //flip 32 bit
    unsigned FlipEndian(unsigned number)
    {
        unsigned tmp = 0;
        tmp |= (number & BYTE4) >> 24;
        tmp |= (number & BYTE3) >> 8;
        tmp |= (number & BYTE2) << 8;
        tmp |= (number & BYTE1) << 24;
        return tmp;
    }
    int FlipEndian  (int number)
    {
        unsigned tmp = FlipEndian(*reinterpret_cast<unsigned *>(&number));
        return *reinterpret_cast<int *>(&tmp); 
    }
    float FlipEndian  (float number)
    {
        unsigned tmp = FlipEndian(*reinterpret_cast<unsigned *>(&number));
        return *reinterpret_cast<float *>(&tmp); 
    }

    //flip 64 bit
    unsigned long   FlipEndian  (unsigned long number)
    {
        unsigned long tmp = 0;
        tmp |= (number & BYTE8) >> 56;
        tmp |= (number & BYTE7) >> 40;
        tmp |= (number & BYTE6) >> 24;
        tmp |= (number & BYTE5) >> 8;
        tmp |= (number & BYTE4) << 8;
        tmp |= (number & BYTE3) << 24;
        tmp |= (number & BYTE2) << 40;
        tmp |= (number & BYTE1) << 56;
        return tmp;
    }
    long FlipEndian  (long number)
    {
        unsigned long tmp = FlipEndian(*reinterpret_cast<unsigned long *>(&number));
        return *reinterpret_cast<long *>(&tmp); 
    }
    double FlipEndian  (double number)
    {
        unsigned long tmp = FlipEndian(*reinterpret_cast<unsigned long *>(&number));
        return *reinterpret_cast<double *>(&tmp); 
    }
} //namespace zg
