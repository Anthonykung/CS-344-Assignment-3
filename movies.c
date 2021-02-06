/****************************************************
 *                                                  *
 * Name: movies.c                                   *
 * Description: CS 344 Assignment 1                 *
 *              Movie Program Function              *
 * Date: January 16, 2021                           *
 * Created with <3 by: Anthony Kung                 *
 * Author URL: https://anth.dev                     *
 * License: Apache-2.0 (See /LICENSE.md)            *
 *                                                  *
 ****************************************************/

#include "movies.h"

/* Validate File Extension */
int movieArgCheck(char *argv[]) {
  /* anthProc("Validating Argument"); */
  if (anthExtChecker(argv[1], ".csv")) {
    /* Validation Passed */
    /* Move To Read File */
    return anthReadFile(argv[1]);
  }
  else {
    return 1;
  }
}

int anthReadFile(char* filePath) {
  /*anthProc("Reading File");*/
  FILE* fileLoc = fopen(filePath, "r");
  if (fileLoc != NULL) {
    /*anthPtn("suc", "File Opened Successfully");*/
    /* anthProc("Processing File Data"); */
    struct movies* movie = movieCreate(fileLoc, filePath);
    return primaryProgram(movie);
    /*anthPtn("suc", "File Data Processed");*/
  }
  else {
    anthPtn("err", "Unable to open file");
    return 1;
  }
}

struct movies* movieCreate(FILE* fileLoc, char* filePath) {
  /* anthProc("Creating Structure"); */
  char* line = NULL;
  size_t length = 0;
  ssize_t curryLine;
  struct movies* movie = NULL;
  struct movies* last = NULL;
  int tracker = 0;
  while ((curryLine = getline(&line, &length, fileLoc)) != -1) {
    /*anthPtn("msg", "enter newline");*/
    /*anthPtn("msg", "While Loop Started");*/
    struct movies* curry = movieAdd(line);
    /* Check If Data Is Valid */
    if (!movieValidator(curry)) {
      tracker++;
      /*anthPtn("msg", "Struct Added");*/
      if (movie == NULL) {
        movie = curry;
        last = curry;
      }
      else {
        last->next = curry;
        last = curry;
      }
    }
    else {
      /* If Not Valid Discard */
      movieRemove(curry);
      /*anthPtn("msg", "exited remove");*/
    }
    /*anthPtn("msg", "exited else");*/
  }
  /*printf("%s %s Processed file %s and parsed data for %d movies %s\n", anthStr("suc"), anthStr("prefix"), filePath, tracker, anthStr("ori"));*/
  free(line);
  fclose(fileLoc);
  return movie;
}

struct movies* movieAdd(char* curryLine) {
  /*anthPtn("msg", "Allocating Curry");*/
  struct movies* curry = malloc(sizeof(struct movies));
  /*anthPtn("suc", "Curry Allocated");*/
  char* token = NULL;

  /* Get Title */
  /*anthPtn("msg", "Getting Title");*/
  token = strtok_r(curryLine, ",", &curryLine);
  if (token == NULL) {
    anthPtn("err", "Movie Data Parsing Failed");
    return NULL;
  }
  /*anthPtnApn("msg", "Title ", token);*/
  curry->title = calloc(strlen(token) + 1, sizeof(char));
  strcpy(curry->title, token);
  /*anthPtn("suc", "Title Received");*/
  /*anthProc("Waiting");*/

  /* Get Year */
  /*anthPtn("msg", "Getting Year");*/
  token = strtok_r(curryLine, ",", &curryLine);
  if (token == NULL) {
    anthPtn("err", "Movie Data Parsing Failed");
    return NULL;
  }
  /*anthPtnApn("msg", "Year ", token);*/
  curry->year = calloc(strlen(token) + 1, sizeof(char));
  strcpy(curry->year, token);
  /*anthProc("Waiting");*/

  /* Get Languages */
  /*anthPtn("msg", "Getting Language");*/
  token = strtok_r(curryLine, ",", &curryLine);
  if (token == NULL) {
    anthPtn("err", "Movie Data Parsing Failed");
    return NULL;
  }
  curry->language = languageFilter(token);

  /* Get Rating */
  /*anthPtn("msg", "Gettine Rating");*/
  token = strtok_r(curryLine, ",", &curryLine);
  if (token == NULL) {
    anthPtn("err", "Movie Data Parsing Failed");
    return NULL;
  }
  curry->rating = calloc(strlen(token) + 1, sizeof(char));
  strcpy(curry->rating, token);

  curry->next = NULL;

  return curry;
}

