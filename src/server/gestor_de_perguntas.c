#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilitarios.c"

#define LER "r"
#define CAMINHO_TOTAL_PERGUNTAS "perguntas\\total.csv"

// Ler e escrever as respostas a uma determinada pergunta na consola
void ler_respostas(int n)
{
    FILE *p2 = fopen(CAMINHO_TOTAL_PERGUNTAS, LER);
    char linha[1024];
    int count = 1;

    while (fgets(linha, 1024, p2) != NULL)
    {
        char *tmp = strdup(linha);

        if (count == n)
        {
            printf("A - %s\n", ler_campo(tmp, 2));
            tmp = strdup(linha);
            printf("B - %s\n", ler_campo(tmp, 3));
            tmp = strdup(linha);
            printf("C - %s\n", ler_campo(tmp, 4));
            tmp = strdup(linha);
            printf("D - %s\n", ler_campo(tmp, 5));
        }

        count++;

        free(tmp);
    }

    fclose(p2);
}

// Ler e escrever um pergunta e as suas respostas na consola
void ler_pergunta_e_respostas(int n)
{
    char linha[1024];
    FILE *p1 = fopen(CAMINHO_TOTAL_PERGUNTAS, LER);
    int count = 1;

    while (fgets(linha, 1024, p1) != NULL)
    {
        char *tmp = strdup(linha);

        if (count == n)
        {
            printf("\n%s\n", ler_campo(tmp, 1));
        }

        count++;

        free(tmp);
    }

    fclose(p1);

    ler_respostas(n);
}

// Retornar a resposta certa
char ler_resposta_certa(int n)
{
    FILE *c = fopen(CAMINHO_TOTAL_PERGUNTAS, LER);
    char linha[1024];
    int count = 1;

    while (fgets(linha, 1024, c) != NULL)
    {
        char *tmp = strdup(linha);

        if (count == n)
        {
            return (ler_campo(tmp, 6)[0]);
        }

        count++;
        free(tmp);
    }

    fclose(c);
    return 1;
}

// Validar a opção indicada pelo jogador
int avaliar_resposta(char resposta)
{
    switch (resposta)
    {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 't':
        case '\n':
            wprintf(L"\nIntroduza a resposta em letra maiúscula !!!\n");
            break;

        case 'A':
        case 'B':
        case 'C':
        case 'D':
            return 0;
            break;

        case 'T':
            break;

        default:
            wprintf(L"\nIntroduza uma resposta válida !!!\n");
            break;
    }

    return 1;
}