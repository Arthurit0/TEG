#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *arq;
FILE *file;
int op;
typedef struct {
    int i;
    int j;
} Vizinho;

Vizinho *neighbours4(int **IM_binaria, int i, int j) {
    Vizinho *Viz_4 = malloc(sizeof(Vizinho) * 4);

    Viz_4[0].i = i - 1;
    Viz_4[0].j = j;

    Viz_4[1].i = i;
    Viz_4[1].j = j + 1;

    Viz_4[2].i = i + 1;
    Viz_4[2].j = j;

    Viz_4[3].i = i;
    Viz_4[3].j = j - 1;

    // printf("\n- Dentro da funcao neighbours4:\n");
    // for (int k = 0; k < 4; k++)
    // {
    //     printf("\nViz %d: [%d] [%d]", k, Viz_4[k].i, Viz_4[k].j);
    // }

    // printf("\n");

    return Viz_4;
}

Vizinho *neighbours8(int **IM_binaria, int i, int j) {
    Vizinho *Viz_8 = malloc(sizeof(Vizinho) * 8);

    Viz_8[0].i = i - 1;
    Viz_8[0].j = j;

    Viz_8[1].i = i;
    Viz_8[1].j = j + 1;

    Viz_8[2].i = i + 1;
    Viz_8[2].j = j;

    Viz_8[3].i = i;
    Viz_8[3].j = j - 1;

    Viz_8[4].i = i - 1;
    Viz_8[4].j = j - 1;

    Viz_8[5].i = i - 1;
    Viz_8[5].j = j + 1;

    Viz_8[6].i = i + 1;
    Viz_8[6].j = j - 1;

    Viz_8[7].i = i + 1;
    Viz_8[7].j = j + 1;

    // printf("\n- Dentro da funcao neighbours8:\n");
    // for (int k = 0; k < 8; k++)
    // {
    //     printf("\nViz %d: [%d] [%d]", k, Viz_8[k].i, Viz_8[k].j);
    // }

    // printf("\n");

    return Viz_8;
}
void pesquisa(int **IM_binaria, int **marcados, int i, int j) {
    marcados[i][j] = 1;
    if (op == 4) {
        Vizinho *Viz_4 = neighbours4(IM_binaria, i, j);

        for (int k = 0; k < 4; k++) {
            if (IM_binaria[Viz_4[k].i][Viz_4[k].j] == 1 &&
                marcados[Viz_4[k].i][Viz_4[k].j] == 0)
                pesquisa(IM_binaria, marcados, Viz_4[k].i, Viz_4[k].j);
        }
    } else {
        Vizinho *Viz_8 = neighbours8(IM_binaria, i, j);

        for (int k = 0; k < 8; k++) {
            if (IM_binaria[Viz_8[k].i][Viz_8[k].j] == 1 &&
                marcados[Viz_8[k].i][Viz_8[k].j] == 0)
                pesquisa(IM_binaria, marcados, Viz_8[k].i, Viz_8[k].j);
        }
    }
}

void findComponents(int **IM_binaria, int **marcados, int num_lin, int num_col,
                    int *cont) {
    int i, j;
    for (i = 0; i < (num_lin)-1; i++) {
        for (j = 0; j < (num_col)-1; j++) {
            if (IM_binaria[i][j] == 1 && marcados[i][j] == 0) {
                pesquisa(IM_binaria, marcados, i, j);
                *cont = *cont + 1;
                // printf("\n=> Cont esta em %d\n", *cont);
            }
        }
    }
}

void func(int **IM_binaria, int num_lin, int num_col) {
    int cont = 0, i, j, **marcados;

    marcados = malloc(num_lin * sizeof(int *));
    for (i = 0; i < num_lin; i++) {
        marcados[i] = malloc(num_col * sizeof(int));
    }
    for (i = 0; i < num_lin; i++) {
        for (j = 0; j < num_col; j++) {
            marcados[i][j] = 0;
        }
    }

    findComponents(IM_binaria, marcados, num_lin, num_col, &cont);

    printf("\n");

    printf("\nMatriz de marcados:\n");

    for (i = 0; i < num_lin; i++) {
        for (j = 0; j < num_col; j++) {
            printf("%d ", marcados[i][j]);
        }
        printf("\n");
    }

    printf("\nQuantidade de componentes conexos com %d vizinhos: %d\n", op,
           cont);
}

int main() {
    int i = 0, j = 0, cont = 0, num_lin = 0, num_col = 0, **M, x;
    char *linha;

    arq = fopen("im_binaria.txt", "r");
    while (fgets(linha, 1000, arq) != NULL) {
        num_lin++;
    }
    num_col = ((strlen(linha) / 2));

    // printf("Linhas: %d\n", num_lin);
    // printf("Colunas: %d\n", num_col);

    M = malloc(num_lin * sizeof(int *));

    for (i = 0; i < num_lin; i++) {
        M[i] = malloc(num_col * sizeof(int));
    }

    fseek(arq, 0, SEEK_SET);

    int aux_linha = 1;
    char Linha[100];
    char *result;

    while (!feof(arq)) {
        for (i = 0; i < num_lin; i++) {
            for (j = 0; j < num_col; j++) {
                fscanf(arq, "%d", &M[i][j]);
            }
        }
    }

    printf("\n");
    printf("Matriz original:\n");
    for (i = 0; i < num_lin; i++) {
        for (j = 0; j < num_col; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    do {
        printf(
            "\nVoce gostaria de contar os 4 ou 8 vizinhos de cada "
            "componente?\n");
        scanf("%d", &op);
    } while (op != 4 && op != 8);

    func(M, num_lin, num_col);

    printf("\nDar o free\n");

    for (i = 0; i < num_lin; i++) free(M[i]);
    free(M);
    printf("\nFeito!");

    return 0;
}
