#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minisystem()
{
    printf("minisystem\n");
}

void student_id()
{
	printf("20192596\nBaek Hyun Woo\n");
}

#include <dirent.h>

void minils() {
  // 현재 디렉토리 열기
  DIR *dir = opendir(".");
  if (dir == NULL) {
    perror("opendir");
    return;
  }

  // 디렉토리 엔트리 읽기
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    // . 및 .. 디렉토리는 제외
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      printf("%s  ", entry->d_name);
    }
  }
  printf("\n");

  // 디렉토리 닫기
  closedir(dir);
}