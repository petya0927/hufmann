#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Binfa {
    int szam;
    char betu;
    struct Binfa *jobb, *bal;
} Binfa;

typedef struct Gyakorisag {
    char betu;
    int gyakorisag;
} Gyakorisag;

int *rendezes(int *t, int meret){
    for (int i = 0; i < meret-1; ++i) {
        int minindex = i;
        for (int j = i+1; j < meret; ++j)
            if (t[j] < t[minindex])
                minindex = j;
 
        if (minindex != i) {
            double n_temp = t[minindex];
            //char s_temp = s[minindex];
            t[minindex] = t[i];
            //s[minindex] = s[i];
            t[i] = n_temp;
            //s[i] = s_temp;
        }
    }
    return t;
}

Gyakorisag *rendezes_struct(Gyakorisag *t, int meret){
    for (int i = 0; i < meret - 1; ++i) {
        int minindex = i;
        for (int j = i + 1; j < meret; ++j){
            if (t[j].gyakorisag < t[minindex].gyakorisag){
                minindex = j;
            }
        }
 
        if (minindex != i) {
            int gyak_temp = t[minindex].gyakorisag;
            char betu_temp = t[minindex].betu;
            t[minindex].gyakorisag = t[i].gyakorisag;
            t[minindex].betu = t[i].betu;
            t[i].gyakorisag = gyak_temp;
            t[i].betu = betu_temp;
        }
    }
    return t;
}

Gyakorisag *tombelem_torol(Gyakorisag *t, int p, int meret){
    for (int k = p - 1; k < meret - 1; k++)
        t[k] = t[k + 1];
    return t;
}

int *struct_tomb_masol(Gyakorisag *t, int meret){
    int *uj_tomb = (int*) malloc(meret * sizeof(int));
    for (int i = 0; i < meret; i++)
        uj_tomb[i] = t[i].gyakorisag;
    return uj_tomb;
}

void sorban_kiir(Binfa *gyoker) {
    if (gyoker == NULL){
        printf("NULL\n");
        return;
    }

    printf("%c%d\n", gyoker->betu, gyoker->szam);
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
    uj->betu = (char) 0;
    uj->bal = uj->jobb = NULL;
    return uj;
}

/*
Binfa *uj_adatpont(Binfa *gyoker, int a, int b){
    if (gyoker == NULL)
        return lefoglal(a);

    gyoker->jobb = uj_adatpont(gyoker->jobb, a, b);

    if (gyoker->jobb->bal == NULL && gyoker->jobb->jobb == NULL){

        gyoker->bal = lefoglal(b);
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
*/

Binfa *uj_adatpont(Binfa *gyoker, int a, int b, char c){
    if (gyoker == NULL)
        return lefoglal(a);

    gyoker->jobb = uj_adatpont(gyoker->jobb, a, b, c);

    if (gyoker->jobb->bal == NULL && gyoker->jobb->jobb == NULL){
        gyoker->bal = lefoglal(b);
        gyoker->bal->betu = c;
    }

    return gyoker;
}

Binfa *rekurziv_tomb_osszeg(Gyakorisag *n, int meret){
    for (int i = 0; i < meret; i++)
        printf("%c%d ", n[i].betu, n[i].gyakorisag);
    printf("\n");

    if (meret == 1){
        Binfa *fa = NULL;
        fa = lefoglal(n[0].gyakorisag);
        return fa;
    }
    
    Gyakorisag *m = (Gyakorisag*) malloc(meret * sizeof(Gyakorisag));
    memcpy(m, n, meret * sizeof(Gyakorisag));

    int osszeg = n[0].gyakorisag + n[1].gyakorisag;
    n[1].gyakorisag = osszeg;
    n[1].betu = '\0';
    n = tombelem_torol(n, 0, meret);
    meret -= 1;
    n = rendezes_struct(n, meret);

    Binfa *r = rekurziv_tomb_osszeg(n, meret);
    r = uj_adatpont(r, m[1].gyakorisag, m[0].gyakorisag, m[0].betu);
    return r;
}


int main(void){
    Gyakorisag elofordulasok[] =
    {
        {'a', 7},
        {'b', 2}
    };
    int meret = 2;
    rendezes_struct(elofordulasok, meret);
    sorban_kiir(rekurziv_tomb_osszeg(elofordulasok, meret));
}