#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *arq;
FILE *file;

int *neighbours(int **IM_binaria, int i, int j)
{
    // Aloca espaços
    int Viz_4 = malloc(4 * sizeof(int *));
    for (int k = 0; k < 2; k++)
    {
        Viz_4[k] = malloc(2 * sizeof(int));
    }

    Viz_4[1][1] = i - 1;
    Viz_4[1][2] = j;

    Viz_4[2][1] = i;
    Viz_4[2][2] = j + 1;

    Viz_4[3][1] = i + 1;
    Viz_4[3][2] = j;

    Viz_4[4][1] = i;
    Viz_4[4][2] = j - 1;

    // *Viz_4 = [i-1, j];
    // *(Viz_4 + 1) = ;
    // *(Viz_4 + 2) = IM_binaria[i + 1][j];
    // *(Viz_4 + 3) = IM_binaria[i][j - 1];

    // for (int k = 0; k < 4; k++)
    // {
    //     printf("%d ", *(Viz_4 + k));
    // }

    return Viz_4;
}

void pesquisa(int **IM_binaria, int **marcados, int i, int j)
{
    marcados[i][j] = 1;
    int l_linha, c_linha;

    int *Viz_4 = neighbours(IM_binaria, i, j);

    for (int k = 0; k < 4; k++)
    {
        l_linha = Viz_4[k][1];
        c_linha = Viz_4[k][2] if (IM_binaria[l_l][Viz_4[k][2]] == 1 && marcados[Viz_4[k][1]][Viz_4[k][2]] == 0)
        {
            pesquisa(IM_binaria, marcados, Viz_4[k][1], Viz_4[k][2])
        }
    }

    // each(i ',j')
    //         in Viz_4 if (IM_binaria[L',C'] == 1 && Marcados[L’, C’] == 0)
    //             search(IM_binaria, Marcados, L',C');
}

void findComponents(int **IM_binaria, int **marcados, int num_lin, int num_col, int cont)
{
    int i, j;
    for (i = 0; i < (num_lin)-1; i++)
    {
        for (j = 0; j < (num_col)-1; j++)
        {
            if (IM_binaria[i][j] == 1 && marcados[i][j] == 0)
            {
                pesquisa(IM_binaria, marcados, i, j);
                cont++;
            }
        }
    }
}

void func(int **IM_binaria, int num_lin, int num_col)
{

    int cont = 0, i, j, **marcados;

    marcados = malloc(num_lin * sizeof(int *));
    for (i = 0; i < num_lin; i++)
    {
        marcados[i] = malloc(num_col * sizeof(int));
    }
    for (i = 0; i < num_lin; i++)
    {
        for (j = 0; j < num_col; j++)
        {
            marcados[i][j] = 0;
        }
    }
    // for (i = 0; i < num_lin; i++)
    // {
    //     for (j = 0; j < num_col; j++)
    //     {
    //         printf("%d ", marcados[i][j]);
    //     }
    //     printf("\n");
    //}

    findComponents(IM_binaria, marcados, num_lin, num_col, cont);

    printf("\nQuantidade de componentes conexos: %d\n", cont);
}

int main()
{

    int i = 0, j = 0, cont = 0, num_lin = 0, num_col = 0, **M, x;
    char *linha;

    arq = fopen("im_binaria.txt", "r");
    while (fgets(linha, 1000, arq) != NULL)
    {
        num_lin++;
    }
    num_col = ((strlen(linha) / 2));

    printf("lin :%d\n", num_lin);
    printf("col :%d\n", num_col);

    M = malloc(num_lin * sizeof(int *));

    for (i = 0; i < num_lin; i++)
    {
        M[i] = malloc(num_col * sizeof(int));
    }

    fseek(arq, 0, SEEK_SET);

    int aux_linha = 1;
    char Linha[100];
    char *result;

    while (!feof(arq))
    {
        for (i = 0; i < num_lin; i++)
        {
            for (j = 0; j < num_col; j++)
            {
                fscanf(arq, "%d", &M[i][j]);
            }
        }
    }

    for (i = 0; i < num_lin; i++)
    {
        for (j = 0; j < num_col; j++)
        {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    func(M, num_lin, num_col);

    for (i = 0; i < num_lin; i++)
        free(M[i]);
    free(M);
}
