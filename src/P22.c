/***********************************
 * Name: Vicky Mohammad
 * Date: February 10, 2018
 ***********************************/

//import library
#include "function.h"

/**
 * a function that uses divide and conquer to find the convex hull points
 * @param points of an arrau of all points
 * @param arraySize of the points array
 * @return the total number of hull points
 */
int divideAndConquerConvexHull(Points* points, int arraySize){
    //dec vars
    int numberOfPoints = 0;
    //going to be a array
    Points* hullPoints = initPoints();
    Points* leftPoints = initPoints();
    Points* rightPoints = initPoints();
    //need only one
    Points* mostLeft = initPoints();
    Points* mostRight = initPoints();
    //init the most left and right to 0
    mostLeft[0].x = points[0].x;
    mostRight[0].x = points[0].x;

    //find the most right and left of the points
    for(int x=0; x<(arraySize/2); x++){
        if(points[x].x < mostLeft[0].x){
            mostLeft[0].x = points[x].x;
            mostLeft[0].y = points[x].y;
        }//end if
        if(points[x].x > mostRight[0].x){
            mostRight[0].x = points[x].x;
            mostRight[0].y = points[x].y;
        }//end if
    }//end for

    //copy into the left and right sections
    for(int x=0; x<(arraySize/2); x++){
        double lineValue = getSideOfLine(&mostLeft[0], &mostRight[0], &points[x]);//problem here, need to be fix
        //add to right
        if(lineValue-0.00000001 > 0){
            addPoints(rightPoints, points[x].x, points[x].y);
        }//end if
        //add to left
        if(lineValue+0.00000001 < 0){
            addPoints(leftPoints, points[x].x, points[x].y);
        }//end if
    }//end for

    //add and recurse
    addPoints(hullPoints, mostLeft[0].x, mostLeft[0].y);
    addPoints(hullPoints, mostRight[0].x, mostRight[0].y);
    searchHull(leftPoints, mostLeft, mostRight, hullPoints);
    searchHull(rightPoints, mostRight, mostLeft, hullPoints);

    //count the number of points of the convex hull
    for(int x=0; x<hullPoints[0].size; x++){
        printf("Found point: %.1lf, %.1lf\n", hullPoints[x].x, hullPoints[x].y);
        //debug("WENT TO NUMBER OF POINTS FOR LOOP\n");
        numberOfPoints++;
    }//end for

    //free and return the number of points
    return numberOfPoints;
}//end func

/**
 * a recursive function to find the hull points
 * @param pointArray of the existing points
 * @param pointA which is use for recursive finding for the hull points
 * @param pointB is the other point for the recursive finding of the hull points
 * @param Hullpoints of an array that will be stored when finding hull points
 */
void searchHull(Points* pointArray, Points* pointA, Points* pointB, Points* hullPoints){
    //dec vars and init points
    double a, b, c, lineValue, maxHeight = 0;
    Points* farthest = initPoints();
    Points* upper = initPoints();
    Points* lower = initPoints();
    //exit the recursion if the array is empty
    if(pointArray[0].size == 0){
        return;
    }//end if
    
    //get the distance
    double num1 = (pointB[0].x-pointA[0].x)*(pointB[0].x-pointA[0].x);
    double num2 = (pointB[0].y-pointA[0].y)*(pointB[0].y-pointA[0].y);
    double distance = sqrt( num1 + num2 );
    //search for the extreme point or vertex from the line segment
    for(int x=0; x<pointArray[0].size; x++){
        double total = pointA[0].x * pointB[0].y + pointArray[x].x * pointA[0].y + pointB[0].x * pointArray[x].y - 
                       pointArray[x].x * pointB[0].y - pointB[0].x * pointA[0].y - pointA[0].x * pointArray[x].y;
        double absolute = fabs(total);
        double currentHeight = absolute/distance;
        if(maxHeight < currentHeight){
            maxHeight = currentHeight;
            farthest[0].x = pointArray[x].x;
            farthest[0].y = pointArray[x].y;
        }//end if
    }//end for
    
    //append convex hull with the point that is the farthest
    addPoints(hullPoints, farthest[0].x, farthest[0].y);

    //use three points a b and c for the triangle
    for(int x=0; x<pointArray[0].size; x++){
        double valueA1 = (pointB[0].y-farthest[0].y) * (pointArray[x].x-farthest[0].x) + (farthest[0].x-pointB[0].x) * (pointArray[x].y-farthest[0].y);
        double valueA2 = (pointB[0].y-farthest[0].y) * (pointA[0].x-farthest[0].x) + (farthest[0].x-pointB[0].x) * (pointA[0].y-farthest[0].y);
        double valueB1 = (farthest[0].y-pointA[0].y) * (pointArray[x].x-farthest[0].x) + (pointA[0].x-farthest[0].x) * (pointArray[x].y-farthest[0].y);
        double valueB2 = (pointB[0].y-farthest[0].y) * (pointA[0].x-farthest[0].x) + (farthest[0].x-pointB[0].x) * (pointA[0].y-farthest[0].y);
        a = valueA1/valueA2;
        b = valueB1/valueB2;
        c = 1 - (a + b);
        
        //check if it is outside of the triangle
        if((a+0.00001 > 0 && b+0.00001 > 0 && c+0.00001 > 0) == false){
            lineValue = getSideOfLine(&pointA[0], &pointArray[x], &farthest[0]);
            if (lineValue+0.0000001 < 0) {
                addPoints(lower, pointArray[x].x, pointArray[x].y);
            }//end if
            if (lineValue-0.0000001 > 0) {
                addPoints(upper, pointArray[x].x, pointArray[x].y);
            }//end if
        }//end if
    }//end for

    //recursive call
    searchHull(upper, pointA, farthest, hullPoints);
    searchHull(lower, farthest, pointB, hullPoints);
}//end func