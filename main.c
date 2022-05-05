#include <stdio.h>
#include <stdlib.h>

const char *file_name = "grafo.txt";
FILE *file;
#define DATA_SIZE 1000

void menu()
{
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("1 - Ver o número de vértices e arestas e ver quais arestas estão no grafo.\n");
    printf("2 - Ver nó(s) com aresta(s) em laço.\n");
    printf("3 - Ver quais vértices tem arestas múltiplas e quantas arestas múltiplas existem entre eles.\n");
    printf("4 - Exibir o grau de um vértice.\n");
    printf("5 - Exibir a soma de todos os graus dos vértices.\n");
    printf("6 - Ver os vértices que são isolados.\n");
    printf("7 - Verificar se o número de arestas é no máximo igual ao número de combinações de |V| tomadas 2 a 2.\n");
    printf("8 - Verificar se o número total de vértices com grau ímpar e par.\n");
    printf("9 - Verificar se o grafo é simples.\n");
    printf("10 - Verificar se o grafo é completo.\n");
    printf("11 - Verificar se o grafo carregado é regular e exibir o grau apresentado pelos seus vértices.\n");
    printf("12 - Verificar a existência de passeio.\n");
    printf("13 - Remover aresta.\n");
    // printf("14 - Remover vértice.\n");
    printf("14 - Sair.\n");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
    printf("Digite a opção desejada: ");
}

int verifica_laco(int **M, int i, int j)
{
    if (i == j)
    {
        if (M[i][j] != 0)
            return 1;
    }
    return 0;
}

void laco(int **M, int v)
{
    int i, j, ver = 0;
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (verifica_laco(M, i, j))
            {
                printf("\n- Possui laço no vértice V%d.\n", i + 1);
                ver = 1;
            }
        }
    }
    if (ver == 0)
    {
        printf("\n-> Não possui laços!\n");
    }
    printf("\n");
}

int arestas_total(int **M, int v, int arestas)
{
    int i, j;
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (M[i][j] > 0)
                arestas += M[i][j];
        }
    }
    return (arestas / 2);
}

void imprime_arestas(int **M, int v)
{
    int i, j, k = 0, celula;
    // fseek(file, 1, SEEK_SET);

    // while (!feof(file))
    // {
    //     fscanf(file, "%d", &i);
    //     fscanf(file, "%d", &j);

    //     printf("v%d -> v%d\n", i, j);
    // }
    for (int i = 0; i < v; i++)
    {
        for (int j = k; j < v; j++)
        {
            celula = M[i][j];

            if (celula > 0)
            {
                if (i != j)
                {
                    while (celula > 0)
                    {
                        printf("v%d -> v%d\n", i + 1, j + 1);
                        celula--;
                    }
                }
                else
                {
                    printf("v%d -> v%d\n", i + 1, j + 1);
                }
            }
        }
        k++;
    }

    printf("\n");
}

void arestas_multiplas(int **M, int v)
{
    int i, j, cont = 0;
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (M[i][j] > 1)
            {
                printf("\n- Possui arestas múltiplas entre os vértices V%d,V%d.\n", i + 1, j + 1);
                cont++;
            }
        }
    }

    cont == 0 ? printf("\n-> Não possui arestas múltiplas!") : printf("\n-> O total de arestas múltiplas é %d!\n\n", cont);
}

void grau_do_vertice(int **M, int v, int opt_v)
{
    int soma = 0, j;

    for (j = 0; j < v; j++)
    {
        soma += M[opt_v - 1][j];
    }
    printf("\nGrau do vértice V%d = %d", opt_v, soma);
    if (soma == 0)
        printf(", ou seja, é um vértice isolado!");
    printf("\n\n");
}

void somatorio_dos_vertices(int **M, int v)
{
    int soma = 0, i, j;

    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            soma += M[i][j];
        }
    }
    printf("Somatório dos graus dos vértices é %d\n\n", soma);
}

void isolaaadoo(int **M, int v)
{
    int soma = 0, i, j, ver = 0;

    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            soma += M[i][j];
        }
        if (soma == 0)
        {
            printf("- v%d é um vértice isolado;\n", i + 1);
            ver = 1;
        }
        soma = 0;
    }

    if (ver == 0)
    {
        printf("\n-> Nao há vértices isolados!\n");
    }
    printf("\n");
}

