#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define uchar unsigned char
 
uchar* readFile(long * fileSize, char * filename)
{
    uchar* buffer;
    FILE * f = fopen (filename, "rb");
    if (f)
    {
        //printf("cool\n");
        fseek (f, 0, SEEK_END);
        *fileSize = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (*fileSize+1);
        if (buffer)
        {
            fread (buffer, sizeof(uchar), *fileSize, f);
        }
        buffer[*fileSize]=0;
        fclose (f);
        return buffer;
    }
    return NULL;
}
 
void writeFile(uchar* data, char* filename)
{
    FILE *f = fopen(filename, "wb");
    if (f)
    {
        fprintf(f, "%s", data);
        fclose(f);
    }
}
 
int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("Usage: xor -option\n");
        return 0;
    }
    int blockSize = 32;
    if(strcmp(argv[1], "-p")==0)
    {
        uchar *orig=0, *plain=0;
        long origSize=0;
        orig = readFile(&origSize, "orig.txt");
        long keySize=0;
        uchar* keyTmp=readFile(&keySize, "key.txt");
        free(keyTmp);
        int pos = 0;
        int validCtr=0;
        while(orig[pos])
        {
            if(orig[pos] >= 'A' && orig[pos] <= 'Z')
            {
                orig[pos] += ('a'-'A');
            }
            if(pos%blockSize==0 && pos !=0)validCtr++;
            if((orig[pos]>='A' && orig[pos]<='z') || orig[pos]==' ')
            validCtr++;
            pos++;
        }
        plain = malloc(validCtr+1);
        pos=0, validCtr=0;
        int fix=0;
        while(orig[pos]){
            if((orig[pos]>='A' && orig[pos]<='z') || orig[pos]==' '){
                plain[validCtr]=orig[pos];
                validCtr++;
                pos++;
                if(validCtr%(blockSize+fix) == 0 && validCtr != 0){
                    plain[validCtr++]='\n';
                    if(fix==0)fix=1;
                }
            }
            else{
                pos++;
            }
        }
        plain[validCtr]='\0';
        writeFile(plain, "plain.txt");
        free(orig);
        free(plain);
    }
    if(strcmp(argv[1], "-e")==0)
    {
        long keySize=0, plainSize=0;
        uchar* key = readFile(&keySize, "key.txt"), *plain = readFile(&plainSize, "plain.txt");
        uchar* encrypted = malloc(plainSize+1000);
        int pos=0;
        int keyPos=0;
        while(plain[pos])
        {
            if(plain[pos] != 32)
                encrypted[pos] = plain[pos]^key[keyPos]-32;
            else
                encrypted[pos] = plain[pos]^key[keyPos];
 
            if(encrypted[pos]==0)encrypted[pos]=255;
            keyPos = keyPos % keySize;
            pos++;
            keyPos++;
            if(pos%blockSize==0){
                encrypted[pos]='\n';
                pos++;
            }
        }
        encrypted[pos]='\0';
        writeFile(encrypted, "crypto.txt");
        free(key);
        free(plain);
        free(encrypted);
    }
    if(strcmp(argv[1], "-k")==0)
    {
        long keySize=0, cryptoSize=0, pSize=0;
        uchar*crypto = readFile(&cryptoSize, "crypto.txt");
        uchar* p = readFile(&pSize, "plain.txt");
        uchar* decrypted=malloc(cryptoSize+1);
        uchar* key = malloc(cryptoSize+1);
        int pos=0;
        while(p[pos]){
            key[pos] = p[pos]^(crypto[pos]-32);
            if(p[pos]==32)
                key[pos] = p[pos]^crypto[pos];
            pos++;
        }
        keySize=pos;
        key[pos]=0;
        printf("Znaleziony klucz: %s\n", key);
        pos=0;
        int keyPos=0;
        while(p[pos]){
            if(p[pos] != 32)
            decrypted[pos] = key[keyPos]^(crypto[pos]-32);
            else
            decrypted[pos] = key[keyPos]^(crypto[pos]);
            //if(decrypted[pos]==0)decrypted[pos]=255;
            keyPos = keyPos % keySize;
            pos++;
            keyPos++;
        }
        decrypted[cryptoSize]=0;
        writeFile(decrypted, "decrypt.txt");
 
 
        free(key);
        free(crypto);
        free(decrypted);
    }
}
