/****************************************************
 *                                                  *
 * Name: program.c                                  *
 * Description: CS 344 Assignment 4                 *
 *              Program Manager                     *
 * Date: Feburary 6, 2021                           *
 * Created with <3 by: Anthony Kung                 *
 * Author URL: https://anth.dev                     *
 * License: Apache-2.0 (See /LICENSE.md)            *
 *                                                  *
 ****************************************************/

#include "program.h"
#include "ashell.h"

/**
 * Program Manager Function
 * Used to call functions from main
 */
int main(int argc, char *argv[]) {
  anth();
  return asMain(argc, argv);
}