int movieRemove(struct movies* movie) {
  while (movie != NULL) {
    free(movie->title);
    free(movie->year);
    languageFreer(movie->language);
    free(movie->rating);
    struct movies* temp = movie;
    movie = movie->next;
    free(temp);
  }
  anthPtn("suc", "Movie Structure Freed");
  return 0;
}


int languageFreer(char** lang) {
  int i = 0;
  for (i = 0; i < 5; i++) {
    if (lang[i]) {
      /*anthPtnApn("warn", "Prefree language: ", lang[i]);*/
      free(lang[i]);
      /*anthPtn("warn", "Language freed");*/
    }
  }
  free(lang);
  /*anthPtn("warn", "Lang freed");*/
  return 0;
}

char** languageFilter(char* lang) {
  /*anthPtn("msg", "Filtering Languages");*/
  char** strArray = malloc(5*sizeof(char*));
  char* token = NULL;
  anthRmCharFromStr(lang, '[');
  anthRmCharFromStr(lang, ']');
  int num = 0;
  while (num < 5) {
    if ((token = strtok_r(lang, ";", &lang))) {
      strArray[num] = malloc(20*sizeof(char));
      /*anthPtn("msg", "Allocating String");*/
      strcpy(strArray[num], token);
      /*anthPtn("msg", "String Allocated");*/
    }
    else {
      strArray[num] = NULL;
    }
    num++;
  }
  /*anthPtn("msg", "Returning");*/
  return strArray;
}

void moviePrintTitle(struct movies* movie, char* year) {
  /*anthPtn("msg", "Option 1 Selected");*/
  struct movies* temp = movie;
  int count = 0;
  if (strtoi(year) >= 1900 && strtoi(year) <= 2021) {
    while (movie != NULL) {
      /*anthPtn("msg", movie->year);*/
      if (strtoi(movie->year) == strtoi(year)) {
        anthPtn("msg", movie->title);
        count++;
      }
      movie = movie->next;
    }
    if (count == 0) {
      anthPtnApn("warn", "WARNING: No data about movies released in the year ", year);
    }
  }
  else {
    anthPtnApn("warn", "WARNING: Year entered out of range ", year);
  }
  movie = temp;
}

void moviePrintRating(struct movies* movie) {
  struct movies* temp = movie;
  char** year = NULL;
  char** rating = NULL;
  char** title = NULL;
  int size = 1;
  while (movie != NULL) {
    /* If Checking Array Is Empty */
    if (size == 1) {
      /* If Empty Create */
      year = malloc((size + 1) * sizeof(char*));
      rating = malloc((size + 1) * sizeof(char*));
      title = malloc((size + 1) * sizeof(char*));
      size++;
      /* Copy First Movie */
      /*anthPtn("msg", "Copy First Movie");*/
      year[0] = movie->year;
      rating[0] = movie->rating;
      title[0] = movie->title;
      /*anthPtn("warn", movie->title);*/
    }
    /* If Not Empty Check If Year Already In Checking Array */
    else {
      int i = 0;
      int checker = 0;
      for (i = 0; i < size; i++) {
        /* To Prevent Seg Fault */
        if (movie->year != NULL && year[i] != NULL) {
          /* If Year Already In, Check If Rating Is Higher */
          /*anthPtn("warn", movie->title);*/
          /*printf("\n Year: %s Year: %s\n", movie->year, year[i]);*/
          /*printf("\n Rating: %s Rating: %s\n", movie->rating, rating[i]);*/
          if (strcmp(movie->year, year[i]) == 0) {
            /* If Rating Is Higher Replace */
            /*anthPtn("msg", "If Rating Is Higher Replace");*/
            /*printf("\n Rating: %s Rating: %s\n", movie->rating, rating[i]);*/
            if (strtof(movie->rating, NULL) > strtof(rating[i], NULL)) {
              /*anthPtn("msg", "Rating Is Higher Replace");*/
              rating[i] = movie->rating;
              title[i] = movie->title;
              /*anthPtn("msg", "Rating Replace");*/
            }
            else if (strtof(movie->rating, NULL) == strtof(rating[i], NULL)) {
              /* If Same Rating Randomly Choose One */
              if (anthRand(0, 1)) {
                rating[i] = movie->rating;
                title[i] = movie->title;
              }
            }
            /* If Rating Is Not Higher Skip */
            else {
              checker = -1;
            }
            /*anthPtn("msg", "Out of IF");*/
          }
          else {
            /* If Year Not Match Increment Checker */
            /*anthPtn("err", "Increment Checker");*/
            checker++;
            /*anthPtn("msg", "Incremented Checker");*/
          }
          /*anthPtn("msg", "Out of ELSE IF");*/
        }
      }
      /*printf("Checker: %d I: %d\n", checker, i);*/
      /* If Checker == i, Year Is Not In Array */
      if (checker == i) {
        /* If Not In Array Create */
        /*anthPtn("msg", "Not In Array Create");*/
        size++;
        year = realloc(year, (size + 1) * sizeof(char*));
        rating = realloc(rating, (size + 1) * sizeof(char*));
        title = realloc(title, (size + 1) * sizeof(char*));
        /* Copy First Movie */
        /*anthPtn("msg", "Copy First Movie");*/
        year[size-1] = movie->year;
        rating[size-1] = movie->rating;
        title[size-1] = movie->title;
      }
    }
    movie = movie->next;
  }
  movie = temp;
  int i = 0;
  for (i = 0; i < size; i++) {
    if (year[i] != NULL && rating[i] != NULL && title[i] != NULL && strtof(rating[i], NULL) >= 1 && strtof(rating[i], NULL) <= 10 && strtoi(year[i]) >= 1900 && strtoi(year[i]) <= 2021) {
      printf("%s %s %s %.1f %s %s", anthStr("msg"), anthStr("prefix"), year[i], strtof(rating[i], NULL), title[i], anthStr("ori"));
    }
  }
  free(year);
  free(rating);
  free(title);
  printf("\n");
}

