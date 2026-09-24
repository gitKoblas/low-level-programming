#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX_SIZE 100

int arr[MAX_SIZE];


void coctail_sort(int* array, int _size) {
    int left = 0;
    int right = _size - 1;
    int swapped = 1;
    int i = 0;
    int j = 0;
    int temp = 0;
start_cycle:
    if (!(left < right)) goto stop_sorting;
    if (!(swapped == 1)) goto stop_sorting;
    swapped = 0;
    i = left;
first_circle:
    if (!(i < right)) goto end_first_circle;
    if (!(array[i] > array[i + 1])) goto skip_switching1;
    temp = array[i];
    array[i] = array[i + 1];
    array[i + 1] = temp;
    swapped = 1;
skip_switching1:
    ++i;
    goto first_circle;
end_first_circle:
    --right;
    if (swapped == 0) goto stop_sorting;
    j = right;
second_circle:
    if (!(j > left)) goto end_second_circle;
    if (!(array[j] < array[j - 1])) goto skip_switching2;
    temp = array[j];
    array[j] = array[j - 1];
    array[j - 1] = temp;
    swapped = 1; 
skip_switching2:
    --j;
    goto second_circle;
end_second_circle:
    ++left;
    if (swapped == 1) goto start_cycle;
stop_sorting:
    return;
}

int main(){
    int _size = 0;
    scanf("%d", &_size);
    if(!(_size < 0)) goto skip_size_check;
    _size = 0;
skip_size_check:
    if(!(_size > MAX_SIZE)) goto skip_max_check;
    _size = MAX_SIZE;
skip_max_check:
int i = 0;
if(_size == 0) goto stop_printing;
writing:
    if(!(i < _size)) goto skip_writing;
    scanf("%d", &arr[i]);
    ++i;
    goto writing;
skip_writing:
    coctail_sort(arr, _size);
i=0;
printing:
    if(!(i < _size)) goto stop_printing;
    printf("%d ", arr[i]);
    ++i;
    goto printing;
stop_printing:
    return 0;
}