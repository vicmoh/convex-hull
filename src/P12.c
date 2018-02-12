/***********************************
 * Name: Vicky Mohammad
 * ID: 0895381
 * Date: February 10, 2018
 ***********************************/

//import library
#include "function.h"

/**
 * a wrapper funtion that will use call a recursive
 * function that will count the inversion and sort using mergsort
 * @param array to be sorted and counted
 * @param arraySize of the array to be counted
 * @return an int that total inversion size 
 */
int mergeSort(int array[], int arraySize){
    //a function wrapper for merge sort
    int tempArray[arraySize];
    int totalInversion = recurseMergeSort(array, tempArray, 0, arraySize - 1);
    return totalInversion;
}//end func
 
/**
 * a recurse merge sort that will sort the array and count the inversion
 * @param array to be sorted and counted
 * @param tempArray for the array to be sorted and copied back to the original array
 * @param left sub section of the array index
 * @param right sub section of the array index
 * @return int of the total inversion count
 */
int recurseMergeSort(int array[], int tempArray[], int left, int right){
    //a recursive functions that will return that inversion
    int middle = 0;
    int inversionCount = 0;
    int leftIndex, rightIndex, resultIndex;
    //check if right is greater than left
    if (right > left){
        //have the array divide into two parts
        middle = (right + left)/2;

        //count the inversion and use recursion to merge array
        inversionCount  = recurseMergeSort(array, tempArray, left, middle);
        inversionCount = inversionCount + recurseMergeSort(array, tempArray, middle+1, right);

        //merge the to a tempArray which will sort it
        middle = middle + 1;//next middle
        leftIndex = left; //left index for the left sub section
        rightIndex = middle;  //right index for the right sub section
        resultIndex = left; //the resulting merge index

        //loop through the array
        while ((leftIndex <= middle-1) && (rightIndex <= right)){
            if(array[leftIndex] > array[rightIndex]){
                tempArray[resultIndex] = array[rightIndex];
                //iterate the next index
                resultIndex = resultIndex + 1;
                rightIndex = rightIndex + 1;
                //count the inversion of the merge sort
                inversionCount = inversionCount + (middle - leftIndex);
            }else{
                tempArray[resultIndex] = array[leftIndex];
                //iterate the next index
                resultIndex = resultIndex + 1;
                leftIndex = leftIndex + 1;
            }//end if
        }//end while

        //copy the right section to the tempArray
        while (rightIndex <= right){
            //copy the element to temp array
            tempArray[resultIndex] = array[rightIndex];
            //iterate through the next index
            resultIndex = resultIndex + 1;
            rightIndex = rightIndex + 1;
        }//end while

        //copy the left section to the tempArray
        while (leftIndex <= middle-1){
            //copy the element to temp array
            tempArray[resultIndex] = array[leftIndex];
            //iterate through the next index
            resultIndex = resultIndex + 1;
            leftIndex = leftIndex + 1;
        }//end while

        //once copied , moved the sorted section to the original array
        for (leftIndex=left; leftIndex<=right; leftIndex++){
            //copy the element from temp array to the original array
            array[leftIndex] = tempArray[leftIndex];
        }//end for

        //return the inversion count
        return inversionCount;
    }//end if
    return inversionCount;
}//end func