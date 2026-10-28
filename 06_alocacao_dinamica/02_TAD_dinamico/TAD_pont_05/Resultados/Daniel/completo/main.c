#include "banco.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    char op;
    tBanco *banco = CriaBanco();

    while (1){
        scanf("%c", &op);

        if (op == 'F'){
            break;
            
        } else if (op == 'A'){
            AbreContaBanco(banco);

        } else if (op == 'S'){
            SaqueContaBanco(banco);

        } else if (op == 'D'){
            DepositoContaBanco(banco);

        } else if (op == 'T'){
            TransferenciaContaBanco(banco);

        } else if (op == 'R'){
            ImprimeRelatorioBanco(banco);
        }
    }

    DestroiBanco(banco);

    return 0;
}