
#ifndef _ZG_ENDIAN_H_
#define _ZG_ENDIAN_H_

namespace zg
{
    //check if is endian
    bool IsLittleEndian();

    //flip 32 bit
    unsigned        FlipEndian  (unsigned number);
    int             FlipEndian  (int number);
    float           FlipEndian  (float number);
    
    //flip 64 bit
    unsigned long   FlipEndian  (unsigned long number);
    long            FlipEndian  (long number);
    double          FlipEndian  (double number);
}

#endif //_ZG_ENDIAN_H_
