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
#define d debug("CHECK\n");

/***********************************************************
 * Headers
 ***********************************************************/

//struct points for array 2
typedef struct points{
    double x;
    double y;
}Points;
//struct that act as instance vars
typedef struct instanceVars{
    char fileName[99];
    int* array1;
    Points* array2;
    int arraySize1;
    int arraySize2;
}Instance;
//helper fucnctions
Instance* initInstance();
char* userInput(char* input);
char* setString(char* string);
int countInversion(int array[], int arraySize);
//functions to load the data
void loadData1(Instance* vars);
void loadData2(Instance* vars);
//for merge sort 
int mergeSort(int array[], int arraySize);
int recurseMergeSort(int array[], int tempArray[], int left, int right);
int merge(int array[], int tempArray[], int left, int middle, int right);

/***********************************************************
 * Functions
 ***********************************************************/

Instance* initInstance(){
    Instance* newVars = calloc(1, sizeof(Instance));
    newVars->arraySize1 = 0;
    newVars->arraySize2 = 0;
    return newVars;
}//end constructor

char* userInput(char* input){
    //ask for user input
    fgets(input, 256, stdin);
    input[strcspn(input, "\r\n")] = '\0';
    //return
    return input;
}//end func

char* setString(char* string){
    char* newString = calloc(strlen(string)+9, sizeof(char)* strlen(string)+9 );
    strcpy(newString, string);
    return newString;
}//end func

int countInversion(int array[], int arraySize){
    //dec vars
    int inversionCount = 0;
    //loop the first comparison index
    for(int x=0; x < arraySize; x++){
        //loop the second comparison index
        for(int i=x+1; i < arraySize; i++){
            //check for inversion when comparing
            if(array[x] > array[i]){
                inversionCount++;
            }//end if
        }//end for
    }//end for
    // debug("debug totalInversion: %d\n", inversionCount);
    // debug("debug timeResult: %d\n", vars->timeResult);
    return inversionCount;
}//end func

void loadData1(Instance* vars){
    //dec vars
    const int arraySize = 50000;
    int* array = malloc(sizeof(int)*arraySize);
    FILE* filePointer = fopen("./assets/data_1_a2.txt", "r");
    //loop until the end of file
    printf("Loading data 1...\n");
    for(int x=0; x<arraySize; x++){
        fscanf(filePointer, "%d", &array[x]);
    }//end for
    fclose(filePointer);
    printf("Data 1 loaded\n");
    vars->array1 = array;
    vars->arraySize1 = arraySize;
}//end func

void loadData2(Instance* vars){
    //count the size of the file
    FILE* filePointerSize = fopen("./assets/data_2_a2.txt", "r");
    char buffer[256];
    int totalSize = 0;
    while(fgets(buffer, 256, filePointerSize)){
        totalSize = totalSize + 2;
    }//end while
    debug("totalSize: %d\n", totalSize);
    fclose(filePointerSize);

    //dec vars for reading the array
    const int arraySize = totalSize;
    Points* array = malloc(sizeof(Points)*arraySize);

    //loop until the end of file
    FILE* filePointer = fopen("./assets/data_2_a2.txt", "r");
    printf("Loading data 1...\n");
    for(int x=0; x<(arraySize/2); x++){
        fscanf(filePointer, "%lf %lf", &array->x, &array->y);
    }//end for
    fclose(filePointer);
    printf("Data 1 loaded\n");
    vars->array2 = array;
    vars->arraySize2 = arraySize;
}//end func
 
int mergeSort(int array[], int arraySize){
    //a function wrapper for merge sort
    int tempArray[arraySize];
    int totalInversion = recurseMergeSort(array, tempArray, 0, arraySize - 1);
    return totalInversion;
}//end func
 
