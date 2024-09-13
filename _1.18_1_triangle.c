#include<stdio.h>
#include<assert.h>



int main(){
    int a,b,c;
    printf("input three numbers to form a triangle in the format: a b c\n");
    scanf("%d %d %d",&a,&b,&c);
    
    assert(a>0 && b>0 && c>0);
    assert(a<b+c && b<a+c && c<a+b);
    
    
}


