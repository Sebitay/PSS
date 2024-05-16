#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 1024
char ROOT[MAX_PATH];

void buscar(const char *file);

int main(int argc, char *argv[]) {
  getcwd(ROOT, MAX_PATH);
  buscar("t3.c");
  return 0;
}

void buscar(const char *file) {
  DIR *dir = opendir(".");
  if (dir == NULL) {
    return;
  }

  // loop para recorrer los contenidos de dir
  for (struct dirent *entry = readdir(dir); entry != NULL;
       entry = readdir(dir)) {
    char* name = entry->d_name;
    struct stat stbf;
    stat(name, &stbf);

    // caso registro
    if (S_ISREG(stbf.st_mode) && strcmp(name, file) == 0) {
      char cd[MAX_PATH];
      getcwd(cd, MAX_PATH);
      printf("%s/%s\n", cd + strlen(ROOT) /* con esto nos evitamos el doxxeo */, name);
    }

    // evitar loop infinito
    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
      continue;
    }

    // caso directorio
    if (S_ISDIR(stbf.st_mode)) {
      chdir(name);
      buscar(file);
      chdir("..");
    }
  }
  closedir(dir);
}
