#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

bool less(int a1, int a2);
void exchange(int* a, int i, int j);
void printarray(int* array, int length);
void copyarray(int* dest, int* src, int length);
void selectionSort(int* a, int length);
void insertionSort(int* a, int low, int high);
void shellSort(int* a, int length);
void mergeSort(int* a, int length);
void merge(int* a, int low, int high, int* aux, int length);
void mergeTwo(int* a, int low, int mid, int high, int* aux, int length);
void quickSort(int* a, int length);
void quick(int* a, int low, int high);
int partition(int* a, int low, int high);

int main() {
	srand(time(NULL));
	int length = 20;
	int* a = (int*)malloc(length*sizeof(int));
	assert(a);
	for (int i = 0; i < length; i++) {
		a[i] = rand() % length;
	}
	printarray(a, length);
	//selectionSort(a,length);
	//insertionSort(a,0, length-1);
	//shellSort(a,length);
	//mergeSort(a, length);
	quickSort(a, length);
	printarray(a, length);
	free(a);
}

bool less(int a1, int a2) {
	return a1 < a2;
}

void exchange(int* a, int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void printarray(int* array, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void copyarray(int* dest, int* src, int length) {
	for (int i = 0; i < length; i++) {
		dest[i] = src[i];
	}
}

void selectionSort(int* a, int length) {
	for (int i = 0; i < length; i++) {
		for (int j = i+1; j < length; j++) {
			if (less(a[j], a[i])) {
				exchange(a, i, j);
			}
		}
	}
}

void insertionSort(int* a, int low, int high) {
	for (int i = low+1; i <= high; i++) {
		for (int j = i ; j>=low; j--) {
			if (less(a[j], a[j-1])) {
				exchange(a, j, j-1);
			}
		}
	}
}

void shellSort(int* a, int length) {
	int h = 1;
	while (h < length/3) {
		h = 3 * h + 1;
	}
	while (h ) {
		for (int i = h; i < length; i++) {
			for (int j = i; j >=h; j-=h) {
				if (less(a[j], a[j - h])) {
					exchange(a, j, j - h);
				}
			}
		}
		h /= 3;
	}
}

void mergeSort(int* a, int length) {
	int* aux = (int*)malloc(length * sizeof(int));
	merge(a,0,length-1,aux, length);
	free(aux);
}

void merge(int* a, int low, int high, int* aux, int length) {
	if (low >= high) {
		return;
	}
	int mid = low + (high - low) / 2;

	merge(a, low, mid, aux, length);
	merge(a, mid + 1, high, aux, length);
	// after soft the two halves, if a[mid]<a[mid+1] two halves are sorted, otherwise:
	if (less(a[mid+1], a[mid])) {
		mergeTwo(a, low, mid, high, aux, length);
	}
}

void mergeTwo(int* a, int low, int mid, int high, int* aux, int length) {
	int i = low;
	int j = mid + 1;
	copyarray(aux, a, length);
	for (int k = low; k <= high;k++) {
		if (j > high) {
			a[k] = aux[i++];
		}
		else if (i > mid) {
			a[k] = aux[j++];
		}
		else if (less(aux[i], aux[j])) {
			a[k] = aux[i++];
		}
		else {
			a[k] = aux[j++];
		}
	}
}

void quickSort(int* a, int length){
	for (int i = 0; i < length; i++) {
		exchange(a,i, rand() % length);
	}
	quick(a, 0, length - 1);
}

void quick(int*a, int low, int high) {
	if (low >= high) {
		return;
	}
	int mid = partition(a,low,high);
	quick(a, low, mid-1);
	quick(a, mid + 1, high);
}

int partition(int* a, int low, int high) {
	int i = low;
	int j = high+1;
	bool flag = false;
	while (!flag) {
		while (less(a[++i], a[low]) && i < high);
		while (less(a[low], a[--j]) && j > low);
		flag = i >= j;
		if (!flag) {
			exchange(a, i, j);
		}
	}
	exchange(a, low, j);
	return j;

}
