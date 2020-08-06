
#ifndef _ZG_BITSET_H_
#define _ZG_BITSET_H_

#include <stdio.h>
#include <string>

namespace zg
{
    //an static arry to grab hex value
    static const char HexChar[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    // ########## this class print Binary, with different number of bits (N) ##########
    template<unsigned N>
    class Bitset
    {

    public:
    	template<typename T>
    	Bitset(T number_)
    		:binarystring{}
    	{
    		int maxsize = sizeof(T) * 8;
    		int getmin = N <= maxsize ? N : maxsize;

    		unsigned long castNumber = *reinterpret_cast<unsigned long*>(&number_);

    		int i = 0;
        	for(; i < getmin; ++i)
        	{
        	    binarystring[N - i - 1] = HexChar[ (castNumber >> i) & 1 ];
        	}
        	int j = getmin;
        	for(; j < N; ++j)
        	{
        	    binarystring[N - j - 1] = HexChar[0];
        	}
    		binarystring[N] = '\0';
    	}

    	std::string GetBinaryString() const
    	{
    		return std::string{ binarystring };
    	}

    	friend std::ostream& operator<<(std::ostream& os, const Bitset& b_)
    	{
			printf("%s ", b_.binarystring);
			return os;
    	}

	private:
    	char binarystring[N + 1];
    };

    // custom class
    // ########## this class prints all 3 mode, BIN, OCT, HEX ##########
    template<unsigned N>
    class TriBitset
    {
      
    public:
    	template<typename T>
    	TriBitset(T number_)
    		:binarystring{}
    	{
    		unsigned long castNumber = *reinterpret_cast<unsigned long *>(&number_);

    		int maxsize = sizeof(T) * 8;
    		int getmin  = N <= maxsize ? N : maxsize;
        	for(int i = 0; i < getmin; ++i)
        	{
        	    binarystring[N - i - 1] = HexChar[ (castNumber >> i) & 1 ];
        	}
        	for(int j = getmin; j < N; ++j)
        	{
        	    binarystring[N - j - 1] = HexChar[0];
        	}
    		binarystring[N] = '\0';

    		//Oct
    		int NumberOfOct = (N / 3) + ((N % 3) ? 1 : 0);; //round up
    		int getminOct = NumberOfOct <= 21 ? NumberOfOct : 21;
    		char tmpO[NumberOfOct + 1];
        	for(int i = 0; i < getminOct; ++i)
        	{
        	    tmpO[NumberOfOct - i - 1] = HexChar[ (castNumber >> (i * 3)) & 0x7 ];
        	}
        	for(int j = getminOct; j < N; ++j)
        	{
        	    tmpO[NumberOfOct - j - 1] = HexChar[0];
        	}
        	tmpO[NumberOfOct] = '\0';
        	octstring = tmpO;

        	//Hex
    		int NumberOfHex = (N >> 2) + ((N % 4) ? 1 : 0); //round up
    		int getminHex = 16 <= NumberOfHex ? 16 : NumberOfHex;
    		char tmpH[NumberOfHex + 1];
        	for(int i = 0; i < getminHex; ++i)
        	{
        	    tmpH[NumberOfHex - i - 1] = HexChar[ (castNumber >> (i * 4)) & 0xF ];
        	}
        	for(int j = getminHex; j < N; ++j)
        	{
        	    tmpH[NumberOfHex - j - 1] = HexChar[0];
        	}
        	tmpH[NumberOfHex] = '\0';
        	hexstring = tmpH;
    	}

    	std::string GetBinaryString() const
    	{
    		return std::string{ binarystring };
    	}

    	std::string GetOctString() const
    	{
    		return octstring;
    	}

    	std::string GetHexString() const
    	{
    		return hexstring;
    	}

    	friend std::ostream& operator<<(std::ostream& os, const TriBitset& b_)
    	{
        printf("%s\n", b_.binarystring);
        printf("%s\n", b_.octstring.c_str());
        printf("0x%s", b_.hexstring.c_str());
        return os;
    	}

	private:
    	char binarystring[N + 1];
    	std::string octstring;
    	std::string hexstring;
    };

    // convert any base to Base 10 value
    // T determin the output type 
    template<typename T>
    T ConvertToDecimal(const char* string_, size_t length)
    {
        unsigned long tmp = 0;
        unsigned long bit = 1;
   
        for(size_t i = length; i > 0; --i)
        {
            tmp |= (string_[i - 1] == '1') ? (bit << (length - i)) : 0;
        }

        return *reinterpret_cast<T *>(&tmp);
    }
    template<typename T>
    T ConvertToDecimal(const std::string& binarystring)
    {
        return ConvertToDecimal<T>(binarystring.c_str(), binarystring.size());
    }
    
    void Print_BuiltInTypeSize();

    std::string ConvertToBinary	(unsigned number_);
    std::string ConvertToBinary	(int number_);
    std::string ConvertToBinary	(float number_);          
    std::string ConvertToBinary	(unsigned long number_);
    std::string ConvertToBinary	(long number_);
    std::string ConvertToBinary	(double number_);         

    std::string ConvertToOct	(unsigned number_);
    std::string ConvertToOct	(int number_);
    std::string ConvertToOct	(float number_);            //not needed
    std::string ConvertToOct	(unsigned long number_);
    std::string ConvertToOct	(long number_);
    std::string ConvertToOct	(double number_);           //not needed

    std::string ConvertToHex	(unsigned number_);
    std::string ConvertToHex	(int number_);
    std::string ConvertToHex	(float number_);
    std::string ConvertToHex	(unsigned long number_);
    std::string ConvertToHex	(long number_);
    std::string ConvertToHex	(double number_);
    
    std::string ConvertToBase(unsigned base, unsigned long number);
    std::string ConvertToBase(unsigned base, unsigned number);
    std::string ConvertToBase(unsigned base, int number);
    std::string ConvertToBase(unsigned base, float number);         //not needed
    std::string ConvertToBase(unsigned base, long number);
    std::string ConvertToBase(unsigned base, double number);        //not needed
}

#endif //_ZG_BITSET_H_
