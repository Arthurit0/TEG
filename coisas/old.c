#include <stdio.h>
#include <stdlib.h>

int main()
{

    int i, j, a, v = 0, soma = 0, soma_total = 0, num_v_grau_impar = 0, k = 0, arestas = 0;

    // printf("Quantos vertices tem seu grafo?\n");
    // scanf("%d", &v);

    int **M = malloc(sizeof(int) * v);
    for (i = 0; i < v; i++)
        M[i] = malloc(sizeof(int) * v);

    // int M[v][v];
    for (i = 0; i < v; i++)
    {
        for (j = k; j < v; j++)
        {
            // printf("V%d,V%d:", i + 1, j + 1);
            // scanf("%d", &a);

            if (i == j)
                M[i][j] = a;
            else
                M[i][j] = a;

            if (i != j)
                M[j][i] = a;
        }
        k++;
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
    // laços
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (i == j)
            {
                if (M[i][j] != 0)
                    printf("\nLaco no vertice V%d.\n", i + 1);
            }
        }
    }

    printf("\n------------------------\n");
    // arestas multiplas entre dois vertices
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (M[i][j] > 1 && i != j)
                printf("\nPossui arestas multiplas entre os vertices V%d,V%d.\n", i + 1, j + 1);
        }
    }

    printf("\n------------------------\n");
    // Grau de um vertice e vertice isolaaadoo
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            soma += M[i][j];
            soma_total += M[i][j];
        }
        printf("\nGrau do Vertice V%d = %d", i + 1, soma);
        if (soma == 0)
            printf(", ou seja, eh um vertice isolado!");
        printf("\n");
        soma = 0;
    }
    printf("\n------------------------\n");
    // Numero maximo de arestas
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (M[i][j] > 0)
                arestas += M[i][j];
        }
    }
    arestas = arestas / 2;

    printf("\nO teorema do numero maximo de arestas se verifica? ");
    if (arestas <= (v * (v - 1)) / 2)
        printf("SIM!");
    else
        printf("NAO!");

    printf("\n");

    printf("\n------------------------\n");
    // Teorema do somatorio dos graus = 2*E

    // printf("soma total dos graus:%d   total de arestas: %d", soma_total, arestas);
    printf("\nO teorema do somatorio dos graus = 2* arestas se verifica? ");
    if (soma_total == 2 * arestas)
        printf("SIM!");
    else
        printf("NAO!");

    printf("\n");

    printf("\n------------------------\n");
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
    printf("\nO teorema do numero total de vertices com grau impar eh sempre par se verifica? ");
    if (num_v_grau_impar % 2 == 0)
        printf("SIM!");
    else
        printf("NAO!");

    printf("\n");
    printf("\n------------------------\n");

    // free na matriz
    for (i = 0; i < v; i++)
        free(M[i]);
    free(M);

    return 0;
}

