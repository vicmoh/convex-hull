/***********************************
 * Name: Vicky Mohammad
 * Date: February 10, 2018
 ***********************************/

#ifndef FUNCTION_H
#define FUNCTION_H
/*import libraries*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
//macros
#define DEBUG false
#define debug if(DEBUG)printf
#define d debug("CHECK\n");
//struct points for array 2
typedef struct points{
    double x;
    double y;
    int size;
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
Points* initPoints();
char* userInput(char* input);
char* setString(char* string);
int countInversion(int array[], int arraySize);
//functions to load the data
void loadData1(Instance* vars);
void loadData2(Instance* vars);
//options for the menu
double option1(Instance* vars);
double option2(Instance* vars);
double option3(Instance* vars);
double option4(Instance* vars);
//for merge sort 
int mergeSort(int array[], int arraySize);
int recurseMergeSort(int array[], int tempArray[], int left, int right);
int merge(int array[], int tempArray[], int left, int middle, int right);
//brute force convex hull 
double getSideOfLine(Points* point1, Points* point2, Points* pointSubject);
int bruteForceConvexHull(Points* array, int arraySize);
//divide and conquer convex hull
void addPoints(Points* array, double x, double y);
int divideAndConquerConvexHull(Points* points, int arraySize);
void searchHull(Points* pointArray, Points* pointA, Points* pointB, Points* hullPoints);
#endif