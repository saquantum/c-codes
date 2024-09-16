#include<stdio.h>
#include<math.h>

#define PHI 1.61803398875

typedef enum bool{False, True} bool;
bool fibword_phi(int n);

int main(){
    
    for(int i=1;i<100;i++){
        printf("%d",fibword_phi(i));
    }
    return 0;

}

bool fibword_phi(int n){
    int temp=2+floor(n*PHI)-floor((n+1)*PHI);
    return (bool)temp;
}
