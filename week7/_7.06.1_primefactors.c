#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

#define MAXSIZE 100
long long parseint(char* str);
int primefactors(long long n, int* buffer);
void printfactors(int* a, int len);
bool isprime(int n);
void test();

int main(int argc, char** argv) {
    assert(argc == 2);
    long long n = parseint(argv[1]);
    printf("%lld\n",n);
    int buffer[MAXSIZE] = { 0 };
    int len;
    printf(" length=%d\n",len=primefactors(n, buffer));
    printfactors(buffer,len);
    test();

}

long long parseint(char* str) {
    long long n = 0L;
    int i = 0;
    bool minus = false;
    while (str[i]) {
        if (i==0 && str[i] == '-') {
            minus = true;
        }
        if ('0' <= str[i] && str[i] <= '9') {
            n = n * 10L + (str[i] - '0');
        }
        i++;
    }
    return minus?-n:n;
}

int primefactors(long long n, int* buffer) {
    // instead of using a large enough buffer, might also use linked list.
    int count = 0;
    while (n > 1) {
        bool flag = true;
        for (long long i = 2; flag && i <= n; i++) {
            if (isprime(i) && n % i == 0) {
                buffer[count] = i;
                printf("%d ", i);
                count++;
                flag = false;
                n = n / i;
            }
        }
        if (flag) {  // If no prime divisor is found, n is prime
            buffer[count] = n;
            count++;
            n = 1;
        }
    }
    return count;
}

void printfactors(int* a, int len) {
    // might use a hashMap to count.
    if (len > 1) {
        for (int i = 1; i < len; i++) {
            for (int j = i; j > 0; j--) {
                if (a[j] < a[j - 1]) {
                    int temp = a[j];
                    a[j] = a[j - 1];
                    a[j - 1] = temp;
                }
            }
        }
    }
    int n = 1;
    for (int i = 0; i < len; i++) {
        n = n * a[i];
    }

    int* nums = (int*)calloc(len, sizeof(int));
    int* expos = (int*)calloc(len, sizeof(int));
    assert(nums && expos);
    int count = 0;
    for (int i = 0; i < len; i++) {

        int k = 0;
        bool flag = false;
        while (!flag) {
            if (!nums[k]) {
                nums[k] = a[i];
                expos[k] = 1;
                count++;
                flag = true;
            }else if(nums[k] == a[i]) {
                expos[k]++;
                flag = true;
            }
            k++;
        }
    }
    printf("%d = 1 x ",n);
    for (int i = 0; i < count;i++) {
        if (expos[i] == 1) {
            printf("%d", nums[i]);
        }
        else {
            printf("%d^%d", nums[i], expos[i]);
        }
        if (i + 1 < count && nums[i + 1]) {
            printf(" x ");
        }
    }
    free(nums);
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

void test() {
    assert(isprime(2));
    assert(isprime(3));
    assert(!isprime(4));
    assert(isprime(5));
    assert(!isprime(6));
    assert(isprime(7));
    assert(!isprime(8));
    assert(!isprime(9));

    //free(primefactors(117));

    //printf("%d\n", parseint("-123"));
}
