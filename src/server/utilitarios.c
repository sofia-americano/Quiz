#include <stdio.h>
#include <stdlib.h>

// Ordenar jogadores no ranking
void ordenar_ranking(int pontuacao[], int * posicao, int numero_jogadores)
{
    int a, b;
    
    for (int i = 0; i < numero_jogadores; i++)
    {
        for (int j = (i+1); j < numero_jogadores; j++)
        {
            if (pontuacao[i] < pontuacao[j]) 
            {
                a = pontuacao[i];
                pontuacao[i] = pontuacao[j];
                pontuacao[j] = a;

                b = posicao[i];
                posicao[i] = posicao[j];
                posicao[j] = b;
            }
        }
    }
}

// Retornar campo de uma linha dum ficheiro .csv
const char * ler_campo(char * line, int num)
{
    const char * tok;
    for (tok = strtok(line, ";"); tok && * tok; tok = strtok(NULL, ";\n"))
    {
        if (!--num)
        {
            return tok;
        } 
    }

    return NULL;
}

// Versão portuguesa do system("pause")
void pause()
{
    printf("\nPrima enter para continuar...");
    getchar();
    getchar();
}