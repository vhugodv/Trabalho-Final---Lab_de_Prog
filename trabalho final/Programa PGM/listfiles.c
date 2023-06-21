#include "lib/lib_alg2.h"

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