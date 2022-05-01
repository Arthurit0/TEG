#include <stdio.h>
#include <stdlib.h>

const char* file_name = "grafo.txt";
FILE* file;

void menu();
int verifica_laco(int **M, int i, int j);
void laco(int **M, int v);
int arestas_total(int **M, int v, int arestas);
void imprime_arestas();
void arestas_multiplas();
void grau_do_vertice(int **M, int v, int opt_v);

int main()
{

    int i, j, a, v, soma = 0, soma_total = 0, num_v_grau_impar = 0, k = 0, arestas = 0, opcao=0, opt_v=0;

    file = fopen (file_name, "r");
    int line = 0;

    fscanf(file, "%d", &v);

    int **M = malloc(sizeof(int*) * v);
    for (i = 0; i < v; i++)
        M[i] = (int *)malloc(sizeof(int) * v);

    for (i = 0; i < v; i++){
        for(j = 0; j < v; j++){
            M[i][j] = 0;
        }
    }

    while (!feof (file)){  
      fscanf (file, "%d", &i);
      fscanf (file, "%d", &j);

      i--;
      j--;

      if(i == j){
          M[i][j] += 2;
      }  else{
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

    arestas = arestas_total(M, v, arestas);
    if (!(arestas <= (v * (v - 1)) / 2)){
        printf("As sequências de números não formam um grafo, pois não respeitam o teorema de arestas com o somatório dos graus!\n");
    }else{
    do
    {
        menu();
        scanf("%d", &opcao);

        system("clear");

        switch (opcao)
        {

        case 1:
            printf("Numero de vertices: %d\n", v);

            printf("Numero de arestas total: %d\n",arestas);
            printf("As arestas sao:\n");
            imprime_arestas();
            // system("pause");
            break;
        case 2:
            printf("O Grafo\n");
            laco(M, v);
            break;
        case 3:
            printf("O Grafo\n");
            arestas_multiplas(M, v);
            break;
        case 4:
            system("clear");
            printf("Qual dos %d vertices você deseja ver? ", v);
            scanf("%d",&opt_v);
            grau_do_vertice(M, v, opt_v-1);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;
        case 16:
            break;
        case 17:
            break;

        default:
            printf("\nOpcao invalida. Digite novamente a opcao desejada.\n");
            system("cls"); // Ubuntu: system("clear")
        }

    } while (opcao != 17);
}

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

void menu()
{
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("1 - Ver o número de vertices e arestas e ver quais arestas estao no grafo.\n");
    printf("2 - Ver no(s) com aresta(s) em laco.\n");
    printf("3 - Ver quais vertices tem arestas multiplas e quantas arestas multilplas existem entre eles.\n");
    printf("4 - Exibir o grau de um vertice.\n");
    printf("5 - Exibir a soma de todos os graus dos vertices.\n");
    printf("6 - Ver vertices sao isolados.\n");
    printf("7 - Verificar se o número de arestas é no máximo igual ao número de combinacoes de |V| tomadas 2 a 2.\n");
    printf("8 - Verificar se o número total de vértices com grau impar e par.\n");
    printf("9 - Verificar se o grafo eh simples.\n");
    printf("10 - Verificar se o grafo e completo.\n");
    printf("11 - verificar se o grafo carregado eh regular e exibir o grau apresentado pelos seus vertices.\n");
    printf("12 - Verificar a existencia de pesseio.\n");
    printf("13 - Remover aresta.\n");
    printf("14 - Remover vertice.\n");
    printf("17 - Sair.\n");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n ");
    printf("Digite a opcao desejada: ");
}

int verifica_laco(int **M, int i, int j){
    if (i == j)
    {
        if (M[i][j] != 0)
            return 1;
    }
    return 0;
}

void laco(int **M, int v){
    int i, j, ver = 0;
    for (i = 0; i < v; i++){
        for (j = 0; j < v; j++){
            if (verifica_laco(M, i, j)){
                printf("\nPossui laço no vertice V%d.\n", i + 1);
                ver = 1;
            }
        }
    }
    if(ver == 0){
        printf("\nNão possui laços!\n");
    }
}


int arestas_total(int **M, int v, int arestas)
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
    return (arestas/2);
}

void imprime_arestas(){
    int i, j;
    fseek(file, 0, SEEK_SET);

    while (!feof (file)){  
      fscanf (file, "%d", &i);
      fscanf (file, "%d", &j);

      printf("v%d -> v%d\n",i, j);
    }
}

void arestas_multiplas(int **M, int v){
    int i, j, cont = 0;
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (M[i][j] > 1){
                printf("\nPossui arestas multiplas entre os vertices V%d,V%d.\n", i + 1, j + 1);
                cont++;
            }
        }
    }

    printf("\nO total de arestas multiplas eh %d", cont);
}

void grau_do_vertice(int **M, int v, int opt_v){
    int soma, j;

    for (j = 0; j < v; j++)
    {
        soma += M[opt_v][j];
    }
    printf("\nGrau do Vertice V%d+1 = %d", opt_v, soma);
    if (soma == 0)
        printf(", ou seja, eh um vertice isolado!");
    printf("\n");
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