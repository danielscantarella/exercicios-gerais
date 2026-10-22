#include "cidade.h"

int main(){
    
    tCidade cidade = CriaCidade();
    cidade = LeEntrada(cidade);
    ProcessaAtaques(cidade);
    ImprimeDados(cidade);
    LiberaCidade(cidade);

    return 0;
}