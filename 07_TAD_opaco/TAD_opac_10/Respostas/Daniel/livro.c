#include "livro.h"
#include <stdlib.h>
#include <stdio.h>

// Estrutura que representa um livro
struct Livros{
    char *titulo;
    char *autor;
    int ano;
};


/**
 * Cria um livro "vazio". Ponteiros devem receber null e os atributos numéricos valor -1;
 *
 * @return Um ponteiro para um livro livro "vazio"
 */
tLivros* CriaLivro(){
    tLivros *l = (tLivros*) calloc (1, sizeof(struct Livros));
    l->ano = -1;
    l->autor = NULL;
    l->titulo = NULL;
    return l;
}

/**
 * Lê os atributos de um livro a partir da entrada padrão (teclado).
 *
 * @param livro Um ponteiro para um livro que receberá os atributos lidos
 */
void LerLivro(tLivros* livro){
    int tamTitulo = 0;
    char c;

    free (livro->titulo);
    livro->titulo = (char*) malloc (sizeof(char));

    while (scanf("%c", &c) == 1 && c != '\n'){

        livro->titulo = (char*) realloc (livro->titulo, (tamTitulo+2) * sizeof(char));
        livro->titulo[tamTitulo] = c;
        tamTitulo++;
    }
    livro->titulo[tamTitulo] = '\0';

    int tamAutor = 0;

    free (livro->autor);
    livro->autor = (char*) malloc (sizeof(char));

    while (scanf("%c", &c) == 1 && c != '\n'){

        livro->autor = (char*) realloc (livro->autor, (tamAutor+2) * sizeof(char));
        livro->autor[tamAutor] = c;
        tamAutor++;
    }
    livro->autor[tamAutor] = '\0';

    scanf("%d\n", &livro->ano);
}

/**
 * Imprime os atributos da TAD tLivros (título, autor e ano de publicação).
 * 
 * @param livro Um ponteiro para o livro cujos atributos serão impressos
*/
void ImprimeLivro(tLivros* livro){
    printf("Titulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Ano de Publicacao: %d\n", livro->ano);
}

/**
 * Retorna o título do livro.
 * 
 * @param livro Ponteiro para o livro cujo título será retornado.
 * @return O título do livro.
*/
char *getTitulo(tLivros* livro){
    return livro->titulo;
}

/**
 * Função para liberar toda a memória alocada por um livro
 * 
 * @param livro Um ponteiro para o livro cujos atributos serão apagados/liberados
*/
void ApagaLivro(tLivros* livro){
    free(livro->autor);
    free(livro->titulo);
    free(livro);
}