int recurseMergeSort(int array[], int tempArray[], int left, int right){
    //a recursive functions that will return that inversion
    int middle = 0;
    int inversionCount = 0;
    //check if right is greater than left
    if (right > left){
        //have the array divide into two parts
        middle = (right + left)/2;

        //coutn the inversion and use recursion to merge array
        inversionCount  = recurseMergeSort(array, tempArray, left, middle);
        inversionCount = inversionCount + recurseMergeSort(array, tempArray, middle+1, right);

        //merge the to a tempArray which will sort it
        middle = middle + 1;
        int leftIndex = left; //left index for the left asub section
        int rightIndex = middle;  //right index for the right sub section
        int resultIndex = left; //the resulting merge index

        //loop through the array
        while ((leftIndex <= middle - 1) && (rightIndex <= right)){
            if (array[leftIndex] <= array[rightIndex]){
                tempArray[resultIndex] = array[leftIndex];
                //iterate the next index
                resultIndex = resultIndex + 1;
                leftIndex = leftIndex + 1;
            }else{
                tempArray[resultIndex] = array[rightIndex];
                //iterate the next index
                resultIndex = resultIndex + 1;
                rightIndex = rightIndex + 1;
                //count the inversion of the merge sort
                inversionCount = inversionCount + (middle - leftIndex);
            }//end if
        }//end while

        //copy the left section to the tempArray
        while (leftIndex <= middle - 1){
            //copy the element to temp array
            tempArray[resultIndex] = array[leftIndex];
            //iterate through the next index
            resultIndex = resultIndex + 1;
            leftIndex = leftIndex + 1;
        }//end while

        //copy the right section to the tempArray
        while (rightIndex <= right){
            //copy the element to temp array
            tempArray[resultIndex] = array[rightIndex];
            //iterate through the next index
            resultIndex = resultIndex + 1;
            rightIndex = rightIndex + 1;
        }//end while

        //once copied , moved the sorted section to the original array
        for (leftIndex=left; leftIndex <= right; leftIndex++){
            //copy the element from temp array to the original array
            array[leftIndex] = tempArray[leftIndex];
        }//end for

        //return the inversion count
        return inversionCount;
    }//end if
    return inversionCount;
}//end func

double whichSideOfLine(Points* point1, Points* point2, Points* pointSubject){
    return (pointSubject->x - point1->x) * (point2->y - point1->y) - (pointSubject->y - point1->y) * (point2->x - point1->x);
}//end func

int bruteForceConvexHull(double array2x[], double array2y[], int arraySize){
    for(int x=0; x<arraySize; x++){
        for(int y=0; y<arraySize; y++){
            //if their are the same points skip
            if(x == y){
                continue;
            }//end if
            
            
        }//end for
    }//endd for
}//end func

/***********************************************************
 * main function to run the program
 ***********************************************************/

int main(int argc, char** argv){
    //dec vars
    char* menu = calloc(256, sizeof(char)*256);
    Instance* vars = initInstance();

    //load the data again
    loadData1(vars);
    loadData2(vars);
    
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
            double start = 0, stop = 0, timeSpent = 0;
            int totalInversion = 0;
            printf("Calculating...\n");
            start = clock();
            totalInversion = countInversion(vars->array1, vars->arraySize1);
            stop = clock();
            timeSpent = (double)(stop - start)/CLOCKS_PER_SEC;
            printf("Total inversion: %d\n", totalInversion);
            printf("Total execution time: %f seconds\n", timeSpent);
        }else if(strcmp(menu, "2") == 0){
            //devide and conquer
            double start = 0, stop = 0, timeSpent = 0;
            int totalInversion = 0;
            printf("calculating...\n");
            start = clock();
            totalInversion = mergeSort(vars->array1, vars->arraySize1);
            stop = clock();
            timeSpent = (double)(stop - start)/CLOCKS_PER_SEC;
            printf("Total Inversion: %d\n", totalInversion);
            printf("Total execution time: %f seconds\n", timeSpent);
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
            free(vars->array1);
            free(vars);
            free(menu);
            exit(0);
        }else{
            printf("Invalid input, please re-enter.\n");
        }//end if

        //load the data again
        free(vars->array1);
        loadData1(vars);
        loadData2(vars);

        //for debugging
        // for(int x =0; x < 50000; x++){
        //     printf("%d\n", vars->array1[x]);
        // }//end if

    }//end while
    return 0;
}//end main