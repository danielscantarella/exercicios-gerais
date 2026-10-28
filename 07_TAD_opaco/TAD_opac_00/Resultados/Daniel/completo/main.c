#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"

int main(){

    float px=0, py=0, r=0, cx=0, cy=0;

    scanf("%f %f %f %f %f", &cx, &cy, &r, &px, &py);

    tCirculo c = Circulo_Cria(cx, cy, r);
    tPonto p = Pto_Cria(px, py);

    int result = Circulo_Interior(c, p);

    Circulo_Apaga(c);
    Pto_Apaga(p);

    printf("%d\n", result);

    return 0;
}