void grau_impar_par(int **M, int v)
{
    int i, j, soma = 0, num_v_grau_impar = 0;
    // se o numero total de vertices com grau impar é sempre par
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            soma += M[i][j];
        }
        if (soma % 2 != 0)
            num_v_grau_impar += 1;
        soma = 0;
    }
    printf("O teorema do numero total de vértices com grau ímpar somados resultam em um número par se verifica? ");
    if (num_v_grau_impar % 2 == 0)
        printf("\n\n-> Sim, se verifica!");
    else
        printf("\n\n-> Não, logo, isto não é um grafo!");
    printf("\n\n");
}

void grafo_simples(int **M, int v)
{
    int i, j, verLaco, verMult = 0;

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            verLaco = verifica_laco(M, i, j);

            if (M[i][j] > 1)
            {
                verMult = 1;
            }

            if (verLaco || verMult)
            {
                break;
            }
        }
        if (verLaco || verMult)
        {
            break;
        }
    }

    verLaco || verMult ? printf("-> Não é um grafo simples!") : printf("-> É um grafo simples");
    printf("\n\n");
}

void grafo_completo(int **M, int v)
{
    int i, j, notComp = 0;

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (i == j)
            {
                if (M[i][j] > 0)
                    notComp = 1;
            }
            else
            {
                if (M[i][j] != 1)
                    notComp = 1;
            }
        }
    }
    notComp ? printf("-> Este não é um grafo completo") : printf("-> Este é um grafo completo");
    printf("\n\n");
}

void grafo_regular(int **M, int v)
{
    int i, j, base, soma = 0, notReg = 0;

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            soma += M[i][j];
        }
        if (i == 0)
            base = soma;
        else if (base != soma)
        {
            notReg = 1;
            break;
        }
        soma = 0;
    }
    notReg ? printf("Este não é um grafo regular") : printf("Este é um grafo regular, e o grau deles é %d", base);
    printf("\n\n");
}

void passeio(int **M, int opt_v, int k, int v, int ant)
{
    int j;

    if (k == 0)
    {
        printf("\nFim do passeio!\n\n");
        return;
    }
    else
    {
        for (j = 0; j < v; j++)
        {
            if (opt_v != j && j != ant && M[opt_v][j] >= 1)
            {
                printf("\n v%d -> v%d\n", opt_v + 1, j + 1);
                passeio(M, j, k - 1, v, opt_v);
                break;
            }
        }
    }
}

void remove_aresta(int **M, int v, int v1, int v2)
{
    int i, j;
    if ((M[v1][v2] >= 0) || (M[v2][v1] >= 0))
    {
        if (M[v1][v2] > 1 && v1 != v2)
        {
            M[v1][v2]--;
            M[v2][v1]--;
        }
        else
        {
            M[v1][v2] = 0;
            M[v2][v1] = 0;
        }

        printf("\n-> A aresta foi removida!\n\n");
    }
    else
    {
        printf("-> Esta aresta não existe\n");
    }
}

void system_pause()
{
    char continuar;
    printf("Pressione Enter para continuar...");
    getchar();
    scanf("%c", &continuar);
}

