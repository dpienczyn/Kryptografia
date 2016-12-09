#include <stdio.h>
#include <math.h>
char *wczytaj(int size, char *nazwapliku){
char *values = new char[size];
FILE* r = fopen(nazwapliku, "r");
char z=getc(r);
for (int i = 0; (i < size) && (feof(r) == 0) && (z != '\n'); i++) {
        values[i] = z;
        z = getc(r);
    }
    fclose(r);
    return values;
}


void printValues(int size, char* text){
for(int i = 0; i < size; i++){
printf("%c\n", text[i]);
}
}

int to(char character){
int to;
if(character >= 'a' && character <= 'z'){
to = 'a';
} else if ((character>='0')&&(character <= '9')){
to = '0';
}
return to;
}

void szyfruj(char* text, char *key, int size){
for (int i=0; i<size; i++){
      if ((text[i] >= 'a') && (text[i] <= 'z')) {
            text[i] -= 'a';
            text[i] += key[i] - to(key[i]);
            text[i] = text[i] % 26;
            text[i] += 'a';
        }
        else if ((text[i] >= 48) && (text[i] <= 57)) {
            text[i] -= 48;
            text[i] += key[i]- to(key[i]);
            text[i] = (text[i] % 10);
            text[i] += 48;
        }
    }
}
void deszyfruj(char * text, char *key, int size){
  for(i=0; i<size; i++){
    if((text[i]>='a') && (text[i] <= 'z')){
      text[i]-='a';
      text[i]=26-text[i];
      text[i] =(text[i]%26);
      text[i]+='a';
    }
    else if ((text[i] >=48) && (text[i] <=57)){
      text[i] -=48;
      text[i]=26-text[i];
      text[i]=(text[i]%10);
      text[i]+=48;
    }
  }
}
void zapiszszyfr(char *text, int size){
FILE *out;
out = fopen("crypto.txt", "w+t");
for(int i=0; i<size; i++){
fprintf(out, "%c", text[i]);
}
fclose(out);
}
void zapiszdeszyfr(char *text, int size){
  FILE *o;
  o = fopen("decrypto.txt", "w+t");
  for(int i=0; i<size; i++){
    fprintf(o, "%c",text[i]);
  }
  fclose(o);
}

int main()
{
int size = 5;
char szyfrujDeszyfruj;
 char e,d;
 
 scanf("%c",&szyfrujDeszyfruj);

 if(szyfrujDeszyfruj=='e'){ 
char * key = wczytaj(size, "key.txt");
char * text = wczytaj(size, "plain.txt");

 printValues(size,text);
szyfruj(text, key, size);
zapiszszyfr(text,size);
 }

 else if(szyfrujDeszyfruj=='d'){ 
   char * key = wczytaj(size, "key.txt");
   char * text = wczytaj(size, "crypto.txt");

   deszyfruj(text, key, size);
   zapiszdeszyfr(text,size);
 }
return 0;
}
