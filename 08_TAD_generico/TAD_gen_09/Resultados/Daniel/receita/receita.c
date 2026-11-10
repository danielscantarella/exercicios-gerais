#include "receita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Estrutura do tipo Receita contendo os atributos necessários para a manipulação
*/
typedef struct _Receita{
    char medico[101];
    char paciente[101];
    char medicamento[101];
    char instrucoes[201];
};

/*
    Função que cria uma receita e retorna o seu endereço de memória
    @param nomeMedicamento: nome do medicamento prescrito na receita
    @param nomePaciente: nome do paciente para quem a receita foi prescrita
    @param nomeMedico: nome do médico que prescreveu a receita
    @param instrucoes: instruções para o uso do medicamento
    @return: endereço de memória da receita criada
*/
Receita *criaReceita(char *nomeMedicamento, char *nomePaciente, char *nomeMedico, char *instrucoes){
    Receita *r = (Receita *) calloc(1, sizeof(struct _Receita));
    strcpy(r->medicamento, nomeMedicamento);
    strcpy(r->medico, nomeMedico);
    strcpy(r->paciente, nomePaciente);
    strcpy(r->instrucoes, instrucoes);
    return r;
}

/*
    Função que lê os dados de uma receita a partir da entrada padrão de acordo com a especificação
    @return: endereço de memória da receita lida
*/
Receita *leReceita(){
    char nomeMedicamento[101];
    char nomePaciente[101];
    char nomeMedico[101];
    char instrucoes[200];

    scanf("%[^\n]\n", nomeMedico);
    scanf("%[^\n]\n", nomePaciente);
    scanf("%[^\n]\n", nomeMedicamento);
    scanf("%[^\n]\n", instrucoes);

    Receita *r = criaReceita(nomeMedicamento, nomePaciente, nomeMedico, instrucoes);
    return r;
}

/*
    Função que calcula o preço de impressão de uma receita de acordo com a especificação
    @param dado: ponteiro genérico para a receita a ser calculada
    @param precoCaractere: preço por caractere utilizado no cálculo
    @return: preço de impressão da receita
*/
float calculaPrecoImpressaoReceita(void *dado, float precoCaractere){
    Receita *r = (Receita *)dado;

    int soma = 0;
    soma += strlen(r->instrucoes);
    soma += strlen(r->medicamento);
    soma += strlen(r->medico);
    soma += strlen(r->paciente);

    return soma * precoCaractere;
}

/*
    Função que imprime uma receita de acordo com a especificação (veja os casos de teste)
    @param dado: ponteiro genérico para a receita a ser impressa
*/
void imprimeReceita(void *dado){
    Receita *r = (Receita *)dado;

    printf("- - RECEITA - - \n");
    printf("MEDICAMENTO: %s\n", r->medicamento) ;
    printf("PACIENTE: %s\n", r->paciente);
    printf("INSTRUCOES: %s\n", r->instrucoes);
    printf("MEDICO: %s\n", r->medico);
    printf("- - - - - - - -\n");
}

/*
    Função que desaloca uma receita
    @param dado: ponteiro genérico para a receita a ser desalocada
*/
void desalocaReceita(void *dado){
    Receita *r = (Receita *) dado;
    free(r);
}