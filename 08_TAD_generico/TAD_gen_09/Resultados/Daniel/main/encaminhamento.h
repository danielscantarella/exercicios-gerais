#ifndef _ENCAMINHAMENTO_H
#define _ENCAMINHAMENTO_H

/*
    Estrutura do tipo Encaminhamento contendo os atributos necessários para a manipulação
*/
typedef struct _Encaminhamento Encaminhamento;

/*
    Função que cria uma Encaminhamento e retorna o seu endereço de memória
    @param nomeMedicamento: nome do medicamento prescrito na Encaminhamento
    @param nomePaciente: nome do paciente para quem a Encaminhamento foi prescrita
    @param nomeMedico: nome do médico que prescreveu a Encaminhamento
    @param instrucoes: instruções para o uso do medicamento
    @return: endereço de memória da Encaminhamento criada
*/
Encaminhamento *criaEncaminhamento(char *nomeMedico, char *nomePaciente, char *especialidade, char *motivo);

/*
    Função que lê os dados de uma Encaminhamento a partir da entrada padrão de acordo com a especificação
    @return: endereço de memória da Encaminhamento lida
*/
Encaminhamento *leEncaminhamento();

/*
    Função que calcula o preço de impressão de uma Encaminhamento de acordo com a especificação
    @param dado: ponteiro genérico para a Encaminhamento a ser calculada
    @param precoCaractere: preço por caractere utilizado no cálculo
    @return: preço de impressão da Encaminhamento
*/
float calculaPrecoImpressaoEncaminhamento(void *dado, float precoCaractere);

/*
    Função que imprime uma Encaminhamento de acordo com a especificação (veja os casos de teste)
    @param dado: ponteiro genérico para a Encaminhamento a ser impressa
*/
void imprimeEncaminhamento(void *dado);

/*
    Função que desaloca uma Encaminhamento
    @param dado: ponteiro genérico para a Encaminhamento a ser desalocada
*/
void desalocaEncaminhamento(void *dado);

#endif