/***********************************
 * Name: Vicky Mohammad
 * Date: February 10, 2018
 ***********************************/

//import library
#include "function.h"

/***********************************************************
 * helper Functions
 ***********************************************************/

Instance* initInstance(){
    Instance* newVars = calloc(1, sizeof(Instance));
    newVars->array1 = NULL;
    newVars->array2 = NULL;
    newVars->arraySize1 = 0;
    newVars->arraySize2 = 0;
    return newVars;
}//end constructor

Points* initPoints(){
    Points* newPoint = malloc(sizeof(Points)*60000);
    newPoint->x = -1;
    newPoint->y = -1;
    newPoint->size = 0;
    return newPoint;
}//end constructor

void addPoints(Points* array, double x, double y){
    int arraySize = array[0].size;
    //array = realloc(array, sizeof(Points)*(arraySize+9));
    array[arraySize].x = x;
    array[arraySize].y = y;
    array[0].size++;
    //debug("arraySize: %d\n",arraySize);
    //debug("debug addPoints: %lf, %lf\n", array[arraySize].x, array[arraySize].y);
}//end func

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

/***********************************************************
 * option for the menu
 ***********************************************************/

double option1(Instance* vars){
    //brute force
    double start = 0, stop = 0, timeSpent = 0;
    int totalInversion = 0;
    printf("Calculating...\n");
    start = clock();
    totalInversion = countInversion(vars[0].array1, vars->arraySize1);
    stop = clock();
    timeSpent = (double)(stop - start)/CLOCKS_PER_SEC;
    printf("----------<<<< RESULT >>>>----------\n");
    printf("Total inversion: %d\n", totalInversion);
    printf("Total execution time: %f second\n", timeSpent);
    printf("------------------------------------\n");
    return timeSpent;
}//end func

double option2(Instance* vars){
    //brute forces convex hull
    double start = 0, stop = 0, timeSpent = 0;
    int totalInversion = 0;
    printf("calculating...\n");
    start = clock();
    totalInversion = mergeSort(vars->array1, vars->arraySize1);
    stop = clock();
    timeSpent = (double)(stop - start)/CLOCKS_PER_SEC;
    printf("----------<<<< RESULT >>>>----------\n");
    printf("Total number of points: %d\n", totalInversion);
    printf("Total execution time: %f second\n", timeSpent);
    printf("------------------------------------\n");
    return timeSpent;
}//end func

double option3(Instance* vars){
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
    printf("Total execution time: %f second\n", timeSpent);
    printf("------------------------------------\n");
    return timeSpent;
}//end func

double option4(Instance* vars){
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
    printf("Total execution time: %f second\n", timeSpent);
    printf("------------------------------------\n");
    return timeSpent;
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
        printf("6: compare execution times of 3 and 4\n");
        printf("7: Exit\n");
        printf("Enter the menu:\n");
        menu = userInput(menu);

        if(strcmp(menu, "1") == 0){
            option1(vars);
        }else if(strcmp(menu, "2") == 0){
            option2(vars);
        }else if(strcmp(menu, "3") == 0){
            option3(vars);
        }else if(strcmp(menu, "4") == 0){
            option4(vars);
        }else if(strcmp(menu, "5") == 0){
            double time1 = option1(vars);
            double time2 = option2(vars);
            printf("----------<<<< FEEDBACK >>>>----------\n");
            printf("Difference between the two time: %lf second\n", time1 - time2);
            printf("------------------------------------\n");
        }else if(strcmp(menu, "6") == 0){
            double time1 = option3(vars);
            double time2 = option4(vars);
            printf("----------<<<< FEEDBACK >>>>----------\n");
            printf("Difference between the two time: %lf second\n", time1 - time2);
            printf("------------------------------------\n");
        }else if(strcmp(menu, "7") == 0){
            //exit
            free(vars->array1);
            free(vars->array2);
            free(vars);
            free(menu);
            exit(0);
        }else{
            printf("----------<<<< FEEDBACK >>>>----------\n");
            printf("Invalid input, please re-enter.\n");
            printf("------------------------------------\n");
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