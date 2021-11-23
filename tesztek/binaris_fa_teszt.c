#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Binfa {
    int szam;
    struct Binfa *szulo;
    struct Binfa *jobb, *bal;
} Binfa;

void rendezes(int *n, int meret){
    for (int i = 0; i < meret-1; ++i) {
        int minindex = i;
        for (int j = i+1; j < meret; ++j)
            if (n[j] < n[minindex])
                minindex = j;
 
        if (minindex != i) {
            double n_temp = n[minindex];
            //char s_temp = s[minindex];
            n[minindex] = n[i];
            //s[minindex] = s[i];
            n[i] = n_temp;
            //s[i] = s_temp;
        }
    }
}

int *tombelem_torol(int *tomb, int poz, int meret){
    for (int k = poz - 1; k < meret - 1; k++)
        tomb[k] = tomb[k + 1];
}

void sorban_kiir(Binfa *gyoker) {
    if (gyoker == NULL){
        printf("NULL\n");
        return;
    }

    printf("%d\n", gyoker->szam);
    printf("bal\n");
    sorban_kiir(gyoker->bal);
    printf("jobb\n");
    sorban_kiir(gyoker->jobb);
}

void tomb_kiir(int *n, int meret){
    for (int i = 0; i < meret; i++)
        printf("%d ", n[i]);
    printf("\n");
}

Binfa *lefoglal(int szam){
    Binfa *uj = (Binfa*) malloc(sizeof(Binfa));
    uj->szam = szam;
    uj->szulo = NULL;
    uj->bal = uj->jobb = NULL;
    return uj;
}

Binfa *uj_adatpont(Binfa *gyoker, int a, int b){
    if (gyoker == NULL){
        return lefoglal(a);
    }
    gyoker->jobb = uj_adatpont(gyoker->jobb, a, b);
    gyoker->jobb->szulo = gyoker;
    if (gyoker->jobb->bal == NULL && gyoker->jobb->jobb == NULL){
        gyoker->bal = lefoglal(b);
        gyoker->bal->szulo = gyoker;
    }
    return gyoker;
}

Binfa *rekurziv_tomb_osszeg(int *n, int meret){
    if (meret == 1){
        Binfa *fa = NULL;
        fa = lefoglal(n[0]);
        return fa;
    }
    
    int *m = (int*) malloc(meret * sizeof(int));
    memcpy(m, n, meret * sizeof(int));

    int osszeg = n[0] + n[1];
    n[1] = osszeg;
    tombelem_torol(n, 0, meret);
    meret -= 1;
    rendezes(n, meret);

    Binfa *r = rekurziv_tomb_osszeg(n, meret);
    r = uj_adatpont(r, m[1], m[0]);
    return r;
}


int main(void){
    char betuk[6] = {'a', 'b', 'c', 'd', 'e', '\0'};
    int elofordulasok[5] = {1, 2, 2, 5, 6};
    int meret = 5;
    rendezes(elofordulasok, 5);
    sorban_kiir(rekurziv_tomb_osszeg(elofordulasok, 5));
}