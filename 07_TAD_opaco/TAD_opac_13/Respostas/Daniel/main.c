#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

int main(){

    tPaciente **pacientes = (tPaciente**) malloc (sizeof(struct Paciente*));
    int numPacientes = 0;
    tData *database = criaData(12, 9, 2023);

    while(1){
        char op;

        scanf("%c%*c", &op);

        if (op == 'F'){
            break;
        }

        if (op == 'P'){

            pacientes = (tPaciente**) realloc (pacientes, (numPacientes+1) * sizeof(struct Paciente*));
            pacientes[numPacientes] = lerPaciente();
            numPacientes++;
        }

        if (op == 'L'){

            int adicionou = 0;
            tLesao *l = lerLesao();
            for (int i=0; i<numPacientes; i++){

                if (strcmp(obtemCartaoSusLesao(l), obtemCartaoSusPaciente(pacientes[i])) == 0){
                    adicionaLesaoPaciente(pacientes[i], l);
                    adicionou = 1;
                    break;
                }
            }
            if (!adicionou){
                liberaLesao(l);
            }
        }
    }

    printf("TOTAL PACIENTES: %d\n", numPacientes);

    int media = 0;
    for (int i=0; i<numPacientes; i++){
        media += calculaIdadePaciente(pacientes[i], database);
    }
    if (numPacientes > 0){
        media = media/numPacientes;
        printf("MEDIA IDADE (ANOS): %d\n", media);
    } else printf("MEDIA IDADE (ANOS): -\n");

    int numlesoes = 0;
    for (int i=0; i<numPacientes; i++){
        numlesoes += obtemNumLesoesPaciente(pacientes[i]);
    }
    printf("TOTAL LESOES: %d\n", numlesoes);

    int cirurgias = 0;
    for (int i=0; i<numPacientes; i++){
        cirurgias += qtdLesoesCirurgicasPaciente(pacientes[i]);
    }
    printf("TOTAL CIRURGIAS: %d\n", cirurgias);

    printf("LISTA DE PACIENTES:\n");
    for (int i=0; i<numPacientes; i++){
        if (obtemNumLesoesPaciente(pacientes[i]) > 0){
            imprimePaciente(pacientes[i]);
        }
    }

    for (int i=0; i<numPacientes; i++){
        liberaPaciente(pacientes[i]);
    }
    free(pacientes);
    liberaData(database);

    return 0;
}