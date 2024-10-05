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
    char resultado  = 0;
    while(caractere32 > 1)
    {
        caractere32 >>= 1;
        resultado +=1;
    }
    return resultado;
}

/* unsigned char retornaByteObservado(unsigned caractere)
{
    unsigned char expoente = log2(caractere);
    unsigned char numObservado = 0;
    if (expoente < 8)
    {
        numObservado = 0;
    }
    else if (expoente < 15)
    {
        numObservado = 1;
    }
    else if (expoente < 23)
    {
        numObservado = 2;
    }
    else{
        numObservado = 3;
    }
    return numObservado;
} */

/* void montaBytes(unsigned char qtdBytes, unsigned caractere32)
{
    unsigned char byte8 = 0xff;
    unsigned char byteObeservado = retornaByteObservado(caractere32);
    unsigned aux = 0;
    if (qtdBytes == 1)
    {
        byte8 = (byte8 << 8) + caractere32;
    }
    else
    {
        for (char i = qtdBytes; i >= 0; i--)
        {
            if (i == qtdBytes)
            {
                byte8 = byte8 << (8 - qtdBytes);
                aux = caractere32 >> (8 * byteObeservado);
                byte8 = byte8 + (aux >> (8 - qtdBytes -1));            
            } 
            else if ( i == qtdBytes -1)
                continue;
            else
            {
                byte8 = byte8 << 7;

                byte8 += (caractere32 >> (6 * i)) & 0x3f;
            }
            printf("i: %hhd\n", i);
            printf("%hhu --- %hhx\n", byte8, byte8);
            byte8 = 0xff;
        }
    }
} */

int main(void)
{
    unsigned numLittleEndian = 0x1d11e;
    printf("%u\n", contaBytes(numLittleEndian));

    return 0;
}