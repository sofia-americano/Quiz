#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOVA_LINHA "\n"
#define LER "r"
#define ESCREVER "w"
#define ACRESCENTAR "a+"
#define ARTE "perguntas\\arte.txt"
#define ASTRONOMIA "perguntas\\astronomia.txt"
#define DESPORTO "perguntas\\desporto.txt"
#define ENTRETENIMENTO "perguntas\\entretenimento.txt"
#define GEOGRAFIA "perguntas\\geografia.txt"
#define HISTORIA "perguntas\\historia.txt"
#define JOGOS "perguntas\\jogos.txt"
#define MUSICA "perguntas\\musica.txt"
#define CAMINHO_TOTAL_PERGUNTAS "perguntas\\total.csv"
#define ULTIMO_JOGO "resultados\\ultimo_jogo.txt"
#define HISTORICO "resultados\\historico.txt"

// Juntar as categorias selecionadas num só ficheiro
void juntar_categorias(int categorias[])
{
    // Definição de variáveis
    char numero_categoria;
    char carater;

    FILE * arte;
    FILE * astronomia;
    FILE * desporto;
    FILE * entretenimento;
    FILE * geografia;
    FILE * historia;
    FILE * jogos;
    FILE * musica;
    FILE * total = fopen(CAMINHO_TOTAL_PERGUNTAS, ESCREVER);

    // Para cada categoria
    for (int i = 0; i < 8; i++)
    {
        // Verificar se foi selecionada
        if (!categorias[i])
        {
            continue;
        }

        numero_categoria = i + '0';

        // Se sim, então compilar as perguntas no ficheiro final
        switch (numero_categoria)
        {
            case '0':
                arte = fopen(ARTE, LER);
                while ((carater = fgetc(arte)) != EOF)
                {
                    fputc(carater, total);
                }
                fclose(arte);
                break;
            case '1':
                astronomia = fopen(ASTRONOMIA, LER);
                while ((carater = fgetc(astronomia)) != EOF)
                {
                    fputc(carater, total);
                }
                fclose(astronomia);
                break;
            case '2':
                desporto = fopen(DESPORTO, LER);
                while ((carater = fgetc(desporto)) != EOF)
                {
                    fputc(carater, total);
                }
                fclose(desporto);
                break;
            case '3':
                entretenimento = fopen(ENTRETENIMENTO, LER);
                while ((carater = fgetc(entretenimento)) != EOF)
                {
                    fputc(carater, total);
                }
                fclose(entretenimento);
                break;
            case '4':
                geografia = fopen(GEOGRAFIA, LER);
                while ((carater = fgetc(geografia)) != EOF)
                {
                    fputc(carater, total);
                }
                fclose(geografia);
                break;
            case '5':
                historia = fopen(HISTORIA, LER);
                while ((carater = fgetc(historia)) != EOF)
                {
                    fputc(carater, total);
                }
                fclose(historia);
                break;
            case '6':
                jogos = fopen(JOGOS, LER);
                while ((carater = fgetc(jogos)) != EOF)
                {
                    fputc(carater, total);
                }
                fclose(jogos);
                break;
            case '7':
                musica = fopen(MUSICA, LER);
                while ((carater = fgetc(musica)) != EOF)
                {
                    fputc(carater, total);
                }
                fclose(musica);
                break;

            default:
                break;
        }

        fputs(NOVA_LINHA, total);
    }

    fclose(total);
}

// Registar as pontuações de cada jogador no último jogo, num ficheiro de resultados
void registar_jogo(int numero_jogadores, int numero_perguntas, char ** nome_jogadores, int * posicao, int * pontuacao)
{
    time_t tempo;   
    time(&tempo);

    FILE * ultimo_jogo = fopen(ULTIMO_JOGO, ESCREVER);

    fprintf(ultimo_jogo, "Jogado a %s\n", ctime(&tempo));
    fprintf(ultimo_jogo, "No total de %d perguntas.\n\n", numero_perguntas);
    fprintf(ultimo_jogo, "Jogadores   |   Pontos");

    for(int j = 0; j < numero_jogadores; j++)
    {
        fprintf(ultimo_jogo, "\n%-12s|     %d", nome_jogadores[posicao[j]], pontuacao[j]);
    } 

    fprintf(ultimo_jogo, "\n\n");
    fclose(ultimo_jogo);
}

// Registar último jogo num ficheiro com o histórico de resultados
void registar_historico()
{
    FILE * ultimo_jogo = fopen (ULTIMO_JOGO, ACRESCENTAR);
    FILE * historico = fopen (HISTORICO, ACRESCENTAR);
    char buf[1000];

    while (!feof(ultimo_jogo))
    {
        fgets(buf, sizeof(buf), ultimo_jogo);
        fprintf(historico, "%s", buf);
    }

    fprintf(historico, NOVA_LINHA);
    fclose(ultimo_jogo);
    fclose(historico);
}
