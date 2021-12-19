#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printInColor(char *color, char *text){
    if(strcmp(color,"black") == 0)
     printf("\033[0;30m");  

    if(strcmp(color,"red") == 0)
     printf("\033[1;31m");
    
    if(strcmp(color,"green") == 0)
     printf("\033[0;32m");
    
    if(strcmp(color,"yellow") == 0)
     printf("\033[1;33m");

    if(strcmp(color,"blue") == 0)
     printf("\033[0;34m");

    if(strcmp(color,"purple") == 0)
     printf("\033[0;35m"); 

    if(strcmp(color,"cyan") == 0)
     printf("\033[0;36m"); 

    if(strcmp(color,"white") == 0)
     printf("\033[0;37m"); 


    printf("%s",text);
}

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

void invalid_param(int argc, char **argv){
    printf("\n\nUsage: %s -m<mode> -d<row> -d<col>\n", argv[0]);
    printf("mode  specifies the mode: \n");
    printf("[1] : single player game (random)\n");
    printf("[2] : single player game (AI)\n");
    printf("[3] : two players game\n");
    printf("<row> : specifies the number of rows (>= 4)\n");
    printf("<col> : specifies the number of columns (>= 4)");
    
}