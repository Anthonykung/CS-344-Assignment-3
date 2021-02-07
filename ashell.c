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
    printf("\n%s:%s", anthStr("prmp"), anthStr("ori"));
    char uin[2048];
    scanf("%s", uin);
  }
  while (!exitStatus);
  return exitCode;
}

int asCmdCheck(char* cmd) {
  if
}
