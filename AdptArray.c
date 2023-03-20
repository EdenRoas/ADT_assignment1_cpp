#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"
// typedef struct AdptArray_* PAdptArray;
// typedef enum  {FAIL = 0, SUCCESS=1} Result;
// typedef void* PElement;
// typedef void(*DEL_FUNC)(PElement);
// typedef PElement(*COPY_FUNC)(PElement);
// typedef void(*PRINT_FUNC)(PElement);

// creat the AdptArray and his constructor
struct AdptArray_
{
    PElement *elements;
    int Array_size;
    // The constructors
    COPY_FUNC copy_func;
    PRINT_FUNC print_func;
    DEL_FUNC del_func;
};

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func)
{
    PAdptArray adpt_Array = (PAdptArray)malloc(sizeof(struct AdptArray_)); // allocate memory for new adparray
    if (!adpt_Array)
        return NULL;
    else
    {
        adpt_Array->Array_size = 0;
        adpt_Array->elements = NULL;
        adpt_Array->copy_func = copy_func;
        adpt_Array->del_func = del_func;
        adpt_Array->print_func = print_func;
        return adpt_Array;
    }
}
void cleanArray(PAdptArray adpt_Array)
{
    for (int i = 0; i < adpt_Array->Array_size; i++)
        {
            if (adpt_Array->elements[i] != NULL)
            {
                adpt_Array->del_func(adpt_Array->elements[i]);
                adpt_Array->elements[i] = NULL;
            }
        }

}

void DeleteAdptArray(PAdptArray adpt_Array)
{ 
    if (adpt_Array != NULL)
    // if the array is not null we used the del_func and delete all the array cell by cell
    {
        cleanArray(adpt_Array);
        free(adpt_Array->elements);// free the memory we used for the elements
    }
    else
        return;
    free(adpt_Array); // free the memeory thet used by the adpt_Array
}


Result SetAdptArrayAt(PAdptArray adpt_Array, int index, PElement element)
{ // check the index's edge cases 
    if (index < 0)
        return FAIL;

    if (index > adpt_Array->Array_size)
    {   // if the index bigger the array size we copy the array by realloc to new array,his size will be index+1
        PElement *new_adpt_Array = (PElement *)realloc(adpt_Array->elements, (index + 1) * (sizeof(PElement)));
        if (new_adpt_Array == NULL)
            return FAIL;
        for (int i = adpt_Array->Array_size; i < index + 1; i++)
        { //make null all the new cells
            new_adpt_Array[i] = NULL;
        }
        adpt_Array->Array_size = (index + 1);
        adpt_Array->elements = new_adpt_Array;
    }
    if (adpt_Array->elements[index] != NULL)
    { // if not empty - delete it and copy the new element we got
        adpt_Array->del_func(adpt_Array->elements[index]);
    }
    adpt_Array->elements[index] = adpt_Array->copy_func(element);
    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray adpt_Array, int index)
{
    // first of all, check the edge cases of the index
    if (adpt_Array == NULL || index < 0 || index > adpt_Array->Array_size)
        return FAIL;
    if (adpt_Array->elements[index] != NULL)
    // if the array[index] is not empty we call the copy_func constructor
        return adpt_Array->copy_func(adpt_Array->elements[index]);
    else
        return NULL;
}
int GetAdptArraySize(PAdptArray adpt_Array)
{
    if (adpt_Array != NULL) // if the array is not empty call the consractor that return the size
        return adpt_Array->Array_size;
    else
        return -1; // if the array empty retryn -1
}
void PrintDB(PAdptArray adpt_Array)
{
    for (int i = 0; i < adpt_Array->Array_size; i++)
    {
        if (adpt_Array->elements[i] != NULL)
        {// the same like the func above but herer we call print_func cons
            adpt_Array->print_func(adpt_Array->elements[i]);
        }
        else
            continue;
    }
}