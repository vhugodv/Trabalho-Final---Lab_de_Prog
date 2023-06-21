#include "lib/lib_alg2.h"

void findMatchingRegion(const Image *image, const Image *subimage, int *x, int *y)
{
  int largura_imagem = image->largura;
  int altura_imagem = image->altura;
  int largura_subimagem = subimage->largura;
  int altura_subimagem = subimage->altura;
  double minMSE = INFINITY;

  for (int i = 0; i <= altura_imagem - altura_subimagem; i++)
  {
    for (int j = 0; j <= largura_imagem - largura_subimagem; j++)
    {
      double mse = calcularMSE(image, subimage, j, i);
      if (mse < minMSE)
      {
        minMSE = mse;
        *x = j;
        *y = i;
      }
    }
  }
}