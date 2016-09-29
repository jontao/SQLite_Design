/*
 * prompt.c
 *
 *  Created on: Sep 26, 2016
 *      Author: tech
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
const char continue_prompt[10];
const char main_prompt[10];
static char *local_getline(char *zSql, FILE *in, int csvFlag){
  char *zLine;
  int nLine;
  int n;
  int inQuote = 0;
  char *zPrompt;

  if( zSql!=NULL && zSql[0]!=NULL )
  {
	  printf("%s",continue_prompt);
  }else{
	  printf("%s",main_prompt);
  }
  fflush(stdout);

  nLine = 100;
  zLine = malloc( nLine );
  if( zLine==0 ) return 0;
  n = 0;
  while( 1 ){
    if( n+100>nLine ){
      nLine = nLine*2 + 100;
      zLine = realloc(zLine, nLine);
      if( zLine==0 ) return 0;
    }
    if( fgets(&zLine[n], nLine - n, in)==0 ){
      if( n==0 ){
        free(zLine);
        return 0;
      }
      zLine[n] = 0;
      break;
    }
    while( zLine[n] ){
      if( zLine[n]=='"' ) inQuote = !inQuote;
      n++;
    }
    if( n>0 && zLine[n-1]=='\n' && (!inQuote || !csvFlag) ){
      n--;
      if( n>0 && zLine[n-1]=='\r' ) n--;
      zLine[n] = 0;
      break;
    }
  }
  zLine = realloc( zLine, n+1 );
  return zLine;
}

static int process_input(struct callback_data *p, FILE *in){
	char *zSql = 0;
}


