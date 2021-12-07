#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void binaris_fajl_ir(char *t, FILE *f){
    char resz[8];
    int meret = strlen(t);
    for (int n = 0; n < meret; n += 8){
        for (int i = 0; i < 8; i++){
            if (n + i < meret)
                resz[i] = t[n + i];
            else
                resz[i] = '0';
        }
        resz[8] = '\n';
        long int l = strtol(resz, 0, 2);
        unsigned char b = l & 0xffl;
        if (b == 0)
            fwrite("0", sizeof(char), 1, f);
        else
            fwrite(&b, 1, 1, f);
    }
}

int main(void){
    char tomb[] = "000001101100110000000000";
    FILE *f = fopen("test.txt", "wb");
    binaris_fajl_ir(tomb, f);
    fclose(f);
}