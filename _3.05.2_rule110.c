#include <stdio.h>

#define LENGTH 34
#define LOOPS 30
/* coloured print https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix */
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

void nextarray(const int current[LENGTH], int target[LENGTH]);
void copyarray(const int current[LENGTH], int target[LENGTH]);
int rule110(const int a[3]);
int rule30(const int a[3]);
int rule90(const int a[3]);

int main()
{
    int a[LENGTH] = {0};
    a[LENGTH-4] = 1;
    //a[LENGTH / 2] = 1;
    int temp[LENGTH];

    for (int i = 0; i < LOOPS; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (a[j]==1) {
                printf("%s1 ",RED);
            }
            else {
                printf("%s0 ",NRM);
            }
        }
        printf("\n");
        nextarray(a, temp);
        copyarray(temp, a);
    }
    return 0;
}

void nextarray(const int current[LENGTH],int target[LENGTH]) {
    int i = 0;
    for (i = 0; i < LENGTH; i++) {
        target[i] = 0;
    }

    int temp[3] = { 0,0,0 };
    for (i = 0; i < LENGTH; i++) {
        if (i > 0 && i < LENGTH - 1) {
            temp[0] = current[i - 1];
            temp[1] = current[i];
            temp[2] = current[i + 1];
            target[i] = rule110(temp);
        }
    }
}

void copyarray(const int current[LENGTH], int target[LENGTH]) {
    for (int i = 0; i < LENGTH; i++) {
        target[i] = current[i];
    }
}

int rule110(const int a[3]) {
    if (a[0] == 1 && a[1] == 1 && a[2] == 1) {
        return 0;
    }else if (a[0] == 1 && a[1] == 0 && a[2] == 0) {
        return 0;
    }else if (a[0] == 0 && a[1] == 0 && a[2] == 0) {
        return 0;
    }
    return 1;
}

int rule30(const int a[3]) {
    if (a[0] == 1 && a[1] == 1 && a[2] == 1) {
        return 0;
    }
    else if (a[0] == 1 && a[1] == 1 && a[2] == 0) {
        return 0;
    }
    else if (a[0] == 1 && a[1] == 0 && a[2] == 1) {
        return 0;
    }
    else if (a[0] == 0 && a[1] == 0 && a[2] == 0) {
        return 0;
    }
    return 1;
}

int rule90(const int a[3]) {
    if (a[0] == 1 && a[1] == 1 && a[2] == 1) {
        return 0;
    }
    else if (a[0] == 0 && a[1] == 1 && a[2] == 0) {
        return 0;
    }
    else if (a[0] == 1 && a[1] == 0 && a[2] == 1) {
        return 0;
    }
    else if (a[0] == 0 && a[1] == 0 && a[2] == 0) {
        return 0;
    }
    return 1;
}

