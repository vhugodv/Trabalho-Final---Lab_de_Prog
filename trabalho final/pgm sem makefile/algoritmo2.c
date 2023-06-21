/*
Aluno: Victor Hugo Santos Silva
Matricula: 20222045050310
Avaliacao 04: Trabalho Final
2023.1 - Prof. Daniel Ferreira
Compilador: gcc versao 6.3.0-1
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#define QTDIMG 2

typedef struct
{
  int largura;
  int altura;
  int max_gray_value;
  int **pixels;
} Image;

Image *readPGM(const char *);
void freeImage(Image *);
double calcularMSE(const Image *, const Image *, int, int);
void findMatchingRegion(const Image *, const Image *, int *, int *);
void listFilesInDirectory(const char *, char ***, int *);
int coordenadas2(int *, int *, int);

int main()
{
  // Informando diretorio das sub-imagens
  char *diretorio;
  printf("Informe o diretorio das sub-imagens: ");
  scanf("%s", diretorio);
  printf("\n\n");
  const char *imageFilename = "input.pgm";
  const char *subimagesDirectory = diretorio;

  Image *image = readPGM(imageFilename);
  if (image == NULL)
  {
    return 1;
  }

  char **subimageFiles;
  int num_sub_images;

  listFilesInDirectory(subimagesDirectory, &subimageFiles, &num_sub_images);

  int *x = (int *)malloc(num_sub_images * sizeof(int));
  int *y = (int *)malloc(num_sub_images * sizeof(int));

  for (int i = 0; i < num_sub_images; i++)
  {
    char subimagePath[256];
    sprintf(subimagePath, "%s/%s", subimagesDirectory, subimageFiles[i]);

    Image *subimage = readPGM(subimagePath);
    if (subimage == NULL)
    {
      continue;
    }

    // Achando x e y na imagem original
    int matchX, matchY;
    findMatchingRegion(image, subimage, &matchX, &matchY);
    printf("Sub-imagem: %s\n", subimageFiles[i]);
    printf("Regiao correspondente encontrada na posicao (%d, %d)\n", matchX, matchY);

    x[i] = matchX;
    y[i] = matchY;

    coordenadas2(x, y, num_sub_images);

    freeImage(subimage);
  }
  // Criando arquivo de texto com as coordenadas de x e y

  free(subimageFiles);
  freeImage(image);

  return 0;
}

Image *readPGM(const char *filename)
{
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    return NULL;
  }

  // Leitura do cabeçalho
  char magic[3];
  fscanf(file, "%2s\n", magic);
  if (magic[0] != 'P' || magic[1] != '5')
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

void freeImage(Image *image)
{
  for (int i = 0; i < image->altura; i++)
  {
    free(image->pixels[i]);
  }
  free(image->pixels);
  free(image);
}

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

void listFilesInDirectory(const char *directory, char ***filenames, int *count)
{
  DIR *dir;
  struct dirent *ent;
  int fileCount = 0;
  char **files = NULL;

  dir = opendir(directory);
  if (dir == NULL)
  {
    printf("Erro ao abrir o diretório.\n");
    return;
  }

  while ((ent = readdir(dir)) != NULL)
  {
    if (ent->d_type == DT_REG)
    {
      fileCount++;
      files = realloc(files, fileCount * sizeof(char *));
      files[fileCount - 1] = malloc((strlen(ent->d_name) + 1) * sizeof(char));
      strcpy(files[fileCount - 1], ent->d_name);
    }
  }

  closedir(dir);

  *filenames = files;
  *count = fileCount;
}

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