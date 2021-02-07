/****************************************************
 *                                                  *
 * Name: ashell.c                                   *
 * Description: CS 344 Assignment 4                 *
 *              Anthonian Shell                     *
 * Date: Feburary 6, 2021                           *
 * Created with <3 by: Anthony Kung                 *
 * Author URL: https://anth.dev                     *
 * License: Apache-2.0 (See /LICENSE.md)            *
 *                                                  *
 ****************************************************/

#include "ashell.h"

int asMain(int argc, char* argv[]) {
  int exitStatus = 0;
  int exitCode = 0;
  do {
    printf("\n%s: %s", anthStr("prmp"), anthStr("ori"));
    char uin[2048];
    scanf("%s", uin);
    anthIOFlush(uin);
    if (asCmdCheck(uin)) {
      fprintf(stderr, "CMD Check Clear");
    }
  }
  while (!exitStatus);
  return exitCode;
}

int asCmdCheck(char* cmd) {
  if (cmd[0] == '#') {
    fprintf(stderr, "Commented Input");
    return 125;  /* Error Code 125 - Ignore */
  }
  else if (strcmp(cmd, "") == 0 || anthIsEmpty(cmd) == 1) {
    fprintf(stderr, "Empty Command");
    return 3;  /* Error Code 3 - Invalid User Input */
  }
  else {
    /* CMD Check Passed */
    fprintf(stderr, "CMD Check Passed");
    return 0;
  }
}
