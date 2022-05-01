#include <stdio.h>
#include <stdlib.h>

const char* file_name = "grafo.txt";

int main(int argc, char *argv[]){

    FILE* file = fopen (file_name, "r");
    int i = 0, vert;

    fscanf(file, "%d", &vert);
    printf("Esse número é uma coisa: %d\n", vert);

    printf("E esses são outras\n");

    while (!feof (file)){  
      fscanf (file, "%d", &i);     
      printf ("%d\n", i);
    }
    fclose (file);  

    return 0;
}