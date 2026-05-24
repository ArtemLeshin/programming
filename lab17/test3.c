#include <stdio.h>
#include <assert.h>
void shellSort(int array[], int len);
int main(){
    int arr1[]={10,2,6,1,24};
    shellSort(arr1,5);
    assert(arr1[0]==1 && arr1[1]==2 && arr1[2]==6 && arr1[3]==10 && arr1[4]==24);
    printf("на случайном все хорошо\n");

    int arr2[]={10,8,7,5,4};
    shellSort(arr2,5);
    assert(arr2[4]==10 && arr2[3]==8 && arr2[2]==7 && arr2[1]==5 && arr2[0]==4);
    printf("на убывающем все хорошо\n");

    int arr3[]={1,2,3,7,24};
    shellSort(arr3,5);
    assert(arr3[0]==1 && arr3[1]==2 && arr3[2]==3 && arr3[3]==7 && arr3[4]==24);
    printf("на возрастающем все хорошо\n");

    int arr4[]={2,2,2,2,2};
    shellSort(arr4,5);
    assert(arr4[0]==2 && arr4[1]==2 && arr4[2]==2 && arr4[3]==2 && arr4[4]==2);
    printf("на одинаковом все хорошо\n");

    int arr5[] = {};
    shellSort(arr5, 0); 
    printf("на пустом все хорошо\n");

    int arr6[]={10,2,4,2,1};
    shellSort(arr6,5);
    assert(arr6[0]==1 && arr6[1]==2 && arr6[2]==2 && arr6[3]==4 && arr6[4]==10);
    printf("с дубликатами все хорошо\n");
}