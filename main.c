#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

void main(int argc, char * argv[]) {
  char name[512];
  if (argc = 1){
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
  }
  else{
    strcpy(name, argv[1]);
  }
  DIR * dir = opendir(name);
  if (dir == NULL){
    printf("%s\n", strerror(errno));
  }
  struct dirent * file = readdir(dir);
  int size = 0;
  while(file != NULL){
    struct stat info;
    stat(file->d_name, &info);
    printf("%s\n", file->d_name);
    if((info.st_mode & S_IFMT) == S_IFDIR){
      printf("Directory\n");
    }
    else {
      printf("File\n");
      printf("%ld bytes\n", info.st_size );
      size += info.st_size;
    }
    file = readdir(dir);
    printf("\n");
  }
  printf("Total size: %d bytes\n", size);
}
