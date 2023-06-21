#include "lib/lib_alg2.h"

int coordenadas2(int *x, int *y, int num_sub_images)
{
  char coords[1000];

  // Abrindo o arquivo em modo escrita
  FILE *file;
  file = fopen("coordenadas2.txt", "w+");
  fclose(file);

  file = fopen("coordenadas2.txt", "w");
  if (file == NULL)
  {
    puts("Erro ao abrir o arquivo.");
    exit(2);
  }

  // Escrevendo coordenadas no arquivo
  for (int k = 0; k < num_sub_images; k++)
  {
    sprintf(coords, "sub_imagem%d, coord_x%d: %d, coord_y%d: %d \n", k + 1, k + 1, x[k], k + 1, y[k]);
    fputs(coords, file);
  }
  printf("\n");

  // Fechando arquivo
  fclose(file);

  return 0;
}