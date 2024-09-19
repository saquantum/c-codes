#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

typedef enum bool{False,True}bool;

void shuffle(int n, int arr[]);
void printarray(int length,int arr[]);

int main(){

    int* p = (int*)malloc(sizeof(int));
    int length=0;
    int validInput = False; 
    while (!validInput) {
        printf("Enter a number: ");
        if (scanf("%d", &length) == 1 && length>=0) {
            *p = length; 
            validInput = True; 
        } else {
            printf("Wrong input, try again\n");
            /* This method, using getchar to clear buffer of scanf, comes from
               https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
                */
            while (getchar() != '\n'); // Clear the buffer
        }
    }
    
    int arr[length];
    
    shuffle(length,arr);
    
    printarray(length,arr);
    
    return 0;
}

void shuffle(int length, int arr[]){  
    // initialise array  
    for (int i=0;i<length;i++){
        arr[i]=i+1;
    }
    // randomise array
    srand(time(NULL));
    int index=0;
    int temp=0;
    for (int i=0;i<length;i++){
        index=rand()%length;
        temp=arr[i];
        arr[i]=arr[index];
        arr[index]=temp;
    }
}

void printarray(int length,int arr[]){
    for (int i=0;i<length;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
