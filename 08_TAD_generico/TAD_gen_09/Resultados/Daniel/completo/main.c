#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_imp.h"
#include "receita.h"
#include "exame.h"
#include "encaminhamento.h"

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

        if (strcmp(comando, "ENCAMINHAMENTO") == 0){
            Encaminhamento *e = leEncaminhamento();
            insereDocumentoFilaImp(fila, e, imprimeEncaminhamento, desalocaEncaminhamento, calculaPrecoImpressaoEncaminhamento);
        }

        if (strcmp(comando, "EXAME") == 0){
            Exame *e = leExame();
            insereDocumentoFilaImp(fila, e, imprimeExame, desalocaExame, calculaPrecoImpressaoExame);
        }

        if (strcmp(comando, "QUANTIDADE") == 0){
            printf("- QUANTIDADE DE DOCUMENTOS NA FILA: %d\n", quantidadeDocumentosNaFilaImp(fila));
        }

        if (strcmp(comando, "PRECO") == 0){
            printf("- PRECO TOTAL DA FILA: R$ %.2f\n", precoTotalImpressaoFilaImp(fila, precoCaractere));
        }

        if (strcmp(comando, "IMPRIME") == 0){
            imprimeFilaImp(fila);
        }

        if (strcmp(comando, "FIM") == 0){
            break;
        }

    }

    desalocaFilaImp(fila);

    return 0;
}