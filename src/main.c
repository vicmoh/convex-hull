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
#include <limits.h>
#include <assert.h>
//macros
#define DEBUG true
#define debug if(DEBUG)printf
#define d debug("CHECK\n");
#define GET_ARRAY_SIZE( array ) ( sizeof( array ) / sizeof( *array )) //or array[0] instead of *array

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
//brute force convex hull 
double whichSideOfLine(Points* point1, Points* point2, Points* pointSubject);
int bruteForceConvexHull(Points* array, int arraySize);
//divide and conquer convex hull
void addPoints(Points* array, double x, double y);
int divideAndConquerConvexHull(Points* points, int arraySize);
void findHull(Points* pointArray, Points* p, Points* q, Points* hullPoints);

/***********************************************************
 * Functions
 ***********************************************************/

Instance* initInstance(){
    Instance* newVars = calloc(1, sizeof(Instance));
    newVars->array1 = NULL;
    newVars->array2 = NULL;
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
    FILE* filePointer = fopen("./assets/data1.txt", "r");
    //loop until the end of file
    debug("Loading data 1...\n");
    for(int x=0; x<arraySize; x++){
        fscanf(filePointer, "%d", &array[x]);
    }//end for
    fclose(filePointer);
    debug("Data 1 loaded\n");
    vars->array1 = array;
    vars->arraySize1 = arraySize;
}//end func

