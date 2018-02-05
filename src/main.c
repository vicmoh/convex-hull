/*import libraries*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <sys/time.h>

#define DEBUG true
#define debug if(DEBUG)printf

char* userInput(char* input){
    //ask for user input
    fgets(input, 100, stdin);
    input[strcspn(input, "\r\n")] = '\0';
    //return
    return input;
}//end func

char* setString(char* string){
    char* newString = calloc(strlen(string)+9, sizeof(char)* strlen(string)+9 );
    strcpy(newString, string);
    return newString;
}//end func

int main(int argc, char** argv){
    //dec vars
    char* menu = calloc(256, sizeof(char)*256);
    
    //infinite loop until user exits 
    while(true){
        //ask the user for the menu
        printf("1: Brute force inversion\n");
        printf("2: Divide and conquer inversion\n");
        printf("3: Brute force convex hull\n");
        printf("4: Divide and conquer convexhull\n");
        printf("5: Compare execution times of 1 and 2\n");
        printf("6: Compare execution times of 3 and 4\n");
        menu = userInput(menu);

        if(strcmp(menu, "1") == 0){
            //brute force
        }else if(strcmp(menu, "2") == 0){
            //devide and conquer
        }else if(strcmp(menu, "3") == 0){
            //brute forces convex hull
        }else if(strcmp(menu, "4") == 0){
            //divide and conquer convex hull
        }else if(strcmp(menu, "5") == 0){
            //compare execution times of 1 and 2
        }else if(strcmp(menu, "6") == 0){
            //compare execution times of 3 and 4
        }else if(strcmp(menu, "7") == 0){
            //exit
            free(menu);
            exit(0);
        }else{
            printf("Invalid input, please re-enter.\n");
        }//end if
    }//end while

}//end main