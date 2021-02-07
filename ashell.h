/****************************************************
 *                                                  *
 * Name: ashell.h                                   *
 * Description: CS 344 Assignment 4                 *
 *              Anthonian Shell                     *
 * Date: Feburary 6, 2021                           *
 * Created with <3 by: Anthony Kung                 *
 * Author URL: https://anth.dev                     *
 * License: Apache-2.0 (See /LICENSE.md)            *
 *                                                  *
 ****************************************************/

#ifndef ASHELL
#define ASHELL

#include "anthonian.h"
#include <sys/types.h>
#include <unistd.h>

int asMain(int argc, char *argv[]);
int asCmdCheck(char* cmd);
char** asBreakdown(char* str);

struct asHistory {
  int pid;
  char** cmd;
  int status;
  int exited;
  struct asHistory* prev;
  struct asHistory* next;
  struct asHistory* head;
  struct asHistory* tail;
};

#endif
