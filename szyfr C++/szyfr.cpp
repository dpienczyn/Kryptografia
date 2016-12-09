#include <stdio.h>
 
char* readValuesFromFile(int size, char *fileName){
    char* values = new char[size];
    FILE* r = fopen(fileName, "r");
    char z = getc(r);
    for (int i = 0; (i < size) && (feof(r) == 0) && (z != '\n'); i++) {
        values[i] = z;
        z = getc(r);
    }
    fclose(r);
    return values;
}
 
void printValues(int size, char* text){
    for (int i = 0; i < size; i++) {
        printf("%c\n", text[i]);
    }
}
 
int toSubstract(char character){
    int toSubstract;
    if(character >= 'a' && character <= 'z'){
        toSubstract = 'a';
    } else if ((character >= '0') && (character <= '9')){
        toSubstract = '0';
    }
    return toSubstract;
}
 
void encrypt(char* text, char* key, int size){
    for (int i = 0; i < size; i++) {
        if ((text[i] >= 'a') && (text[i] <= 'z')) {
            text[i] -= 'a';
            text[i] += key[i] - toSubstract(key[i]);
            text[i] = text[i] % 26;
            text[i] += 'a';
        }
        else if ((text[i] >= 48) && (text[i] <= 57)) {
            text[i] -= 48;
            text[i] += key[i]- toSubstract(key[i]);
            text[i] = (text[i] % 10);
            text[i] += 48;
        }
    }
}
void deszyfruj(char* text,char* key, int size){
  for(i=0; i<size; i++){
    if((text[i]>='a') && (text[i]<='z')){
      text[i]-='a';
      text[i]=26-text[i];
      text[i]=(text[i]%26);
      text[i]+='a';
    }
    else if ((text[i]>=48)&&(text[i]<=57)){
      text[i]-=48;
      text[i]=26-text[i];
      text[i]=(text[i]%10);
      text[i]+=48;
    }
  }
}
void savedeszyfr(char* text, int size){
  FILE*o;
  o=fopen("decrypto.txt","w+t");
  for(int i=0; i<size; i++){
    fprintf(o,"%c",text[i]);
  }
  fclose(o);
}
void saveEncryptedText(const char* text, int size){
    FILE* out;
    out = fopen("crypto.txt", "w+t");
    printf("Szyfrujemy:\n");
    for (int i = 0; i < size; i++) {
        printf("%c\n", text[i]);
        fprintf(out, "%c", text[i]);
    }
    fclose(out);
}
 
int main()
{
    int size = 5;
    char szyfrujDeszyfruj;
    char e,d;
    scanf("%s",&szyfrujDeszyfruj);

    if(szyfrujDeszyfruj=='e'){
    char* key = readValuesFromFile(size, "key.txt");
    char* text = readValuesFromFile(size, "plain.txt");
 
    printf("Tekst:\n");
    printValues(size, text);
 
    printf("Klucz:\n");
    printValues(size, key);
 
    encrypt(text, key, size);
    saveEncryptedText(text, size);
    }

    if(szyfrujDeszyfruj=='d'){
    char* key= readValuesFromFile(size, "key.txt");
    char* text=readValuesFromFile(size, "crypto.txt");

    printf("Tekst:\n");
    printValues(size,text);

    printf("klucz:\n");
    printValues(size,key);

    deszyfruj(text,key,size);
    savedeszyfr(text,size);
    }
    
    return 0;
}
