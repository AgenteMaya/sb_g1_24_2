#include <stdio.h>
#include <math.h>

unsigned int inverteNum(unsigned int caractere32)
{
    unsigned int aux = 0;
    for (unsigned char i = 0; i < 4; i++)
    {
        aux = aux << 8;
        aux += (caractere32 >> (i * 8)) & 0xff;
    }
    return aux;
}

unsigned char contaBytes(unsigned int caractere32)
{
    unsigned log = log2(caractere32);
    printf("expoente: %d\n", log );
    unsigned dividendo = (log2(caractere32)) / 4;
    printf("dividendo: %d\n", dividendo);

    return (((log ) / 4));
}

int main(void)
{
    unsigned numBigEndian = 0x1ed10100;
    unsigned numLittleEndian = 0x0080;

    unsigned numBigInvertido = inverteNum(numBigEndian);

    if(numBigInvertido == numLittleEndian)
    {
        printf("Inverteu!!!\n");
    }
    else
    {
        printf("Não inverteu!!!\n");
    }

    printf("qtd de bytes: %d\n",contaBytes(numLittleEndian));

    return 0;
}