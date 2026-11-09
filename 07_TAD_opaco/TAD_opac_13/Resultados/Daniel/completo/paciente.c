#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

/**
 * @brief Tipo opaco que representa um paciente que possui pelo menos os seguintes atributos:
 * nome, cartão SUS, gênero, data de nascimento e a lista de lesões. Não há limite para a
 * quantidade de lesões de um paciente (a lista deve crescer conforme a necessidade).
 */
struct Paciente{
    char nome[MAX_NOME_PAC];
    char cartao[MAX_CARTAO_SUS];
    char genero;
    tData *nascimento;
    tLesao **lesoes;
    int qtdLesoes;
};

/**
 * @brief Cria um paciente a partir dos dados fornecidos, ainda sem lesões.
 * Todos os campos da estrutura devem ser inicializados aqui.
 *
 * @param nome Nome do paciente.
 * @param cartaoSus Cartão SUS do paciente.
 * @param genero Gênero do paciente.
 * @param dataNasc Ponteiro para a data de nascimento do paciente.
 * @return tPaciente* Ponteiro para o paciente criado.
 */
tPaciente *criaPaciente(char *nome, char *cartaoSus, char genero, tData *dataNasc){
    tPaciente *p = (tPaciente*) malloc (sizeof(struct Paciente));
    strcpy(p->nome, nome);
    strcpy(p->cartao, cartaoSus);
    p->genero = genero;
    p->nascimento = dataNasc;
    p->lesoes = NULL;
    p->qtdLesoes = 0;
    return p;
}

/**
 * @brief Lê os dados de um paciente da entrada padrão.
 * Assuma que o caractere 'P' já foi lido. Esta função lê as 4 linhas seguintes: nome, data de
 * nascimento (utilizando sua função apropriada), cartão SUS e gênero, inclusive a quebra de linha da última.
 *
 * @return tPaciente* Ponteiro para o paciente lido.
 */
tPaciente *lerPaciente(){
    char nome[MAX_NOME_PAC];
    char cartao[MAX_CARTAO_SUS];
    char genero;
    tData *nascimento;
    scanf("%[^\n]\n", nome);
    nascimento = lerData();
    scanf("%[^\n]\n", cartao);
    scanf("%c\n", &genero);
    tPaciente *p = criaPaciente(nome, cartao, genero, nascimento);
    return p;
}

/**
 * @brief Adiciona uma lesão ao final da lista de lesões do paciente.
 *
 * @param p Ponteiro para o paciente ao qual a lesão será vinculada.
 * @param l Ponteiro para a lesão a ser vinculada ao paciente.
 */
void adicionaLesaoPaciente(tPaciente *p, tLesao *l){
    if (p->qtdLesoes == 0){
        free(p->lesoes);
        p->lesoes = (tLesao**) malloc (sizeof(tLesao*));
        p->lesoes[p->qtdLesoes] = l;
        p->qtdLesoes++;

    } else{
        p->lesoes = (tLesao**) realloc (p->lesoes,(p->qtdLesoes+1) * sizeof(tLesao*));
        p->lesoes[p->qtdLesoes] = l;
        p->qtdLesoes++;
    }
}

/**
 * @brief Calcula a idade do paciente em anos completos com base em uma data de referência
 * (utilizando sua função apropriada).
 *
 * @param p Ponteiro para o paciente cuja idade será calculada.
 * @param dataBase Ponteiro para a data de referência para o cálculo da idade.
 * @return int A idade do paciente em anos completos.
 */
int calculaIdadePaciente(tPaciente *p, tData *dataBase){
    return diferencaAnoData(p->nascimento, dataBase);
}

/**
 * @brief Obtém o cartão SUS de um paciente.
 *
 * @param p Ponteiro para o paciente.
 * @return char* O cartão SUS do paciente (a string pertence ao paciente; não a libere).
 */
char *obtemCartaoSusPaciente(tPaciente *p){
    return p->cartao;
}

/**
 * @brief Obtém o número de lesões associadas a um paciente.
 *
 * @param p Ponteiro para o paciente.
 * @return int O número de lesões do paciente.
 */
int obtemNumLesoesPaciente(tPaciente *p){
    return p->qtdLesoes;
}

/**
 * @brief Calcula a quantidade de lesões cirúrgicas associadas a um paciente
 * (utilizando sua função apropriada).
 *
 * @param p Ponteiro para o paciente.
 * @return int A quantidade de lesões cirúrgicas do paciente.
 */
int qtdLesoesCirurgicasPaciente(tPaciente *p){
    int total=0;
    for (int i=0;i<p->qtdLesoes; i++){
        if (verificaCirurgicaLesao(p->lesoes[i])){
            total++;
        }
    }
    return total;
}

/**
 * @brief Imprime o nome do paciente e o identificador das suas lesões: primeiro "- <nome> - ",
 * em seguida o identificador de cada lesão (utilizando sua função apropriada) na ordem de
 * cadastro e, por fim, uma quebra de linha. Ex.: "- SON GOKU - L1 L3 \n".
 * Se o paciente não tiver lesões, não imprime nada.
 *
 * @param p Ponteiro para o paciente a ser impresso.
 */
void imprimePaciente(tPaciente *p){
    if (p->qtdLesoes > 0){
        printf("- %s - ", p->nome);
        for (int i=0; i<p->qtdLesoes; i++){
            imprimeIdLesao(p->lesoes[i]);
        }
        printf("\n");
    }
}

/**
 * @brief Libera a memória de um paciente, inclusive a da data de nascimento e a das lesões
 * (utilizando suas funções apropriadas).
 *
 * @param p Ponteiro para o paciente a ser liberado.
 */
void liberaPaciente(tPaciente *p){
    for (int i=0; i<p->qtdLesoes; i++){
        liberaLesao(p->lesoes[i]);
    }
    free(p->lesoes);
    liberaData(p->nascimento);
    free(p);
}