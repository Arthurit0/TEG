#include <stdio.h>
#include <stdlib.h>

const char* file_name = "grafo.txt";
FILE* file;


void menu()
{
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("1 - Ver o número de vertices e arestas e ver quais arestas estao no grafo.\n");
    printf("2 - Ver no(s) com aresta(s) em laco.\n");
    printf("3 - Ver quais vertices tem arestas multiplas e quantas arestas multilplas existem entre eles.\n");
    printf("4 - Exibir o grau de um vertice.\n");
    printf("5 - Exibir a soma de todos os graus dos vertices.\n");
    printf("6 - Ver os vertices que sao isolados.\n");
    printf("7 - Verificar se o número de arestas é no máximo igual ao número de combinacoes de |V| tomadas 2 a 2.\n");
    printf("8 - Verificar se o número total de vértices com grau impar e par.\n");
    printf("9 - Verificar se o grafo eh simples.\n");
    printf("10 - Verificar se o grafo e completo.\n");
    printf("11 - Verificar se o grafo carregado eh regular e exibir o grau apresentado pelos seus vertices.\n");
    printf("12 - Verificar a existencia de passeio.\n");
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
    int soma=0, j;

    for (j = 0; j < v; j++)
    {
        soma += M[opt_v-1][j];
    }
    printf("\nGrau do Vertice V%d = %d", opt_v, soma);
    if (soma == 0)
        printf(", ou seja, eh um vertice isolado!");
    printf("\n");
}

void somatorio_dos_vertices(int **M, int v){
    int soma=0, i, j;

    for(i = 0; i < v; i++){
        for (j = 0; j < v; j++){
            soma += M[i][j];
        }
    }
    printf("Somatorio dos graus dos vertices eh %d\n", soma);
}

void isolaaadoo(int **M, int v){
    int soma=0, i, j, ver = 0;

    for(i = 0; i< v; i++){
        for (j = 0; j < v; j++){
            soma += M[i][j];
        }
        if (soma == 0){
            printf("\nv%d eh um vertice isolado\n", i+1);
            ver = 1;
        }
        soma = 0;
    }

    if(ver == 0){
        printf("\nNao ha vertices isolados!\n");
    }
}

void grau_impar_par(int **M, int v){
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
    printf("\nO teorema do numero total de vertices com grau impar eh sempre par se verifica? ");
    if (num_v_grau_impar % 2 == 0)
        printf("Sim, se verifica!\n");
    else
        printf("Nao, logo, isto nao é um grafo!\n");
}

void grafo_simples(int **M, int v){
    int i, j, verLaco, verMult = 0;

    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            verLaco = verifica_laco(M,i,j);
            
            if(M[i][j] > 1){
                verMult = 1;
            }

            if(verLaco || verMult){
                break;
            }
        }
            if(verLaco || verMult){
                break;
            }
    }
    
    if(verLaco || verMult){
        printf("\nNao eh um grafo simples!\n");
    }else{
        printf("\nEh um grafo simples\n");
    }
}

void grafo_completo(int **M, int v){
    int i, j, notComp = 0;

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if(i == j){
                if(M[i][j] > 0) notComp = 1;
            }else{
                if(M[i][j] != 1) notComp = 1;
            }
        }

    }
    notComp ? printf("Este nao eh um grafo completo") :  printf("Este eh um grafo completo");
}

void grafo_regular(int **M, int v){
    int i, j, base, soma = 0, notReg = 0;

    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            soma += M[i][j];    
        }
        if(i == 0) base = soma;
        else if(base != soma){
            notReg = 1;
            break;
        }
        soma = 0;
    }
    printf("\n");

    notReg ? printf("Este nao eh um grafo regular") :  printf("Este eh um grafo regular, e o grau deles eh %d", base);
}

void passeio(int **M, int opt_v, int k, int v, int ant){
    int j;

    if(k == 0){
        printf("Fim do passeio!\n");
        return;
    }else{
        for(j = 0; j < v; j++){
            if(opt_v != j && j != ant && M[opt_v][j] >= 1){
                printf("\n v%d -> v%d\n", opt_v+1, j+1);
                passeio(M, j, k-1, v, opt_v);
                break;
            }
        }
    }
}

int main()
{
    int i, j, v, arestas=0, opcao=0, opt_v, k;

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

        switch (opcao)
        {

        case 1:
            printf("Numero de vertices: %d\n", v);

            printf("Numero de arestas total: %d\n",arestas);
            printf("As arestas sao:\n");
            imprime_arestas();
            system("pause");
            break;
        case 2:
            printf("O Grafo\n");
            laco(M, v);
            system("pause");
            break;
        case 3:
            printf("O Grafo\n");
            arestas_multiplas(M, v);
            system("pause");
            break;
        case 4:
            system("cls");
            do{
                printf("Qual dos %d vertices você deseja ver? ", v);
                scanf("%d",&opt_v);

                if((opt_v < 0) || (opt_v > v)){
                    printf("Vertice invalido, tente um numero entre 1 e %d\n\n", v);
                }

            }while((opt_v < 0) || (opt_v > v));

            grau_do_vertice(M, v, opt_v);
            system("pause");
            break;
        case 5:
            system("cls");
            somatorio_dos_vertices(M, v);
            system("pause");
            break;
        case 6:
            isolaaadoo(M,v);
            system("pause");
            break;
        case 7:
            break;
        case 8:
            grau_impar_par(M,v);
            system("pause");
            break;
        case 9:
            grafo_simples(M,v);
            system("pause");
            break;
        case 10:
            grafo_completo(M,v);
            system("pause");
            break;
        case 11:
            grafo_regular(M,v);
            system("pause");
            break;
        case 12:
            system("cls");
            do{
                printf("Em qual vertice voce quer iniciar o passeio? ");
                scanf("%d",&opt_v);

                printf("Quantos passos deve ter o passeio? ");
                scanf("%d", &k);

                if(opt_v < 0 || opt_v > v) printf("Vertice invalido, tente novamente!\n");
                if(k < 0) printf("Caminho invalido, tente novamente!\n");

            }while(opt_v < 0 || opt_v > v || k < 0);

            if(k <= arestas && arestas > 0) passeio(M, opt_v-1, k, v, -1);
            else printf("O numero de passos eh maior que o numero de arestas");
            system("pause");
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            return 0;

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
   

    // printf("\n");
    // printf("\n------------------------\n");

    // // free na matriz
    // for (i = 0; i < v; i++)
    //     free(M[i]);
    // free(M);

    return 0;
}

// int numer_aresta_max()
// {
// }
// void grau_total()
// {
// }
// int vertice_grau_impar()
// {
// }