#include <stdio.h>
#include "converteutf832.h"

/* unsigned char contaQtdBytes(unsigned char byte)
{
    unsigned char cont = 0;
    unsigned char i = 7;
    while((byte>>i) & 1)
    {
        cont++;
        i--;
    }
    return cont;
}

unsigned char pegaBit(unsigned char caractere, unsigned char qtdBytes)
{
    unsigned char novoByte = 0;
    printf("qtdBytes -> %hhd\n", qtdBytes);
    printf("mascara -> %hhd\n", (0xff >> (qtdBytes + 1)));
    novoByte = caractere & (0xff >> (qtdBytes + 1));
    return novoByte;
}

unsigned int colocaBits(unsigned char bits, unsigned int caractere32, unsigned char qtdBytes)
{
    for (unsigned char i = (8-qtdBytes - 1); i > 0; i--)
    {
        caractere32 = caractere32 << 1;
        caractere32 += (bits >> (i-1)) & 1;
    }
    return caractere32;
} */

int main(void)
{
    FILE* arqIn = fopen("utf8_peq.txt", "r");
    FILE* arqOut = fopen("utf32_teste.txt", "w");
    int num = convUtf8p32(arqIn, arqOut);
    fclose(arqIn);
    fclose(arqOut);
    return num;
}