#include "lib/lib_alg2.h"

double calcularMSE(const Image *image1, const Image *image2, int x, int y)
{
  int largura = image2->largura;
  int altura = image2->altura;
  int soma = 0;

  for (int i = 0; i < altura; i++)
  {
    for (int j = 0; j < largura; j++)
    {
      unsigned char pixel1 = (unsigned char)image1->pixels[y + i][x + j];
      unsigned char pixel2 = (unsigned char)image2->pixels[i][j];
      int diff = pixel1 - pixel2;
      soma += diff * diff;
    }
  }

  return (double)soma / (largura * altura);
}