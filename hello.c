#include<stdio.h>
void bubbleSorting(int* arr,int len);
int compare(int num1,int num2);

int main(){
	int i=0;
	int arr[]={5,6,7,8,1,4,2,3,9,10};

	bubbleSorting(arr,sizeof(arr)/sizeof(int));
	for (i=0;i<sizeof(arr)/sizeof(int);i++){
		printf("%d ",*(arr+i));
	}
	return 0;
}
void bubbleSorting(int* arr,int len){
	int i,j,temp;
	for(i=0;i<len-1;i++){
		for(j=0;j<len-1-i;j++){
			if(compare(*(arr+j),*(arr+j+1))){
				temp=*(arr+j);
				*(arr+j)=*(arr+j+1);
				*(arr+j+1)=*(arr+j);
			}
		}
	}
}
int compare(int num1,int num2){
	return num1>num2;
}
