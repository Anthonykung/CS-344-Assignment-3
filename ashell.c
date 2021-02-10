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
  struct asTrack* ps = NULL;
  while (exitStatus == 0) {
    printf("\n%s: %s", anthStr("prmp"), anthStr("ori"));
    char uin[2048];
    fgets(uin, 2048, stdin);
    anthLogB(debug, "IO Flush Input", uin);
    anthIOFlush(uin);
    char* cmd = anthRmNln(uin);
    anthLogB(debug, "Remove Newline Result", cmd);
    if (asCmdCheck(cmd) == 0) {
      anthLog(debug, "CMD Check Clear");
      if (strcmp(anthToLower(cmd), "exit") == 0) {
        anthLog(debug, "Exit Command Received\nExiting...");
        exitStatus = 1;
        exitCode = 0;
      }
      else if (strcmp(anthToLower(cmd), "status") == 0) {
          printf("%s%s Last Exit Code: %d %s\n", anthStr("suc"), anthStr("prefix"), exitCode, anthStr("ori"));
      }
      else if (cmd[0] == 'c' && cmd[1] == 'd') {
          printf("%s%s Last Exit Code: %d %s\n", anthStr("suc"), anthStr("prefix"), exitCode, anthStr("ori"));
      }
      else if (cmd[strlen(cmd) - 1] == '&') {
        anthLog(debug, "Background Request Detected");
        cmd[strlen(cmd) - 1] = '\0';
        int child = fork();
        if (child == 0) {
          ps = asTrackCon(ps);
          ps->pid = getpid();
          ps->cmd = asBreakdown(cmd);
          printf("%s%s Child ID: %d %s", anthStr("msg"), anthStr("prefix"), ps->pid, anthStr("ori"));
          execvp(ps->cmd[0], &(*(ps->cmd)));
          anthPtnApn("err", "Child Error: ", strerror(errno));
          perror("\nChild Error");
        }
        else {
          if (debug) {
            fprintf(stderr, "\nChild Created ID: %d", ps->pid);
          }
          waitpid(child, &exitCode, WNOHANG);
          kill(child, SIGTERM);
          anthLog(debug, "Execution Complete");
          ps->status = exitCode;
          ps->exited = 1;
        }
      }
      else {
        anthLog(debug, "Foreground Request Detected");
        int child = fork();
        if (child == 0) {
          char** exCmd = asBreakdown(cmd);
          execvp(exCmd[0], &(*(exCmd)));
          perror("\nChild Error");
          anthPtnApn("err", "Child Error: ", strerror(errno));
        }
        else {
          waitpid(child, &exitCode, 0);
          kill(child, SIGTERM);
          anthLog(debug, "Execution Complete");
        }
      }
    }
  }
  anthBye();
  return exitCode;
}

int asCmdCheck(char* cmd) {
  if (cmd == NULL) {
    anthLog(debug, "Input Return NULL");
    return 124;  /* Error Code 124 - Invalid User Input */
  }
  else if (strcmp(cmd, "") == 0) {
    anthLog(debug, "Empty Command");
    return 124;  /* Error Code 124 - Invalid User Input */
  }
  else if (isspace(cmd[0])) {
    anthLog(debug, "Space Detected");
    return 124;  /* Error Code 124 - Invalid User Input */
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
  char** strArr = calloc(2, sizeof(char*));
  int i = 0;
  char* token = NULL;
  /* Break down word surrounded by spaces */
  do {
    token = strtok_r(str, " ", &str);
    if (token != NULL) {
      anthLog2(debug, "token: ", token);
      strArr[i] = calloc((strlen(token) + 1), sizeof(char));
      strcpy(strArr[i], token);
      anthLog2(debug, "strArr[i]: ", strArr[i]);
      i++;
      strArr = realloc(strArr, (sizeof(char*) * (i + 1)));
      strArr[i] = NULL;
    }
  } while (token != NULL);
  anthLog2(debug, "strArr[i]: ", strArr[i]);
  return strArr;
}

/**
 * asTrack Constructor
 * Take the previous struct as param
 * If previous struct is NULL assume head
 */
struct asTrack* asTrackCon(struct asTrack* prev) {
  struct asTrack* curry = malloc(sizeof(struct asTrack*));
  curry->pid = 0;
  curry->cmd = NULL;
  curry->status = 0;
  curry->exited = 0;
  curry->prev = prev;
  curry->next = NULL;
  if (prev == NULL) {
    curry->head = curry;
  }
  else {
    curry->head = curry->prev->head;
  }
  curry->head->prev = curry;
  return curry;
}

void asTrackDec(struct asTrack* head) {
  while (head != NULL) {
    if (head->prev != NULL) {
      free(head->prev);
    }
    int i = 0;
    while (head->cmd[i]) {
      free(head->cmd[i]);
      i++;
    }
    free(head);
  }
}
