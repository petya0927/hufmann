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

bool level(Binfa *gyoker){
    return gyoker->bal == NULL && gyoker->jobb == NULL;
}

Binfa *faban_van(Binfa *gyoker, int n){
    if (gyoker == NULL)
        return NULL;

    if (gyoker->szam = n)
        return gyoker;

    Binfa *b = faban_van(gyoker->bal, n);
    if (b != NULL) return b;
    Binfa *j = faban_van(gyoker->jobb, n);
    return j;
}

Binfa *osszeg_keres(Binfa *gyoker, int osszeg, int a, int b, char ca, char cb){
    printf("====================================\n");
    printf("#ELOTTE:\n");
    if (gyoker == NULL)
        return NULL;

    printf("#Vizsgalt:%d, level:%d, a:%d, ca:%c, b:%d, cb:%c\n", gyoker->szam, level(gyoker), a, b, ca, cb);
    sorban_kiir(gyoker);

    // akkor hívom ha levél és kétféle képpen tudok visszatérni, azonos az érték, vbagy nem azonos az érték
    if (level(gyoker)){
        printf("#LEVEL\n");
        if (gyoker->szam == osszeg){
            printf("#EGYENLO\n");
            printf("#BEILLESZTES\n");
            gyoker->jobb = lefoglal(a);
            gyoker->jobb->betu = ca;
            gyoker->bal = lefoglal(b);
            gyoker->bal->betu = cb;
            printf("UTANA:\n");
            sorban_kiir(gyoker);
            return gyoker;
        }
        else{
            printf("#NEM EGYENLO");
            return NULL;
        }
    }

    else{
        printf("#NEM LEVEL\n");
        if (!osszeg_keres(gyoker->bal, osszeg, a, b, ca, cb)){
            printf("#gyoker->bal = NULL\n");
            if (!osszeg_keres(gyoker->jobb, osszeg, a, b, ca, cb))
                return NULL;
        }
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
        fa->betu = n[0].betu;
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
    r = osszeg_keres(r, m[1].gyakorisag + m[0].gyakorisag, m[1].gyakorisag, m[0].gyakorisag, m[1].betu, m[0].betu);

    
    return r;
}

int main(void){
    Gyakorisag elofordulasok[] =
    {
        {'a', 1},
        {'b', 1},
        {'c', 1},
        {'d', 1},
        {'e', 1}
    };
    int meret = 5;
    rendezes_struct(elofordulasok, meret);
    Binfa *fa = rekurziv_tomb_osszeg(elofordulasok, meret);
    printf("================================\n");
    sorban_kiir(fa);
    free(fa);
}