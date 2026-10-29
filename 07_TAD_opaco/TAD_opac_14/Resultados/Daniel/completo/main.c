#include "nba.h"

int main(){

    tNBA *nba = CriaNBA();

    RodaNBA(nba);
    
    ImprimeRelatorioNBA(nba);

    LiberaNBA(nba);

    return 0;
}