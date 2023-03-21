#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

// Struct of adptArray
// Includes PElement (void) pointer to array, array size (int), 2 void functions (delete & print), 1 Pelement function (copy)
typedef struct AdptArray_{
    PElement *arr;
    int arrSize;
    PElement (*COPY_FUNC)(PElement);
    void (*DEL_FUNC)(PElement);
    void (*PRINT_FUNC)(PElement);
}AdptArray, *PAdptArray;

//Create adptArray function:
//recives the 3 functions (copy, delete, print).
//creates a new struct of AdptArray (tries to allocate space if not returns null).
//assigns memebr arrsize to 0, arr to NULL, each function to its coresponding funciton recived.
//returns a pointer to the Adptarray struct
PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf){
    PAdptArray adparr = (PAdptArray)malloc(sizeof(AdptArray));
    if(adparr == NULL){
        return NULL;
    }
    adparr->arrSize = 0;
    adparr->arr = NULL;
    adparr->COPY_FUNC = cf;
    adparr->DEL_FUNC = df;
    adparr->PRINT_FUNC = pf;

    return adparr;
}

//delete adpt array
//uses a temp pointer for "running through" array values, then uses the delete funciton to delete items in array
// the delete function also frees the memroy. then free the array and then free the struct itself
void DeleteAdptArray(PAdptArray ptr){
    PElement *runner;
    runner = ptr->arr;
    //running through array items
    for(int i = 0; i<ptr->arrSize; i++){
        if(runner[i]!=NULL){
            //deleting each item
            ptr->DEL_FUNC(runner[i]);
        }
    }
    //freeing array
    free(ptr->arr);
    //freeing struct
    free(ptr);
    
}

//set AdptArray function:
//if index is in range of arrays size: if index is occupied then delets element with del function
//then copies new element to that index, else if index is NULL (NOT OCCUPIED) just copies new element to that index.
//if array size not big enough, makes new array big enough, copies items with copy function, frees old array, inserts Null to index's not occupied , frees old array
//and sets new array as the array
//returns Success or fail if operation was successfull or failed
Result SetAdptArrayAt(PAdptArray ptr, int index, PElement obj){
    if(index<ptr->arrSize){
        //inserts new item at index via copy funciton;
        if(ptr->arr[index]==NULL){
            ptr->arr[index] = ptr->COPY_FUNC(obj);
            return SUCCESS;
        //deletes item via del function at current index, then inserts new item at index via copy function
        }else{
            ptr->DEL_FUNC(ptr->arr[index]);
            ptr->arr[index] = ptr->COPY_FUNC(obj);
            return SUCCESS;
        }
    }else{
        //make new arr big enough
        PElement *newArr = (PElement)malloc((index+1)*sizeof(PElement));
        //if new array not made returns fail
        if(newArr == NULL){
            return FAIL;
        }
        //copies old array to new array
        for(int i = 0; i<ptr->arrSize; i++){
            if(ptr->arr[i]!=NULL){
                newArr[i] = ptr->COPY_FUNC(ptr->arr[i]);
            }else{
                newArr[i] = NULL;
            }
        }
        //makes gap between size of old array and new array all null
        for(int i = ptr->arrSize; i<index; i++){
            newArr[i] = NULL;
        }
        //inserts new item at new array index (now big enough)
        newArr[index] = ptr->COPY_FUNC(obj);
        //delets old array elements
        PElement *runner;
        runner = ptr->arr;
        for(int i = 0; i<ptr->arrSize; i++){
            if(runner[i]!=NULL){
                ptr->DEL_FUNC(runner[i]);
            }
        }
        //frees old array
        free(ptr->arr);
        //assigns new size for adptArray
        ptr->arrSize = index+1;
        //sets new array as array
        ptr->arr = newArr;

        return SUCCESS;
    }
}

//Get AdptArray at:
//returns a copy of the item at index in Array
PElement GetAdptArrayAt(PAdptArray ptr, int index){
    if(ptr->arr[index]!=NULL){
        //original item
        PElement origi = ptr->arr[index];
        //copy of item
        PElement cpy = ptr->COPY_FUNC(origi);
        //returns copy
        return cpy;
    }else{
        //no item at index returns Null
        return NULL;
    }
}

//Returns array size
int GetAdptArraySize(PAdptArray ptr){
    return ptr->arrSize;
}

//Prints Array via print function
void PrintDB(PAdptArray ptr){
    //runs through array
    for(int i = 0; i<ptr->arrSize; i++){
        //if not null
        if(ptr->arr[i]!=NULL){
            //print via print function
            ptr->PRINT_FUNC(ptr->arr[i]);
        }
    }
}