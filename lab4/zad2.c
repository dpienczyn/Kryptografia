#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
    char napis1[100] = "e83e129a4bf98394ebb230e8c0ca3c190473df45550c0d1c10eed8ea";
    char napis2[100] = "d3ee2ff3860810093c016266108760f29bcd7ebb2ad4436e94ee8343";
    (int)strlen(napis1);
    if (napis1 == napis2)
        printf("Oba ciagi sa takie same");
    else {
        int roznica = 0;
        for (int i = 0; i < 56; i++) {
            if (napis1[i] != napis2[i]) {
                ++roznica;
            }
        }
	float result = roznica * 100 / strlen(napis1);
        printf("Liczba rozniacych się bitow z %ld to %d, %0.2f %%\n", strlen(napis1), roznica, result);
        
    }
 
    return 0;
}