void print_matrix(int **M, int v)
{
    printf("Sua Matriz:\n\n");

    int i, j;

    printf("    ");
    for (int i = 0; i < v; i++)
    {
        printf("v%d ", i + 1);
    }
    printf("\n");

    for (i = 0; i < v; i++)
    {
        printf("v%d ", i + 1);
        for (j = 0; j < v; j++)
        {
            printf(" %d ", M[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int i, j, v, arestas = 0, opcao = 0, opt_v, k, v1, v2;
    int cont = 2, celula;

    file = fopen(file_name, "r");
    int line = 0;

    // Escrever num txt
    FILE *output;

    fscanf(file, "%d", &v);

    int **M = malloc(sizeof(int *) * v);
    for (i = 0; i < v; i++)
        M[i] = (int *)malloc(sizeof(int) * v);

    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            M[i][j] = 0;
        }
    }

    while (!feof(file))
    {
        fscanf(file, "%d", &i);
        fscanf(file, "%d", &j);

        i--;
        j--;

        if (i == j)
        {
            M[i][j] += 2;
        }
        else
        {
            M[i][j] += 1;
            M[j][i] += 1;
        }
    }

    arestas = arestas_total(M, v, arestas);
    if (!(arestas <= (v * (v - 1)) / 2))
    {
        printf("As sequências de números não formam um grafo, pois não respeitam o teorema de arestas com o somatório dos graus!\n");
    }
    else
    {
        do
        {
            system("clear");
            print_matrix(M, v);
            menu();
            scanf("%d", &opcao);
            system("clear");
            switch (opcao)
            {

            case 1:
                printf("- Número de vértices: %d\n", v);
                printf("\n- Número de arestas: %d\n", arestas);
                printf("\n- As arestas são:\n\n");
                imprime_arestas(M, v);
                break;
            case 2:
                printf("O seu Grafo: \n");
                laco(M, v);
                break;
            case 3:
                printf("O seu Grafo:\n");
                arestas_multiplas(M, v);
                break;
            case 4:
                do
                {
                    printf("Qual dos %d vértices você deseja ver? ", v);
                    scanf("%d", &opt_v);

                    if ((opt_v < 0) || (opt_v > v))
                    {
                        printf("Vértice inválido, tente um número entre 1 e %d\n\n", v);
                    }

                } while ((opt_v < 0) || (opt_v > v));

                grau_do_vertice(M, v, opt_v);
                break;
            case 5:
                somatorio_dos_vertices(M, v);
                break;
            case 6:
                isolaaadoo(M, v);
                break;
            case 7:
                (!(arestas <= (v * (v - 1)) / 2)) ? printf("O teorema não se verifica!\n\n") : printf("O teorema se verifica!\n\n");
                break;
            case 8:
                grau_impar_par(M, v);
                break;
            case 9:
                printf("Este Grafo:\n\n");
                grafo_simples(M, v);
                break;
            case 10:
                printf("Este Grafo:\n\n");
                grafo_completo(M, v);
                break;
            case 11:
                printf("Este Grafo:\n\n");
                grafo_regular(M, v);
                break;
            case 12:
                do
                {
                    printf("Em qual vértice voce quer iniciar o passeio? ");
                    scanf("%d", &opt_v);

                    printf("Quantos passos deve ter o passeio? ");
                    scanf("%d", &k);

                    if (opt_v < 0 || opt_v > v)
                        printf("Vértice inválido, tente novamente!");
                    if (k < 0)
                        printf("Caminho inválido, tente novamente!");

                    printf("\n");

                } while (opt_v < 0 || opt_v > v || k < 0);

                if (k <= arestas && arestas > 0)
                    passeio(M, opt_v, k, v, -1);
                else
                    printf("O número de passos é maior que o número de arestas\n\n");
                break;
            case 13:
                print_matrix(M, v);
                do
                {
                    printf("\nDigite o vértice de um extremo da aresta: v");
                    scanf("%d", &v1);
                    printf("Digite o vértice do segundo extremo da aresta: v");
                    scanf("%d", &v2);

                    v1--;
                    v2--;

                    if ((v1 >= v) || (v1 < 0) || (v2 >= v) || (v2 < 0))
                    {
                        printf("\nAlgum dos vértices não existe!\n");
                    }

                } while ((v1 >= v) || (v1 < 0) || (v2 >= v) || (v2 < 0));

                remove_aresta(M, v, v1, v2);
                break;
            // case 14:
            //     break;
            case 14:
                k = 0;
                fseek(stdin, 0, SEEK_END);
                output = fopen("grafo final.txt", "w");

                fprintf(output, "%d\n", v);

                for (int i = 0; i < v; i++)
                {
                    for (int j = k; j < v; j++)
                    {
                        celula = M[i][j];

                        if (celula > 0)
                        {
                            if (i != j)
                            {
                                while (celula > 0)
                                {
                                    fprintf(output, "%d %d\n", i + 1, j + 1);
                                    celula--;
                                }
                            }
                            else
                            {
                                fprintf(output, "%d %d\n", i + 1, j + 1);
                            }
                        }
                    }
                    k++;
                }

                fclose(output);

                return 0;
            default:
                printf("\nOpção invalida. Digite novamente a opção desejada.\n");
            }
            system_pause();
            system("clear");
        } while (opcao != 14);
    }

    return 0;
}