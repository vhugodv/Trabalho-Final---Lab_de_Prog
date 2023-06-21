#include "lib/lib_alg1.h"

Image *extractSubimage(const Image *image, int x, int y, int largura, int altura)
{
  Image *subimage = (Image *)malloc(sizeof(Image));
  subimage->largura = largura;
  subimage->altura = altura;
  subimage->max_gray_value = image->max_gray_value;

  // Alocando memória para os pixels da subimagem
  subimage->pixels = (int **)malloc(altura * sizeof(int *));
  for (int i = 0; i < altura; i++)
  {
    subimage->pixels[i] = (int *)malloc(largura * sizeof(int));
  }

  // Copiando os pixels da área selecionada
  for (int i = 0; i < altura; i++)
  {
    for (int j = 0; j < largura; j++)
    {
      subimage->pixels[i][j] = image->pixels[y + i][x + j];
    }
  }

  return subimage;
}

void freeImage(Image *image)
{
  for (int i = 0; i < image->altura; i++)
  {
    free(image->pixels[i]);
  }
  free(image->pixels);
  free(image);
}