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

int debug = 0;

int asMain(int argc, char* argv[]) {
  if (argv[1] && strcmp(argv[1], "debug") == 0) {
    debug = 1;
  }
  int exitStatus = 0;
  int exitCode = 0;
  do {
    printf("\n%s: %s", anthStr("prmp"), anthStr("ori"));
    char uin[2048];
    fgets(uin, 2048, stdin);
    anthIOFlush(uin);
    char* cmd = anthRmNln(uin);
    if (asCmdCheck(cmd) == 0) {
      anthLog(debug, "CMD Check Clear");
      if (strcmp(anthToLower(cmd), "exit") == 0) {
        anthLog(debug, "Exit Command Received\nExiting...");
        exitStatus = 1;
        exitCode = 0;
      }
    }
  }
  while (exitStatus == 0);
  anthBye();
  return exitCode;
}

int asCmdCheck(char* cmd) {
  if (cmd == NULL) {
    anthLog(debug, "Input Return NULL");
    return 3;  /* Error Code 3 - Invalid User Input */
  }
  else if (strcmp(cmd, "") == 0) {
    anthLog(debug, "Empty Command");
    return 3;  /* Error Code 3 - Invalid User Input */
  }
  else if (isspace(cmd[0])) {
    anthLog(debug, "Commented Input");
    return 3;  /* Error Code 3 - Invalid User Input */
  }
  else if (cmd[0] == '#') {
    anthLog(debug, "Commented Input");
    return 125;  /* Error Code 125 - Ignore */
  }
  else {
    /* CMD Check Passed */
    anthLog(debug, "CMD Check Passed");
    return 0;
  }
}

char** asBreakdown(char* str) {
  char** strArr = malloc(sizeof(char*));
  int i = 1;
  char* token = NULL;
  /* Break down word surrounded by spaces */
  do {
    token = strtok_r(str, " ", &str);
    anthLog2(debug, "token: ", token);
    strArr[i] = calloc((strlen(token) + 1), sizeof(char));
    strcpy(strArr[i], token);
    anthLog2(debug, "strArr[i]: ", strArr[i]);
    i++;
    strArr = realloc(strArr, (sizeof(char*) * i));
  } while (token != NULL);
  return strArr;
}
