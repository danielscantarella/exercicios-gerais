#include "documento.h"
#include <stdlib.h>
#include <stdio.h>

/*
    Estrutura do tipo Documento contendo os atributos necessários para a manipulação
*/
struct _Documento{
    void *dado;
    func_ptr_imprime imprime;
    func_ptr_desaloca desaloca;
    func_ptr_calculaPreco calculaPreco;
};

/*
    Definição dos tipo ponteiro para função utilizado para imprimir um documento genérico
*/
typedef void (*func_ptr_imprime)(void *dado);

/*
    Definição do tipo ponteiro para função utilizado para desalocar um documento genérico
*/
typedef void (*func_ptr_desaloca)(void *dado);

/*
    Definição do tipo ponteiro para função utilizado para calcular o preço de impressão
    de um documento genérico
*/
typedef float (*func_ptr_calculaPreco)(void *dado, float precoCaractere);

/*
    Função que cria um documento genérico e retorna o seu endereço de memória
    @param dado: ponteiro genérico para o dado do documento
    @param imprimeDado: ponteiro para a função de impressão do dado do documento genérico
    @param desalocaDado: ponteiro para a função de desalocação do dado do documento genérico
    @param calculaPrecoDado: ponteiro para a função de cálculo do preço do dado do documento genérico
    @return: endereço de memória do documento genérico criado
*/
Documento *criaDocumento(void *dado, func_ptr_imprime imprimeDado, func_ptr_desaloca desalocaDado, func_ptr_calculaPreco calculaPrecoDado){
    Documento *d = (Documento *) calloc (1, sizeof (Documento));
    d->dado = dado;
    d->calculaPreco = calculaPrecoDado;
    d->desaloca = desalocaDado;
    d->imprime = imprimeDado;
    return d;
}

/*
    Função que imprime um documento genérico de acordo com a função de impressão passada
    @param doc: ponteiro para um documento a ser impresso
*/
void imprimeDocumento(Documento *doc){
    doc->imprime(doc->dado);
}

/*
    Função que calcula o preço de impressão de um documento de acordo com a função de cálculo estabelecida na especificação
    @param doc: ponteiro para um documento a ser calculado o preço
    @param precoCaractere: preço por caractere utilizado no cálculo
    @return: preço de impressão do documento
*/
float calculaPrecoImpressaoDocumento(Documento *doc, float precoCaractere){
    return doc->calculaPreco(doc->dado, precoCaractere);
}

/*
    Função que desaloca um documento de acordo com a função de desalocação passada
    @param doc: ponteiro para um documento a ser desalocado
*/
void desalocaDocumento(Documento *doc){
    doc->desaloca(doc->dado);
    free(doc);
}