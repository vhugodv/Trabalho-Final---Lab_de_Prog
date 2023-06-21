#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <string.h>

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