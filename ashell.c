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
    fgets(uin, 2048, stdin);
    fprintf(stderr, "\nInput: %s", uin);
    anthIOFlush(uin);
    fprintf(stderr, "\nIO Flush Called");
    if (asCmdCheck(uin) == 0) {
      fprintf(stderr, "\nCMD Check Clear");
    }
    else if (strcmp(uin, "exit") == 0 || strcmp(uin, "Exit") == 0 || strcmp(uin, "EXIT") == 0) {
      exitStatus = 1;
      exitCode = 0;
    }
  }
  while (exitStatus == 0);
  anthBye();
  return exitCode;
}

int asCmdCheck(char* cmd) {
  if (cmd == NULL) {
    fprintf(stderr, "\nInput Return NULL");
    return 3;  /* Error Code 3 - Invalid User Input */
  }
  else if (strcmp(cmd, "") == 0) {
    fprintf(stderr, "\nEmpty Command");
    return 3;  /* Error Code 3 - Invalid User Input */
  }
  else if (isspace(cmd[0])) {
    fprintf(stderr, "\nCommented Input");
    return 3;  /* Error Code 3 - Invalid User Input */
  }
  else if (cmd[0] == '#') {
    fprintf(stderr, "\nCommented Input");
    return 125;  /* Error Code 125 - Ignore */
  }
  else {
    /* CMD Check Passed */
    fprintf(stderr, "\nCMD Check Passed");
    return 0;
  }
}
