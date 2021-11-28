#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Binfa {
    int szam;
    char betu;
    char *ut;
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

    printf("%c %d %s\n", gyoker->betu, gyoker->szam, gyoker->ut);
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
    uj->ut = (char*) 0;
    uj->bal = uj->jobb = NULL;
    return uj;
}

bool level(Binfa *gyoker){
    return gyoker->bal == NULL && gyoker->jobb == NULL;
}

int index_keres(Gyakorisag *t, char c){
    int meret = sizeof(t) / sizeof(t[0]);
    int i = 0;
    while (i < meret && t[i].betu != c)
        i++;
    return (i == meret ? -1 : i);
}

char *tomb_megnovel(char *t){
    int meret = sizeof(t) / sizeof(t[0]);
    char *uj = (char*) malloc((meret + 2) * sizeof(char));
    return uj;
}

Binfa *beszur(Binfa *gyoker, int osszeg, int a, int b, char ca, char cb){
    if (gyoker == NULL)
        return NULL;

    if (level(gyoker)){        
        if (gyoker->szam == osszeg && gyoker->betu == '\0'){
            gyoker->jobb = lefoglal(a);
            gyoker->jobb->betu = ca;
            if (gyoker->ut == NULL)
                gyoker->jobb->ut = "1";
            else{
                gyoker->jobb->ut = tomb_megnovel(gyoker->jobb->ut);
                strcpy(gyoker->jobb->ut, gyoker->ut);
                gyoker->jobb->ut = strcat(gyoker->jobb->ut, "1");
            }


            gyoker->bal = lefoglal(b);
            gyoker->bal->betu = cb;
            if (gyoker->ut == NULL)
                gyoker->bal->ut = "0";
            else{
                gyoker->bal->ut = tomb_megnovel(gyoker->bal->ut);
                strcpy(gyoker->bal->ut, gyoker->ut);
                gyoker->bal->ut = strcat(gyoker->bal->ut, "0");
            }
            return gyoker;
        }
        else
            return NULL;
    }

    else
        if (!beszur(gyoker->bal, osszeg, a, b, ca, cb))
            if (!beszur(gyoker->jobb, osszeg, a, b, ca, cb))
                return NULL;

    return gyoker;
}

Binfa *rekurziv_tomb(Gyakorisag *n, int meret){
    if (meret == 1){
        Binfa *fa = NULL;
        fa = lefoglal(n[0].gyakorisag);
        fa->betu = n[0].betu;
        fa->ut = NULL;
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

    Binfa *r = rekurziv_tomb(n, meret);
    r = beszur(r, m[1].gyakorisag + m[0].gyakorisag, m[1].gyakorisag, m[0].gyakorisag, m[1].betu, m[0].betu);
    
    return r;
}

void kodok_fileba(Binfa *gyoker, FILE *f){
    if (gyoker == NULL)
        return;

    if (level(gyoker)){
        /*https://stackoverflow.com/questions/29087129/how-to-calculate-the-length-of-output-that-sprintf-will-generate*/
        int meret = snprintf(NULL, 0, "%c%s\n", gyoker->betu, gyoker->ut, 'a');
        char *fajlba = (char*) malloc(meret + 1);
        sprintf(fajlba, "%c%s\n", gyoker->betu, gyoker->ut, 'a');
        fwrite(fajlba, sizeof(fajlba), sizeof(fajlba), f);
        free(fajlba);
    }

    kodok_fileba(gyoker->jobb, f);
    kodok_fileba(gyoker->bal, f);
}

int fajlmeret(FILE *fajlp){
    fseek(fajlp, 0, SEEK_END);          /* A fájlmutatót a pointer végére mozgatja a fájlméret meghatározásához*/
    int fajlmeret = ftell(fajlp);   
    fseek(fajlp, 0, SEEK_SET);          /* A fájlmutatót a fájl elejére mozgatja a fájl beolvasásához */
    return fajlmeret;
}

void faban_keres(Binfa *gyoker, char c){
    if (gyoker == NULL)
        return;

    if (gyoker->betu == c){
        printf("%s", gyoker->ut);
        return;
    }
    
    faban_keres(gyoker->bal, c);
    faban_keres(gyoker->jobb, c);
    
    return;

}

Gyakorisag *gyak_szamol(char *szoveg){
    if (szoveg == NULL)
        return NULL;

    int meret = strlen(szoveg);
    int beolvasva = -1;
    int *elofordulas = (int*) malloc(meret * sizeof(int));              /* Lefoglal a memóriában egy helyet az elofordulasok tarolasara */

    /* Végigiterál a szövegen és ha azonos betűk vannak, a számlálóhoz ad egyet*/
    for (int i = 0; i < meret; i++){
        int szamol = 1;
        for (int j = i + 1; j < meret; j++){
            if (szoveg[i] == szoveg[j]){
                szamol++;
                elofordulas[j] = -1;                    /* Ha azonos betűt talált, jelzi, hogy ne számoljuk meg újra */
            }
        }

        if (elofordulas[i] != -1)
            elofordulas[i] = szamol;                    /* Eltárolja a gyakoriságot */
    }

    int j = 0;
    Gyakorisag *cel = (Gyakorisag*) malloc(sizeof(Gyakorisag));         /*Lefoglal egy területet a végelges tömbnek*/

    for (int i = 0; i < meret; i++){
        if (elofordulas[i] != -1){
            Gyakorisag *uj = (Gyakorisag*) malloc((j + 1) * sizeof(Gyakorisag));         /* Lefoglal egyel nagyobb tömböt a gyakoriságok tárolására */
            for (int k = 0; k < j; ++k)
                uj[k] = cel[k];                     /* Átmásolja az eddigi elemeket az új tömbbe*/
            free(cel);
            cel = uj;
            cel[j].betu = szoveg[i];                /* Eltárolja a karaktert*/
            cel[j].gyakorisag = elofordulas[i];     /* Eltárolja a karakter előfordulásának számát */
            j++;
        }
    }

    for (int i = 0; i < meret; i++)
        printf("%c %d\n", cel[i].betu, cel[i].gyakorisag);
    return cel;
}

int main(void){
    /*Gyakorisag elofordulasok[] = {
        {'a', 3},
        {'l', 5},
        {'m', 1},
        {'f', 1}
    };*/
    char *szoveg = "almafallll\0";
    Gyakorisag *elofordulasok = gyak_szamol(szoveg);
    int meret = sizeof(elofordulasok) / sizeof(elofordulasok[0]);

    rendezes_struct(elofordulasok, meret);
    for (int i = 0; i < meret; i++)
        printf("%c %d\n", elofordulasok[i].betu, elofordulasok[i].gyakorisag);

    Binfa *fa = rekurziv_tomb(elofordulasok, meret);

    FILE *fajl = fopen("tomoritett.hcf", "wb");
    kodok_fileba(fa, fajl);
    for (int i = 0; i < strlen(szoveg); i++)
        faban_keres(fa, szoveg[i]);
    fclose(fajl);

    free(fa);
}