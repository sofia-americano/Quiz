#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "gestor_de_ficheiros.c"
#include "gestor_de_perguntas.c"

#define REGRAS "\n\t\tRegras do Jogo das Perguntas\n\
\n\
- Cada categoria tem apenas 5 perguntas definidas.\n\
- Devera escolher apenas uma hipotese.\n\
- Cada resposta certa vale 1 ponto e resposta errada vale 0 pontos.\n\
- Cada jogador tem um TOKEN que pode utilizar para saber a resposta de uma pergunta.\n\
- Para utilizar o token devera introduzir T, como resposta.\n\
- So podera responder com uma das seguintes letras A, B, C, D ou T.\n\
- No final, o jogador com mais pontos vence o jogo.\n\
\n\
"

#define CATEGORIAS "\n\t\tCategorias\n\
\n\
1 - Arte\n\
2 - Astronomia\n\
3 - Desporto\n\
4 - Entretenimento\n\
5 - Geografia\n\
6 - Historia\n\
7 - Jogos\n\
8 - Musica\n\
9 - Todas\n\
\n\
Devera responder, como indicado no exemplo abaixo, com os numeros espacados e terminar com '0'.\n\
Exemplo -> '1 4 0' \n\
\n\
"

#define NUMERO_PERGUNTAS_POR_CATEGORIA 5
#define NUMERO_CATEGORIAS 8

