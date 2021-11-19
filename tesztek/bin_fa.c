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

    printf("balra\n");
    sorban_kiir(gyoker->bal);     /* 1 */
    printf("%d\n", gyoker->adat);
    printf("jobbra\n");
    sorban_kiir(gyoker->jobb);    /* 3 */
}

int main(void) {
    BinFa *fa = NULL;
    int szamok[10] = {5, 6, 2, 1, 9, 4, 7, 0, 3, 8};
    for (int i = 0; i < 10; i++){
        fa = beszur(fa, szamok[i]);
    }

    sorban_kiir(fa);
}