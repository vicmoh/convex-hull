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

typedef struct instanceVars{
    char fileName[99];
    int* array1;
    double* array2;
    int arraySize1;
    int arraySize2;
}Instance;

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
    //dec vars
    const int arraySize = 50000;
    double* array = malloc(sizeof(double)*arraySize);
    FILE* filePointer = fopen("./assets/data_1_a2.txt", "r");
    //loop until the end of file
    printf("Loading data 1...\n");
    for(int x=0; x<arraySize; x++){
        fscanf(filePointer, "%lf", &array[x]);
    }//end for
    fclose(filePointer);
    printf("Data 1 loaded\n");
    vars->array2 = array;
    vars->arraySize2 = arraySize;
}//end func

/*
int merge(int array[], int tempArray[], int left, int middle, int right){
    //dec a tempArray vars
    int inversionCount = 0;
    int rightIndex = left;
    int leftIndex = left;//for teh left and right array index section
    int middleIndex = middle;//for the right array index section 
    //combined the two sections
    while ((leftIndex <= middle - 1) && (middleIndex <= right)){
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
            inversionCount += (middle - leftIndex);
        }//end if
    }//end while

    //copy the left section of the remaining element of the arrayay
    while(leftIndex <= middle - 1){
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

    //copy to the originated array
    for(leftIndex=left; leftIndex <= right; leftIndex++){
        array[leftIndex] = tempArray[leftIndex];
    }//end for

    //return the inversion count
    //free(tempArray);
    return inversionCount;
}//end func

int recurseMergeSort(int array[], int tempArray[], int left, int right){
    //a recursion function that sorts using merge sort
    int middle = 0;
    int inversionCount = 0;
    if(right > left){
        //divide the array into 2
        middle = (left + right)/2;
        //sum the inversion for left and right sections
        inversionCount = recurseMergeSort(array, tempArray, left, middle);
        inversionCount = inversionCount + recurseMergeSort(array, tempArray, middle+1, right);
        inversionCount = inversionCount + merge(array, tempArray, left, middle+1, right);
    }//end if
    return inversionCount;
}//end func

int mergeSort(int array[], int arraySize){
    //this function sort the input using divide conquer
    int* tempArray = malloc(sizeof(int)*arraySize);
    //int tempArray[arraySize];
    return recurseMergeSort(array, tempArray, 0, arraySize - 1);
}//end func*/

int  _mergeSort(int arr[], int temp[], int left, int right);
int merge(int arr[], int temp[], int left, int mid, int right);
 
/* This function sorts the input array and returns the
   number of inversions in the array */
int mergeSort(int arr[], int array_size)
{
    int *temp = (int *)malloc(sizeof(int)*array_size);
    return _mergeSort(arr, temp, 0, array_size - 1);
}
 
/* An auxiliary recursive function that sorts the input array and
  returns the number of inversions in the array. */
int _mergeSort(int arr[], int temp[], int left, int right)
{
  int mid, inv_count = 0;
  if (right > left)
  {
    /* Divide the array into two parts and call _mergeSortAndCountInv()
       for each of the parts */
    mid = (right + left)/2;
 
    /* Inversion count will be sum of inversions in left-part, right-part
      and number of inversions in merging */
    inv_count  = _mergeSort(arr, temp, left, mid);
    inv_count += _mergeSort(arr, temp, mid+1, right);
 
    /*Merge the two parts*/
    inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}
 
/* This funt merges two sorted arrays and returns inversion count in
   the arrays.*/
int merge(int arr[], int temp[], int left, int mid, int right)
{
  int i, j, k;
  int inv_count = 0;
 
  i = left; /* i is index for left subarray*/
  j = mid;  /* j is index for right subarray*/
  k = left; /* k is index for resultant merged subarray*/
  while ((i <= mid - 1) && (j <= right))
  {
    if (arr[i] <= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];
 
     /*this is tricky -- see above explanation/diagram for merge()*/
      inv_count = inv_count + (mid - i);
    }
  }
 
  /* Copy the remaining elements of left subarray
   (if there are any) to temp*/
  while (i <= mid - 1)
    temp[k++] = arr[i++];
 
  /* Copy the remaining elements of right subarray
   (if there are any) to temp*/
  while (j <= right)
    temp[k++] = arr[j++];
 
  /*Copy back the merged elements to original array*/
  for (i=left; i <= right; i++)
    arr[i] = temp[i];
 
  return inv_count;
}

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
            vars = initInstance();
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
            free(vars);
            free(vars->array1);
            free(vars->array2);
            free(menu);
            exit(0);
        }else{
            printf("Invalid input, please re-enter.\n");
        }//end if

        //load the data again
        loadData1(vars);
        loadData2(vars);

        // for(int x =0; x < 50000; x++){
        //     printf("%d\n", vars->array1[x]);
        // }//end if
    }//end while
}//end main