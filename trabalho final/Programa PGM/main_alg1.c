#include "lib/lib_alg1.h"

#define MAX 100
#define MIN 0

int main()
{
  srand(time(NULL));

  // Leitura da imagem
  const char *filename = "input.pgm";
  Image *image = readPGM(filename);
  if (image == NULL)
  {
    return 1;
  }

  // Criação de variáveis
  int num_sub_images = 2;
  int largura = 100, altura = 100;

  // Alocando memória
  int *x = (int *)malloc(num_sub_images * sizeof(int));
  int *y = (int *)malloc(num_sub_images * sizeof(int));

  // Solicitando e criando o diretório de destino
  char outputPath[256];
  printf("Informe o diretorio de destino para as sub-imagens: ");
  scanf("%s", outputPath);
  printf("\n");
  CreateDirectory(outputPath, NULL);

  for (int i = 0; i < num_sub_images; i++)
  {
    // Definindo as coordenadas de x e y
    x[i] = MIN + rand() % MAX;
    y[i] = MIN + rand() % MAX;
    printf("Coordenada de x: %d\n", x[i]);
    printf("Coordenada de y: %d\n", y[i]);

    // Criando sub-imagem
    Image *subimage = extractSubimage(image, x[i], y[i], largura, altura);

    // Enviando para o diretório escolhido
    char outputFilename[256];
    sprintf(outputFilename, "%s/sub_imagem%d.pgm", outputPath, i + 1);
    writePGM(outputFilename, subimage);
    printf("Subimagem %d extraida com sucesso e salva como '%s'.\n", i + 1, outputFilename);

    // Criando arquivo de texto com as coordenadas de x e y
    coordenadas1(x, y, num_sub_images);

    freeImage(subimage);
  }

  free(x);
  free(y);
  freeImage(image);

  return 0;
}