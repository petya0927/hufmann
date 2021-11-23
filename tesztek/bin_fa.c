#include <stdio.h>
#include <stdlib.h>

typedef struct BinFa{
    int adat;
    struct BinFa *bal, *jobb;
} BinFa;

BinFa *beszur(BinFa *gyoker, int adat) {
    if (gyoker == NULL) {                        /* üres? */
        BinFa *uj = (BinFa*) malloc(sizeof(BinFa));
        uj->bal = uj->jobb = NULL;    /* levél lesz */
        uj->adat = adat;
        return uj;     /* vissza kell térni vele! */
    }
 
    if (adat <= gyoker->adat)                /* kisebb? */
        gyoker->bal = beszur(gyoker->bal, adat);
    else if (adat > gyoker->adat)                /* nagyobb? */
        gyoker->jobb = beszur(gyoker->jobb, adat);
    else
        NULL;
 
    return gyoker;
}

void sorban_kiir(BinFa *gyoker) {
    if (gyoker == NULL){
        printf("NULL\n");
        return;
    }

    printf("%d\n", gyoker->adat);
    printf("balra\n");
    sorban_kiir(gyoker->bal);
    printf("jobbra\n");
    sorban_kiir(gyoker->jobb);
    
}

int main(void) {
    BinFa *fa = NULL;
    int szamok[3] = {5, 6, 2};
    for (int i = 0; i < 3; i++){
        fa = beszur(fa, szamok[i]);
    }

    sorban_kiir(fa->bal);
}