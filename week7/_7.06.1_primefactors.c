#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

#define MAXSIZE 100

long long parsell(char* str);
int primefactors(long long n, int* buffer);
int primefactors2draw(int length, int* buffer);
void printfactors(int* a, int len);
bool isprime(int n);

int main(int argc, char** argv) {
    assert(argc == 2);
    long long n = parsell(argv[1]);
    printf("%lld\n", n);
    int buffer[MAXSIZE] = { 0 };
    int len;
    printf("length=%d\n", len = primefactors(n, buffer));
    
    for(int i=0;i<len;i++){
        printf("%d ",buffer[i]);
    }
    printf("\n");
    
    len=primefactors2draw(len,buffer);
    for(int i=0;i<len;i++){
        printf("%d ",buffer[i]);
    }
    printf("\n");
    //printfactors(buffer, len);
}

long long parsell(char* str) {
    long long n = 0L;
    int i = 0;
    bool minus = false;
    while (str[i]) {
        if (str[0] == '-') {
            minus = true;
        }
        if ('0' <= str[i] && str[i] <= '9') {
            n = n * 10L + (str[i] - '0');
        }
        i++;
    }
    return minus ? -n : n;
}

int primefactors(long long n, int* buffer) {
    int count = 0;
    while (n % 2 == 0) {
        buffer[count++] = 2;
        n /= 2;
    }
    while (n > 1) {
        bool flag = false;
        for (long long i = 3; !flag && i <= sqrt(n); i+=2) {
            if (isprime(i) && n % i == 0) {
                buffer[count++] = i;
                flag = true;
                n = n / i;
            }
        }
        if (!flag) {  // If no prime divisor is found, n is prime itself
            buffer[count++] = n;
            n = 1; // set n=1 to exit loop
        }
    }
    if (count > 1) {
        for (int i = 1; i < count; i++) {
            for (int j = i; j > 0; j--) {
                if (buffer[j] < buffer[j - 1]) {
                    int temp = buffer[j];
                    buffer[j] = buffer[j - 1];
                    buffer[j - 1] = temp;
                }
            }
        }
    }
    return count;
}

int primefactors2draw(int length, int* buffer){
    int out=0;
    int count2=0;
    for(int i=0;i<length;i++){
        if(buffer[i]==2){
            count2++;
        }
    }
    int count4=count2/2;
    count2=count2%2;
    int* temp=(int*)calloc(length,sizeof(int));
    assert(temp);
    int k = 0;
    for (int i = length - 1; i >= 0; i--) {
        if (buffer[i] != 2) {
            temp[k++] = buffer[i];
            out++;
        }
    }
    if (count2 > 0) {
        temp[k++] = 2;
        out++;
    }
    for (int i = 0; i < count4; i++) {
        temp[k++] = 4;
        out++;
    }
    for(int i=0;i<length;i++){
        if(i<out){
            buffer[i]=temp[i];
        }else{
            buffer[i]=0;
        }
    }
    free(temp);
    return out;
}

void printfactors(int* a, int len) {
    if (len <= 0) {
        return;
    }
   
    long long n = 1;
    for (int i = 0; i < len; i++) {
        n = n * a[i];
    }
    int count = 1;
    for (int i = 1; i < len; i++) {
        if (a[i - 1] != a[i]) {
            count++;
        }
    }

    // might use a hashMap to count.
    int* facs = (int*)calloc(count, sizeof(int));
    int* expos = (int*)calloc(count, sizeof(int));
    assert(facs && expos);
    int factor = a[0];
    int exponent = 1;
    int k = 0;
    for (int i = 1; i < len && k<count; i++) {
        if (a[i] == factor) {
            exponent++;
        }
        else {
            facs[k] = factor;
            expos[k] = exponent;
            k++;
            factor = a[i];
            exponent = 1;
        }
    }
    facs[k] = factor;
    expos[k] = exponent;
    k++;
    printf("%lld = 1 x ", n);
    for (int i = 0; i < k; i++) {
        if (expos[i] == 1) {
            printf("%d", facs[i]);
        }
        else {
            printf("%d^%d", facs[i], expos[i]);
        }
        if (i + 1 < k) {
            printf(" x ");
        }
    }
    printf("\n");
    free(facs);
    free(expos);
}

bool isprime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= floor(sqrt((double)n)); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
