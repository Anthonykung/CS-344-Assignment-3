/**************************************************
 *                                                *
 * Name: anthonian.c                              *
 * Description: Anthonian Helper Utility          *
 * Date: July 19, 2020                            *
 * Created by: Anthony Kung                       *
 * Author URL: https://anth.dev                   *
 * License: Apache-2.0 (See /LICENSE.md)          *
 *                                                *
 **************************************************/

#include "anthonian.h"

const char* anthStr(char* arg) {
  /* Super Duper Pinkish Pink */
  char* pink = "\033[38;2;255;20;147m";
  /* Colors */
  char* ori = "\033[0m";
  char* red = "\033[91m";
  char* green = "\033[92m";
  char* yellow = "\033[93m";
  char* blue = "\033[94m";
  char* cyan = "\033[96m";

  char* prefix = "\n>_";

  if (strcmp(arg, "pink") == 0 || strcmp(arg, "anth") == 0) {
    return pink;
  }
  else if (strcmp(arg, "ori") == 0) {
    return ori;
  }
  else if (strcmp(arg, "red") == 0 || strcmp(arg, "err") == 0) {
    return red;
  }
  else if (strcmp(arg, "green") == 0 || strcmp(arg, "suc") == 0) {
    return green;
  }
  else if (strcmp(arg, "yellow") == 0 || strcmp(arg, "warn") == 0) {
    return yellow;
  }
  else if (strcmp(arg, "blue") == 0 || strcmp(arg, "msg") == 0) {
    return blue;
  }
  else if (strcmp(arg, "cyan") == 0 || strcmp(arg, "prmp") == 0 || strcmp(arg, "prpt") == 0) {
    return cyan;
  }
  else if (strcmp(arg, "prefix") == 0) {
    return prefix;
  }
  else
  {
    return NULL;
  }
}

/* Anth Dev */
void anthdev() {
  printf("\n\033[38;2;255;20;147m");
  printf(" █████  ███    ██ ████████ ██   ██    ██████  ███████ ██    ██\n");
  printf("██   ██ ████   ██    ██    ██   ██    ██   ██ ██      ██    ██\n");
  printf("███████ ██ ██  ██    ██    ███████    ██   ██ █████   ██    ██\n");
  printf("██   ██ ██  ██ ██    ██    ██   ██    ██   ██ ██       ██  ██ \n");
  printf("██   ██ ██   ████    ██    ██   ██ ██ ██████  ███████   ████  \n");
  printf("\033[0m\n");
}

/* Intro */
void anthIntro() {
  anthdev();
  printf("%s %s Welcome to Anthonian Config Utility!", anthStr("blue"), anthStr("prefix"));
  printf("%s Find up to date information on Anth.Dev!", anthStr("prefix"));
  printf("%s Let's get you familiarize with this", anthStr("prefix"));
  printf("%s %s Press [ENTER] to continue %s", anthStr("cyan"), anthStr("prefix"), anthStr("ori"));
  printf("%s", anthStr("ori"));
}

/* Color Coding */
void anthColors() {
  printf("%s %s", anthStr("prefix"), "Color Coding");
  printf("%s %s RED %s -- Error, user action required", anthStr("prefix"), anthStr("red"), anthStr("ori"));
  printf("%s %s YELLOW %s -- Warning, user action not required", anthStr("prefix"), anthStr("yellow"), anthStr("ori"));
  printf("%s %s GREEN %s -- Success, no further action required", anthStr("prefix"), anthStr("green"), anthStr("ori"));
  printf("%s %s CYAN %s -- Prompt, user input required", anthStr("prefix"), anthStr("cyan"), anthStr("ori"));
  printf("%s %s BLUE %s -- Information, no action required", anthStr("prefix"), anthStr("blue"), anthStr("ori"));
  printf("%s %s PINK %s -- Anthonian Message, action maybe required", anthStr("prefix"), anthStr("pink"), anthStr("ori"));
  printf("%s %s WHITE %s -- All Others, messages from system or debugger or uncategorized", anthStr("prefix"), anthStr("ori"), anthStr("ori"));
  printf("%s %s Alright, that\'t all for now. If you need more help, try %s --help %s", anthStr("prefix"), anthStr("blue"), anthStr("pink"), anthStr("ori"));
  printf("%s %s Press [ENTER] to continue %s\n", anthStr("cyan"), anthStr("prefix"), anthStr("ori"));
}

/* Newline */
void anthNln() {
  printf("\n");
}

/* Clear Console */
void anthClr() {
  /* For Linux */
  system("clear");
  /* For Windows */
  system("cls");
}

