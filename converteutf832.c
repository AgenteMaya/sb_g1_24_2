/* Maria Eduarda da Fonseca  2212985 33WB */
/* Mayara Ramos Damazio 2210833 33WC */

#include "converteutf832.h"
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
    return (((log2(caractere32) + 1) / 8) + 1);
}

unsigned char contaQtdBytes(unsigned char byte)
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

unsigned char pegaBits(unsigned char caractere, unsigned char qtdBytes)
{
    unsigned char novoByte = 0;
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
}

int colocaInteiroNoArquivo(FILE *arqOut, int caractere32)
{
    int verificaErro = 0;
    for(unsigned char i = 0; i < 4; i++)
    {
        verificaErro = fputc((caractere32 >> i * 8), arqOut);
        if (verificaErro == EOF)
        {
            fputs("Erro ao inserir no arquivo", stderr);
            return -1;
        }
    }
    
    return 0;
}

int convUtf32p8(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned int caractere32 = 0;
    unsigned char qtdBytes = 0;
    int verificaEndian = 0; //se e littleEndian, é 0. Senão, é BigEndian
    while (fread(&caractere32, sizeof(unsigned int), 1, arquivo_entrada) == 1)
    {
        if (caractere32 == 0xfeff || caractere32 == 0xfffe0000)
        {
            if (caractere32 == 0xfffe0000)
            {
                verificaEndian = 1;
            }
            continue;
        }            
        if (verificaEndian){
            caractere32 = inverteNum(caractere32);
        }
        qtdBytes = contaBytes(caractere32);

    }
}

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned char caracter = 0;
    unsigned char qtdBytes = 0;
    unsigned char bits = 0;
    unsigned int caractere32 = 0xfeff;
    int verificaErro = 0;
    while(1)
    {
        caracter = fgetc(arquivo_entrada);
        
        qtdBytes = contaQtdBytes(caracter);
        if (qtdBytes != 1)
        {
            verificaErro = colocaInteiroNoArquivo(arquivo_saida, caractere32);
            if (verificaErro)
            {
                return verificaErro;
            }
            caractere32 = 0;
        }
        if(feof(arquivo_entrada))
        {
            break;
        }        
        bits = pegaBits(caracter, qtdBytes);
        caractere32 = colocaBits(bits, caractere32, qtdBytes);
    }
    return 0;
}