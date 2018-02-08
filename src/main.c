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
    double timeResult;
    int totalInversion;
    char fileName[99];
    int* array1;
    double* array2;
    int arraySize1;
    int arraySize2;
    struct timeval stop;
    struct timeval start;
}Instance;

Instance initInstance(){
    Instance newVars;
    newVars.timeResult = 0;
    newVars.totalInversion = 0;
    newVars.arraySize1 = 0;
    newVars.arraySize2 = 0;
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
    double start = 0;
    double stop = 0;
    //loop the first comparison index
    start = clock();
    for(int x=0; x < arraySize; x++){
        //loop the second comparison index
        for(int i=x+1; i < arraySize; i++){
            //check for inversion when comparing
            if(array[x] > array[i]){
                inversionCount++;
            }//end if
        }//end for
    }//end for
    stop = clock();
    double timeSpent = (double)(stop - start)/CLOCKS_PER_SEC;
    vars->totalInversion = inversionCount;
    vars->timeResult = timeSpent;
    // debug("debug totalInversion: %d\n", inversionCount);
    // debug("debug timeResult: %d\n", vars->timeResult);
}//end func

void loadData1(Instance* vars){
    //dec vars
    char line[256] = {"\0"};
    FILE* filePointer = fopen("./assets/data_1_a2.txt", "r");
    int memSize = 5;
    int* array = calloc(1, sizeof(array)*memSize);
    int arrayIndex = 0;
    //loop until the end of file
    printf("Loading data 1...\n");
    while(fgets(line, sizeof(line), filePointer) != NULL){
        line[strcspn(line, "\r\n")] = '\0';
        //debug("%s\n", line);
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
    fclose(filePointer);
    printf("Data 1 loaded\n");
    vars->arraySize1 = arrayIndex;
    vars->array1 = array;
}//end func

void loadData2(Instance* vars){
    //dec vars
    char line[256] = {"\0"};
    FILE* filePointer = fopen("./assets/data_2_a2.txt", "r");
    int memSize = 2;
    double* array = calloc(1, sizeof(array)*memSize);
    int arrayIndex = 0;
    //loop until the end of file
    printf("Loading data 2...\n");
    while(fgets(line, sizeof(line), filePointer) != NULL){
        line[strcspn(line, "\r\n")] = '\0';
        //debug("%s\n", line);
        //take line and put it to the array
        for(int x = 0; x < 2; x++){
            char temp[99] = {"\0"};
            sprintf(temp, "%s", line);
            array[arrayIndex] = atof(temp);
            arrayIndex++;
        }//end for
        //create more memory
        memSize += 2;
        array = realloc(array, sizeof(array)*(memSize));
    }//end while
    fclose(filePointer);
    printf("Data 2 loaded\n");
    vars->arraySize2 = arrayIndex;
    vars->array2 = array;
}//end func

int mergeSort(int array[], int array_size){
    //this function sort the input using divide conquer
    int* tempArray = malloc(sizeof(tempArray)*arraySize);
    return recurseMergeSort(array, tempArray, 0, arraySize - 1);
}//end func
 
int recurseMergeSort(int array[], int tempArray[], int left, int right){
    //a recursion function that sorts using merge sort
    int middle = 0;
    int inversionCoutn = 0;
    if(left < right){
        //divide the array into 2
        middle = (left + right)/2;
        //sum the inversion for left and right sections
        inversionCount  = recurseMergeSort(arr, tempArray, left, middle);
        inversionCount = inversionCount + recurseMergeSort(arr, tempArray, middle+1, right);
        
        //dec a tempArray vars
        int leftIndex = rightIndex = left;//for teh left and right array index section
        int middleIndex = middle;//for the right array index section 
        //combined the two sections
        while ((leftIndex <= middle) && (middleIndex <= right)){
            if (array[leftIndex] <= array[middleIndex]){
                //iterate to the next index
                rightIndex = rightIndex + 1;
                leftIndex = leftIndex + 1;
                //added it to the temp array
                tempArray[rightIndex] = array[leftIndex];
            }else{
                //iterate to the next index
                rightIndex = rightIndex + 1;
                leftIndex = leftIndex + 1;
                //added to the temp array
                tempArray[rightIndex] = array[middleIndex];
                inversionCount += (middle + 1 - leftIndex);
            }//end if
        }//end while

        //copy the left section of the remaining element of the arrayay
        while(leftIndex <= middle){
            //iterate to the next index
            rightIndex = rightIndex + 1;
            leftIndex = leftIndex + 1;
            //added to the temp array
            tempArray[rightIndex] = array[leftIndex];
        }//end while

        //copy again, but this time do to the right
        while(middleIndex <= right){
            //iterate to the next index
            rightIndex = rightIndex + 1;
            leftIndex = leftIndex + 1;
            //added to the temp array
            tempArray[rightIndex] = array[middleIndex];
        }//end while

        //copy to the originated arrayay
        for(leftIndex=left; leftIndex <= right; leftIndex++){
            array[leftIndex] = tempArray[leftIndex];
        }//end for

        //return the inversion count
        return inversionCount;
    }//end if

    //return the inversion count
    return inversionCount;
}//end func

int main(int argc, char** argv){
    //dec vars
    char* menu = calloc(256, sizeof(char)*256);
    Instance vars = initInstance();

    //load data 1 and 2
    loadData1(&vars);
    loadData2(&vars);
    
    //infinite loop until user exits 
    while(1){
        //ask the user for the menu
        printf("1: Brute force inversion\n");
        printf("2: Divide and conquer inversion\n");
        printf("3: Brute force convex hull\n");
        printf("4: Divide and conquer convexhull\n");
        printf("5: Compare execution times of 1 and 2\n");
        printf("6: Compare execution times of 3 and 4\n");
        printf("7: Exit\n");
        printf("Enter the menu:\n");
        menu = userInput(menu);

        if(strcmp(menu, "1") == 0){
            //brute force
            printf("Calculating...\n");
            countInversion(vars.array1, vars.arraySize1, &vars);
            printf("Total inversion: %d\n", vars.totalInversion);
            printf("Total execution time: %f seconds\n", vars.timeResult);
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
            free(vars.array2);
            free(menu);
            exit(0);
        }else{
            printf("Invalid input, please re-enter.\n");
        }//end if
    }//end while
}//end main