/* Printing Function */
void anthPtn(char* color, char* str) {
  if (strcmp(color, "suc") == 0) {
    printf("%s %s SUCCESS: %s %s\n", anthStr(color), anthStr("prefix"), str, anthStr("ori"));
  }
  else if (strcmp(color, "err") == 0) {
    printf("%s %s ERROR: %s %s\n", anthStr(color), anthStr("prefix"), str, anthStr("ori"));
  }
  else if (strcmp(color, "warn") == 0) {
    printf("%s %s WARNING: %s %s\n", anthStr(color), anthStr("prefix"), str, anthStr("ori"));
  }
  else {
    printf("%s %s %s %s\n", anthStr(color), anthStr("prefix"), str, anthStr("ori"));
  }
}

/* Printing String And Append Function */
void anthPtnApn(char* color, char* str, char* apn) {
  printf("%s %s %s%s %s\n", anthStr(color), anthStr("prefix"), str, apn, anthStr("ori"));
}

/* Wait Function Miliseconds */
int anthWait(unsigned long milisec) {
  struct timespec anth;
  time_t sec = (int)(milisec / 1000);
  milisec = milisec - (sec * 1000);
  anth.tv_sec = sec;
  anth.tv_nsec = milisec * 1000000L;
  while (nanosleep(&anth, &anth) == -1)
    continue;
  return 1;
}

/* Processing Function */
void anthProc(char* str) {
  anthPtnApn("msg", str, ".");
  anthWait(1000);
  anthPtnApn("msg", str, "..");
  anthWait(1000);
  anthPtnApn("msg", str, "...");
}

/* Primary Function */
void anth() {
  char temp = NULL;
  anthIntro();
  temp = getchar();
  if (temp) {
    anthColors();
    temp = getchar();
    if (temp) {
      return;
    }
  }
}

/* File Extension Checker */
int anthExtChecker(char* str, char* ext) {
  int i = 0;
  for (i = 0; i < strlen(ext); i++) {
    if (str[strlen(str) - i] != ext[strlen(ext) - i]) {
      /*anthPtn("err", "File Extension Check Failed");*/
      return 0;
    }
  }
  /*anthPtn("suc", "File Extension Check Passed");*/
  return 1;
}

/* String To Integer */
int strtoi(const char* str) {
  return (int) strtol(str, (char **)NULL, 10);
}

/* Remove Char From String */
void anthRmCharFromStr(char* str, char cmp) {
  int i = 0;
  int j = 0;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] != cmp) {
      str[j++] = str[i];
    }
  }
  str[j] = '\0';
}

void anthIOFlush(char* str) {
  /* Check For Newline */
  if (strchr(str, '\n') == NULL){
    /* Scan Until Newline */
    scanf("%*[^\n]");
    /* Take The Newline */
    scanf("%*c");
  }
}

char* anthToLower(char* str) {
  int i = 0;
  for(i = 0; str[i]; i++){
    str[i] = tolower(str[i]);
  }
  return str;
}

char* anthRmNln(char* str) {
  int i = 0;
  for(i = 0; str[i]; i++){
    if (str[i] == '\n')
    str[i] = '\0';
  }
  return str;
}

void anthBye() {
  printf("\n%s %s %s", anthStr("green"), "██████╗ ██╗   ██╗███████╗", anthStr("ori"));
  printf("\n%s %s %s", anthStr("green"), "██╔══██╗╚██╗ ██╔╝██╔════╝", anthStr("ori"));
  printf("\n%s %s %s", anthStr("green"), "██████╔╝ ╚████╔╝ █████╗  ", anthStr("ori"));
  printf("\n%s %s %s", anthStr("green"), "██╔══██╗  ╚██╔╝  ██╔══╝  ", anthStr("ori"));
  printf("\n%s %s %s", anthStr("green"), "██████╔╝   ██║   ███████╗", anthStr("ori"));
  printf("\n%s %s %s", anthStr("green"), "╚═════╝    ╚═╝   ╚══════╝", anthStr("ori"));
  printf("\n");
}

int anthRand(int min, int max) {
  srand(time(0));
  int num = (rand() % (max - min + 1)) + min;
  return num;
}

int anthCheckPrefix(char* str, char* prefix) {
  int i = 0;
  for (i = 0; i < strlen(prefix); i++) {
    if (str[i] != prefix[i]) {
      /*anthPtn("err", "File Prefix Check Failed");*/
      return 0;
    }
  }
  /*anthPtn("suc", "File Prefix Check Passed");*/
  return 1;
}

int anthIfFileExist(char* name) {
  FILE* curry = fopen(name, "r");
  if (curry) {
    fclose(curry);
    return 1;
  }
  else {
    anthPtnApn("err", "Unable to locate file with name ", name);
    /*printf("TEST");*/
    return 0;
  }
}

int anthIsEmpty(const char* str) {
  int i = 0;
  for (i = 0; i < strlen(str); i++) {
    if (!isspace(str)) {
      return 0;
    }
  }
  return 1;
}
