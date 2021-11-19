#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct SzoStat {
    char szo[51];
    int db;
    struct SzoStat *bal, *jobb;
} SzoStat;

SzoStat *beszur(SzoStat *gyoker, char *szo) {
    if (gyoker == NULL) {
        SzoStat *uj = (SzoStat*) malloc(sizeof(SzoStat));
        strcpy(uj->szo, szo);
        uj->db = 1;
        uj->bal = uj->jobb = NULL;
        return uj;
    }
    
    int er = strcmp(szo, gyoker->szo);
    if (er < 0){
        gyoker->bal = beszur(gyoker->bal, szo);
    }
    else if (er > 0){
        gyoker->jobb = beszur(gyoker->jobb, szo);
    }
    else
        gyoker->db++;
 
    return gyoker;
}

void felszabadit(SzoStat *gyoker) {
    if (gyoker == NULL)
        return;
    
    felszabadit(gyoker->bal);
    felszabadit(gyoker->jobb);
    free(gyoker);
}

void kiir(SzoStat *gyoker) {
    if (gyoker == NULL)
        return;
 
    kiir(gyoker->bal);
    printf("%s ", gyoker->szo);
    printf("%d ", gyoker->db);
    kiir(gyoker->jobb);
}

int main(void) {
    SzoStat *fa = NULL;
    char szo[51];
    
    while (fgets(szo, 50, stdin)[0] != '\n'){
        fa = beszur(fa, szo);
    }

    kiir(fa);
    felszabadit(fa);
    
    return 0;
}