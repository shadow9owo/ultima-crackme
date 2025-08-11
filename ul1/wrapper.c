#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "wrapper.h"

unsigned long unixtimestamp()
{
    return (unsigned long)time(NULL);
}

int wraparound(int input, int min, int max)
{
    int range = max - min + 1;
    int _input = input;

    while (_input < min)
        _input += range;

    while (_input > max)
        _input -= range;

    return _input;
}


char* rotN(char* input, int diff)
{
    int i = 0;
    while (input[i] != '\0')
    {
        char c = input[i];
        if (c >= 'A' && c <= 'Z')
        {
            input[i] = (char)wraparound(c + diff, 'A', 'Z');
        }
        else if (c >= 'a' && c <= 'z')
        {
            input[i] = (char)wraparound(c + diff, 'a', 'z');
        }
        i++;
    }
    return input;
}

unsigned short fl_checksum(char* input)
{
    int len = 0;
    while (input[len] != '\0')
    {
        len = len + 1;
    }
    
    unsigned short sum1 = 0, sum2 = 0;
    for (int i =0;i < len;i++) {
        sum1 = (sum1 + (unsigned char)input[i]) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    return (sum2 << 8) | sum1;
}