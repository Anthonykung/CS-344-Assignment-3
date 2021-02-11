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
int curryFPS = 0;
int enBGP = 1;
struct asTrack* ps = NULL;

int asMain(int argc, char* argv[]) {
  fflush(stdout);
  anthPtn("pink", "Note: Commands are case sensitive, for debug log use [make debug]");
  if (argv[1] && strcmp(argv[1], "debug") == 0) {
    debug = 1;
  }
  int exitStatus = 0;
  int exitCode = 0;
  /* Get Parent PID for $$ */
  int ppid = getpid();
  /* Saving current stds to return to */
  int oristdin = dup(0);
  int oristdout = dup(1);
  /* Signal Handling */

  struct sigaction asCaInt = {{0}};
  asCaInt.sa_handler = asHdInt;
  sigfillset(&asCaInt.sa_mask);
  sigaction(SIGINT, &asCaInt, NULL);
  asCaInt.sa_flags = 0;

  struct sigaction asCaStop = {{0}};
  asCaStop.sa_handler = SIG_IGN;
  sigfillset(&asCaStop.sa_mask);
  sigaction(SIGTSTP, &asCaStop, NULL);
  asCaStop.sa_flags = 0;

  struct sigaction asCaChild = {{0}};
  asCaChild.sa_handler = asHdChild;
  sigfillset(&asCaChild.sa_mask);
  sigaction(SIGCHLD, &asCaChild, NULL);
  asCaChild.sa_flags = 0;

  fflush(stdout);

  if (debug) {
    fprintf(stderr, "\nParent PID: %d", ppid);
  }
  while (exitStatus == 0) {
    int cpid = getpid();
    if (debug) {
      fprintf(stderr, "\nCurrent PID: %d", cpid);
    }
    printf("\n%s: %s", anthStr("prmp"), anthStr("ori"));
    char uin[2048];
    fgets(uin, 2048, stdin);
    anthLogB(debug, "IO Flush Input", uin);
    anthIOFlush(uin);
    char* cmd = anthRmNln(uin);
    anthLogB(debug, "Remove Newline Result", cmd);
    if (asCmdCheck(cmd) == 0) {
      anthLog(debug, "CMD Check Clear");
      if (strcmp(cmd, "exit") == 0) {
        anthLog(debug, "Exit Command Received\nExiting...");
        exitStatus = 1;
        exitCode = 0;
      }
      else if (strcmp(cmd, "status") == 0) {
        printf("%s%s Last Exit Code: %d %s\n", anthStr("suc"), anthStr("prefix"), exitCode, anthStr("ori"));
      }
      else if (cmd[0] == 'c' && cmd[1] == 'd') {
        char** exCmd = asBreakdown(cmd, ppid);
        if (exCmd[1] == NULL) {
          chdir(getenv("HOME"));
          printf("%s%s Current Directory Changed To: %s %s\n", anthStr("suc"), anthStr("prefix"), getenv("HOME"), anthStr("ori"));
        }
        else if (strcmp(exCmd[1], "~/") == 0) {
          chdir(getenv("HOME"));
          printf("%s%s Current Directory Changed To: %s %s\n", anthStr("suc"), anthStr("prefix"), getenv("HOME"), anthStr("ori"));
        }
        else {
          chdir(exCmd[1]);
          printf("%s%s Current Directory Changed To: %s %s\n", anthStr("suc"), anthStr("prefix"), getenv("PWD"), anthStr("ori"));
        }
      }
      else if (enBGP == 1 && cmd[strlen(cmd) - 1] == '&') {
        anthLog(debug, "Background Request Detected");
        cmd[strlen(cmd) - 1] = '\0';
        ps = asTrackCon(ps);
        ps->cmd = asBreakdown(cmd, ppid);
        ps->fdin = asRedirectIn(ps->cmd);
        ps->fdout = asRedirectOut(ps->cmd);
        ps->cmd = asRmSpace(ps->cmd);
        int child = fork();
        ps->pid = child;
        if (child == 0) {
          waitpid(child, &exitCode, WNOHANG);
          /* Get path from env */
          char* path = getenv("PATH");
          /* Make sure path is an array that ends with NULL */
          char* envp[] = {path, NULL};
          execvpe(ps->cmd[0], &(*(ps->cmd)), envp);
          anthPtnApn("err", "Child Error: ", strerror(errno));
          if (debug) {
            perror("\nChild Error");
          }
          exit(1);
        }
        else {
          printf("%s%s Child Created ID: %d %s", anthStr("msg"), anthStr("prefix"), child, anthStr("ori"));
          if (debug) {
            perror("\nChild Error");
            fprintf(stderr, "\nChild Created ID: %d", child);
          }
          ps->pid = waitpid(child, &exitCode, WNOHANG);
          if (ps->pid != 0) {
            kill(child, SIGTERM);
            if (ps->fdin != 0) {
              close(ps->fdin);
              dup2(oristdin, 0);
            }
            if (ps->fdout != 0) {
              close(ps->fdout);
              dup2(oristdout, 1);
            }
            anthLog(debug, "Execution Complete");
            ps->status = exitCode;
            ps->exited = 1;
          }
        }
      }
      else {
        anthLog(debug, "Foreground Request Detected");
        char** exCmd = asBreakdown(cmd, ppid);
        int fdin = asRedirectIn(exCmd);
        int fdout = asRedirectOut(exCmd);
        if (fdin >= 0 && fdout >= 0) {
          exCmd = asRmSpace(exCmd);
          int child = fork();
          if (child == 0) {
            curryFPS = 1;
            /* Get path from env */
            char* path = getenv("PATH");
            /* Make sure path is an array that ends with NULL */
            char* envp[] = {path, NULL};
            execvpe(exCmd[0], &(*(exCmd)), envp);
            if (debug) {
              perror("\nChild Error");
            }
            anthPtnApn("err", "Child Error: ", strerror(errno));
            exit(1);
          }
          else {
            waitpid(child, &exitCode, 0);
            curryFPS = 0;
            kill(child, SIGTERM);
            if (fdin != 0) {
              close(fdin);
              dup2(oristdin, 0);
            }
            if (fdout != 0) {
              close(fdout);
              dup2(oristdout, 1);
            }
            if (WIFSIGNALED(exitCode)) {
              anthPtnApn("err", "The Child has been successfully assassinated by signal", strsignal(WTERMSIG(exitCode)));
            }
            if (debug) {
              fprintf(stderr, "\nChild Status: %d - %s", WTERMSIG(exitCode), strsignal(WTERMSIG(exitCode)));
            }
            anthLog(debug, "Execution Complete");
          }
        }
      }
    }
    /* CLEAR UIN HERE */
    memset(uin, 0, sizeof(uin));
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

char** asBreakdown(char* str, int pid) {
  char** strArr = calloc(2, sizeof(char*));
  int i = 0;
  char* token = NULL;
  /* Break down word surrounded by spaces */
  do {
    token = strtok_r(str, " ", &str);
    if (token != NULL) {
      anthLog2(debug, "token: ", token);
      strArr[i] = calloc((strlen(token) + 1), sizeof(char));
      if (asPID(token)) {
        char temp[2048];
        sprintf(temp, "%d", pid);
        strcpy(strArr[i], temp);
      }
      else {
        strcpy(strArr[i], token);
      }
      anthLog2(debug, "strArr[i]: ", strArr[i]);
      i++;
      strArr = realloc(strArr, (sizeof(char*) * (i + 1)));
      strArr[i] = NULL;
    }
  } while (token != NULL);
  anthLog2(debug, "strArr[i]: ", strArr[i]);
  return strArr;
}

char** asRmSpace(char** str) {
  int i = 0;
  while (str[i] != NULL) {
    if (strcmp(str[i], ">") == 0 || strcmp(str[i], "<") == 0) {
      free(str[i]);
      str[i] = NULL;
      anthLog(debug, "Redirection detected, replacing with NULL");
    }
    i++;
  }
  return str;
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

/**
 * Deconstruct asTrack
 */
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

int asRedirectIn(char** cmd) {
  int i = 0;
  int fd = 0;
  while (cmd[i] != NULL) {
    /* Input Redirect */
    if (strcmp(cmd[i], "<") == 0) {
      fd = open(cmd[i + 1], O_RDONLY);
      if (fd < 0) {
        anthPtnApn("err", "Unable to open file ", cmd[i + 1]);
        perror("Unable to open file");
      }
      else {
        if (dup2(fd, 0) == -1) {
          anthPtn("err", "Redirection failed");
          perror("Redirection failed");
        }
      }
    }
    i++;
  }
  return fd;
}

int asRedirectOut(char** cmd) {
  int i = 0;
  int fd = 0;
  while (cmd[i] != NULL) {
    /* Output Redirect */
    if (strcmp(cmd[i], ">") == 0) {
      fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (fd < 0) {
        anthPtnApn("err", "Unable to open file ", cmd[i + 1]);
        perror("Unable to open file");
      }
      else {
        if (dup2(fd, 1) == -1) {
          anthPtn("err", "Redirection failed");
          perror("Redirection failed");
        }
      }
    }
    i++;
  }
  return fd;
}

int asKillAll(struct asTrack* children) {
  while (children->next != NULL) {
    if (debug) {
      fprintf(stderr, "\n%sKilling PID: %d %s", anthStr("pink"), children->pid, anthStr("ori"));
    }
    kill(children->pid, SIGTERM);
    children = children->next;
  }
  return 0;
}

int asPID(char* cmd) {
  if (cmd[0] == '$' && cmd[1] == '$') {
    return 1;
  }
  return 0;
}

/**
 * A Shell Handle SIGINT
 */
void asHdInt(int signal) {
  /*write(STDOUT_FILENO, "Interrupt Signal Detected\n", 256);
  if (curryFPS == 1) {
    write(STDOUT_FILENO, "Assassinating The Child...\n", 256);
  }
  fflush(stdout);*/
}

/**
 * A Shell Handle SIGTSTP
 */
void asHdStop(int signal) {
  /*if (enBGP == 1) {
    char* message = "WARNING: Foreground Only Mode Activated\n";
    write(STDOUT_FILENO, message, 256);
    enBGP = 0;
  }
  else if (enBGP == 0) {
    char* message = "WARNING: Foreground Only Mode Deactivated\n";
    write(STDOUT_FILENO, message, 256);
    enBGP = 1;
  }
  fflush(stdout);*/
}

/**
 * A Shell Handle SIGTSTP
 */
void asHdChild(int signal) {
  /*char* message = "Child Termination Signal Detected\n";
  write(STDOUT_FILENO, message, 256);
  fflush(stdout);*/
  int pid;
  int stats;
  if ((pid = waitpid(-1, &stats, WNOHANG)) > 0) {
    printf("\n%s%s Child PID %d successfully assassinated by %d - %s %s\n", anthStr("warn"), anthStr("prefix"), pid, stats, strsignal(stats), anthStr("ori"));
  }
  fflush(stdout);
}
