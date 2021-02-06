/****************************************************
 *                                                  *
 * Name: terminal.c                                 *
 * Description: CS 344 Assignment 2                 *
 *              Primary Program Function            *
 * Date: January 25, 2021                           *
 * Created with <3 by: Anthony Kung                 *
 * Author URL: https://anth.dev                     *
 * License: Apache-2.0 (See /LICENSE.md)            *
 *                                                  *
 ****************************************************/

#include "terminal.h"

/* Main Function */
int tmain(int argc, char *argv[]) {
  anth();
  int checker = 1;
  /* Until Stated Otherwise, Keep Prompting User */
  do {
    fflush(stdout);
    printf("\n");
    printf("\n %s %s %s", anthStr("prmp"), "1. Select file to process", anthStr("ori"));
    printf("\n %s %s %s", anthStr("prmp"), "2. Exit the program", anthStr("ori"));
    printf("\n %s %s %s", anthStr("prmp"), "Enter a choice 1 or 2:", anthStr("ori"));
    char uin[512];
    /* Get User Input */
    fgets(uin, 512, stdin);
    /* Flush Input Buffer */
    anthIOFlush(uin);
    if (strtoi(uin) == 1) {
      if (fileProcess()) {
        anthPtn("err", "File Processing Error");
      }
    }
    else if (strtoi(uin) == 2) {
      checker = 0;
    }
    else {
      anthPtn("warn", "Input value out of range");
    }
  } while (checker);
  anthBye();
  return 0;
}

int fileProcess() {
  printf("\n");
  int checker = 1;
  /* Get Current Directory */
  struct directory* curryDir = getCurryDir();
  /* Until Stated Otherwise, Keep Prompting User */
  do {
    printf("\n %s %s %s", anthStr("prmp"), "Which file you want to process?", anthStr("ori"));
    printf("\n %s %s %s", anthStr("prmp"), "Enter 1 to pick the largest file", anthStr("ori"));
    printf("\n %s %s %s", anthStr("prmp"), "Enter 2 to pick the smallest file", anthStr("ori"));
    printf("\n %s %s %s", anthStr("prmp"), "Enter 3 to specify the name of a file", anthStr("ori"));
    printf("\n %s %s %s", anthStr("prmp"), "Enter a choice from 1 to 3:", anthStr("ori"));
    char uin[512];
    /* Get User Input */
    fgets(uin, 512, stdin);
    /* Flush Input Buffer */
    anthIOFlush(uin);
    if (strtoi(uin) == 1) {
      checker = largestFile(curryDir);
    }
    else if (strtoi(uin) == 2) {
      checker = smallestFile(curryDir);
    }
    else if (strtoi(uin) == 3) {
      checker = userSelectedFile();
    }
    else {
      anthPtn("warn", "Input value out of range");
    }
  } while (checker);
  return 0;
}

struct directory* getCurryDir() {
  struct dirent* curry = NULL;
  struct directory* allDir = NULL;
  struct directory* head = NULL;
  /* Open Current Directory */
  DIR* curryDir = opendir(".");
  /* If Current Directory Not Empty */
  if (curryDir) {
    /* Make Structs */
    allDir = malloc(sizeof(struct directory*));
    head = allDir;
    int size = 0;
    /* Read Current Directory */
    while ((curry = readdir(curryDir))) {
      if (anthCheckPrefix(curry->d_name, "movies_") && anthExtChecker(curry->d_name, ".csv")) {
        allDir->dirs = curry;
        allDir->next = malloc(sizeof(struct directory*));
        allDir = allDir->next;
        size++;
      }
    }
    /* Close Current Directory */
    closedir(curryDir);
    if (size == 0) {
      anthPtn("warn", "Nothing has been found in current directory");
      removeCurryDir(allDir);
      return NULL;
    }
    return head;
  }
  else {
    anthPtn("err", "Unable to open file, terminating");
    return NULL;
  }
  return head;
}

void removeCurryDir(struct directory* curryDir) {
  struct directory* temp = NULL;
  while (curryDir) {
    temp = curryDir;
    curryDir = temp->next;
    free(temp);
  }
}

