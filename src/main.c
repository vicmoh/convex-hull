/***********************************
 * Vicky Mohammad
 * 0895381
 ***********************************/

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
#include <time.h>
//macros
#define DEBUG true
#define debug if(DEBUG)printf

typedef struct instanceVars{
    int timeResult;
    int totalInversion;
    int timerWhich;
    char fileName[99];
    int* array1;
    int* array2;
    int arraySize1;
    int arraySize2;
    struct itimerval timerValue;
    struct itimerval timerOValue;
    struct itimerval timerPValue;
}Instance;

Instance initInstance(){
    Instance newVars;
    newVars.timeResult = 0;
    newVars.totalInversion = 0;
    newVars.arraySize1 = 0;
    newVars.arraySize2 = 0;
    newVars.timerWhich = ITIMER_REAL;
    return newVars;
}//end constructor

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

void countInversion(int array[], int arraySize, Instance* vars){
    //dec vars
    int inversionCount = 0;
    time_t currentTime = 0;
    getitimer(vars->timerWhich, &vars->timerPValue);
    //loop the first comparison index
    for(int x=0; x < arraySize; x++){
        //loop the second comparison index
        for(int i=x+1; i < arraySize; i++){
            //check for inversion when comparing
            if(array[x] > array[i]){
                time(&currentTime);
                debug("debug timer currentTime: %s\n", ctime(&currentTime));
                inversionCount++;
            }//end if
        }//end for
    }//end for
    debug("debug totalInversion: %d\n", inversionCount);
    vars->totalInversion = inversionCount;
    vars->timeResult = setitimer(vars->timerWhich, &vars->timerValue, &vars->timerOValue);
}//end func

void loadData1(Instance* vars){
    //dec vars
    char line[256] = {"\0"};
    FILE* filePointer = fopen("./assets/data_1_a2.txt", "r");
    int memSize = 5;
    int* array = calloc(1, sizeof(array)*memSize);
    int arrayIndex = 0;
    //loop until the end of file
    printf("Loading data...\n");
    while(fgets(line, sizeof(line), filePointer) != NULL){
        line[strcspn(line, "\r\n")] = '\0';
        debug("%s\n", line);
        //take line and put it to the array
        for(int x = 0; x < 5; x++){
            char temp[99] = {"\0"};
            sprintf(temp, "%s", line);
            array[arrayIndex] = atoi(temp);
            arrayIndex++;
        }//end for
        //create more memory
        memSize += 5; 
        array = realloc(array, sizeof(array)*(memSize));
    }//end while
    printf("Data loaded...\n");
    vars->arraySize1 = arrayIndex;
    vars->array1 = array;
}//end func

int main(int argc, char** argv){
    //dec vars
    char* menu = calloc(256, sizeof(char)*256);
    Instance vars = initInstance();

    //load data 1
    loadData1(&vars);
    
    //infinite loop until user exits 
    while(1){
        //ask the user for the menu
        printf("1: Brute force inversion\n");
        printf("2: Divide and conquer inversion\n");
        printf("3: Brute force convex hull\n");
        printf("4: Divide and conquer convexhull\n");
        printf("5: Compare execution times of 1 and 2\n");
        printf("6: Compare execution times of 3 and 4\n");
        printf("Enter the menu:\n");
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
            free(vars.array1);
            free(menu);
            exit(0);
        }else{
            printf("Invalid input, please re-enter.\n");
        }//end if
    }//end while

}//end main