void moviePrintLanguage(struct movies* movie, char* lang) {
  struct movies* temp = movie;
  int checker = 0;
  char comparer[strlen(lang) - 1];
  strncpy(comparer, lang, (strlen(lang) - 1));
  while (movie != NULL) {
    int i = 0;
    for (i = 0; i < 5; i++) {
      /*anthPtnApn("msg", "Language: ", movie->language[i]);*/
      /*anthPtnApn("msg", "Lang: ", lang);*/
      if (movie->language[i] == NULL) {
        /*anthPtn("msg", "NULL");*/
        break;
      }
      else if (strcmp(movie->language[i], comparer) == 0) {
        /*anthPtn("msg", "Matched");*/
        checker++;
        printf("%s %s %s %s %s", anthStr("msg"), anthStr("prefix"), movie->year, movie->title, anthStr("ori"));
      }
      else {
        /*printf("%i", strcmp(movie->language[i], lang));*/
      }
    }
    movie = movie->next;
  }
  if (checker == 0) {
    anthPtnApn("warn", "WARNING: No data found with the language ", lang);
  }
  movie = temp;
  printf("\n");
}

int movieValidator(struct movies *movie) {
  if (movie != NULL) {
    if (movie->title != NULL && movie->language != NULL && movie->rating != NULL && movie->year != NULL) {
      if (strtoi(movie->year) >= 1900 && strtoi(movie->year) <= 2021) {
        if (strtof(movie->rating, NULL) >= 1 && strtof(movie->rating, NULL) <= 10) {
          /* anthPtn("suc", "Movie Date Accepted"); */
          return 0;
        }
        else {
          anthPtn("err", "Movie Rating Rejected");
          return 1;
        }
      }
      else {
        anthPtn("err", "Movie Date Rejected");
        return 1;
      }
    }
    else {
      anthPtn("err", "Movie Objects Returned NULL");
      return 1;
    }
  }
  else {
    anthPtn("err", "Movie Returned NULL");
    return 1;
  }
}

int primaryProgram(struct movies *movie) {
  int terminator = 1;
  while (terminator) {
    anthNln();
    anthPtn("prpt", "1. Show movies released in the specified year");
    anthPtn("prpt", "2. Show highest rated movie for each year");
    anthPtn("prpt", "3. Show the title and year of release of all movies in a specific language");
    anthPtn("prpt", "4. Exit from the program");
    char uin[512];
    fgets(uin, 512, stdin);
    anthIOFlush(uin);
    if (strtoi(uin) == 1) {
      anthPtn("prpt", "Enter the year for which you want to see movies:");
      char year[6];
      fgets(year, 6, stdin);
      moviePrintTitle(movie, year);
      anthIOFlush(year);
    }
    else if (strtoi(uin) == 2) {
      moviePrintRating(movie);
    }
    else if (strtoi(uin) == 3) {
      anthPtn("prpt", "Enter the language for which you want to see movies:");
      char lang[21];
      fgets(lang, 21, stdin);
      moviePrintLanguage(movie, lang);
      /*anthPtn("suc", "Returned successfully");*/
      anthIOFlush(lang);
    }
    else if (strtoi(uin) == 4) {
      terminator = 0;
    }
    else {
      anthPtn("err", "Invalid Input");
    }
    /*anthPtn("suc", "Existed if statements");*/
  }
  movieRemove(movie);
  anthBye();
  return 0;
}