#include<stdio.h>

int main(){
    int x;
    int* p=&x;
    printf("%p\n",p);
    printf("input a integer\n");
    scanf("%d",&x);
    printf("%p",p);
    
    return 0;
}