int largestFile(struct directory* curryDir) {
  struct directory* temp = curryDir;
  char* file = NULL;
  off_t size = 0;
  while (curryDir) {
    if (curryDir->next != NULL) {
      struct stat sts;
      if (stat(curryDir->dirs->d_name, &sts) == -1) {
        anthPtn("err", "Stat Error");
      }
      /*anthPtn("warn", "Comparing");*/
      /*anthPtn("prmp", curryDir->dirs->d_name);*/
      /*printf("\nFile st_size %ld \n", sts.st_size);*/
      off_t stsSize = sts.st_size;
      if (stsSize > size) {
        /*anthPtn("warn", "Bigger");*/
        size = stsSize;
        /*anthPtn("warn", "Bigger");*/
        file = (char*)malloc(strlen(curryDir->dirs->d_name) + 1);
        strcpy(file, curryDir->dirs->d_name);
      }
      else if (stsSize == size) {
        /*anthPtn("warn", "Same");*/
        if (anthRand(0, 1)) {
          free(file);
          file = (char*)malloc(strlen(curryDir->dirs->d_name) + 1);
          strcpy(file, curryDir->dirs->d_name);
        }
      }
      /*anthPtn("warn", "Out");*/
    }
    curryDir = curryDir->next;
  }
  /*anthPtn("warn", "Open File");*/
  FILE* fileLoc = fopen(file, "r");
  printf("\n %s %s %s %s \n", anthStr("msg"), "Now processing the chosen file named ", file, anthStr("ori"));
  removeCurryDir(temp);
  if (file) {
    free(file);
    struct movies* movie = movieCreate(fileLoc, file);
    return createMovieFiles(movie);
  }
  else {
    anthPtn("err", "NULL File");
    return fileProcess();
  }
}

int smallestFile(struct directory* curryDir) {
  struct directory* temp = curryDir;
  char* file = NULL;
  off_t size = 0;
  while (curryDir) {
    if (curryDir->next != NULL) {
      struct stat sts;
      if (stat(curryDir->dirs->d_name, &sts) == -1) {
        anthPtn("err", "Stat Error");
      }
      /*anthPtn("warn", "Comparing");*/
      /*anthPtn("prmp", curryDir->dirs->d_name);*/
      /*printf("\nFile st_size %ld \n", sts.st_size);*/
      off_t stsSize = sts.st_size;
      if (size == 0 || stsSize < size) {
        /*anthPtn("warn", "Smaller");*/
        size = stsSize;
        /*anthPtn("warn", "Smaller");*/
        file = (char*)malloc(strlen(curryDir->dirs->d_name) + 1);
        strcpy(file, curryDir->dirs->d_name);
      }
      else if (stsSize == size) {
        /*anthPtn("warn", "Same");*/
        if (anthRand(0, 1)) {
          free(file);
          file = (char*)malloc(strlen(curryDir->dirs->d_name) + 1);
          strcpy(file, curryDir->dirs->d_name);
        }
      }
      /*anthPtn("warn", "Out");*/
    }
    curryDir = curryDir->next;
  }
  /*anthPtn("warn", "Open File");*/
  FILE* fileLoc = fopen(file, "r");
  printf("\n %s %s %s %s \n", anthStr("msg"), "Now processing the chosen file named ", file, anthStr("ori"));
  removeCurryDir(temp);
  if (file) {
    free(file);
    struct movies* movie = movieCreate(fileLoc, file);
    return createMovieFiles(movie);
  }
  else {
    anthPtn("err", "NULL File");
    return fileProcess();
  }
}

/* movies_sample_1.csv */

int userSelectedFile() {
  anthPtn("prmp", "Enter the complete file name:\n");
  char uin[512];
  fgets(uin, 512, stdin);
  anthIOFlush(uin);
  if (anthIfFileExist(anthRmNln(uin))) {
    FILE* fileLoc = fopen(anthRmNln(uin), "r");
    printf("\n %s %s %s %s \n", anthStr("msg"), "Now processing the chosen file named ", uin, anthStr("ori"));
    struct movies* movie = movieCreate(fileLoc, anthRmNln(uin));
    return createMovieFiles(movie);
  }
  return 1;
}

int createMovieFiles(struct movies* movie) {
  if (movie == NULL) {
    anthPtn("err", "Movie Return NULL");
    return 1;
  }
  char str[512];
  if (sprintf(str, "kungc.movies.%d", anthRand(0, 99999)) > 0) {
    if (mkdir(str, 0710) == 0) {
      int year = 0;
      for (year = 0; year < 9999; year++) {
        movieToFile(movie, year, str);
      }
      anthPtnApn("msg", "Created directory with name ", str);
      movieRemove(movie);
    }
    else {
      anthPtn("err", "Directory creation failure - Unable to create directory");
      return 1;
    }
  }
  else {
    anthPtn("err", "Unable to create directory path");
    return 1;
  }
  return 0;
}

int ifYearExist(struct movies* movie, int year) {
  struct movies* temp = movie;
  int count = 0;
  if (year >= 1900 && year <= 2021) {
    while (movie != NULL) {
      if (strtoi(movie->year) == year) {
        count++;
      }
      movie = movie->next;
    }
  }
  movie = temp;
  return count;
}

void movieToFile(struct movies* movie, int year, char* dir) {
  struct movies* temp = movie;
  if (ifYearExist(movie, year)) {
    char str[512];
    sprintf(str, "%s/%d.txt", dir, year);
    int fd = open(str, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0600);
    while (movie != NULL) {
      if (strtoi(movie->year) == year) {
        char str2[512];
        sprintf(str2, "%s\n", movie->title);
        write(fd, str2, strlen(str2));
      }
      movie = movie->next;
    }
  }
  movie = temp;
}