int main()
{
    // Configura a linguagem para PT
    setlocale(LC_ALL, "Portuguese");

    // Definição das constantes
    const int tamanho_nome = 256; // número limite de caracteres para o nome dum jogador

    // Para jogar um jogo novo, caso os jogadores o pretendam
    int novo_jogo = 1; // definir se um novo jogo deve ser iniciado ou não (1 -> sim, 0 -> não)
    while (novo_jogo)
    {
        // Definição das variáveis
        int numero_jogadores; // número de jogadores (input utilizador)
        int numero_perguntas; // número de perguntas (input utilizador)
        int numero_categorias_escolhidas = 0; // número de categorias (definido consoante as categorias escolhidas. ver variável a seguir)
        int categorias[NUMERO_CATEGORIAS] = {0}; // categorias (input utilizador)

        printf("\nBem-vindos ao Jogo de Perguntas!\n");
        printf("Autores: Ana Americano & Telmo Silva\n\n");

        novo_jogo = 0;

        // Obter número de jogadores
        wprintf(L"Insira o número de jogadores: ");
        scanf("%d", &numero_jogadores);

        // Obter nome dos jogadores
        char **nome_jogadores = malloc(numero_jogadores * sizeof(*nome_jogadores)); // nome de cada jogador (input utilizador), com base no número de jogadores
        for (int i = 0; i < numero_jogadores; i++)
        {
            nome_jogadores[i] = malloc(tamanho_nome * sizeof(nome_jogadores[0]));
        }

        // Definir variáveis com base no número de jogadores
        int **mapa_perguntas_jogador = malloc(50 * sizeof(*mapa_perguntas_jogador)); // mapa com as perguntas escolhidas para cada jogador, com base nas suas posições no ficheiro total.csv
        for (int i = 0; i < 50; i++)
        {
            mapa_perguntas_jogador[i] = malloc(numero_jogadores * sizeof(mapa_perguntas_jogador[0]));
        }
        int *tokens = malloc(numero_jogadores * sizeof(*tokens)); // token de cada jogador (0 -> não utilizado, 1 -> utilizado)
        int *posicao = malloc(numero_jogadores * sizeof(*posicao)); // posição inicial de cada jogador. utilizado para posteriormente servir de mapa para ordenar o ranking
        int *pontuacao = malloc(numero_jogadores * sizeof(*pontuacao)); // pontuação de cada jogador

        printf("\nInsira o nome do(s) jogador(es):\n");
        for (int i = 0; i < numero_jogadores; i++)
        {
            printf("Nome do jogador %d: ", i + 1);
            scanf("%s", nome_jogadores[i]);
        }

        // Definição das perguntas
        int suficiente = 1;
        while (suficiente)
        {
            suficiente = 0;

            // Obter o número de perguntas
            printf("\nQuantas perguntas por partida? [1-5]\n");
            wprintf(L"Número de perguntas: ");
            scanf("%d", &numero_perguntas);

            system("cls");
            printf("\nSejam Bem-Vindos ao Jogo de Perguntas!\n");
            for (int i = 0; i < numero_jogadores; i++)
            {
                printf("%s \n", nome_jogadores[i]);
            }
            pause();

            // Apresentação das regras do jogo das perguntas
            system("cls");
            printf(REGRAS);
            pause();

            // Apresentação das categorias do jogo
            system("cls");
            printf(CATEGORIAS);

            // Escolha das categorias a jogar
            int cat;
            wprintf(L"Indique as categorias que pretende jogar: ");
            scanf("%d", &cat);
            while (cat != 0)
            {
                if (cat == 9)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        categorias[i] = 1;
                    }
                    scanf("%d", &cat);
                }
                else
                {
                    categorias[cat - 1] = 1;
                    scanf("%d", &cat);
                }
            }

            // Obter as perguntas das categorias selecionadas e para as persistir num novo ficheiro
            juntar_categorias(categorias);
            system("cls");

            for (int i = 0; i < 8; i++)
            {
                numero_categorias_escolhidas += categorias[i];
            }

            // Validar se o número de perguntas escolhidas estão disponíveis tendo em conta a quantidade de perguntas existentes
            if (numero_perguntas > (numero_categorias_escolhidas * NUMERO_PERGUNTAS_POR_CATEGORIA))
            {
                for (int i = 0; i < 8; i++)
                {
                    categorias[i] = 0;
                }

                numero_categorias_escolhidas = 0;
                suficiente = 1;
                wprintf(L"\n\nNúmero de perguntas indisponível para o número de categorias escolhidas.\nPor favor insira um novo número de perguntas, ou escolha mais categorias.\n\n");
            }
        }

        srand(time(NULL));

        // Início do jogo
        for (int i = 0; i < numero_perguntas; i++)
        {
            for (int j = 0; j < numero_jogadores; j++)
            {
                // Gerar número aleatório para selecionar pergunta
                int ind = 1;
                while (ind)
                {
                    mapa_perguntas_jogador[i][j] = (rand() % (numero_categorias_escolhidas * NUMERO_PERGUNTAS_POR_CATEGORIA) + 1);

                    ind = 0;

                    for (int h = 0; h < i; h++)
                    {
                        if (mapa_perguntas_jogador[i][j] == mapa_perguntas_jogador[h][j])
                        {
                            ind = 1;
                        }
                    }
                }

                // Escrever pergunta selecionada e possíveis respostas para um determinado jogador
                printf("Pergunta %d de %d\nJogador %s\n", i + 1, numero_perguntas, nome_jogadores[j]);
                ler_pergunta_e_respostas(mapa_perguntas_jogador[i][j]);

                // Ler a resposta do jogador
                char resposta; // resposta do utilizador
                int ciclo_resposta = 1;
                while (ciclo_resposta)
                {
                    printf("\nResposta ? ");
                    scanf(" %c", &resposta);

                    ciclo_resposta = avaliar_resposta(resposta);

                    // Obter a resposta certa caso um token tenha sido acionado
                    if (resposta == 'T')
                    {
                        if (!tokens[j])
                        {
                            tokens[j] = 1;
                            wprintf(L"\nA resposta certa é a opçao %c.\n", ler_resposta_certa(mapa_perguntas_jogador[i][j]));
                        }
                        else
                        {
                            wprintf(L"\nO seu token já foi usado !!!\n");
                        }
                    }
                }

                // Validar a resposta
                if (resposta == ler_resposta_certa(mapa_perguntas_jogador[i][j]))
                {
                    pontuacao[j]++;
                    printf("\nCerto!!!\n");
                }
                else
                {
                    printf("\nErrado!!!\n");
                }

                pause();
                system("cls");
            }
        }

        // Ajustar ranking do jogo
        for (int i = 0; i < numero_jogadores; i++)
        {
            posicao[i] = i;
        }

        ordenar_ranking(pontuacao, posicao, numero_jogadores);

        // Apresentar resultados do jogo
        if (numero_jogadores == 1)
        {
            printf("\nParabens %s, acertaste %d de %d perguntas!", nome_jogadores[0], pontuacao[0], numero_perguntas);
        }
        else
        {
            printf("\nPara um total de %d perguntas.\n\n", numero_perguntas);
            printf("Jogadores   |   Pontos");

            for (int j = 0; j < numero_jogadores; j++)
            {
                printf("\n%-12s|     %d", nome_jogadores[posicao[j]], pontuacao[j]);
            }
        }

        // Registar resultados do jogo
        registar_jogo(numero_jogadores, numero_perguntas, nome_jogadores, posicao, pontuacao);
        registar_historico();

        // Libertar memória
        free(nome_jogadores);
        free(mapa_perguntas_jogador);
        free(tokens);
        free(posicao);
        free(pontuacao);

        // Perguntar ao(s) jogador(es) se pretende(m) jogar um novo jogo
        char jogar_novamente; // input do utilizador para o início de um novo jogo (S/s -> sim, outro caracter -> não) 
        wprintf(L"\n\nPretende(m) começar um novo jogo? [S/N]\n");
        scanf("%c", &jogar_novamente);

        if (jogar_novamente == 'S' || jogar_novamente == 's')
        {
            novo_jogo = 1;
            system("cls");
        }
    }

    return 0;
}