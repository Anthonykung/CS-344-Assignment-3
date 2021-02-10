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
#include <sys/wait.h>
#include <errno.h>

int asMain(int argc, char *argv[]);
int asCmdCheck(char* cmd);
char** asBreakdown(char* str, int pid);
struct asTrack* asTrackCon(struct asTrack* prev);
void asTrackDec(struct asTrack* head);
int asPID(char* cmd);
int asRedirectIn(char** cmd);
int asRedirectOut(char** cmd);
int asKillAll(struct asTrack* children);
char** asRmSpace(char** str);

struct asTrack {
  int pid;
  char** cmd;
  int status;
  int exited;
  int fdin;
  int fdout;
  struct asTrack* prev;
  struct asTrack* next;
  struct asTrack* head;
};

#endif
