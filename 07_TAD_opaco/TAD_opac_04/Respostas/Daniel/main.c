#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

int main(){

    int qtd;
    scanf("%d", &qtd);
    tAluno *alunos[qtd];

    for (int i=0; i<qtd; i++){
        alunos[i] = CriaAluno();
        LeAluno(alunos[i]);
    }

    for (int i=0; i<qtd; i++){
        for (int j=i+1; j<qtd; j++){
            if (ComparaMatricula(alunos[i], alunos[j]) == 1){
                tAluno *temp = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = temp;
            }
        }
    }

    for (int i=0; i<qtd; i++){
        if (VerificaAprovacao(alunos[i])){
            ImprimeAluno(alunos[i]);
        }
    }

    for (int i=0; i<qtd; i++){
        ApagaAluno(alunos[i]);
    }

    return 0;
}