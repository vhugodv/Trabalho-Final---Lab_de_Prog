#include "lib/lib_alg1.h"

Image *readPGM(const char *filename)
{
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }

  // Leitura do cabeçalho
  char pgmbin[3];
  fscanf(file, "%2s\n", pgmbin);
  if (pgmbin[0] != 'P' || pgmbin[1] != '5')
  {
    printf("Formato de arquivo inválido.\n");
    fclose(file);
    return NULL;
  }

  Image *image = (Image *)malloc(sizeof(Image));
  fscanf(file, "%d %d\n", &image->largura, &image->altura);
  fscanf(file, "%d\n", &image->max_gray_value);

  // Alocando memória para os pixels
  image->pixels = (int **)malloc(image->altura * sizeof(int *));
  for (int i = 0; i < image->altura; i++)
  {
    image->pixels[i] = (int *)malloc(image->largura * sizeof(int));
  }

  // Lendo os pixels da imagem
  for (int i = 0; i < image->altura; i++)
  {
    fread(image->pixels[i], sizeof(int), image->largura, file);
  }

  fclose(file);
  return image;
}

void writePGM(const char *filename, const Image *image)
{
  FILE *file = fopen(filename, "wb");
  if (file == NULL)
  {
    printf("Erro ao criar arquivo de saída.\n");
    return;
  }

  // Escrevendo cabeçalho
  fprintf(file, "P5\n");
  fprintf(file, "%d %d\n", image->largura, image->altura);
  fprintf(file, "%d\n", image->max_gray_value);

  // Escrevendo pixels
  for (int i = 0; i < image->altura; i++)
  {
    fwrite(image->pixels[i], sizeof(int), image->largura, file);
  }

  fclose(file);
}