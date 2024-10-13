#include<stdio.h>
#define HEIGHT 17
int main(void)
{
int i = 0;
int j=0;
int dist;
int dist0=0.15*(17/2)*(17/2);

for (j=0;j<dist0+2;j++){
	printf(" ");
}

printf("CCCCCCCCCCCCC\n");
while(i < HEIGHT){

dist=0.15*(i-17/2)*(i-17/2);
for (j=0;j<dist;j++){
	printf(" ");
}

printf("CCC\n");
i = i + 1;

}

for (j=0;j<dist0+2;j++){
	printf(" ");
}
printf("CCCCCCCCCCCCC\n");
return 0;
}
