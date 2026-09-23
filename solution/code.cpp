#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX_SIZE 100

int arr[MAX_SIZE];


void coctail_sort(int* array, int _size){
    int left = 0;
    int right = _size - 1;
    int swapped = 1;
    while((left < right) && (swapped == 1)){
        swapped = 0;
        for(int i = left; i < right; ++i){
            if(array[i] > array[i+1]){
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                swapped = 1;
            }
        }
        --right;
        if(swapped == 0) break;
        for(int j = right; j > left; --j){
            if(array[j] < array[j-1]){
                int temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
                swapped = 1;
           }
        }
        ++left;
    }
}

int main(){
    int _size = 0;
    scanf("%d", &_size);
    if(_size < 0){
        _size = 0;
    }
    if(_size > MAX_SIZE){
        _size = MAX_SIZE;
    }
    for(int i = 0; i < _size; ++i){
        scanf("%d", &arr[i]);
    }
    coctail_sort(arr, _size);
    for(int i = 0; i < _size; ++i){
        printf("%d ", arr[i]);
    }
    return 0;
}