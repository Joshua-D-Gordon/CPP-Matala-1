#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_{
    PElement *arr;
    int arrSize;
    PElement (*COPY_FUNC)(PElement);
    void (*DEL_FUNC)(PElement);
    void (*PRINT_FUNC)(PElement);
}AdptArray, *PAdptArray;

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
void DeleteAdptArray(PAdptArray ptr){
    PElement *runner;
    runner = ptr->arr;
    for(int i = 0; i<ptr->arrSize; i++){
        if(runner[i]!=NULL){
            ptr->DEL_FUNC(runner[i]);
        }
    }
    free(ptr->arr);
    free(ptr);
    
}
Result SetAdptArrayAt(PAdptArray ptr, int index, PElement obj){
    if(index<ptr->arrSize){
        //free and insert;
        if(ptr->arr[index]==NULL){
            ptr->arr[index] = ptr->COPY_FUNC(obj);
            return SUCCESS;
        }else{
            ptr->DEL_FUNC(ptr->arr[index]);
            ptr->arr[index] = ptr->COPY_FUNC(obj);
            return SUCCESS;
        }
    }else{
        //make new arr big enough
        PElement *newArr = (PElement)malloc((index+1)*sizeof(PElement));
        if(newArr == NULL){
            return FAIL;
        }
        for(int i = 0; i<ptr->arrSize; i++){
            if(ptr->arr[i]!=NULL){
                newArr[i] = ptr->COPY_FUNC(ptr->arr[i]);
            }else{
                newArr[i] = NULL;
            }
        }
        for(int i = ptr->arrSize; i<index; i++){
            newArr[i] = NULL;
        }
        newArr[index] = ptr->COPY_FUNC(obj);
        
        PElement *runner;
        runner = ptr->arr;
        for(int i = 0; i<ptr->arrSize; i++){
            if(runner[i]!=NULL){
                ptr->DEL_FUNC(runner[i]);
            }
        }
        free(ptr->arr);

        ptr->arrSize = index+1;
        ptr->arr = newArr;

        return SUCCESS;
    }
}
PElement GetAdptArrayAt(PAdptArray ptr, int index){
    if(ptr->arr[index]!=NULL){
        PElement origi = ptr->arr[index];
        PElement cpy = ptr->COPY_FUNC(origi);
        return cpy;
    }else{
        return NULL;
    }
}
int GetAdptArraySize(PAdptArray ptr){
    return ptr->arrSize;
}
void PrintDB(PAdptArray ptr){
    for(int i = 0; i<ptr->arrSize; i++){
        if(ptr->arr[i]!=NULL){
            ptr->PRINT_FUNC(ptr->arr[i]);
        }
    }
}