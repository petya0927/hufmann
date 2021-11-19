#include <stdio.h>
#include <stdlib.h>

typedef struct Binfa {
    int szam;
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

Binfa *uj_adatpont(Binfa *gyoker, int szam, int idx){
    if (gyoker == NULL){
        Binfa *uj = (Binfa*) malloc(sizeof(Binfa));
        uj->szam = szam;
        uj->bal = uj->jobb = NULL;
        return uj;
    }

    if (idx == 1)
        gyoker->jobb = uj_adatpont(gyoker->jobb, szam, idx);
    else if (idx == 0)
        gyoker->bal = uj_adatpont(gyoker->bal, szam, idx);
 
    return gyoker;
}

void sorban_kiir(Binfa *gyoker) {
    if (gyoker == NULL)
       return;

    printf("%d\n", gyoker->szam);
    printf("bal\n");
    sorban_kiir(gyoker->bal);
    printf("jobb\n");
    sorban_kiir(gyoker->jobb);
}

int *tombelem_torol(int *tomb, int poz, int meret){
    for (int k = poz - 1; k < meret - 1; k++)
        tomb[k] = tomb[k + 1];
}

void tomb_kiir(int *n, int meret){
    for (int i = 0; i < meret; i++)
        printf("%d ", n[i]);
    printf("\n");
}

Binfa *rekurziv_tomb_osszeg(int *n, int meret){
    if (meret == 0){
        Binfa *fa = NULL;
        fa = uj_adatpont(fa, n[0], 0);
        return fa;
    }

    tomb_kiir(n, meret);
    int osszeg = n[0] + n[1];
    n[1] = osszeg;
    tombelem_torol(n, 0, meret);
    meret -= 1;
    rendezes(n, meret);
    Binfa *r = rekurziv_tomb_osszeg(n, meret);
    r = uj_adatpont(r, n[0], 0);
    r = uj_adatpont(r, n[1], 1);
    return r;
}


int main(void){
    char betuk[6] = {'a', 'b', 'c', 'd', 'e', '\0'};
    int elofordulasok[5] = {5, 2, 1, 6, 2};
    rendezes(elofordulasok, 5);
    sorban_kiir(rekurziv_tomb_osszeg(elofordulasok, 5));
}