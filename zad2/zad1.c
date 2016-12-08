#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NumberOfSetBits(int i)
{
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}


int CountDifferentBitsInBytes(const char *a, const char *b, int count)
{
    int result = 0;
    
    while (count--)
    {
        result += NumberOfSetBits(*a ^ *b);
        a++;
        b++;
    }
    return result;
}

int CountDifferentBitsInStrings(const char *a, const char *b)
{
    int lenA = strlen(a);
    int lenB = strlen(b);
    int minLen = lenA<lenB ? lenA : lenB;
    int maxLen = lenA<lenB ? lenB : lenA;
    
    return (maxLen - minLen) * 8 + CountDifferentBitsInBytes(a, b, minLen);
}

int main(void)
{
    char s1[0x100];
    char s2[0x100];
    
    while (gets(s1) && gets(s2)) {
        printf("%s - %s\n\tbits difrent: %d\n ", s1, s2, CountDifferentBitsInStrings(s1, s2));
    }
    return 0;
}