void loadData2(Instance* vars){
    //count the size of the file
    FILE* filePointerSize = fopen("./assets/data2.txt", "r");
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
    FILE* filePointer = fopen("./assets/data2.txt", "r");
    debug("Loading data 2...\n");
    for(int x=0; x<(arraySize/2); x++){
        fscanf(filePointer, "%lf %lf", &array[x].x, &array[x].y);
        //debug("%lf %lf\n", array[x].x, array[x].y);
    }//end for
    fclose(filePointer);
    debug("Data 2 loaded\n");
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

int bruteForceConvexHull(Points* array, int arraySize){
    //dec vars
    int numberOfPoints = 0;
    debug("arraySize: %d\n", arraySize/2);
    //nested loop to find the next point
    for(int x=0; x<arraySize/2; x++){
        for(int y=0; y<arraySize/2; y++){
            //dec vars
            int side = 0;
            //loop the last points
            for(int k=0; k<arraySize/2; k++){
                //assign the three points
                Points* point1 = &array[x];
                Points* point2 = &array[y];
                Points* point3 = &array[k];

                double lineValue = whichSideOfLine(point1, point2, &array[k]);

                if (lineValue > 0) {
                    //check if its the right side of checking points, if wrong skip
                    if (side == -1) {
                        break;
                    }//end if
                    side = 1;
                }//endd if

                if (lineValue < 0) {
                    //check if its the right side of checking points, if wrong skip
                    if (side == 1) {
                        break;
                    }//end if
                    side = -1;
                }//end if

                //checking extreme
                if (lineValue == 0) {
                    if ((point3->x > point2->x && point3->x > point1->x) || (point3->x < point2->x && point3->x > point1->x) || 
                        (point3->y < point2->y && point3->y < point1->y) || (point3->y > point2->y && point3->y > point1->y)){
                        break;
                    }//end if
                }//end if
                
                //when every point is successful
                if (k == (arraySize/2)-1) {
                    if (side != 0) {
                        if (x != y) {
                            numberOfPoints++;
                            printf("Found Point: %.1f, %.1f\n", point1->x, point1->y);
                            x = x + 1;
                            y = y + 1;
                        }//end if
                    }//end if
                }//end if
            }//end for
        }//end for
    }//end for
    return numberOfPoints;
}//end func

void addPoints(Points* array, double x, double y){
    int arraySize = GET_ARRAY_SIZE(array);
    array = realloc(array, sizeof(Points)*(arraySize+1));
    array[arraySize].x = x;
    array[arraySize].y = y;
    debug("debug addPoints: %lf, %lf\n", array[arraySize].x, array[arraySize].y);
}//end func

int divideAndConquerConvexHull(Points* points, int arraySize){
    //dec vars
    int numberOfPoints = 0;
    //going to be a array
    Points* hullPoints = malloc(sizeof(Points));
    Points* leftPoints = malloc(sizeof(Points));
    Points* rightPoints = malloc(sizeof(Points));
    //need only one
    Points* mostLeft = malloc(sizeof(Points));
    Points* mostRight = malloc(sizeof(Points));
    //init the most left and right to 0
    mostLeft->x = 0;
    mostLeft->y = 0;
    mostRight->x = 0;
    mostRight->y = 0;
    mostLeft->x = points[0].x;
    mostRight->x = points[0].x;

    //find the most right and left of the points
    for(int x=0; x<(arraySize/2); x++){
        if(points[x].x < mostLeft->x){
            mostLeft->x = points[x].x;
            mostLeft->y = points[x].y;
        }//end if
        if(points[x].x > mostRight->x){
            mostRight->x = points[x].x;
            mostRight->y = points[x].y;
        }//end if
    }//end for

    //copy into the left and right sections
    for(int x=0; x<(arraySize/2); x++){
        double lineValue = whichSideOfLine(mostLeft, mostRight, points);//not sure if im doing it 
        //add to left
        if(lineValue + 0.00000001 < 0){
            addPoints(leftPoints, points[x].x, points[x].y);
        }//end if
        if(lineValue - 0.00000001 > 0){
            addPoints(rightPoints, points[x].x, points[x].y);
        }//end if
    }//end for

    //add and recurse
    addPoints(hullPoints, mostLeft->x, mostLeft->y);
    addPoints(hullPoints, mostRight->x, mostRight->y);
    findHull(leftPoints, mostLeft, mostRight, hullPoints);
    findHull(rightPoints, mostRight, mostLeft, hullPoints);

    //count the number of points of the convex hull
    for(int x=0; x<GET_ARRAY_SIZE(hullPoints);x++){
        debug("WENT TO NUMBER OF POINTS FOR LOOP\n");
        numberOfPoints++;
    }//end for

    //free and return the number of points
    free(hullPoints);
    free(leftPoints);
    free(rightPoints);
    return numberOfPoints;
}//end func

void findHull(Points* pointArray, Points* p, Points* q, Points* hullPoints){
    //dec vars
    Points* farthest = malloc(sizeof(Points));
    Points* upper = malloc(sizeof(Points));
    Points* lower = malloc(sizeof(Points));
    int maxHeight = 0;
    if(GET_ARRAY_SIZE(pointArray) == 0){
        return;
    }//end if
    
    double distance = sqrt((q->x - p->x) * (q->x - p->x) + (q->y - p->y) * (q->y - p->y));
    //saerch for the point that extreme from the segment line
    for(int x=0; x<GET_ARRAY_SIZE(pointArray);x++){
        double absolute = fabs(p->x * q->y + pointArray[x].x * p->y + q->x * pointArray[x].y - pointArray[x].x * q->y - q->x * p->y - p->x * pointArray[x].y);
        double height = absolute / distance;
        if(height > maxHeight){
            maxHeight = height;
            farthest->x = pointArray[x].x;
            farthest->y = pointArray[x].y;
        }//end if
    }//end for
    
    //append convex hull with the point that is the farthest
    addPoints(hullPoints, farthest->x, farthest->y);
    double a, b, c, lineValue;
    for(int x=0; x<GET_ARRAY_SIZE(pointArray);x++){
        a = ((q->y - farthest->y) * (pointArray[x].x - farthest->x) + (farthest->x - q->x) * (pointArray[x].y - farthest->y)) /
            ((q->y - farthest->y) * (p->x - farthest->x) + (farthest->x - q->x) * (p->y - farthest->y));
        b = ((farthest->y - p->y) * (pointArray[x].x - farthest->x) + (p->x - farthest->x) * (pointArray[x].y - farthest->y)) /
            ((q->y - farthest->y) * (p->x - farthest->x) + (farthest->x - q->x) * (p->y - farthest->y));
        c = 1.0f - a - b;
        
        //check if it is outside of the triangle
        if(!(a + 0.00001 > 0 && b + 0.00001 > 0 && c + 0.00001 > 0)){
            lineValue = whichSideOfLine(p, &pointArray[x], farthest);
            if (lineValue - 0.0000001 > 0) {
                addPoints(upper, pointArray[x].x, pointArray[x].y);
            }//end if
            if (lineValue + 0.0000001 < 0) {
                addPoints(lower, pointArray[x].x, pointArray[x].y);
            }//end if
        }//end if
    }//end for

    //recurse
    findHull(upper, p, farthest, hullPoints);
    findHull(lower, farthest, q, hullPoints);
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
            printf("----------<<<< RESULT >>>>----------\n");
            printf("Total inversion: %d\n", totalInversion);
            printf("Total execution time: %f seconds\n", timeSpent);
            printf("------------------------------------\n");
        }else if(strcmp(menu, "2") == 0){
            //devide and conquer
            double start = 0, stop = 0, timeSpent = 0;
            int totalInversion = 0;
            printf("calculating...\n");
            start = clock();
            totalInversion = mergeSort(vars->array1, vars->arraySize1);
            stop = clock();
            timeSpent = (double)(stop - start)/CLOCKS_PER_SEC;
            printf("----------<<<< RESULT >>>>----------\n");
            printf("Total Inversion: %d\n", totalInversion);
            printf("Total execution time: %f seconds\n", timeSpent);
            printf("------------------------------------\n");
        }else if(strcmp(menu, "3") == 0){
            //brute forces convex hull
            double start = 0, stop = 0, timeSpent = 0;
            int totalPoints = 0;
            printf("calculating...\n");
            start = clock();
            totalPoints = bruteForceConvexHull(vars->array2, vars->arraySize2);
            stop = clock();
            timeSpent = (double)(stop - start)/CLOCKS_PER_SEC;
            printf("----------<<<< RESULT >>>>----------\n");
            printf("Total number of points: %d\n", totalPoints);
            printf("Total execution time: %f seconds\n", timeSpent);
            printf("------------------------------------\n");
        }else if(strcmp(menu, "4") == 0){
            //divide and conquer convex hull
            double start = 0, stop = 0, timeSpent = 0;
            int totalPoints = 0;
            printf("calculating...\n");
            start = clock();
            totalPoints = divideAndConquerConvexHull(vars->array2, vars->arraySize2);
            stop = clock();
            timeSpent = (double)(stop - start)/CLOCKS_PER_SEC;
            printf("----------<<<< RESULT >>>>----------\n");
            printf("Total number of points: %d\n", totalPoints);
            printf("Total execution time: %f seconds\n", timeSpent);
            printf("------------------------------------\n");
        }else if(strcmp(menu, "5") == 0){
            //compare execution times of 1 and 2
        }else if(strcmp(menu, "4") == 0){
        }else if(strcmp(menu, "6") == 0){
            //compare execution times of 3 and 4
        }else if(strcmp(menu, "7") == 0){
            //exit
            free(vars->array1);
            free(vars->array2);
            free(vars);
            free(menu);
            exit(0);
        }else{
            printf("Invalid input, please re-enter.\n");
        }//end if

        //load the data again
        free(vars->array1);
        free(vars->array2);
        loadData1(vars);
        loadData2(vars);

        //for debugging
        // for(int x =0; x < 50000; x++){
        //     printf("%d\n", vars->array1[x]);
        // }//end if

    }//end while
    return 0;
}//end main