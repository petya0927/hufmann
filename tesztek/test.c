#include <stdio.h>

int main(void){
    for (int szam = 0b0; szam < 256; szam++)
        printf("%d", szam);

    return 0;
}