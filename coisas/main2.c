#include <stdio.h>
#include <stdlib.h>

const char *file_name = "grafo.txt";

void laco(int **M, int v)
{
    int i, j;
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (verifica_laco(*M, i, j))
            {
                printf("\nLaco no vertice V%d.\n", i + 1);
            }
        }
    }
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

int main()
{

    int i, j, a, v, soma = 0, soma_total = 0, num_v_grau_impar = 0, k = 0, arestas = 0, opcao = 0;

    FILE *file = fopen(file_name, "r");
    int line = 0;

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

    printf("\nSua Matriz:\n");
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            printf(" %d", M[i][j]);
        }
        printf("\n");
    }
    printf("\n------------------------\n");

    laco(*M, v);

    

    // laços

    // printf("\n------------------------\n");
    // // arestas multiplas entre dois vertices
    // for (i = 0; i < v; i++)
    // {
    //     for (j = 0; j < v; j++)
    //     {
    //         if (M[i][j] > 1)
    //             printf("\nPossui arestas multiplas entre os vertices V%d,V%d.\n", i + 1, j + 1);
    //     }
    // }

    // printf("\n------------------------\n");
    // // Grau de um vertice e vertice isolaaadoo
    // for (i = 0; i < v; i++)
    // {
    //     for (j = 0; j < v; j++)
    //     {
    //         soma += M[i][j];
    //         soma_total += M[i][j];
    //     }
    //     printf("\nGrau do Vertice V%d = %d", i + 1, soma);
    //     if (soma == 0)
    //         printf(", ou seja, eh um vertice isolado!");
    //     printf("\n");
    //     soma = 0;
    // }
    // printf("\n------------------------\n");
    // // Numero maximo de arestas
    // for (i = 0; i < v; i++)
    // {
    //     for (j = 0; j < v; j++)
    //     {
    //         if (M[i][j] > 0)
    //             arestas += M[i][j];
    //     }
    // }
    // arestas = arestas / 2;

    // printf("\nO teorema do numero maximo de arestas se verifica? ");
    // if (arestas <= (v * (v - 1)) / 2)
    //     printf("SIM!");
    // else
    //     printf("NAO!");

    // printf("\n");

    // printf("\n------------------------\n");
    // // Teorema do somatorio dos graus = 2*E

    // // printf("soma total dos graus:%d   total de arestas: %d", soma_total, arestas);
    // printf("\nO teorema do somatorio dos graus = 2* arestas se verifica? ");
    // if (soma_total == 2 * arestas)
    //     printf("SIM!");
    // else
    //     printf("NAO!");

    // printf("\n");

    // printf("\n------------------------\n");
    // // se o numero total de vertices com grau impar é sempre par
    // for (i = 0; i < v; i++)
    // {
    //     for (j = 0; j < v; j++)
    //     {
    //         soma += M[i][j];
    //     }
    //     if (soma % 2 != 0)
    //         num_v_grau_impar += 1;
    //     soma = 0;
    // }
    // printf("\nO teorema do numero total de vertices com grau impar eh sempre par se verifica? ");
    // if (num_v_grau_impar % 2 == 0)
    //     printf("SIM!");
    // else
    //     printf("NAO!");

    // printf("\n");
    // printf("\n------------------------\n");

    // // free na matriz
    // for (i = 0; i < v; i++)
    //     free(M[i]);
    // free(M);

    return 0;
}

// void arestamultilpla()
// {
// }

// int grau()
// {
// }

// void isolaaadoo()
// {
// }

// int numer_aresta_max()
// {
// }
// void grau_total()
// {
// }
// int vertice_grau_impar()
// {
// }

void menu()
{
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("1 - Ver o número de vertices e arestas e ver quais arestas estao no grafo.");
    printf("2 - Ver no(s) com aresta(s) em laco.");
    printf("3 - Ver quais vertices tem arestas multiplas e quantas arestas multilplas existem entre eles.");
    printf("4 - Exibir o grau de um vertice.");
    printf("5 - Exibir a soma de todos os graus dos vertices.");
    printf("6 - Ver vertices sao isolados.");
    printf("7 - Verificar se o número de arestas é no máximo igual ao número de combinacoes de |V| tomadas 2 a 2.");
    printf("8 - Verificar se o número total de vértices com grau impar e par.");
    printf("9 - Verificar se o grafo eh simples.");
    printf("10 - Verificar se o grafo e completo.");
    printf("11 - verificar se o grafo carregado eh regular e exibir o grau apresentado pelos seus vertices.");
    printf("12 - Verificar a existencia de pesseio.");
    printf("13 - Remover aresta.");
    printf("14 - Remover vertice.");
    printf("17 - Sair.");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n ");
    printf("Digite a opcao desejada: ");
}
int arestas_total(int **M, int v, int *arestas)
{
    int i,j;
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (M[i][j] > 0)
                arestas += M[i][j];
        }
    }
    return (*arestas/2);
}