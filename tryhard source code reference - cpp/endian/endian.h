
#ifndef _ZG_ENDIAN_H_
#define _ZG_ENDIAN_H_


namespace zg
{
    bool IsLittleEndian();

    unsigned    FlipEndian  (unsigned number);
    int         FlipEndian  (int number);
    float       FlipEndian  (float number);

    unsigned long   FlipEndian  (unsigned long number);
    long            FlipEndian  (long number);
    double          FlipEndian  (double number);
}

#endif //_ZG_ENDIAN_H_
