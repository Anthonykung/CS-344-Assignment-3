/****************************************************
 *                                                  *
 * Name: movies.h                                   *
 * Description: CS 344 Assignment 2                 *
 *              Movie Program Function Header       *
 * Date: January 16, 2021                           *
 * Created with <3 by: Anthony Kung                 *
 * Author URL: https://anth.dev                     *
 * License: Apache-2.0 (See /LICENSE.md)            *
 *                                                  *
 ****************************************************/

#ifndef MOVIES
#define MOVIES

#include "anthonian.h"

int movieArgCheck(char *argv[]);
int anthReadFile(char* filePath);
struct movies* movieCreate(FILE* fileLoc, char* filePath);
struct movies* movieAdd(char* curryLine);
int movieRemove(struct movies* movie);
int languageFreer(char** lang);
char** languageFilter(char* lang);
void moviePrintTitle(struct movies* movie, char* year);
void moviePrintRating(struct movies* movie);
void moviePrintLanguage(struct movies* movie, char* lang);
int movieValidator(struct movies *movie);
int primaryProgram(struct movies *movie);

struct movies {
  char* title;
  char* year;
  char** language;
  char* rating;
  struct movies* next;
};

struct movieArr {
  char* year;
  char** title;
  int size;
  struct movieArr* next;
};

#endif