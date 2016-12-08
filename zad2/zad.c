#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int charToHex(char x){
    if(x>='0' && x<='9')return x-'0';
    if(x>='a')return x-'a'+10;
}
 
int calcDiff(char x, char y){
    x=charToHex(x);
    y=charToHex(y);
    char bin1[] = {0,0,0,0,0,0,0,0}, bin2[]={0,0,0,0,0,0,0,0};
    int ctr=0;
    while(x!=0){
        bin1[ctr]=x%2;
        x/=2;
        ctr++;
    }
    ctr=0;
    while(y!=0){
        bin2[ctr]=y%2;
        y/=2;
        ctr++;
    }
    int i = 0;
    int retVal=0;
    for(i; i < 8; i++){
        if(bin1[i]!=bin2[i])
            retVal++;
    }
    return retVal;
}
 
int main(void)
{
    char napis1[] = "ce0d535d2691f9ddd3393b8d6566322e574e97c6b996f64dc1fa6b568542323866e6ffc9badd0322fa1e1647af70ffdb12f6a4d361eff834d7f1cf2f6453c1d8";
    char napis2[] = "46ba32946b387cfd552c1b973c88cb8a391fb884d1330216427f5642ed795443356e0d1cd045562594c38709321f72594128ecc7a2aaa933561852b87f238f90";
    //calcDiff('A', 'B');
    int length =  strlen(napis1);
    printf("length:%d\n", length);
    if (napis1 == napis2)
        printf("Oba ciagi sa takie same");
    else {
        int roznica = 0;
        int i = 0;
        for (i; i < length; i++) {
            roznica += calcDiff(napis1[i], napis2[i]);
        }
	float result = roznica * 100 / (length*4.0);
        printf("Liczba bitow różnicująca wyniki: %d tj. %0.2f %% z %d\n", roznica, result, length*4);
    }
 
    return 0;
}
