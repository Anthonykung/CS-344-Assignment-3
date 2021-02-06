/****************************************************
 *                                                  *
 * Name: movies.h                                   *
 * Description: CS 344 Assignment 1                 *
 *              Primary Program Function Header     *
 * Date: January 16, 2021                           *
 * Created with <3 by: Anthony Kung                 *
 * Author URL: https://anth.dev                     *
 * License: Apache-2.0 (See /LICENSE.md)            *
 *                                                  *
 ****************************************************/

#ifndef TERMINAL
#define TERMINAL

#include "anthonian.h"
#include "movies.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

struct directory {
  struct dirent* dirs;
  struct stat sts;
  struct directory* next;
};

int main(int argc, char *argv[]);
int fileProcess();
struct directory* getCurryDir();
void removeCurryDir(struct directory* curryDir);
int largestFile(struct directory* curryDir);
int smallestFile(struct directory* curryDir);
int userSelectedFile();
int createMovieFiles(struct movies* movie);
void movieToFile(struct movies* movie, int year, char* dir);
int ifYearExist(struct movies* movie, int year);

#endif