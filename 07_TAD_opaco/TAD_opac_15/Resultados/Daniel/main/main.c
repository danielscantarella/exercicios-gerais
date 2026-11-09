#include <stdio.h>
#include <stdlib.h>
#include "dracomania.h"

int main(){

    tDracomania *d = CriaDracomania();

    RodaDracomania(d);

    ImprimeRelatorioDracomania(d);

    LiberaDracomania(d);

    return 0;
}