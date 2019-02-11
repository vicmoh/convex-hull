/***********************************
 * Name: Vicky Mohammad
 * Date: February 10, 2018
 ***********************************/

//import library
#include "function.h"

/**
 * a function to get the value that passes through the points
 * @param point1
 * @param point2
 * @point pointSubject
 * @return the value of the points that passes through
 */
double getSideOfLine(Points* point1, Points* point2, Points* pointSubject){
    double num1 = (pointSubject->x - point1->x) * (point2->y - point1->y);
    double num2 = (pointSubject->y - point1->y) * (point2->x - point1->x);
    return num1 - num2;
}//end func

/**
 * function bruteforce using for loops to find convex hull points
 * @param array of points
 * @param arraySize of the points
 * @return the total number of hull points
 */
int bruteForceConvexHull(Points* array, int arraySize){
    //dec vars
    int section, pointCounter = 0;
    double lineValue = 0;
    debug("arraySize: %d\n", arraySize/2);
    //nested loop to find the next point
    for(int x=0; x<arraySize/2; x++){
        for(int y=0; y<arraySize/2; y++){
            //dec vars
            section = 0;
            //loop the last points
            for(int z=0; z<arraySize/2; z++){
                //assign the three points
                Points* point1 = &array[x];
                Points* point2 = &array[y];
                Points* point3 = &array[z];

                //checking the side of the line, if wrong section skip
                lineValue = getSideOfLine(point1, point2, point3);
                if(lineValue < 0){
                    //check if its the right section of checking points, if wrong skip
                    if(section > 0){
                        break;
                    }else{
                        section = -999;
                    }//end if
                }else if (lineValue > 0){
                    //check if its the right side of checking points, if wrong skip
                    if(section < 0){
                        break;
                    }else{
                        section = 999;
                    }//end if
                }else if (lineValue == 0){
                    //extreme
                    if( (point3->y > point2->y && point3->y > point1->y) || (point3->y < point2->y && point3->y < point1->y) || 
                        (point3->x < point2->x && point3->x > point1->x) || (point3->x > point2->x && point3->x > point1->x)){
                        break;
                    }//end if
                }//end if
                
                //if every point is good there is no wrong section
                if(z == (arraySize/2)-1 && section != 0 && x != y){
                    x = x + 1;
                    y = y + 1;
                    pointCounter++;
                    printf("Found Point: %.1f, %.1f\n", point1->x, point1->y);
                }//end if
            }//end for
        }//end for
    }//end for
    return pointCounter;
}//end func