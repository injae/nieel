#include <iostream>
#include <nieel/version.h>
#include <nieel/program_option.h>
#include <nieel/filesystem.h>

unsigned char get_bit(unsigned char bit, int pos) { return ((bit >> (pos - 1)) & 1); }

int main()
{
    unsigned char bit8 = 5;
    for(int i = 8; i > 0; --i) printf("%d", get_bit(bit8, i));

    return 0; 
}
