#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_imp.h"
#include "receita.h"

int main(){

    float precoCaractere;
    scanf("%f\n", &precoCaractere);

    FilaImp *fila = criaFilaImp();

    while(1){

        char comando[20];
        scanf("%[^\n]\n", comando);

        if (strcmp(comando, "RECEITA") == 0){
            Receita *r = leReceita();
            insereDocumentoFilaImp(fila, r, imprimeReceita, desalocaReceita, calculaPrecoImpressaoReceita);
        }


    }

    return 0;
}