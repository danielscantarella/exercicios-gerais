#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encaminhamento.h"

/*
    Estrutura do tipo Receita contendo os atributos necessários para a manipulação
*/
struct _Encaminhamento{
    char medico[101];
    char paciente[101];
    char especialidade[51];
    char motivo[201];
};

/*
    Função que cria uma Encaminhamento e retorna o seu endereço de memória
    @param nomeMedicamento: nome do medicamento prescrito na Encaminhamento
    @param nomePaciente: nome do paciente para quem a Encaminhamento foi prescrita
    @param nomeMedico: nome do médico que prescreveu a Encaminhamento
    @param instrucoes: instruções para o uso do medicamento
    @return: endereço de memória da Encaminhamento criada
*/
Encaminhamento *criaEncaminhamento(char *nomeMedico, char *nomePaciente, char *especialidade, char *motivo){
    Encaminhamento *e = (Encaminhamento *) calloc (1, sizeof(Encaminhamento));
    strcpy(e->medico, nomeMedico);
    strcpy(e->paciente, nomePaciente);
    strcpy(e->especialidade, especialidade);
    strcpy(e->motivo, motivo);
    return e;
}

/*
    Função que lê os dados de uma Encaminhamento a partir da entrada padrão de acordo com a especificação
    @return: endereço de memória da Encaminhamento lida
*/
Encaminhamento *leEncaminhamento(){
    char nomeMedico[101];
    char nomePaciente[101];
    char especialidade[101];
    char motivo[200];

    scanf("%[^\n]\n", nomeMedico);
    scanf("%[^\n]\n", nomePaciente);
    scanf("%[^\n]\n", especialidade);
    scanf("%[^\n]\n", motivo);

    Encaminhamento *e = criaEncaminhamento(nomeMedico, nomePaciente, especialidade, motivo);
    return e;
}

/*
    Função que calcula o preço de impressão de uma Encaminhamento de acordo com a especificação
    @param dado: ponteiro genérico para a Encaminhamento a ser calculada
    @param precoCaractere: preço por caractere utilizado no cálculo
    @return: preço de impressão da Encaminhamento
*/
float calculaPrecoImpressaoEncaminhamento(void *dado, float precoCaractere){
    Encaminhamento *e = (Encaminhamento *)dado;

    int soma = strlen(e->medico) + strlen(e->paciente) + strlen(e->motivo) + strlen(e->especialidade);
    return soma * precoCaractere;
}

/*
    Função que imprime uma Encaminhamento de acordo com a especificação (veja os casos de teste)
    @param dado: ponteiro genérico para a Encaminhamento a ser impressa
*/
void imprimeEncaminhamento(void *dado){
    Encaminhamento*e = (Encaminhamento *) dado;

    printf("- - ENCAMINHAMENTO - - \n");
    printf("PACIENTE: %s\n", e->paciente);
    printf("ESPECIALIDADE: %s\n", e->especialidade) ;
    printf("MOTIVO: %s\n", e->motivo);
    printf("MEDICO: %s\n", e->medico);
    printf("- - - - - - - - - - - -\n");
}

/*
    Função que desaloca uma Encaminhamento
    @param dado: ponteiro genérico para a Encaminhamento a ser desalocada
*/
void desalocaEncaminhamento(void *dado){
    Encaminhamento *e = (Encaminhamento *) dado;

    free(e);
}