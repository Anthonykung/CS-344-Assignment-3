/**************************************************
 *                                                *
 * Name: anthonian.h                              *
 * Description: Anthonian Helper Program          *
 * Date: July 21, 2020                            *
 * Created by: Anthony Kung                       *
 * Author URL: https://anthonykung.com            *
 * License: Apache-2.0 (See /LICENSE.md)          *
 *                                                *
 **************************************************/

#ifndef ANTHONIAN
#define ANTHONIAN

#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

const char* anthStr(char* arg);
void anthdev();
void anthIntro();
void anthColors();
void anthNln();
void anthClr();
void anthPtn(char* color, char* str);
void anthPtnApn(char* color, char* str, char* apn);
int anthWait(unsigned long milisec);
void anthProc(char* str);
void anth();
int anthExtChecker(char* str, char* ext);
int strtoi(const char* str);
void anthRmCharFromStr(char* str, char cmp);
void anthIOFlush(const char* str);
char* anthToLower(char* str);
char* anthRmNln(char* str);
void anthBye();
int anthRand(int min, int max);
int anthCheckPrefix(char* str, char* prefix);
int anthIfFileExist(char* name);
int anthIsEmpty(const char* str);

struct anthStrArr {
  char** arr;
  int size;
};

#endif
