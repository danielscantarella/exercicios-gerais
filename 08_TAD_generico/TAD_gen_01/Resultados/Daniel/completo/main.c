#include "tadgen.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    int type, numelemenetos;

    printf("tad_gen_01\n");
    printf("Digite o tipo e numero de elementos: ");
    scanf("%d %d\n", &type, &numelemenetos);

    tGeneric *gen = CriaGenerico(type, numelemenetos);

    LeGenerico(gen);

    ImprimeGenerico(gen);

    DestroiGenerico(gen);
    return 0;
}