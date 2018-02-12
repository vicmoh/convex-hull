/***********************************
 * Name: Vicky Mohammad
 * ID: 0895381
 * Date: February 10, 2018
 ***********************************/

//import library
#include "function.h"

/**
 * a functions that counts the inversion of an array
 * @param array to be counted
 * @param arraySize of the array to be counted
 * @return the total inversion count
 */
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